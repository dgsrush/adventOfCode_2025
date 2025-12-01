#include<iostream>
#include<string>
#include<vector>
#include"ReadFile.h"
#include"Utils.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

vector<int> data;

void readInput(const std::string &fileName)
{
	data.clear();
	ReadFile inf(fileName);
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		if(ss[0] == 'R')
			data.push_back(stoi(ss.substr(1)));
		else
			data.push_back(-1 * stoi(ss.substr(1)));
	}
	inf.close();
}

void part1()
{
	int answer1 = 0;
	int pos = 50;
	for(int i : data)
	{
		pos += i;
		while(pos > 99) pos -= 100;
		while(pos <  0) pos += 100;
		if(pos == 0) answer1++;
	}
	cout << "PART1 answer = " << answer1 << endl;
}

void part2()
{
	int answer2 = 0;
	int pos = 50;
	for(int i : data)
	{
		if(i > 0)
		{
			for(int j = 0; j < i; j++)
			{
				pos++;
				if(pos > 99) pos -= 100;
				if(pos == 0) answer2++;
			}
		}
		else
		{
			int cnt = abs(i);
			for(int j = 0; j < cnt; j++)
			{
				pos--;
				if(pos <  0) pos += 100;
				if(pos == 0) answer2++;
			}
		}
	}
	cout << "PART2 answer = " << answer2 << endl;
}

int main()
{
	//readInput("test_input.txt");
	//part1();
	//part2();
	readInput("input.txt");
	part1();
	part2();
	return 0;
}
