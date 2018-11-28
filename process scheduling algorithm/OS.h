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
	size_t _weight;
	size_t _time_T;
	double _time_T_Weight;

	pcb(std::string name, size_t time_come, size_t time_need,size_t weight = 0)
	{
		_name = name;
		_time_come = time_come;
		_time_nowneed = time_need;
		_time_begin = INT_MAX;
		_time_need = time_need;
		_time_finish = INT_MAX;
		_weight = weight;
	}

	void setweight(size_t weight)
	{
		_weight = weight;
	}

	void print(int flag = 0)
	{
		std::cout << "进程：" << _name << " 到达：" << _time_come << " 所需服务：" << _time_need;
		if (flag == 1)
			std::cout << " 优先权：" << _weight;
	}

	void SetTTimeAndTTimeWithW()
	{
		_time_T = _time_finish - _time_begin;
		_time_T_Weight = (double)_time_T / (double)_time_need;
	}
	friend bool CmpByFcfs(pcb& a, pcb& b);
	friend bool CmpBySjf(pcb& a, pcb& b);
	friend bool CmpByPsa(pcb& a, pcb& b);

};

void PintfPcbs(std::vector<pcb>& pcbs,int flag = 0)
{
	for (size_t i = 0; i < pcbs.size(); ++i)
	{
		pcbs[i].print(flag);
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool CmpByFcfs(pcb& a, pcb& b)
{
	return a._time_come < b._time_come;
}

bool CmpBySjf(pcb& a, pcb& b)
{
	return a._time_need < b._time_need;
}

bool CmpByPsa(pcb& a, pcb& b)
{
	return a._weight > b._weight;
}

void GetPcbs(std::vector<pcb>& pcbs,int flag = 0)
{
	system("cls");
	size_t num;
	std::string name;
	size_t time_come;
	size_t time_need;
	size_t weight;
	

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
		if (flag == 1)
		{
			std::cout << "请输入进程优先级：";
			std::cin >> weight;
			pcbs.back().setweight(weight);
		}
	}
	system("cls");
}

void GetRoundTime(size_t& times)
{
	system("cls");
	std::cout << "请输入时间片大小：";
	std::cin >> times;
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
	system("pause");
}

void SortPcbsBySjf(std::vector<pcb>& pcbs)
{
	if (pcbs.size() == 0)
		return;
	sort(pcbs.begin(), pcbs.end(), CmpBySjf);
}

void SJF(std::vector<pcb>& pcbs)
{
	PintfPcbs(pcbs);
	size_t nowtime = 0;
	std::vector<pcb> pcbQ;
	SortPcbsByFcfs(pcbs);

	size_t index = 0;
	while (1)
	{
		if (pcbQ.empty() && index >= pcbs.size())
			break;
		if (pcbQ.empty())
		{
			pcbQ.push_back(pcbs[index]);
			index++;
		}

		while (index < pcbs.size() && pcbs[index]._time_come <= nowtime)
		{
			pcbQ.push_back(pcbs[index]);
			index++;
		}
		SortPcbsBySjf(pcbQ);

		if (pcbQ[0]._time_come > nowtime)
			nowtime = pcbQ[0]._time_come;

		//取队头pcb，出队
		pcb nowpcb(pcbQ[0]);
		pcbQ[0] = pcbQ[pcbQ.size() - 1];
		pcbQ.pop_back();

		//计算刚才取出的pcb的finish时间
		nowpcb._time_begin = nowtime;
		nowpcb._time_finish = nowpcb._time_need + nowtime;
		nowtime += nowpcb._time_need;
		nowpcb.SetTTimeAndTTimeWithW();
		nowpcb.print();
		std::cout << " 开始：" << nowpcb._time_begin << " 完成：" << nowpcb._time_finish <<
			" 周转："<<nowpcb._time_T<<" 带权周转："<<nowpcb._time_T_Weight<< std::endl;
		SortPcbsBySjf(pcbQ);
	}
	system("pause");
}

void RR(std::vector<pcb>& pcbs, std::size_t times)
{
	PintfPcbs(pcbs);
	SortPcbsByFcfs(pcbs);
	size_t  nowtime = 0;
	std::queue<pcb> pcbQ;

	size_t index = 0;
	while (1)
	{
		if (pcbQ.empty() && index >= pcbs.size())
			break;
		if (pcbQ.empty())
		{
			pcbQ.push(pcbs[index]);
			index++;
		}
		if (pcbQ.front()._time_come > nowtime)
			nowtime = pcbQ.front()._time_come;

		while (index < pcbs.size() && pcbs[index]._time_come <= nowtime + 1)
		{
			pcbQ.push(pcbs[index]);
			index++;
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
			nowpcb.SetTTimeAndTTimeWithW();
			nowpcb.print();
			std::cout << " 开始：" << nowpcb._time_begin << " 完成：" << nowpcb._time_finish <<
				" 周转：" << nowpcb._time_T << " 带权周转：" << nowpcb._time_T_Weight << std::endl;
		}
		else
		{
			nowpcb._time_nowneed -= times;
			nowtime += times;
			pcbQ.push(nowpcb);
		}
	}
	system("pause");
}

void SortPcbsByPSA(std::vector<pcb>& pcbs)
{
	if (pcbs.size() == 0)
		return;
	sort(pcbs.begin(), pcbs.end(), CmpByPsa);
}

void PSA(std::vector<pcb>& pcbs)
{
	PintfPcbs(pcbs, 1);
	size_t nowtime = 0;
	size_t index = 0;
	std::vector<pcb> pcbQ;
	SortPcbsByFcfs(pcbs);

	while (1)
	{
		if (pcbQ.empty() && index >= pcbs.size())
			break;
		if (pcbQ.empty())
		{
			pcbQ.push_back(pcbs[index]);
			index++;
		}

		while (index < pcbs.size() && pcbs[index]._time_come <= nowtime)
		{
			pcbQ.push_back(pcbs[index]);
			index++;
		}
		SortPcbsByPSA(pcbQ);

		if (pcbQ.front()._time_come > nowtime)
			nowtime = pcbQ.front()._time_come;

		if (pcbQ.front()._time_begin == INT_MAX)
			pcbQ.front()._time_begin = nowtime;

		if (pcbQ.front()._time_nowneed == 1)
		{
			pcbQ.front()._time_nowneed = 0;
			pcbQ.front()._time_finish = nowtime + 1;
			nowtime++;
			pcbQ.front().SetTTimeAndTTimeWithW();
			pcbQ.front().print(1);
			std::cout << " 开始：" << pcbQ.front()._time_begin << " 完成：" << pcbQ.front()._time_finish <<
				" 周转：" << pcbQ.front()._time_T << " 带权周转：" << pcbQ.front()._time_T_Weight << std::endl;
			pcbQ.front() = pcbQ.back();
			pcbQ.pop_back();
		}
		else
		{
			pcbQ.front()._time_nowneed --;
			nowtime++;
		}
	}
	system("pause");
}


