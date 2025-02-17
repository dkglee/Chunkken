#include "ConditionManager.h"
#include "ConditionListParser.h"
#include "JsonUtilities.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

// Singleton Instance Getter
FConditionManager& FConditionManager::Get()
{
    static FConditionManager Instance;
    return Instance;
}

// Function to execute condition check
bool FConditionManager::CheckCondition(int32 ConditionID, const FString& ComparisonJSON)
{
    const FConditionStruct* Condition = UConditionListParser::GetConditionData(ConditionID);
    if (!Condition)
    {
        return false;
    }

    return ValidationCondition(Condition->ConditionData, ComparisonJSON);
}

// Sample static condition functions
bool FConditionManager::ValidationCondition(const FString& ReferenceJSON, const FString& ComparisonJSON)
{
    TSharedPtr<FJsonObject> ReferenceJsonObject;
    TSharedRef<TJsonReader<>> ReferenceReader = TJsonReaderFactory<>::Create(ReferenceJSON);
    FJsonSerializer::Deserialize(ReferenceReader, ReferenceJsonObject);

    TSharedPtr<FJsonObject> ComparisonJsonObject;
    TSharedRef<TJsonReader<>> ComparisonReader = TJsonReaderFactory<>::Create(ComparisonJSON);
    FJsonSerializer::Deserialize(ComparisonReader, ComparisonJsonObject);

    if (!ReferenceJsonObject.IsValid() || !ComparisonJsonObject.IsValid())
    {
        return false;
    }

    for (const auto& Pair : ReferenceJsonObject->Values)
    {
        const FString& Key = Pair.Key;
        const TSharedPtr<FJsonValue>& ReferenceValue = Pair.Value;

        if (!ComparisonJsonObject->HasField(Key))
        {
            return false;
        }

        const TSharedPtr<FJsonValue> ComparisonValue = ComparisonJsonObject->TryGetField(Key);
        if (!ComparisonValue.IsValid() || !CompareValue(ReferenceValue, ComparisonValue))
        {
            return false;
        }
    }

    return true;
}

// JSON 값 비교 함수
bool FConditionManager::CompareValue(TSharedPtr<FJsonValue> A, TSharedPtr<FJsonValue> B)
{
    if (!A.IsValid() || !B.IsValid() || A->Type != B->Type)
    {
        return false;
    }

    switch (A->Type)
    {
        case EJson::String: return A->AsString() == B->AsString();
        case EJson::Number: return FMath::IsNearlyEqual(A->AsNumber(), B->AsNumber());
        case EJson::Boolean: return A->AsBool() == B->AsBool();
        default: return false;
    }
}
