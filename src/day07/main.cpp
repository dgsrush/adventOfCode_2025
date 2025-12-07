#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include"ReadFile.h"
#include"Utils.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;

typedef unsigned long long ull;

vector<string> data;
void readInput(const std::string &fileName)
{
	data.clear();

	ReadFile inf(fileName);
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) break;
		data.push_back(ss);
	}

	inf.close();
}

void printGrid(const vector<string> &dat)
{
	cout << "******************************" << endl;
	for(string s : dat)
		cout << s << endl;
}

vector<int> findBeams(int row, vector<string> &dat)
{
	vector<int> beams;
	for(int i = 0; i < dat[row].length(); i++)
		if(dat[row][i] == 'S' || dat[row][i] == '|')
			beams.push_back(i);
	return beams;
}

void part1()
{
	ull answer1 = 0;
	for(int i = 1; i < data.size(); i++)
	{
		vector<int> beams = findBeams(i - 1, data);
		for(int ii : beams)
		{
			if(data[i][ii] == '.')
				data[i][ii] = '|';
			else if(data[i][ii] == '^')
			{
				answer1++;
				data[i][ii-1] = '|';
				data[i][ii+1] = '|';
			}
		}
	}
	cout << "PART1 answer = " << answer1 << endl;
}

string key(int r, int c) { return std::to_string(r) + " " + std::to_string(c); }
map<string, ull> cache;

void printCache()
{
	std::map<string, ull>::iterator it;
	for(it = cache.begin(); it != cache.end(); it++)
	    cout << it->first << " => " << it->second << endl;
}

ull calc(int r, int c)
{
	ull ret = 0;
	vector<string> dt = data;
	dt[r][c-1] = '|';
	dt[r][c+1] = '|';
	for(int i = r + 1; i < dt.size(); i++)
	{
		vector<int> beams = findBeams(i - 1, dt);
		for(int ii : beams)
		{
			if(dt[i][ii] == '.')
			{
				dt[i][ii] = '|';
				if(i == dt.size() - 1)
					ret++;
			}
			else if(dt[i][ii] == '^')
				ret += cache[key(i,ii)];
		}
	}
	return ret;
}

void buildCache()
{
	cache.clear();
	int r = data.size() - 2;
	for(int c = 0; c < data[r].size(); c++)
	{
		if(data[r][c] == '^')
			cache[key(r,c)] = 2;
	}
	while(r > 0)
	{
		r -= 2;
		for(int c = 0; c < data[r].size(); c++)
		{
			if(data[r][c] == '^')
				cache[key(r,c)] = calc(r, c);
		}
	}
}

void part2()
{
	buildCache();
	ull answer2 = 0;
	for(int i = 0; i < 150; i++)
	{
		if(cache.count(key(2,i)) == 1)
		{
			answer2 = cache[key(2,i)];
			break;
		}
	}
	cout << "PART2 answer = " << answer2 << endl;
}

int main()
{
	readInput("test_input.txt");
	part1();
	readInput("test_input.txt");
	part2();
	readInput("input.txt");
	part1();
	readInput("input.txt");
	part2();
	return 0;
}
