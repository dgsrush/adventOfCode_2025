#include<iostream>
#include<string>
#include<vector>
#include<set>
#include"ReadFile.h"
#include"Utils.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::set;

class Range
{
public:
	Range(unsigned long long s, unsigned long long e) : start(s), end(e) {}
	void print() { cout << "Range: " << start << " " << end << endl; }
	unsigned long long start;
	unsigned long long end;
};

vector<Range> data;

void readInput(const std::string &fileName)
{
	data.clear();
	ReadFile inf(fileName);
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		std::vector<std::string> ll;
		Utils::tokenize(ss, ",-", ll, false);
		for(int i = 0; i < ll.size(); i += 2)
			data.emplace_back(std::stoull(ll[i]), std::stoull(ll[i+1]));
	}
	inf.close();
}

void part1()
{
	unsigned long long answer1 = 0;
	for(Range &range : data)
	{
		for(unsigned long long i = range.start; i <= range.end; i++)
		{
			string ss = std::to_string(i);
			int len = ss.length();
			if((len % 2) == 0)
			{
				len /= 2;
				string s1 = ss.substr(0, len);
				string s2 = ss.substr(len);
				if(s1 == s2)
					answer1 += i;
			}
		}
	}
	cout << "PART1 answer = " << answer1 << endl;
}

bool areAllEqual(const vector<string> &ll)
{
	if(ll.size() < 2) return false;
	set<string> mm(ll.begin(), ll.end());
	if(mm.size() == 1) return true;
	return false;
}

bool isInvalid(const string &ss)
{
	int len = ss.length() / 2;
	if((ss.length() % 2) != 0)
		len++;
	for(int i = 1; i <= len; i++)
	{
		vector<string> subs;
		int st = 0;
		int cnt = (ss.length() / i) + 1;
		for(int j = 0; j < cnt; j++)
		{
			string xx = ss.substr(st, i);
			if(xx.empty()) continue;
			subs.push_back(xx);
			st += i;
		}
		if(areAllEqual(subs)) return true;
	}
	return false;
}

void part2()
{
	unsigned long long answer2 = 0;
	for(Range &range : data)
	{
		for(unsigned long long i = range.start; i <= range.end; i++)
		{
			string ss = std::to_string(i);
			if(isInvalid(ss))
				answer2 += i;
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
