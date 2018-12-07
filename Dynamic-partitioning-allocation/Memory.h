#pragma once
#include<iostream>
#include<stdlib.h>
#include<list>
#include<vector>

#include<queue>

class MemoryBlock
{
public:
	size_t _length;
	size_t _start;
	size_t _end;
	
	MemoryBlock(size_t length, size_t start = 0)
	{
		_length = length;
		_start = start;
		_end = _start + _length - 1;
	}

	MemoryBlock(const MemoryBlock& m)
	{
		_length = m._length;
		_start = m._start;
		_end = m._end;
	}

	bool operator == (MemoryBlock& m)
	{
		return m._end == _end && m._start == _start && m._length == _length;
	}

	void Print()
	{
		printf("------------------------------------\n");
		printf("| 起始地址 | 结束地址 | 内存块大小 |\n");
		printf("------------------------------------\n");
		printf("| %7d  | %7d  | %9d  |\n", _start, _end, _length);
		printf("------------------------------------\n");
	}

	friend bool CmpByFF(MemoryBlock& a, MemoryBlock& b);
};

void InitMB(std::list<MemoryBlock> &MB)
{
	system("cls");
	size_t size = 0;
	std::cout << "请输入初始内存总大小：";
	std::cin >> size;
	MemoryBlock NewMB(size);
	MB.push_back(NewMB);
	std::cout << "内存初始化成功!!" << std::endl;
	system("pause");
}

void InitSize(size_t &size)
{
	std::cout << "请输入参数G的大小：";
	std::cin >> size;
}

void MBPrintf(std::list<MemoryBlock> &MB)
{
	if (MB.empty())
	{
		std::cout << "空" << std::endl;
		return;
	}
	//std::list<MemoryBlock>::iterator i = MB.begin();
	printf("-------------------------------------------\n");
	printf("| 编号 | 起始地址 | 结束地址 | 内存块大小 |\n");
	printf("-------------------------------------------\n");
	
	size_t i = 0;
	for (auto m : MB)
	{
		printf("| %4d | %7d  | %7d  | %9d  |\n", i++, m._start, m._end, m._length);
		printf("-------------------------------------------\n");
		//m.Print();
	}
	std::cout << std::endl;
}

void PrintMBAndHelp(std::list<MemoryBlock> &FreeMB, std::list<MemoryBlock> &UsedMB)
{
	std::cout << "空闲内存块：" << std::endl;
	MBPrintf(FreeMB);
	std::cout << "已使用内存块：" << std::endl;
	MBPrintf(UsedMB);

	std::cout << std::endl << "操作指南：1、内存分配  2、回收内存   按q退出！！" << std::endl;
	std::cout << "请输入接下来要进行的操作：";
}

bool CmpByFF(MemoryBlock& a, MemoryBlock& b)
{
	return a._start < b._start;
}

void SortMBByFF(std::list<MemoryBlock> &MB)
{
	MB.sort(CmpByFF);
}

std::list<MemoryBlock>::iterator FindIterator(std::list<MemoryBlock> &FreeMB, MemoryBlock &MB)
{
	std::list<MemoryBlock>::iterator result;
	std::list<MemoryBlock>::iterator it = FreeMB.begin();
	for (; it != FreeMB.end(); ++it)
	{
		if (*it == MB)
		{
			result = it;
			return result;
		}
	}
	return result;
}

void MallocMBByFF(std::list<MemoryBlock> &FreeMB, std::list<MemoryBlock>& UsedMB, size_t size_g)
{
	size_t size;
	std::cout << "\n请输入你要申请分配的内存块大小：";
	std::cin >> size;
	if (size == 0)
	{
		std::cout << "申请内存大小不合法，内存分配失败！" << std::endl;
		system("pause");
		return;
	}

	std::list<MemoryBlock>::iterator it = FreeMB.begin();
	for (;it!=FreeMB.end();++it)
	{
		if ((*it)._length >= size)
		{
			std::cout << std::endl << "内存分配成功,分配的内存块如下：" << std::endl;
			if ((*it)._length > size + size_g)
			{
				MemoryBlock NewMB(size, (*it)._start);
				(*it)._start += size;
				(*it)._length -= size;
				UsedMB.push_back(NewMB);
				NewMB.Print();
			}
			else
			{
				(*it).Print();
				UsedMB.push_back((*it));
				FreeMB.erase(it);
			}
			SortMBByFF(UsedMB);
			SortMBByFF(FreeMB);
			system("pause");
			return;
		}
	}
	std::cout << std::endl << "内存分配失败，未找到合适可分配的空闲内存块" << std::endl;
	system("pause");
	return;
}

void FreeMBByFF(std::list<MemoryBlock> &FreeMB, std::list<MemoryBlock> &UsedMB)
{
	size_t ID;
	std::cout << "请输入你要回收的内存编号：";
	std::cin >> ID;
	if (ID >= UsedMB.size())
	{
		std::cout << std::endl << "编号超出范围，回收内存失败！！" << std::endl;
		system("pause");
		return;
	}

	std::list<MemoryBlock>::iterator it = UsedMB.begin();
	if (ID != 0)
	{
		while (ID--)
			it++;
	}
	FreeMB.push_back(*it);
	UsedMB.erase(it);
	SortMBByFF(FreeMB);

	for(int i = 0; i< 2 && FreeMB.size() > 1; ++i)
	{
		std::list<MemoryBlock>::iterator it = FreeMB.begin();
		std::list<MemoryBlock>::iterator its = it;
		its++;
		for (; its != FreeMB.end(); ++it,++its)
		{
			if ((*it)._end + 1 == (*its)._start)
			{
				(*its)._start = (*it)._start;
				(*its)._length += (*it)._length;
				FreeMB.erase(it);
				break;
			}
		}
	}

	std::cout << std::endl << "内存回收成功！！" << std::endl;
	system("pause");

}

void MallocMBByNF(std::list<MemoryBlock> &FreeMB, std::list<MemoryBlock>& UsedMB,std::list<MemoryBlock>::iterator& Nowit, size_t size_g)
{
	if (FreeMB.size() == 0)
	{
		std::cout << "无剩余内存块，无法进行分配！" << std::endl;
		system("pause");
		return;
	}

	size_t size;
	std::cout << "\n请输入你要申请分配的内存块大小：";
	std::cin >> size;
	if (size == 0)
	{
		std::cout << "申请内存大小不合法，内存分配失败！" << std::endl;
		system("pause");
		return;
	}

	std::list<MemoryBlock>::iterator it = Nowit;
	int flag = 0;
	for (; it != Nowit || flag == 0; ++it)
	{
		if (it == Nowit)
		{
			flag = 1;
		}
		if (it == FreeMB.end())
		{
			it = FreeMB.begin();
		}
		if ((*it)._length >= size)
		{
			std::cout << std::endl << "内存分配成功,分配的内存块如下：" << std::endl;
			if ((*it)._length > size + size_g)
			{
				MemoryBlock NewMB(size, (*it)._start);
				(*it)._start += size;
				(*it)._length -= size;
				Nowit = it;
				Nowit++;
				if (Nowit == FreeMB.end())
				{
					Nowit = FreeMB.begin();
				}
				UsedMB.push_back(NewMB);
				NewMB.Print();
			}
			else
			{
				(*it).Print();
				UsedMB.push_back((*it));
				Nowit = it;
				Nowit++;
				if (Nowit == FreeMB.end())
				{
					Nowit++;
				}
				FreeMB.erase(it);
			}
			SortMBByFF(UsedMB);
			SortMBByFF(FreeMB);
			system("pause");
			return;
		}
	}
	std::cout << std::endl << "内存分配失败，未找到合适可分配的空闲内存块" << std::endl;
	system("pause");
	return;
}

void FreeMBByNF(std::list<MemoryBlock> &FreeMB, std::list<MemoryBlock> &UsedMB,std::list<MemoryBlock>::iterator& Nowit)
{
	size_t ID;
	std::cout << "请输入你要回收的内存编号：";
	std::cin >> ID;
	if (ID >= UsedMB.size())
	{
		std::cout << std::endl << "编号超出范围，回收内存失败！！" << std::endl;
		system("pause");
		return;
	}

	std::list<MemoryBlock>::iterator it = UsedMB.begin();
	if (ID != 0)
	{
		while (ID--)
			it++;
	}
	FreeMB.push_back(*it);
	UsedMB.erase(it);

	MemoryBlock tmp(*Nowit);
	SortMBByFF(FreeMB);
	Nowit = FindIterator(FreeMB, tmp);

	for (int i = 0; i< 2 && FreeMB.size() > 1; ++i)
	{
		std::list<MemoryBlock>::iterator it = FreeMB.begin();
		std::list<MemoryBlock>::iterator its = it;
		its++;
		for (; its != FreeMB.end(); ++it, ++its)
		{
			if ((*it)._end + 1 == (*its)._start)
			{
				(*its)._start = (*it)._start;
				(*its)._length += (*it)._length;
				if (it == Nowit)
				{
					Nowit = its;
				}
				FreeMB.erase(it);
				break;
			}
		}
	}

	std::cout << std::endl << "内存回收成功！！" << std::endl;
	system("pause");
}

void MallocMBByBF(std::list<MemoryBlock> &FreeMB, std::list<MemoryBlock>& UsedMB, size_t size_g)
{
	size_t size;
	std::cout << std::endl << "请输入你要申请分配的内存块大小：";
	std::cin >> size;
	if (size == 0)
	{
		std::cout << "申请内存大小不合法，内存分配失败！" << std::endl;
		system("pause");
		return;
	}

	std::list<MemoryBlock>::iterator it = FreeMB.begin();
	std::list<MemoryBlock>::iterator Best = FreeMB.begin();

	size_t nowsize = INT_MAX;
	for (; it != FreeMB.end(); ++it)
	{
		if ((*it)._length >= size && (*it)._length < nowsize)
		{
			Best = it;
			nowsize = (*it)._length;
		}
	}

	if (nowsize != INT_MAX)
	{
		std::cout << std::endl << "内存分配成功,分配的内存块如下：" << std::endl;
		if ((*Best)._length > size + size_g)
		{
			MemoryBlock NewMB(size, (*Best)._start);
			(*Best)._start += size;
			(*Best)._length -= size;
			UsedMB.push_back(NewMB);
			NewMB.Print();
		}
		else
		{
			(*Best).Print();
			UsedMB.push_back((*Best));
			FreeMB.erase(Best);
		}
		SortMBByFF(UsedMB);
		SortMBByFF(FreeMB);
		system("pause");
		return;
	}

	std::cout << std::endl << "内存分配失败，未找到合适可分配的空闲内存块" << std::endl;
	system("pause");
	return;
}

void MallocMBByWF(std::list<MemoryBlock> &FreeMB, std::list<MemoryBlock>& UsedMB, size_t size_g)
{
	size_t size;
	std::cout << std::endl << "请输入你要申请分配的内存块大小：";
	std::cin >> size;
	if (size == 0)
	{
		std::cout << "申请内存大小不合法，内存分配失败！" << std::endl;
		system("pause");
		return;
	}

	std::list<MemoryBlock>::iterator it = FreeMB.begin();
	std::list<MemoryBlock>::iterator Best = FreeMB.begin();

	size_t nowsize = 0;
	for (; it != FreeMB.end(); ++it)
	{
		if ((*it)._length >= size && (*it)._length > nowsize)
		{
			Best = it;
			nowsize = (*it)._length;
		}
	}

	if (nowsize != 0)
	{
		std::cout << std::endl << "内存分配成功,分配的内存块如下：" << std::endl;
		if ((*Best)._length > size + size_g)
		{
			MemoryBlock NewMB(size, (*Best)._start);
			(*Best)._start += size;
			(*Best)._length -= size;
			UsedMB.push_back(NewMB);
			NewMB.Print();
		}
		else
		{
			(*Best).Print();
			UsedMB.push_back((*Best));
			FreeMB.erase(Best);
		}
		SortMBByFF(UsedMB);
		SortMBByFF(FreeMB);
		system("pause");
		return;
	}

	std::cout << std::endl << "内存分配失败，未找到合适可分配的空闲内存块" << std::endl;
	system("pause");
	return;
}

void FistFit()
{
	std::list<MemoryBlock> FreeMB;
	std::list<MemoryBlock> UsedMB;
	size_t size;
	InitMB(FreeMB);
	InitSize(size);


	char c = 0;
	size_t MBLenth = 0;
	while (1)
	{
		system("cls");
		PrintMBAndHelp(FreeMB, UsedMB);
		std::cout << "参数G为：" << size << std::endl;
		std::cin >> c;
		switch (c)
		{
		case '1':
			MallocMBByFF(FreeMB, UsedMB, size);
			break;
		case '2':
			FreeMBByFF(FreeMB, UsedMB);
			break;
		case 'q':
			goto FFend;
		}
	}
FFend:
	return;
}

void NextFit()
{
	std::list<MemoryBlock> FreeMB;
	std::list<MemoryBlock> UsedMB;
	size_t size;
	InitMB(FreeMB);
	InitSize(size);

	std::list<MemoryBlock>::iterator Nowit = FreeMB.begin();

	char c = 0;
	size_t MBLenth = 0;
	while (1)
	{
		system("cls");
		std::cout << "下次开始查找的内存块为：" << std::endl;
		if (Nowit != FreeMB.end())
		{
			(*Nowit).Print();
		}
		else
		{
			std::cout << "为空！" << std::endl;
		}
		PrintMBAndHelp(FreeMB, UsedMB);
		std::cout << "参数G为：" << size << std::endl;
		std::cin >> c;
		switch (c)
		{
		case '1':
			MallocMBByNF(FreeMB, UsedMB, Nowit, size);
			break;
		case '2':
			FreeMBByNF(FreeMB, UsedMB, Nowit);
			break;
		case 'q':
			goto NFend;
		}

	}
NFend:
	return;
}

void BestFit()
{
	std::list<MemoryBlock> FreeMB;
	std::list<MemoryBlock> UsedMB;
	size_t size;
	InitMB(FreeMB);
	InitSize(size);

	char c = 0;
	size_t MBLenth = 0;
	while (1)
	{
		system("cls");
		PrintMBAndHelp(FreeMB, UsedMB);
		std::cout << "参数G为：" << size << std::endl;

		std::cin >> c;
		switch (c)
		{
		case '1':
			MallocMBByBF(FreeMB, UsedMB, size);
			break;
		case '2':
			FreeMBByFF(FreeMB, UsedMB);
			break;
		case 'q':
			goto NFend;
		}

	}
NFend:
	return;
}

void WorstFit()
{
	std::list<MemoryBlock> FreeMB;
	std::list<MemoryBlock> UsedMB;
	size_t size;
	InitMB(FreeMB);
	InitSize(size);

	char c = 0;
	size_t MBLenth = 0;
	while (1)
	{
		system("cls");
		PrintMBAndHelp(FreeMB, UsedMB);
		std::cout << "参数G为：" << size << std::endl;

		std::cin >> c;
		switch (c)
		{
		case '1':
			MallocMBByWF(FreeMB, UsedMB, size);
			break;
		case '2':
			FreeMBByFF(FreeMB, UsedMB);
			break;
		case 'q':
			goto NFend;
		}

	}
NFend:
	return;
}

