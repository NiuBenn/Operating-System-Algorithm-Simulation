#pragma
#include<iostream>
#include<stdlib.h>
#include<vector>

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
	R._Finish.resize(R._ResourcesNum);
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

	system("pause");
}
