#pragma once

#include "Board.h"

#include <random>

/**
* Structure to represent a game move
*/
struct Move
{
		Move(int _score) : score(_score) { }
		Move() {}
		uint x; //column coordinate
		uint y; //row coordinate
		int score; //the score value of the move
};

/**
* The difficulty settings of the AI
*/
enum class Difficulty : unsigned int
{
		EASY						= 1, // High chance for the player to win
		HARD						= 2, // Medium chance for the player to win
		VERY_HARD = 3  // Winning is impossible, tie at best
};

/**
* The AI player logic
*/
class AI
{
public:
		/**
		* Constructor for the AI, which sets the index of the AI player and the human player in the game
		* and it also sets the difficulty of the AI
		*/
		AI(uint _aiIndex, uint _playerIndex, const Difficulty& _difficulty = Difficulty::VERY_HARD);

		// Empty contructor if initialization needs to be done manually with init()
		AI() {}
		~AI();

		/**
		* Initializes the AI which sets it in a use-able state
		*/
		void init(uint _aiIndex, uint _playerIndex, const Difficulty& _difficulty = Difficulty::VERY_HARD);

		/**
		* Performs a single legal move on the board, the skill-level of the move depends on the difficulty setting
		*/
		void performMove(Board& _board);

private:
		/**
		* recursive function which uses minimax algorithm
		*/
		Move getBestMove(const Board& _board, uint _currentPlayer, uint _depth);

		/**
		* first checks if there is a winning move for the ai, and places it if there is
		* If not, then it chekcs if there is a winning move for the player, and blocks it if there is
		* and if that is also not the case, it places the move randomly
		*/
		Move getHardMove(const Board& _board);

		/**
		* Randomly chooses a move
		*/
		Move getEasyMove(const Board& _board);

private:
		uint m_aiIndex{ 0 };						///<index of the ai player (usually player2 = 2)
		uint m_playerIndex{ 0 };  ///<index of the human player (usually 1)
		Difficulty m_difficulty;  ///<difficulty setting of the AI
		std::mt19937 m_generator; ///<the engine used for random number generation
};