#pragma once

#include "AI.h"

/**
* The state of the game
*/
enum class GameState
{
		PLAYING, //Currently playing
		EXIT					//Exiting
};

/**
* The class encapsulationg the whole tic tac toe application
*/
class TTTApp
{
public:
		TTTApp();
		~TTTApp();

		/**
		* Runs the tic tac toe application
		*/
		void run();

private:
		/**
		* starts the game
		*/
		void start();

		/**
		* performs a human controlled move
		*/
		void playerMove();

		/**
		* performs an AI move
		*/
		void aiMove();

		/**
		* changes players
		*/
		void changePlayer();

		/**
		* ends a game and prompts for quit or re-try
		*/
		void endGame(uint result);

		/**
		* print a bunch of new space to "clear" the command prompt
		*/
		void clearScreen() const;

private:
		Board m_board;																															///< the game board
		AI m_ai;																																					///< the AI player
		GameState m_gameState{ GameState::PLAYING }; ///< current state of the game
		uint m_currentPlayer{ 0 };																		 ///< the index of the player whose turn it currently is
		uint m_player1{ 1 };																								 ///< index of player 1
		uint m_player2{ 2 };																								 ///< index of player 2
		bool m_isMupltiplayer{ false };													 ///< flag whether the game is played by 2 human players or just 1
};

