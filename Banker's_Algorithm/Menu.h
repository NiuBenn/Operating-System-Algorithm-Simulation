#pragma once
#include"Banker.h"

int menu_select()
{
	int i;
	do {
		system("cls");
		std::cout << "\t\t�q����������-���������������������r\n";
		std::cout << "\t\t��       ��  ��  ��  ��  ��      ��\n";
		std::cout << "\t\t�t����������������������������-���s\n";
		std::cout << "\t\t������������������������������������\n";
		std::cout << "\t\t��     1. ��Դ�Լ����̳�ʼ��      ��\n";
		std::cout << "\t\t��                                ��\n";
		std::cout << "\t\t��     2. �鿴��Դ״̬            ��\n";
		std::cout << "\t\t��                                ��\n";
		std::cout << "\t\t��     3. ���м��㷨������Դ����  ��\n";
		std::cout << "\t\t��                                ��\n";
		std::cout << "\t\t��     0. �˳�ϵͳ                ��\n";
		std::cout << "\t\t������������������������������������\n";
		std::cout << "\t\tPlease choose(0-3):";
		std::cin >> i;
	} while (i < 0 || i>3);
	return i;
}
