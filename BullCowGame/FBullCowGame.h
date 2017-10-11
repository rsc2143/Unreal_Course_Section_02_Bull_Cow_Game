#pragma once
#include <string>

using FString = std::string;
using int32 = int;


// all values initialized to zero
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public :
	FBullCowGame(); //Constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; // TODO make a more rich return value.
	
	void Reset(); // TODO a more rich return value.
	FBullCowCount SubmitValidGuess(FString);


// ^^ Please try and ignore this on focus on the interface above ^^
private:
	// See constructor for values
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;
};
