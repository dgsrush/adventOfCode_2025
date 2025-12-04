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

void part1()
{
	int answer1 = 0;
	for(string ss : data)
	{
		int mx = 0;
		for(int i1 = 0; i1 < ss.length(); i1++)
		{
			for(int i2 = i1 + 1; i2 < ss.length(); i2++)
			{
				string tt = ss.substr(i1, 1) + ss.substr(i2, 1);
				mx = std::max(stoi(tt), mx);
			}
		}
		answer1 += mx;
	}
	cout << "PART1 answer = " << answer1 << endl;
}

int getMaxIndex(string fnd)
{
	string ll = "9876543210";
	for(int i = 0; i < ll.length(); i++)
	{
		int ii = fnd.find_first_of(ll[i]);
		if(ii != string::npos) return ii;
	}
	return -1;
}

void part2()
{
	unsigned long long answer2 = 0;
	for(string ss : data)
	{
		int llen = ss.length();
		int need = 11;
		string ans = "";
		for(int i = 0; i < 12; i++)
		{
			string fnd = ss.substr(0, llen - need);
			int indx = getMaxIndex(fnd);
			ans += fnd[indx];
			ss = ss.substr(indx + 1);
			need--;
			llen = ss.length();
		}
		answer2 += stoull(ans);
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
