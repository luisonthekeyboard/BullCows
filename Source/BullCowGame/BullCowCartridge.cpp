// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"
#include "Math/UnrealMathUtility.h"

void UBullCowCartridge::BeginPlay()
{
	Super::BeginPlay();

	SetupGame();

	// debug stuff
	PrintLine(TEXT("You currently have %i lives."), Lives);
	PrintLine(TEXT("The secret word is %s."), *HiddenWord);
}

void UBullCowCartridge::OnInput(const FString& Input)
{
	if (bGameOver)
	{
		ClearScreen();
		SetupGame();
		return;
	}

	ProcessGuess(Input);
}

void UBullCowCartridge::EndGame()
{
	bGameOver = true;
	PrintLine(TEXT("Press enter to play again."));
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
	const FString LoweredWord = Word.ToLower();

	if (LoweredWord.IsEmpty())
	{
		return false;
	}

	bool Seen[26] = {};

	for (int32 i = 0; i < LoweredWord.Len(); i++)
	{
		if (Seen[LoweredWord[i] - 'a'])
		{
			return false;
		}

		Seen[LoweredWord[i] - 'a'] = true;
	}

	return true;
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
	if (HiddenWord == Guess)
	{
		ClearScreen();
		PrintLine(TEXT("You win chickens and banjos. It's gonna be sunny forever!"));

		EndGame();
		++Lives;
		return;
	}

	if (HiddenWord.Len() != Guess.Len())
	{
		PrintLine(TEXT("The hidden word is %i characters long, try again."), HiddenWord.Len());
		return;
	}

	if (!IsIsogram(Guess))
	{
		PrintLine(TEXT("Your guess is not an isogram, try again."));
		return;
	}

	// Losing lives scenario
	--Lives;
	int32 Bulls, Cows;
	FBullCowCount Count;
	GetBullCows(Guess, Bulls, Cows);
	GetBullCowCount(Guess, Count);

	PrintLine(TEXT("Your kneecaps have exploded a bit."));
	PrintLine(TEXT("You still have %i lives left."), Lives);
	PrintLine(TEXT("There's %i Bulls and %i Cows. Try again"), Count.Bulls, Count.Cows);


	if (Lives == 0)
	{
		ClearScreen();
		PrintLine(TEXT("Game over."));
		PrintLine(TEXT("The hidden word was %s."), *HiddenWord);

		EndGame();
	}
}

void UBullCowCartridge::GetBullCows(const FString& Guess, int32& Bulls, int32& Cows) const
{
	Bulls = 0;
	Cows = 0;

	for (int32 i = 0; i < Guess.Len(); ++i)
	{
		if (Guess[i] == HiddenWord[i])
		{
			++Bulls;
			continue;
		}

		for (int32 j = 0; j < Guess.Len(); ++j)
		{
			if (Guess[i] == HiddenWord[j])
			{
				++Cows;
				break;
			}
		}
	}
}

void UBullCowCartridge::GetBullCowCount(const FString& Guess, FBullCowCount& BullCowCount) const
{
	BullCowCount.Bulls = 0;
	BullCowCount.Cows = 0;

	for (int32 i = 0; i < Guess.Len(); ++i)
	{
		if (Guess[i] == HiddenWord[i])
		{
			++BullCowCount.Bulls;
			continue;
		}

		for (int32 j = 0; j < Guess.Len(); ++j)
		{
			if (Guess[i] == HiddenWord[j])
			{
				++BullCowCount.Cows;
				break;
			}
		}
	}

}

void UBullCowCartridge::SetupGame()
{
	HiddenWord = HiddenWords[FMath::RandRange(0, HiddenWords.Num() - 1)];
	Lives = HiddenWord.Len() * 2;
	bGameOver = false;

	PrintLine(TEXT("Welcome to the BullCow game, a really odd and difficult game."));
	PrintLine(TEXT("You have %i lives."), Lives);
	PrintLine(TEXT("Go on, type something down"));
	PrintLine(TEXT("and try to guess the %i word."), HiddenWord.Len());
}
