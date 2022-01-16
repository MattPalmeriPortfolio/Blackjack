# Blackjack

Contents
---------------------
* File Contents
* Introduction
* Algorithm
* Requirements

## File Contents
	
	Bottom_Up_BlackJack.cpp  (program file containing code)

## Introduction
Book practice project from Problem Solving With C++ Chapter 5. Project 9.
A dice blackjack program, using bottom-up design. Demonstrates ability to use multiple functions and create a program using a bottom-up design in c++.
Written using Microsoft Visual Studio. 

## Algorithm

	1. start player with $100, and get wager
		1a. wager must be a positive amount less than the player's cash
	2. begin player turn
		2a. rolls twice for player, rolls once for house; displays all results to player
			2aa. if player rolls > 21, player immediately loses and the round is over
			2ab. else, ask player to hit or stand; if hit, roll again and re-prompt; if stand, end round
	3. begin house turn
		3a. rolls once more for house, combines first and second rolls
			3aa. if score less than 17, house must hit again until their score is over 17
			3ab. if house busts, player wins
	4. assuming no busts, check for winner
		4a. if house rolls > player rolls, house wins; vice versa, player wins
		4b. if both have same score, house "pushes" and no money is gained or lost
	5. if player's cash > 0, prompt whether to continue playing

## Requirements
No requirements or modules needed for running this program.
