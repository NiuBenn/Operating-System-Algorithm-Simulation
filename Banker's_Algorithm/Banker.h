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

	std::cout << "请输入资源种类总数：";
	std::cin >> R._ResourcesNum;
	std::cout << "请输入进程总数量：";
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
		std::cout << "请输入第" << i + 1 << "类资源的系统剩余数量：";
		std::cin >> R._Available[i];
	}

	for (size_t i = 0; i < R._PcbNum; ++i)
	{
		system("cls");
		std::cout << "请输入第" << i + 1 << "个进程已分配的资源数量：" << std::endl;
		for (size_t j = 0; j < R._ResourcesNum; ++j)
		{
			std::cout << "请输入已分配的第" << j + 1 << "类资源数量：";
			std::cin >> R._Allocation[i][j];
		}
	}

	for (size_t i = 0; i < R._PcbNum; ++i)
	{
		system("cls");
		std::cout << "请输入第" << i + 1 << "个进程对资源的最大需求数量：" << std::endl;
		for (size_t j = 0; j < R._ResourcesNum; ++j)
		{
			std::cout << "请输入对第" << j + 1 << "类资源最大需求数量：";
			std::cin >> R._MaxNeed[i][j];
			R._Need[i][j] = R._MaxNeed[i][j] - R._Allocation[i][j];
		}
	}
	std::cout << "————————————————————————————————" << std::endl;
	std::cout << "初始化成功！！" << std::endl;
	std::cout << "即将进行安全性序列检测！！" << std::endl;
	system("pause");

	for (size_t i = 0; i < R._ResourcesNum; ++i)
	{
		R._Work[i] = R._Available[i];
	}
	bool safe = IsSafety(R);

	if (safe)
	{
		std::cout << "目前系统资源状态安全！";
		system("pause");
	}
	else
	{
		std::cout << "目前资源状态不安全，资源初始化失败！" << std::endl;
		std::cout << "请返回主菜单重新进行初始化!!";
		system("pause");
	}

}

void PrintResources(Resources& R)
{	
	printf("\n系统剩余资源：");
	for (size_t i = 0; i < R._ResourcesNum; ++i)
	{
		printf("%4d", R._Available[i]);
	}

	printf("\n\n      目前占有量  最大需求量  尚需求量   \n");
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
		std::cout << "不满足安全性算法!!" << std::endl;
		return false;
	}
	else
	{
		std::cout << "满足安全性算法!!" << std::endl;
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
		std::cout << "请输入要进行资源分配的进程：";
		std::cin >> PcbIndex;
		for (size_t i = 0; i < R._ResourcesNum; ++i)
		{
			std::cout << "请输入对第" << i + 1 << "类资源的申请量：";
			std::cin >> R._Request[i];
			if (R._Request[i] > R._Need[PcbIndex][i])
			{
				std::cout << "申请资源失败：当前类资源申请量大于当前进程对该进程的最大需求数！！" << std::endl;
				system("pause");
				goto end;
			}
			if (R._Request[i] > R._Available[i])
			{
				std::cout << "申请资源失败：当前类资源申请量大于当前系统中该类资源总数量！！" << std::endl;
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
			std::cout << "分配成功！！" << std::endl;
		}
		else
		{
			std::cout << "分配失败：当前状态不安全！！" << std::endl;
			for (size_t i = 0; i < R._ResourcesNum; ++i)
			{
				R._Available[i] += R._Request[i];
				R._Allocation[PcbIndex][i] -= R._Request[i];
				R._Need[PcbIndex][i] += R._Request[i];
			}
		}
end:
		std::cout << "请选择：输入1继续分配，输入0退出分配：";
		std::cin >> Flag;
	}

}

