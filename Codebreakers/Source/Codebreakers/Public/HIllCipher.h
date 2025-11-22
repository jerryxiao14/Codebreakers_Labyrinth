#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HillCipher.generated.h"

UCLASS()
class CODEBREAKERS_API UHillCipher : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category = "HillCipher")
    static FString EncryptHillCipher(const TArray<int32>& FlatMatrix, int32 N, const FString& Plaintext);

private:

    static int32 Convert(TCHAR C);
    static TCHAR ConvertBack(int32 Value);

    static TArray<int32> MultiplyVector(
        const TArray<TArray<int32>>& M,
        const TArray<int32>& V,
        int32 N
    );
};
