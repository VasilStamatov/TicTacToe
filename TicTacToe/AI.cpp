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
		// initialize all the member variables
		m_aiIndex = _aiIndex;
		m_playerIndex = _playerIndex;
		m_difficulty = _difficulty;
		m_generator.seed(static_cast<unsigned int>(HighResClock::now().time_since_epoch().count()));
}

void AI::performMove(Board & _board)
{
		Move move;

		//perform move according to difficulty
		switch (m_difficulty)
		{
		case Difficulty::EASY:
				move = getEasyMove(_board);
				break;
		case Difficulty::HARD:
				move = getHardMove(_board);
				break;
		case Difficulty::VERY_HARD:
				move = getBestMove(_board, m_aiIndex, 0);
				break;
		default:
				break;
		}

		//set the AI's move
		_board.setValueAt(move.x, move.y, 'o');
}

Move AI::getBestMove(const Board & _board, uint _currentPlayer, uint _depth)
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
				//tie
				return Move(0);
		}
		//surviving through the if checks means the game isn't over so continue recursing
		//increment the depth as it's going deeper in the tree
		_depth++;

		//all of the possible moves
		std::vector<Move> moves;

		//check all possible moves in the current board
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

								//use the move to make a new possible game state
								if (_currentPlayer == m_aiIndex)
								{
										//get the new possible game state
										Board possibleGameState = _board.getNewState(x, y, 'o');

										//set the score for the ai by checking what the player's best move would be
										move.score = getBestMove(possibleGameState, m_playerIndex, _depth).score;
								}
								else
								{
										//get the new possible game state
										Board possibleGameState = _board.getNewState(x, y, 'x');

										//set the score for the player by checking the ai's best move
										move.score = getBestMove(possibleGameState, m_aiIndex, _depth).score;
								}
								// push back all moves with their set coordinates and score
								moves.push_back(move);
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

				//go over all possible moves
				for (uint i = 0; i < moves.size(); i++)
				{
						//check if the score of the current move is better than the current best score
						if (moves.at(i).score > bestScore)
						{
								//if the score is higher, then the current move is better
								bestMove = i; //best move index set to this i index
								bestScore = moves.at(i).score; // best current possible score set to the move's score
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
						// check if the current move's score is less than the best
						if (moves.at(i).score < bestScore)
						{
								//if it is, then this move is better for the human player
								bestMove = i; //so set the index of the best move to this i index
								bestScore = moves.at(i).score; //and set the current best score to the score of the move
						}
				}
		}

		//finally return the very best move for the current player
		return moves.at(bestMove);
}

Move AI::getHardMove(const Board & _board)
{
		//check if there is a winning slot for the ai
		for (uint y = 0; y < _board.getSize(); y++)
		{
				for (uint x = 0; x < _board.getSize(); x++)
				{
						if (_board.getValueAt(x, y) == ' ')
						{
								//place the possible move
								Board possibleGameState = _board.getNewState(x, y, 'o');

								//check for victory
								uint victory = possibleGameState.checkForVictory();

								if (victory == 2)
								{
										//ai won, so choose this move
										Move move;
										move.x = x;
										move.y = y;
										return move;
								}
						}
				}
		}

		//check if there is a winning slot for the player
		for (uint y = 0; y < _board.getSize(); y++)
		{
				for (uint x = 0; x < _board.getSize(); x++)
				{
						if (_board.getValueAt(x, y) == ' ')
						{
								//place the possible move
								Board possibleGameState = _board.getNewState(x, y, 'x');

								//check for victory
								uint victory = possibleGameState.checkForVictory();

								if (victory == 1)
								{
										//player won, therefore BLOCK HIM!
										Move move;
										move.x = x;
										move.y = y;
										return move;
								}
						}
				}
		}

		//if nobody can win in the next slot, place it randomly
		return getEasyMove(_board);
}

Move AI::getEasyMove(const Board & _board)
{
		//randomly generate a possible move
		std::uniform_int_distribution<int> realDis(0, _board.getSize() - 1);

		int x = realDis(m_generator);
		int y = realDis(m_generator);

		//make sure the move is legal by checking the current value at the board coordinates
		while (_board.getValueAt(x, y) != ' ')
		{
				x = realDis(m_generator);
				y = realDis(m_generator);
		}

		//by this move the move coordinates should be okay, so create the new move
		Move move;
		move.x = x;
		move.y = y;

		//return the randomly generated move
		return move;
}