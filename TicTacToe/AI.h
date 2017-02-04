#pragma once

#include "Board.h"

#include <random>

struct Move
{
		Move(int _score) : score(_score) { }
		Move() {}
		uint x; //column coordinate
		uint y; //row coordinate
		int score; //the score value of the move
};

enum class Difficulty : unsigned int
{
		EASY = 1,
		HARD = 2,
		VERY_HARD = 3
};

class AI
{
public:
		AI(uint _aiIndex, uint _playerIndex, const Difficulty& _difficulty = Difficulty::VERY_HARD);
		AI() {}
		~AI();

		void init(uint _aiIndex, uint _playerIndex, const Difficulty& _difficulty = Difficulty::VERY_HARD);

		void performMove(Board& _board);

private:
		//recursive function which uses minimax algorithm
		Move getBestMove(Board& _board, uint _currentPlayer, uint _depth);
		Move getFatalisticMove(Board& _board, uint _currentPlayer);
		Move getRandomMove(Board& _board);

private:
		uint m_aiIndex{ 0 };
		uint m_playerIndex{ 0 };
		Difficulty m_difficulty;
		std::mt19937 m_generator;
};