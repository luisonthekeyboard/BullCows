// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount
{
	int32 Bulls;
	int32 Cows;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	void SetupGame();
	virtual void OnInput(const FString& Input) override;
	void EndGame();
	bool IsIsogram(const FString& Word) const;
	void ProcessGuess(const FString& Guess);
	void GetBullCows(const FString& Guess, int32& Bulls, int32& Cows) const;
	void GetBullCowCount(const FString& Guess, FBullCowCount& BullCowCount) const;

	// Your declarations go below!
	private:
	FString HiddenWord;
	int32 Lives;
	bool bGameOver;
	
};
