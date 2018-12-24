#pragma once
#include"Memory.h"

int menu_select()
{
	int i;
	do {
		system("cls");
		std::cout << "\t\t ¨q¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ö¡õ¡ö¡õ¡ª¡ª¡ª¡ª¡ª¨r\n";
		std::cout << "\t\t©¦   Dynamic-partitioning-allocation    ©¦\n";
		std::cout << "\t\t¨t¡ª¡ª¡ª¡ö¡õ¡ö¡õ¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¨s\n";
		std::cout << "\t\t   ©°¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª©´\n";
		std::cout << "\t\t   ©¦       1. First Fit             ©¦\n";
		std::cout << "\t\t   ©¦                                ©¦\n";
		std::cout << "\t\t   ©¦       2. Next Fit              ©¦\n";
		std::cout << "\t\t   ©¦                                ©¦\n";
		std::cout << "\t\t   ©¦       3. Best Fit              ©¦\n";
		std::cout << "\t\t   ©¦                                ©¦\n";
		std::cout << "\t\t   ©¦       4. Worst Fit             ©¦\n";
		std::cout << "\t\t   ©¦                                ©¦\n";
		std::cout << "\t\t   ©¦       0. Exit                  ©¦\n";
		std::cout << "\t\t   ©¸¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª©¼\n";
		std::cout << "\t\tPlease choose(0-4):";
		std::cin >> i;
	} while (i < 0 || i>4);
	return i;
}

void MemoryFit()
{
	/*std::list<MemoryBlock> FreeMB;
	std::list<MemoryBlock> UsedMB;
	InitMB(FreeMB);*/

	while (1)
	{
		switch (menu_select())
		{
		case 1:
			FistFit();
			break;
		case 2:
			NextFit();
			break;
		case 3:
			BestFit();
			break;
		case 4:
			WorstFit();
			break;
		case 0:
			std::cout << "\t\tsystem exit" << std::endl;
			system("pause");
			exit(0);
		}
	}
}

