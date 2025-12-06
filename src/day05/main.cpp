#include<iostream>
#include<string>
#include<vector>
#include"ReadFile.h"
#include"Utils.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Range
{
public:
	Range(unsigned long long ss, unsigned long long ee) : s(ss), e(ee) {}
	bool contains(unsigned long long i) { if(i < s || i > e) return false; return true; }
	unsigned long long size() { return e - s + 1; }
	unsigned long long s, e;
};

vector<Range> ranges;
vector<unsigned long long> ids;

void readInput(const std::string &fileName)
{
	ranges.clear();
	ids.clear();

	ReadFile inf(fileName);
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) break;
		std::vector<std::string> output;
		Utils::tokenize(ss, "-", output);
		if(output.size() == 2)
			ranges.emplace_back(std::stoull(output[0]),std::stoull(output[1]));
	}

	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		ids.emplace_back(std::stoull(ss));
	}
	inf.close();

	std::sort(ranges.begin(), ranges.end(), [](const Range &a, const Range &b) { return a.s < b.s; });
}

bool inRange(unsigned long long i)
{
	for(Range range : ranges)
		if(range.contains(i)) return true;
	return false;
}

void part1()
{
	unsigned long long answer1 = 0;
	for(unsigned long long id : ids)
		if(inRange(id)) answer1++;
	cout << "PART1 answer = " << answer1 << endl;
}

void part2()
{
	unsigned long long answer2 = 0;

	while(true)
	{
		vector<int> deletes;
		bool merged = false;

		for(int i = 0; i < ranges.size(); i++)
		{
			if((i + 1) < ranges.size())
			{
				if(ranges[i].s < ranges[i+1].s && ranges[i].e > ranges[i+1].e)
				{
					deletes.push_back(i+1);
					i++;
					merged = true;
				}
				else if(ranges[i].s == ranges[i+1].s)
				{
					ranges[i].e = std::max(ranges[i].e, ranges[i+1].e);
					deletes.push_back(i+1);
					i++;
					merged = true;
				}
				else if(ranges[i].e == ranges[i+1].e)
				{
					ranges[i].s = std::min(ranges[i].s, ranges[i+1].s);
					deletes.push_back(i+1);
					i++;
					merged = true;
				}
				else if(ranges[i].e >= ranges[i+1].s && ranges[i].s < ranges[i+1].e)
				{
					ranges[i].e = ranges[i+1].e;
					deletes.push_back(i+1);
					i++;
					merged = true;
				}
			}
		}

		for(int i = deletes.size()-1; i >= 0; i--)
			ranges.erase(ranges.begin() + deletes[i]);

		if(!merged) break;
	}

	for(Range range : ranges)
		answer2 += range.size();
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
