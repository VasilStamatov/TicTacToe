#pragma once

#include "AI.h"

enum class GameState
{
		PLAYING,
		EXIT
};

class TTTApp
{
public:
		TTTApp();
		~TTTApp();

		void run();

private:
		// starts the game
		void start();
		// Performs a human controlled move
		void playerMove();
		// Performs an AI move
		void aiMove();
		// Changes players
		void changePlayer();
		// Ends a game and prompts for quit or re-try
		void endGame(uint result);
		// print a bunch of new space to "clear" the command prompt
		void clearScreen();

private:
		Board m_board;
		AI m_ai;
		GameState m_gameState{ GameState::PLAYING };
		uint m_currentPlayer{ 0 };
		uint m_player1{ 1 };
		uint m_player2{ 2 };
		bool m_isMupltiplayer{ false };
};

