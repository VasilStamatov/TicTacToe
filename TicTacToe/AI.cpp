#include "AI.h"

#include <chrono>

using HighResClock = std::chrono::high_resolution_clock;

AI::AI(uint _aiIndex, uint _playerIndex, const Difficulty& _difficulty)
{
		init(_aiIndex, _playerIndex, _difficulty);
}

AI::~AI()
{
}

void AI::init(uint _aiIndex, uint _playerIndex, const Difficulty& _difficulty)
{
		m_aiIndex = _aiIndex;
		m_playerIndex = _playerIndex;
		m_difficulty = _difficulty;
		m_generator.seed(static_cast<unsigned int>(HighResClock::now().time_since_epoch().count()));
}

void AI::performMove(Board & _board)
{
		Move move;
		switch (m_difficulty)
		{
		case Difficulty::EASY:
				move = getRandomMove(_board);
				break;
		case Difficulty::HARD:
				move = getFatalisticMove(_board, m_aiIndex);
				break;
		case Difficulty::VERY_HARD:
				move = getBestMove(_board, m_aiIndex, 0);
				break;
		default:
				break;
		}
		_board.setValueAt(move.x, move.y, 'o');
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
		else if (victory == 0)
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

Move AI::getFatalisticMove(Board & _board, uint _currentPlayer)
{
		//check for the end state to avoid infinite recursion
		uint victory = _board.checkForVictory();
		if (victory == 2)
		{
				//ai won
				return Move(10);
		}
		else if (victory == 1)
		{
				//player won
				return Move(-10);
		}
		else if (victory == 0)
		{
				return Move(0);
		}
		//surviving through the if checks means the game isn't over so continue recursing

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
										move.score = getFatalisticMove(_board, m_playerIndex).score;
								}
								else
								{
										_board.setValueAt(x, y, 'x');
										//set the score for the player
										move.score = getFatalisticMove(_board, m_aiIndex).score;
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

Move AI::getRandomMove(Board & _board)
{
		std::uniform_int_distribution<int> realDis(0, _board.getSize() - 1);

		int x = realDis(m_generator);
		int y = realDis(m_generator);

		while (_board.getValueAt(x, y) != ' ')
		{
				x = realDis(m_generator);
				y = realDis(m_generator);
		}

		Move move;
		move.x = x;
		move.y = y;

		return move;
}