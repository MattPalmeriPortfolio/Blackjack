#include <iostream>
#include <ctime>
#include <string>
//declare functions
int rollDice();
//"rolls dice" for blackjack, returning a value between 1 and 11, with 10 weighted highest
int getWager(int money);
//precondition: money > 0
//postcondition: prompts player to wager money; continues until player enters wager between 0 and money
void playerTurn(int money, int& wager, bool& bust, int& total, int& houseRoll);
//precondition: player still has money
//postcondition: runs the player's turn of a round of blackjack; determines if they bust or not, stored in param bust,
//and stores the player's total and the house's first roll in parameters total and houseRoll respectively
void houseTurn(int& total, bool& bust);
//precondition: total provided includes the value of param houseRoll in function playerTurn;
//postcondition: runs the house's turn in a round of blackjack; determines their roll totals in param total
//and whether or not they went bust (true if bust) in param bust;
void determineResults(int& money, int wager, int playerTotal, int houseTotal, bool playerBust, bool houseBust);
//precondition: both a player turn and house turn have been run
//postcondition: determines the winner of a round of dice blackjack, and adjusts the players cash accordingly
bool promptContinue();
//precondition: program is intended to end or continue based on user decision
//postcondition: prompts user whether to continue the program; returns true if they do, false if they don't
//main
int main()
{
	using namespace std;
	//seed random
	srand(time(0));
	//initialize variables
	int cash(100), wager;
	//greet user
	cout << "Welcome to Bob Slover's House of Dice! We run the finest dice blackjack games this side of the Mississippi.\n"
		<< "I see you came in with a pretty hundred dollar bill in your hands. Let's get started!\n\n";
	//run game round
	do
	{
		//reset game variables
		bool playerBust = false, houseBust = false;
		int playerTotal = 0, houseTotal = 0;
		//begin round
		cout << "Round start!\n";
		playerTurn(cash, wager, playerBust, playerTotal, houseTotal);
		if (playerBust) //if player busts
			determineResults(cash, wager, playerTotal, houseTotal, playerBust, houseBust);
		else //if player does not bust
		{
			houseTurn(houseTotal, houseBust);
			determineResults(cash, wager, playerTotal, houseTotal, playerBust, houseBust);
		}
		cout << "Your current cash is: $" << cash << endl;
	} while (cash > 0 && promptContinue());
	cout << "See you next time, partner!\n";
	return 0;
}

//define functions
int rollDice()
{
	int result = (rand() % 13) + 2;
	if (result < 11)
		return result;
	else
	{
		switch (result)
		{
		case 11:
		case 12:
		case 13:
			result = 10;
			break;
		case 14:
			result = 11;
			break;
		}
		return result;
	}
}
//uses iostream
int getWager(int money)
{
	int wager;
	bool postcondition = false;
	do
	{
		std::cout << "Place your bet, partner, and make sure its all dollars. Bob doesn't take any pocket change.\n" << "$";
		std::cin >> wager;
		if (wager < 1)
			std::cout << "Ha! That's a good one, partner. now, what's your real bet?\n";
		else if (wager > money)
			std::cout << "Woah there! Don't get ahead of yourself. Bet what you got,\n unless you want Bob feeding you to the sharks.\n";
		else
		{
			postcondition = true;
			return wager;
		}
	} while (postcondition == false);
	return wager;
}
//uses iostream
void playerTurn(int money, int& wager, bool& bust, int& total, int& houseRoll)
{
	using namespace std;
	char hitOrStand;
	//get user's wager
	wager = getWager(money);
	//get user's first two rolls and house's first roll
	total = rollDice() + rollDice();
	houseRoll = rollDice();
	cout << "Your first two rolls add up to: " << total << endl
		<< "House's first roll: " << houseRoll << endl;
	//prompt user to hit or stand
	while (total <= 21)
	{
		cout << "Hit or stand? H to hit, S to stand\n";
		cin >> hitOrStand;
		if (hitOrStand == 'H' || hitOrStand == 'h')
			total += rollDice();
		else //if player stands
			break;
		cout << "New total: " << total << endl;
	}
	//check whether player is bust
	if (total > 21)
		bust = true;
	return;
}
void houseTurn(int& total, bool& bust)
{
	//do rolls for house
	do
	{
		total += rollDice();
	} while (total < 17);
	//check whether house is bust
	if (total > 21)
		bust = true;
	return;
}
//uses iostream
void determineResults(int& money, int wager, int playerTotal, int houseTotal, bool playerBust, bool houseBust)
{
	std::cout << "Player's total: " << playerTotal << std::endl << "House's total: " << houseTotal << std::endl;
	if (playerBust)
	{
		std::cout << "Sorry, you went bust! Better luck next time, partner!\n";
		money -= wager;
	}
	else if (houseBust)
	{
		std::cout << "The house went bust. It's your win!\n";
		money += wager;
	}
	else //if nobody went bust
	{
		if (playerTotal > houseTotal)
		{
			std::cout << "Fortune favors you today, partner! Your win!\n";
			money += wager;
		}
		else if (playerTotal < houseTotal)
		{
			std::cout << "Looks like we got the win this time, partner. Maybe you'll win next round?\n";
			money -= wager;
		}
		else //if both totals are equal
			std::cout << "Well i'll be darned, it's a push!\n";
	}
	return;
}
//uses iostream
bool promptContinue()
{
	using namespace std;
	char prompt;
	cout << "Would you like to continue? Y to continue, N to end\n";
	cin >> prompt;
	if (prompt == 'Y' || prompt == 'y')
		return true;
	else
		return false;
}