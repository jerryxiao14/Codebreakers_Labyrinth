#include "HillCipher.h"

static const int32 MOD = 37;

// ----------------------
// Character  number 0–36
// ----------------------
int32 UHillCipher::Convert(TCHAR C)
{
    if (C >= 'A' && C <= 'Z')
        return C - 'A';

    if (C >= '0' && C <= '9')
        return 26 + (C - '0');

    if (C == ' ')
        return 36;

    return 36; // treat unexpected characters as space
}

// ----------------------
// Number 0–36 character
// ----------------------
TCHAR UHillCipher::ConvertBack(int32 V)
{
    if (V < 26)
        return 'A' + V;

    if (V < 36)
        return '0' + (V - 26);

    return ' ';
}

// ----------------------
// TRUE 2D Matrix x Vector (mod 37)
// ----------------------
TArray<int32> UHillCipher::MultiplyVector(
    const TArray<TArray<int32>>& M,
    const TArray<int32>& V,
    int32 N)
{
    TArray<int32> Result;
    Result.Init(0, N);

    for (int32 i = 0; i < N; ++i)
    {
        for (int32 j = 0; j < N; ++j)
        {
            Result[i] = (Result[i] + M[i][j] * V[j]) % MOD;
        }
    }

    return Result;
}

// ----------------------
// MAIN ENCRYPT FUNCTION (Blueprint calls this)
// ----------------------
FString UHillCipher::EncryptHillCipher(
    const TArray<int32>& FlatMatrix,
    int32 N,
    const FString& Plaintext)
{
    if (FlatMatrix.Num() != N * N)
    {
        UE_LOG(LogTemp, Error, TEXT("EncryptHillCipher: Matrix dimension mismatch!"));
        return "";
    }

    // ------------------------------------
    // Convert 1D to TRUE 2D matrix
    // ------------------------------------
    TArray<TArray<int32>> Matrix;
    Matrix.SetNum(N);

    for (int32 r = 0; r < N; r++)
    {
        Matrix[r].SetNum(N);
        for (int32 c = 0; c < N; c++)
        {
            Matrix[r][c] = FlatMatrix[r * N + c];
        }
    }
    TArray<int32> Arr;
    Arr.Reserve(Plaintext.Len());

    for (TCHAR C : Plaintext)
        Arr.Add(Convert(C));

    // ------------------------------------
    // Pad with 36 (" ")
    // ------------------------------------
    int32 Padding = (N - (Arr.Num() % N)) % N;
    for (int i = 0; i < Padding; i++)
        Arr.Add(36);

    // ------------------------------------
    // Encrypt in blocks of size N
    // ------------------------------------
    TArray<int32> Encrypted;
    Encrypted.Reserve(Arr.Num());

    for (int32 i = 0; i < Arr.Num(); i += N)
    {
        // Extract vector
        TArray<int32> Block;
        Block.SetNum(N);
        for (int32 j = 0; j < N; j++)
            Block[j] = Arr[i + j];

        // Multiply
        TArray<int32> Out = MultiplyVector(Matrix, Block, N);
        Encrypted.Append(Out);
    }

   
    FString Result;
    Result.Reserve(Encrypted.Num());

    for (int32 Val : Encrypted)
        Result.AppendChar(ConvertBack(Val));
    //UE_LOG(LogTemp, Warning, TEXT("EncryptHillCipher Result: %s"), *Result);
    /*
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Green, Result);

        FString LengthString = FString::Printf(TEXT("Result length: %d"), Result.Len());
        GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Yellow, LengthString);
    }
    */
    return Result;
}

FString UHillCipher::MatrixToMultilineString(const TArray<int32>& FlatMatrix, int32 N)
{
    FString Output;
    if (FlatMatrix.Num() != N * N) {
        UE_LOG(LogTemp, Error, TEXT("MatrixToMultilineString: Matrix dimension mismatch!"));
		return "";
    }

    for (int32 Row = 0; Row < N; Row++) {
        for (int32 Col = 0; Col < N; Col++) {
            int32 Index = Row * N + Col;
            Output += FString::FromInt(FlatMatrix[Index]);
            if (Col < N - 1) {
                Output += TEXT(" ");
            }
        }


        if (Row < N - 1) {
            Output += TEXT("\n");
        }
    }
    
    return Output;
}
