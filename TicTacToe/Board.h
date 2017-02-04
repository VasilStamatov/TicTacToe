#pragma once

#include <vector>

// new generation typedef
using uint = unsigned int;

/**
* The Board representation
*/
class Board
{
public:
		/**
		* This constructor creates the board of dimensions size x size
		*/
		Board(uint _size);

		/**
		* Copy constructor
		*/
		Board(const Board& _other);

		/**
		* Empty constructor if the board creation is needed to be done manually with create
		*/
		Board() {}
		~Board();

		/**
		* create the tic tac toe board with dimensions size x size (supports from 3x3 to 9x9)
		*/
		void create(uint _size);

		/**
		* clear the board
		*/
		void clear();

		/**
		* print the board
		*/
		void print() const;

		/**
		*	Checks if someone won, or if it's a draw
		*	returns 0 if it's a draw
		*	returns 1 if player 1 won
		*	returns 2 if player 2 / ai won
		*	returns 3 if the game isn't over
		*/
		uint checkForVictory() const;

		/**
		* Performs a possible move on a new board(copy of current) and returns it as a possible game state
		*/
		Board getNewState(uint _x, uint _y, char _val) const;

		/**
		* sets the value of the board at certain position
		*/
		void setValueAt(uint _x, uint _y, char _val) {	m_board.at(_x + m_size * _y) = _val; }

		/**
		* gets the value of the board at certain position
		*/
		char getValueAt(uint _x, uint _y) const { return m_board.at(_x + m_size * _y); }

		/**
		* gets the size of the board
		*/
		uint getSize() const noexcept { return m_size; }

private:
		/**
		* 1D vector of chars representing the 2D board
		* 1D is faster than 2D and can be treated the same way
		* the way to convert from 1D coordinate to 2D or the other way around is:
		*	i = x + size*y;
		*	x = i % size;    // % is the "modulo operator", the remainder of i / width;
		*	y = i / size;    // where "/" is an integer division
		*/
		std::vector<char> m_board{};  

		/**
		* The size of the board in 1 of it's 2 dimensions
		* ex. size 3 = 3x3 board = 9 elements in the board vector
		*/
		uint m_size{ 0 }; ///< the width and height of the tic tac toe board (square)
};

