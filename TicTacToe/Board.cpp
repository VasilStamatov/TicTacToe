#include "Board.h"

#include <string>

Board::Board(uint _size)
{
		create(_size);
}

Board::~Board()
{
}

void Board::create(uint _size)
{
		//the board must be between 3 and 9
		if (_size < 3)
		{
				_size = 3;
		}
		else if (_size > 9)
		{
				_size = 9;
		}
		m_size = _size;

		m_board.resize(m_size * m_size);
		clear();
}

void Board::clear()
{
		for (uint i = 0; i < m_board.size(); i++)
		{
				m_board.at(i) = ' ';
		}
}

void Board::print() const
{
		//instead of printing to the console multiple times, it is faster to build 1 string and output it once
		std::string text{ "" };

		//reserve some memory for the string so that it's resized less often
		text.reserve(m_size * m_size * 4);

		text += '\n';

		for (uint i = 0; i < m_size; i++)
		{
				text += " |" + std::to_string(i);
		}

		text += "|\n";

		for (uint y = 0; y < m_size; y++)
		{
				text += " -------\n";
				text += std::to_string(y) + "|";

				for (uint x = 0; x < m_size; x++)
				{
						text += getValueAt(x, y);
						text += "|";
				}

				text += '\n';
		}

		printf("%s\n", text.c_str());
}

uint Board::checkForVictory()
{
		bool victory{ false };
		char boardValue{ ' ' };

		//Check if there is a win row-based (left to right)
		for (uint y = 0; y < m_size; y++)
		{
				boardValue = getValueAt(0, y);

				if (boardValue != ' ')
				{
						victory = true;

						for (uint x = 1; x < m_size; x++)
						{
								if (getValueAt(x, y) != boardValue)
								{
										victory = false;
										break;
								}
						}

						if (victory)
						{
								//check who won

								//x is the player
								if (boardValue == 'x')
								{
										return 1;
								}
								else
								{
										return 2;
								}
						}
				}
		}

		//Check if there is a win column-based (top to down
		for (uint x = 0; x < m_size; x++)
		{
				boardValue = getValueAt(x, 0);

				if (boardValue != ' ')
				{
						victory = true;

						for (uint y = 1; y < m_size; y++)
						{
								if (getValueAt(x, y) != boardValue)
								{
										victory = false;
										break;
								}
						}

						if (victory)
						{
								//check who won

								//x is the player
								if (boardValue == 'x')
								{
										return 1;
								}
								else
								{
										return 2;
								}
						}
				}
		}

		// Check top left diagonal (top left to bottom right)
		boardValue = getValueAt(0, 0);

		if (boardValue != ' ')
		{
				victory = true;

				for (uint xy = 0; xy < m_size; xy++)
				{
						if (getValueAt(xy, xy) != boardValue)
						{
								victory = false;
								break;
						}
				}

				if (victory)
				{
						//check who won

						//x is the player
						if (boardValue == 'x')
						{
								return 1;
						}
						else
						{
								return 2;
						}
				}
		}

		// Check top right diagonal (top right to bottom left)
		boardValue = getValueAt(m_size - 1, 0);

		if (boardValue != ' ')
		{
				victory = true;
				for (uint xy = 0; xy < m_size; xy++)
				{
						if (getValueAt(m_size - xy - 1, xy) != boardValue)
						{
								victory = false;
								break;
						}
				}

				if (victory)
				{
						//check who won

						//x is the player
						if (boardValue == 'x')
						{
								return 1;
						}
						else
						{
								return 2;
						}
				}
		}

		// Check for tie game y checking if the whole board is filled
		for (uint i = 0; i < m_board.size(); i++)
		{
				if (m_board.at(i) == ' ') return 3;
		}
		// return 0 for a tie, as all the board has been filled
		return 0;
}
