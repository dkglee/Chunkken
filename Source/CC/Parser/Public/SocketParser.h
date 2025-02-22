#pragma once

#include <map>

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SocketParser.generated.h"

UCLASS()
class USocketParser : public UObject
{
	GENERATED_BODY()
public:
	USocketParser();

	UFUNCTION()
	void ParseData();

	UFUNCTION()
	static FString GetSocketName(int32 SocketID);
	
protected:
	static std::map<int32, FString> SocketMap;
};
