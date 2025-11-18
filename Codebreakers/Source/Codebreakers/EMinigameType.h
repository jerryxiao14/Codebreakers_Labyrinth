// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EMinigameType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)

enum class EminigameType : uint8 {
	EMT_None 		UMETA(DisplayName = "None"),
	EMT_Encryption  UMETA(DisplayName = "Encrpytion"),
	EMT_Decryption	UMETA(DisplayName = "Decryption"),
	EMT_Quiz		UMETA(DisplayName = "Quiz")
};
