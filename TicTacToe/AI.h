#pragma once

#include "Board.h"

struct Move
{
		Move(int _score) : score(_score) { }
		Move() {}
		uint x; //column coordinate
		uint y; //row coordinate
		int score; //the score value of the move
};

class AI
{
public:
		AI(uint _aiIndex, uint _playerIndex);
		AI() {}
		~AI();

		void init(uint _aiIndex, uint _playerIndex);

		void performMove(Board& _board);

private:
		//recursive function which uses minimax algorithm
		Move getBestMove(Board& _board, uint _currentPlayer, uint _depth);

private:
		uint m_aiIndex{ 0 };
		uint m_playerIndex{ 0 };
};