#define _CRT_SECURE_NO_WARNINGS 1
#include"OS.h"
#include<stdlib.h>


int main()
{

	std::vector<pcb> pcbs;
	pcbs.push_back(pcb("A", 0, 4));
	pcbs.push_back(pcb("B", 1, 3));
	pcbs.push_back(pcb("C", 2, 5));
	pcbs.push_back(pcb("D", 3, 2));
	pcbs.push_back(pcb("E", 4, 4));
	size_t times = 1;
	//std::cout << "请输入时间片大小：";
	//std::cin >> times;
	//getpcbs(pcbs);
	//FCFS(pcbs);
	//SJF(pcbs);
	RR(pcbs, times);
	system("pause");
	return 0;
}