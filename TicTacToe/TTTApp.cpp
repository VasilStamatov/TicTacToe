#include "TTTApp.h"

#include <iostream>

TTTApp::TTTApp()
{
}


TTTApp::~TTTApp()
{
}

void TTTApp::run()
{
		//start the game
		start();

		//enter the game loop
		while (m_gameState != GameState::EXIT)
		{
				clearScreen();
				//print the board at the start of the turn
				m_board.print();

				//Tell whose turn it is and perform a move
				if (m_currentPlayer == m_player1)
				{
						printf("Player 1's turn\n\n");
						//perform a player move
						playerMove();
				}
				else
				{
						printf("Player 2's turn\n\n");

						//perform a move depending on multiplayer mode
						if (m_isMupltiplayer && m_currentPlayer == 2)
						{
								//Second player's turn
								playerMove();
						}
						else
						{
								//AI's turn
								aiMove();
						}
				}

				//Check if somebody won
				uint state = m_board.checkForVictory();

				if (state == 3)
				{
						// the game isn't over
						changePlayer();
				}
				else
				{
						//the game is in its ending state
						endGame(state);
				}
		}
}

void TTTApp::start()
{
		//do some printing to request input from the player
		printf("\n\n ------- Welcome to Tic-Tac-Toe ------- \n\n");
		printf("Please enter the size of the board (3 to 9): \n");

		bool validInput{ false };
		int boardSize;

		do
		{
				while (!(std::cin >> boardSize))
				{
						std::cin.clear();
						std::cin.ignore(1000, '\n');
						printf("ERROR: Invalid input!\n");
				}
				if (boardSize >= 3 && boardSize <= 9)
				{
						validInput = true;
				}
				else
				{
						std::cin.clear();
						std::cin.ignore(1000, '\n');
						printf("ERROR: Invalid input!\n");
				}
		} while (validInput == false);
		//set the game state to playing
		m_gameState = GameState::PLAYING;
		//create the board
		m_board.create(boardSize);
		//set the current player
		m_currentPlayer = m_player1;

		printf("Would you like to play multiplayer ? (y/n): \n");

		char input{ ' ' };

		// take the player's input while making sure it's a valid one
		do
		{
				validInput = true;
				if (!(std::cin >> input))
				{
						std::cout << "Invalid input!";
						std::cin.clear();
						std::cin.ignore(1000, '\n');
						validInput = false;
				}
				else if (input == 'y' || input == 'Y')
				{
						m_isMupltiplayer = true;
				}
				else if (input == 'n' || input == 'N')
				{
						m_isMupltiplayer = false;
				}
				else
				{
						validInput = false;
				}

		} while (validInput == false);

		//check if the game is not mupltiplayer(only 1 human)
		if (!m_isMupltiplayer)
		{
				//prompt for input again
				printf("\n\n What difficulty AI would you like to play against ?\n");
				printf("\tPress 1 for easy \n\tPress 2 for hard \n\tPress 3 for very hard\n");

				uint difficulty;
				validInput = false;
				//take the input for the ai difficulty, while making sure it's valid
				do
				{
						while (!(std::cin >> difficulty))
						{
								std::cin.clear();
								std::cin.ignore(1000, '\n');
								printf("ERROR: Invalid input!\n");
						}

						if (difficulty >= 1 && difficulty <= 3)
						{
								validInput = true;
						}
						else
						{
								std::cin.clear();
								std::cin.ignore(1000, '\n');
								printf("ERROR: Invalid input!\n");
						}
				} while (validInput == false);

				//initialize the ai with proper value
				m_ai.init(m_player2, m_player1, Difficulty(difficulty));
		}
}

void TTTApp::playerMove()
{
		//perform a human-controlled move
		bool validInput{ false };
		uint x{ 0 };
		uint y{ 0 };

		//take the human's input and make sure it's valid
		do
		{
				printf("Enter the coordinate on the x axis (column): ");

				while (!(std::cin >> x))
				{
						std::cin.clear();
						std::cin.ignore(1000, '\n');
						printf("ERROR: Invalid input!");
				}

				printf("Enter the coordinate on the y axis (row): ");

				while (!(std::cin >> y))
				{
						std::cin.clear();
						std::cin.ignore(1000, '\n');
						printf("ERROR: Invalid input!");
				}

				//check if the coordinates are higher than the size of the board
				//The coordinates cannot be smaller as it's an unisgned int so it's always at least 0
				if (x >= m_board.getSize() || y >= m_board.getSize())
				{
						printf("ERROR: Invalid X or Y!\n");
				}
				//Check if the slot at the coordinates is already taken
				else if (m_board.getValueAt(x, y) != ' ')
				{
						printf("ERROR: That spot is taken!\n");
				}
				else
				{
						//everything is ok
						validInput = true;
				}
		} while (!validInput);

		//after the correct input is given, place it on the board
		if (m_currentPlayer == 1)
		{
				m_board.setValueAt(x, y, 'x');
		}
		else
		{
				m_board.setValueAt(x, y, 'o');
		}
}

void TTTApp::aiMove()
{
		//let the ai perform a move
		m_ai.performMove(m_board);
}

void TTTApp::changePlayer()
{
		//change whose turn it currently is
		if (m_currentPlayer == m_player1)
		{
				m_currentPlayer = m_player2;
		}
		else
		{
				m_currentPlayer = m_player1;
		}
}

void TTTApp::endGame(uint result)
{
		//clear the screen
		clearScreen();
		//show the final board
		m_board.print();

		//print how the game ended accordingly
		if (result == 0)
		{
				printf("\n\n The game ended in a draw ! Press 'e' to exit or any other key to start again: ");
		}
		else
		{
				if (result == 1)
				{
						printf("\n\n Player 1 wins ! Press 'e' to exit or any other key to start again: ");
				}
				else
				{
						printf("\n\n Player 2 wins ! Press 'e' to exit or any other key to start again: ");
				}
		}

		//take another input from the player wether he should continue playing or exit
		char input{ ' ' };
		std::cin >> input;
		if (input == 'e' || input == 'E')
		{
				//exit the game on the next while check
				m_gameState = GameState::EXIT;
		}
		else
		{
				//clear the screen
				clearScreen();
				//and restart the game
				start();
		}
}

void TTTApp::clearScreen() const
{
		//print 100 new lines
		std::string buffer;
		buffer.reserve(100);
		for (int i = 0; i < 5; i++)
		{
				buffer += ("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		}
		printf("%s\n", buffer.c_str());
}
