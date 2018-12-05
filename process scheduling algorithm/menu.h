#pragma once
#include"OS.h"

int menu_select()
{
	int i;
	do {
		system("cls");
		std::cout << "\t\t ╭——————————————■□■□—————╮\n";
		std::cout << "\t\t│     Operating-System-Algorithm-Simulation     │\n";
		std::cout << "\t\t╰———————■□■□————————————╯\n";
		std::cout << "\t\t   ┌————————————————————┐\n";
		std::cout << "\t\t   │       1. First Come First Served       │\n";
		std::cout << "\t\t   │                                        │\n";
		std::cout << "\t\t   │       2. Short Job First               │\n";
		std::cout << "\t\t   │                                        │\n";
		std::cout << "\t\t   │       3. Round Robin                   │\n";
		std::cout << "\t\t   │                                        │\n";
		std::cout << "\t\t   │       4. Priority Scheduling Algorithm │\n";
		std::cout << "\t\t   │                                        │\n";
		std::cout << "\t\t   │       0. Exit                          │\n";
		std::cout << "\t\t   └————————————————————┘\n";
		std::cout << "\t\tPlease choose(0-4):";
		std::cin >> i;
	} while (i < 0 || i>4);
	return i;
}

void OSAlgorithmSimulation()
{
	std::vector<pcb> pcbs;
	size_t roundtime;

	while (1)
	{
		pcbs.clear();
		switch (menu_select())
		{
		case 1:
			GetPcbs(pcbs);
			FCFS(pcbs);
			break;
		case 2:
			GetPcbs(pcbs);
			SJF(pcbs);
			break;
		case 3:
			GetPcbs(pcbs);
			GetRoundTime(roundtime);
			RR(pcbs, roundtime);
			break;
		case 4:
			GetPcbs(pcbs, 1);	
			//void GetPcbs(std::vector<pcb>& pcbs,int flag = 0)
			//第二个参数来判断是否需要输入优先级
			PSA(pcbs);
			break;
		case 0:
			std::cout << "\t\tsystem exit" << std::endl;
			system("pause");
			exit(0);
		}
	}
}

