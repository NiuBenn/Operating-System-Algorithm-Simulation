#pragma
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<map>

class Resources
{
public:
	std::vector<int> _Available;
	std::vector<std::vector<int>> _Allocation;
	std::vector< std::vector<int>> _Need;
	std::vector< std::vector<int>> _MaxNeed;
	std::vector<int> _Work;
	std::vector<bool> _Finish;
	std::vector<int> _Request;
	size_t _PcbNum;
	size_t _ResourcesNum;

};

bool IsSafety(Resources& R);

void Init(Resources& R)
{
	system("cls");

	std::cout << "��������Դ����������";
	std::cin >> R._ResourcesNum;
	std::cout << "�����������������";
	std::cin >> R._PcbNum;

	R._Available.resize(R._ResourcesNum);	
	R._Allocation.resize(R._PcbNum);
	R._Need.resize(R._PcbNum);
	R._MaxNeed.resize(R._PcbNum);

	for (size_t i = 0; i < R._PcbNum; ++i)
	{
		R._Allocation[i].resize(R._ResourcesNum);
		R._Need[i].resize(R._ResourcesNum);
		R._MaxNeed[i].resize(R._ResourcesNum);
	}
	R._Work.resize(R._ResourcesNum);
	R._Finish.resize(R._PcbNum);
	R._Request.resize(R._ResourcesNum);

	system("cls");
	for (size_t i = 0; i < R._ResourcesNum; ++i)
	{
		std::cout << "�������" << i + 1 << "����Դ��ϵͳʣ��������";
		std::cin >> R._Available[i];
	}

	for (size_t i = 0; i < R._PcbNum; ++i)
	{
		system("cls");
		std::cout << "�������" << i + 1 << "�������ѷ������Դ������" << std::endl;
		for (size_t j = 0; j < R._ResourcesNum; ++j)
		{
			std::cout << "�������ѷ���ĵ�" << j + 1 << "����Դ������";
			std::cin >> R._Allocation[i][j];
		}
	}

	for (size_t i = 0; i < R._PcbNum; ++i)
	{
		system("cls");
		std::cout << "�������" << i + 1 << "�����̶���Դ���������������" << std::endl;
		for (size_t j = 0; j < R._ResourcesNum; ++j)
		{
			std::cout << "������Ե�" << j + 1 << "����Դ�������������";
			std::cin >> R._MaxNeed[i][j];
			R._Need[i][j] = R._MaxNeed[i][j] - R._Allocation[i][j];
		}
	}
	std::cout << "����������������������������������������������������������������" << std::endl;
	std::cout << "��ʼ���ɹ�����" << std::endl;
	std::cout << "�������а�ȫ�����м�⣡��" << std::endl;
	system("pause");

	for (size_t i = 0; i < R._ResourcesNum; ++i)
	{
		R._Work[i] = R._Available[i];
	}
	bool safe = IsSafety(R);

	if (safe)
	{
		std::cout << "Ŀǰϵͳ��Դ״̬��ȫ��";
		system("pause");
	}
	else
	{
		std::cout << "Ŀǰ��Դ״̬����ȫ����Դ��ʼ��ʧ�ܣ�" << std::endl;
		std::cout << "�뷵�����˵����½��г�ʼ��!!";
		system("pause");
	}

}

void PrintResources(Resources& R)
{	
	printf("\nϵͳʣ����Դ��");
	for (size_t i = 0; i < R._ResourcesNum; ++i)
	{
		printf("%4d", R._Available[i]);
	}

	printf("\n\n      Ŀǰռ����  ���������  ��������   \n");
	for (size_t i = 0; i < R._PcbNum; ++i)
	{
		printf("P[%d]", i);
		printf(" |");
		for (size_t j = 0; j < R._ResourcesNum; ++j)
		{
			printf("%3d", R._Allocation[i][j]);
		}
		printf(" |");
		for (size_t j = 0; j < R._ResourcesNum; ++j)
		{
			printf("%3d", R._MaxNeed[i][j]);
		}
		printf(" |");
		for (size_t j = 0; j < R._ResourcesNum; ++j)
		{
			printf("%3d", R._Need[i][j]);
		}
		printf("\n");
	}
	system("pause");
}

bool IsSafety(Resources& R)
{
	for (size_t i = 0; i < R._PcbNum; ++i)
	{
		R._Finish[i] = false;
	}

	size_t FinshNum = 0;
	int flag = 1;
	printf("       Work       Need        Alloc       W+A       Finish\n");
	while (flag)
	{
		flag = 0;
		for (size_t i = 0; i < R._PcbNum; ++i)
		{
			if (R._Finish[i] == false)
			{
				int ResFlag = 1;
				for (size_t j = 0; j < R._ResourcesNum; ++j)
				{
					if (R._Need[i][j] > R._Work[j])
					{
						ResFlag = 0;
						break;
					}
				}
				if (ResFlag)
				{
					R._Finish[i] = true;
					flag = 1;
					printf("P[%d]", i);
					printf(" |");
					for (size_t j = 0; j < R._ResourcesNum; ++j)
					{
						printf("%3d", R._Work[j]);
					}
					printf(" |");
					for (size_t j = 0; j < R._ResourcesNum; ++j)
					{
						printf("%3d", R._Need[i][j]);
					}
					printf(" |");
					for (size_t j = 0; j < R._ResourcesNum; ++j)
					{
						printf("%3d", R._Allocation[i][j]);
					}
					printf(" |");
					for (size_t j = 0; j < R._ResourcesNum; ++j)
					{
						printf("%3d", R._Allocation[i][j] + R._Work[j]);
						R._Work[j] += R._Allocation[i][j];
					}
					printf(" | true");
					FinshNum++;
					flag = 1;
					printf("\n");
				}
			}
		}
	}

	if (FinshNum < R._PcbNum)
	{
		std::cout << "�����㰲ȫ���㷨!!" << std::endl;
		return false;
	}
	else
	{
		std::cout << "���㰲ȫ���㷨!!" << std::endl;
		return true;
	}

}

void Banker(Resources& R)
{
	system("cls");
	
	int PcbIndex;
	int Flag = 1;
	
	while (Flag)
	{
		PrintResources(R);
		std::cout << "������Ҫ������Դ����Ľ��̣�";
		std::cin >> PcbIndex;
		for (size_t i = 0; i < R._ResourcesNum; ++i)
		{
			std::cout << "������Ե�" << i + 1 << "����Դ����������";
			std::cin >> R._Request[i];
			if (R._Request[i] > R._Need[PcbIndex][i])
			{
				std::cout << "������Դʧ�ܣ���ǰ����Դ���������ڵ�ǰ���̶Ըý��̵��������������" << std::endl;
				system("pause");
				goto end;
			}
			if (R._Request[i] > R._Available[i])
			{
				std::cout << "������Դʧ�ܣ���ǰ����Դ���������ڵ�ǰϵͳ�и�����Դ����������" << std::endl;
				system("pause");
				goto end;
			}
		}
		for (size_t i = 0; i < R._ResourcesNum; ++i)
		{
			R._Available[i] -= R._Request[i];
			R._Allocation[PcbIndex][i] += R._Request[i];
			R._Need[PcbIndex][i] -= R._Request[i];
			R._Work[i] = R._Available[i];
		}

		bool safe = IsSafety(R);
		if (safe)
		{
			std::cout << "����ɹ�����" << std::endl;
		}
		else
		{
			std::cout << "����ʧ�ܣ���ǰ״̬����ȫ����" << std::endl;
			for (size_t i = 0; i < R._ResourcesNum; ++i)
			{
				R._Available[i] += R._Request[i];
				R._Allocation[PcbIndex][i] -= R._Request[i];
				R._Need[PcbIndex][i] += R._Request[i];
			}
		}
end:
		std::cout << "��ѡ������1�������䣬����0�˳����䣺";
		std::cin >> Flag;
	}

}

