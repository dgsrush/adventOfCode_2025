#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include"ReadFile.h"
#include"Utils.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

typedef unsigned long long ull;

class Problem
{
public:
	Problem() {}
	vector<string> data;
	string oper;
	void rotate();
	ull calc();
};

ull Problem::calc()
{
	ull total;
	if(oper == "+")
	{
		total = 0;
		for(string val : data)
		{
			Utils::removeAllSpaces(val);
			if(val.empty()) continue;
			total += std::stoull(val);
		}
	}
	else
	{
		total = 1;
		for(string val : data)
		{
			Utils::removeAllSpaces(val);
			if(val.empty()) continue;
			total *= std::stoull(val);
		}
	}
	return total;
}

void Problem::rotate()
{
	for(string &ss : data)
		while(ss.length() < 4)
			ss += " ";
	int n = data.size();
	for(int i = 0; i < n; i++)
	{
		for(int j = i + 1; j < n; j++)
			std::swap(data[i][j], data[j][i]);
	}
	for(int j = 0; j < n; j++)
	{
		for(int i = 0; i < n / 2; i++)
			std::swap(data[i][j], data[n - 1 - i][j]);
	}
}

vector<Problem> problems;

void readInput(const std::string &fileName)
{
	problems.clear();
	vector<string> dat;

	ReadFile inf(fileName);
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) break;
		dat.push_back(ss);
	}

	vector<int> cols;
	int last = dat.size() - 1;
	for(int i = 0; i < dat[last].size(); i++)
	{
		if(dat[last][i] != ' ')
			cols.push_back(i);
	}

	for(int i = 0; i < cols.size(); i++)
		problems.emplace_back();

	for(string ss : dat)
	{
		std::vector<string> ll;
		for(int i = 0; i < cols.size(); i++)
		{
			string s = ss.substr(cols[i], cols[i+1] - cols[i] - 1);
			if(i == cols.size() - 1)
				s = ss.substr(cols[i]);

			if(s[0] == '*' || s[0] == '+')
				problems[i].oper = s[0];
			else
				problems[i].data.push_back(s);
		}
	}
	inf.close();
}

void part1()
{
	ull answer1 = 0;
	for(Problem &p : problems)
		answer1 += p.calc();
	cout << "PART1 answer = " << answer1 << endl;
}

void part2()
{
	ull answer2 = 0;
	for(Problem &p : problems)
	{
		p.rotate();
		answer2 += p.calc();
	}
	cout << "PART2 answer = " << answer2 << endl;
}

int main()
{
	readInput("test_input.txt");
	part1();
	part2();
	readInput("input.txt");
	part1();
	part2();
	return 0;
}
