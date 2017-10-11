/* This is the console executable that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/


#include <iostream>
#include <string>
#include "FBullCowGame.h"


using FText = std::string;
using int32 = int;


void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; //instantiate a new game


//this is the entry point of the application
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain == 1);
	return 0;//exit the application
}



//introduce the game
void PrintIntro() 
{
	std::cout << "Welcome to Bulls and Cows, a fun word game" << std::endl;
	std::cout << " Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	

	// loop asking for guesses while the game
	// is not won and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); 
		// submit valid guess to the game, and receives counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << " Bulls " << BullCowCount.Bulls ;
		std::cout << ". Cows " << BullCowCount.Cows << std::endl;

		std::cout << std::endl;
	}
	// TODO summarise game
}
//loop continually untill the user gives a valid guess
FText GetValidGuess() 
{ 
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do 
	{
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Try " << CurrentTry << " ";
		std::cout << "Enter your guess:" << std::endl;
		
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " length isogram\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word isogram in Lower Case\n";
			break;
		default:
			// assuming the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping unitl we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)?" << std::endl;
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
	
}

