#pragma once
#include"Banker.h"

int menu_select()
{
	int i;
	do {
		system("cls");
		std::cout << "\t\t╭—————-—■□■□—————╮\n";
		std::cout << "\t\t│       银  行  家  算  法      │\n";
		std::cout << "\t\t╰———■□■□———————-—╯\n";
		std::cout << "\t\t┌————————————————┐\n";
		std::cout << "\t\t│     1. 资源以及进程初始化      │\n";
		std::cout << "\t\t│                                │\n";
		std::cout << "\t\t│     2. 查看资源状态            │\n";
		std::cout << "\t\t│                                │\n";
		std::cout << "\t\t│     3. 银行家算法进行资源分配  │\n";
		std::cout << "\t\t│                                │\n";
		std::cout << "\t\t│     0. 退出系统                  │\n";
		std::cout << "\t\t└————————————————┘\n";
		std::cout << "\t\tPlease choose(0-3):";
		std::cin >> i;
	} while (i < 0 || i>3);
	return i;
}
