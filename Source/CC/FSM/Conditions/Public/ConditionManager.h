#pragma once

#include "CoreMinimal.h"

class FConditionManager
{
public:
	// Singleton Instance Getter
	static FConditionManager& Get();

	// Execute condition check for a specific ConditionID
	bool CheckCondition(int32 ConditionID, const FString& ComparisonJSON);

private:
	// Private constructor (Singleton pattern applied)
	bool ValidationCondition(const FString& ReferenceJSON, const FString& ComparisonJSON);
	bool CompareValue(TSharedPtr<FJsonValue> A, TSharedPtr<FJsonValue> B);
};
