#pragma once
#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector>
#include<queue>

class pcb
{
public:
	std::string _name;
	size_t _time_come;
	size_t _time_nowneed;
	size_t _time_need;
	size_t _time_begin;
	size_t _time_finish;

	pcb(std::string name, size_t time_come, size_t time_need)
	{
		_name = name;
		_time_come = time_come;
		_time_nowneed = time_need;
		_time_begin = INT_MAX;
		_time_need = time_need;
		_time_finish = INT_MAX;
	}

	void print()
	{
		std::cout << "进程名：" << _name << "  " << "到达时间：" << _time_come << "所需服务时间：" << _time_need;
	}

	
	friend bool CmpByFcfs(pcb& a, pcb& b);
};

void PintfPcbs(std::vector<pcb>& pcbs)
{
	for (size_t i = 0; i < pcbs.size(); ++i)
	{
		pcbs[i].print();
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool CmpByFcfs(pcb& a, pcb& b)
{
	return a._time_come < b._time_come;
}

void getpcbs(std::vector<pcb>& pcbs)
{
	size_t num;
	std::string name;
	std::size_t time_come;
	std::size_t time_need;

	std::cout << "请输入模拟算法中进程数量：";
	std::cin >> num;
	for (size_t i = 0; i < num; ++i)
	{
		system("cls");
		std::cout << "请输入进程名：";
		std::cin >> name;
		std::cout << "请输入到达时间：";
		std::cin >> time_come;
		std::cout << "请输入服务所需时间：";
		std::cin >> time_need;
		pcbs.push_back(pcb(name, time_come, time_need));
	}
	system("cls");
}

void SortPcbsByFcfs(std::vector<pcb>& pcbs)
{
	sort(pcbs.begin(), pcbs.end(), CmpByFcfs);
}

void FCFS(std::vector<pcb>& pcbs)
{
	PintfPcbs(pcbs);
	size_t nowtime = 0;

	//按照到达时间排序
	SortPcbsByFcfs(pcbs);

	//对finish时间计算
	for (size_t i = 0; i < pcbs.size(); ++i)
	{
		if (nowtime < pcbs[i]._time_come)
		{
			nowtime = pcbs[i]._time_come;
		}
		pcbs[i]._time_finish = pcbs[i]._time_need + nowtime;
		pcbs[i]._time_begin = nowtime;
		nowtime += pcbs[i]._time_need;
	}

	for (size_t i = 0; i < pcbs.size(); ++i)
	{
		pcbs[i].print();
		std::cout << " 完成时间："<<pcbs[i]._time_finish << std::endl;
	}
}

void SortPcbsBySjf(std::vector<pcb>& pcbs,std::size_t time)
{
	SortPcbsByFcfs(pcbs);
	if (pcbs.size() == 0)
		return;
	for (size_t i = 0; i < pcbs.size() -1; ++i)
	{
		for (size_t j = 0; j < pcbs.size() - 1 - i; ++j)
		{
			if (pcbs[i+1]._time_come <= time
				&& pcbs[i]._time_need > pcbs[i + 1]._time_need)
			{
				pcb tmp(pcbs[i]);
				pcbs[i] = pcbs[i + 1];
				pcbs[i + 1] = tmp;
			}
		}
	}
}

void SJF(std::vector<pcb>& pcbs)
{
	PintfPcbs(pcbs);
	size_t nowtime = 0;
	std::vector<pcb> pcbQ;
	SortPcbsBySjf(pcbs,nowtime);

	pcbQ.push_back(pcbs[0]);
	for (size_t i = 1; i < pcbs.size();)
	{
		if (pcbQ.size() == 0)
		{
			pcbQ.push_back(pcbs[i]);
			i++;
		}
		if (pcbQ[0]._time_come > nowtime)
			nowtime = pcbQ[0]._time_come;
		
		if (i<pcbs.size()&&pcbs[i]._time_come <= nowtime)
		{
			while (i < pcbs.size() && pcbs[i]._time_come <= nowtime)
			{
				pcbQ.push_back(pcbs[i]);
				i++;
			}
			SortPcbsBySjf(pcbQ,nowtime);
		}

		//取队头pcb，出队
		pcb nowpcb(pcbQ[0]);
		pcbQ[0] = pcbQ[pcbQ.size() - 1];
		pcbQ.pop_back();

		//计算刚才取出的pcb的finish时间
		nowpcb._time_begin = nowtime;
		nowpcb._time_finish = nowpcb._time_need + nowtime;
		nowtime += nowpcb._time_need;
		nowpcb.print();
		std::cout << "  服务开始时间" << nowpcb._time_begin << " 完成时间：" << nowpcb._time_finish << std::endl;
		SortPcbsBySjf(pcbQ,nowtime);
	}
	while (pcbQ.size())
	{
		pcb nowpcb(pcbQ[0]);
		pcbQ[0] = pcbQ[pcbQ.size() - 1];
		pcbQ.pop_back();

		//计算刚才取出的pcb的finish时间
		nowpcb._time_begin = nowtime;
		nowpcb._time_finish = nowpcb._time_need + nowtime;
		nowtime += nowpcb._time_need;
		nowpcb.print();
		std::cout << "  服务开始时间" << nowpcb._time_begin << " 完成时间：" << nowpcb._time_finish << std::endl;
	}
}

void RR(std::vector<pcb>& pcbs, std::size_t times)
{
	PintfPcbs(pcbs);
	SortPcbsByFcfs(pcbs);
	size_t  nowtime = 0;
	std::queue<pcb> pcbQ;
	pcbQ.push(pcbs[0]);
	for (size_t i = 1; i < pcbs.size();)
	{
		if (pcbQ.size() == 0)
		{
			pcbQ.push(pcbs[i]);
			i++;
		}
		if (pcbQ.front()._time_come > nowtime)
			nowtime = pcbQ.front()._time_come;

		if (i<pcbs.size() && pcbs[i]._time_come <= nowtime+1)
		{
			while (i < pcbs.size() && pcbs[i]._time_come <= nowtime+1)
			{
				pcbQ.push(pcbs[i]);
				i++;
			}
		}

		//取队头pcb，出队
		pcb nowpcb(pcbQ.front());
		pcbQ.pop();

		if (nowpcb._time_begin == INT_MAX)
			nowpcb._time_begin = nowtime;

		if (nowpcb._time_nowneed <= times)
		{
			nowpcb._time_finish = nowpcb._time_nowneed + nowtime;
			nowtime += nowpcb._time_nowneed;
			nowpcb.print();
			std::cout << " 完成时间：" << nowpcb._time_finish << std::endl;
		}
		else
		{
			nowpcb._time_nowneed -= times;
			nowtime += times;
			pcbQ.push(nowpcb);
		}
	}
	while (pcbQ.size())
	{
		//取队头pcb，出队
		pcb nowpcb(pcbQ.front());
		pcbQ.pop();

		if (nowpcb._time_begin == INT_MAX)
			nowpcb._time_begin = nowtime;

		if (nowpcb._time_nowneed <= times)
		{
			nowpcb._time_finish = nowpcb._time_nowneed + nowtime;
			nowtime += nowpcb._time_nowneed;
			nowpcb.print();
			std::cout <<" 开始时间："<< nowpcb._time_begin<< " 完成时间：" << nowpcb._time_finish << std::endl;
		}
		else
		{
			nowpcb._time_nowneed -= times;
			nowtime += times;
			pcbQ.push(nowpcb);
		}
	}
}


