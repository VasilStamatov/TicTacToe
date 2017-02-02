#pragma once

#include <vector>

using uint = unsigned int;

class Board
{
public:
		Board(uint _size);
		Board() {}
		~Board();

		// create the tic tac toe board of a certain size
		void create(uint _size);

		// clear the board
		void clear();

		// print the board
		void print() const;

		// Checks if someone won, or if it's a draw
		// returns 0 if it's a draw
		// returns 1 if player 1 won
		// returns 2 if player 2 / ai won
		// returns 3 if the game isn't over
		uint checkForVictory();

		// sets the value of the board at certain position
		void setValueAt(uint _x, uint _y, char _val) {	m_board.at(_x + m_size * _y) = _val; }

		// gets the value of the board at certain position
		char getValueAt(uint _x, uint _y) const { return m_board.at(_x + m_size * _y); }

		//gets the size of the board
		uint getSize() const noexcept { return m_size; }

private:
		//i = x + size*y;
		//x = i % size;    // % is the "modulo operator", the remainder of i / width;
		//y = i / size;    // where "/" is an integer division

		std::vector<char> m_board{};

		uint m_size{ 0 }; ///< the width and height of the tic tac toe board (square)
};

