#include<iostream>
#include<string>
#include<vector>
#include"ReadFile.h"
#include"Utils.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

vector<string> data;

void readInput(const std::string &fileName)
{
	data.clear();
	ReadFile inf(fileName);
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		data.push_back(ss);
	}
	inf.close();
}

bool isRoll(int r, int c)
{
	if(r < 0 || r >= data.size()) return false;
	if(c < 0 || c >= data[r].length()) return false;
	if(data[r][c] == '@') return true;
	return false;
}

int countAdjacentRolls(int r, int c)
{
	int cnt = 0;
	if(isRoll(r-1, c-1)) cnt++;
	if(isRoll(r-1, c  )) cnt++;
	if(isRoll(r-1, c+1)) cnt++;
	if(isRoll(r+1, c-1)) cnt++;
	if(isRoll(r+1, c  )) cnt++;
	if(isRoll(r+1, c+1)) cnt++;
	if(isRoll(r  , c-1)) cnt++;
	if(isRoll(r  , c+1)) cnt++;
	return cnt;
}

void part1()
{
	int answer1 = 0;
	for(int r = 0; r < data.size(); r++)
	{
		for(int c = 0; c < data[r].length(); c++)
		{
			if(data[r][c] == '@')
			{
				if(countAdjacentRolls(r, c) < 4) answer1++;
			}
		}
	}
	cout << "PART1 answer = " << answer1 << endl;
}

class Cell
{
public:
	Cell(int rr, int cc) : r(rr), c(cc) {}
	int r, c;
};

void part2()
{
	int answer2 = 0;
	while(true)
	{
		vector<Cell> cells;
		for(int r = 0; r < data.size(); r++)
		{
			for(int c = 0; c < data[r].length(); c++)
			{
				if(data[r][c] == '@')
				{
					if(countAdjacentRolls(r, c) < 4)
					{
						answer2++;
						cells.emplace_back(r, c);
					}
				}
			}
		}
		if(cells.size() == 0) break;
		for(Cell cell : cells)
			data[cell.r][cell.c] = 'x';
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
