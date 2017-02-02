#include "Board.h"

int main()
{
		Board test(3);

		test.setValueAt(1, 1, 'x');

		test.print();

		system("Pause");
		return 0;
}