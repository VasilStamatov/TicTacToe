#include "AI.h"



AI::AI(uint _aiIndex, uint _playerIndex)
{
		init(_aiIndex, _playerIndex);
}


AI::~AI()
{
}

void AI::init(uint _aiIndex, uint _playerIndex)
{
		m_aiIndex = _aiIndex;
		m_playerIndex = _playerIndex;
}

void AI::performMove(Board & _board)
{
		Move bestMove = getBestMove(_board, m_aiIndex, 0);
		_board.setValueAt(bestMove.x, bestMove.y, 'o');
}

Move AI::getBestMove(Board & _board, uint _currentPlayer, uint _depth)
{
		//check for the end state to avoid infinite recursion
		uint victory = _board.checkForVictory();
		if (victory == 2)
		{
				//ai won
				return Move(10 - _depth);
		}
		else if (victory == 1)
		{
				//player won
				return Move(_depth - 10);
		}
		else if(victory == 0)
		{
				return Move(0);
		}
		//surviving through the if checks means the game isn't over so continue recursing
		_depth++;

		//all of the children moves
		std::vector<Move> moves;

		for (uint y = 0; y < _board.getSize(); y++)
		{
				for (uint x = 0; x < _board.getSize(); x++)
				{
						//check if the board has this slot free for moving
						if (_board.getValueAt(x, y) == ' ')
						{
								Move move;
								move.x = x;
								move.y = y;
								//temporality set the board's value at this position
								if (_currentPlayer == m_aiIndex)
								{
										_board.setValueAt(x, y, 'o');
										//set the score for the ai
										move.score = getBestMove(_board, m_playerIndex, _depth).score;
								}
								else
								{
										_board.setValueAt(x, y, 'x');
										//set the score for the player
										move.score = getBestMove(_board, m_aiIndex, _depth).score;
								}
								moves.push_back(move);
								//set the value back to empty so the board isn't actually changing
								_board.setValueAt(x, y, ' ');
						}
				}
		}

		// Pick the best move for the current player
		int bestMove{ 0 };

		// Check if it's the ai player or the human player
		if (_currentPlayer == m_aiIndex)
		{
				// The ai player will try to get the highest numbered score
				// so set the initial best score very low
				int bestScore{ -1000000 };
				for (uint i = 0; i < moves.size(); i++)
				{
						if (moves.at(i).score > bestScore)
						{
								bestMove = i;
								bestScore = moves.at(i).score;
						}
				}
		}
		else
		{
				// The human player will try to get the lowest numbered score (to hinder the ai)
				// so set the initial score to very high
				int bestScore{ 1000000 };
				for (uint i = 0; i < moves.size(); i++)
				{
						if (moves.at(i).score < bestScore)
						{
								bestMove = i;
								bestScore = moves.at(i).score;
						}
				}
		}

		//finally return the very best move
		return moves.at(bestMove);
}
