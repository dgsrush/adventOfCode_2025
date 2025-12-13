#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<climits>
#include"ReadFile.h"
#include"Utils.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::set;
using std::queue;

typedef long long ll;

class Machine
{
public:
	Machine() {};
	void print();
	vector<bool> expected;
	vector<bool> lights;
	vector<vector<int>> buttons;
	string jolts;

	void pressButton(int);
	void printLights();
	void printExpected();
	void reset();
	bool solved();
};

bool Machine::solved()
{
	for(int i = 0; i < lights.size(); i++)
		if(lights[i] != expected[i]) return false;
	//cout << "SOLVED" << endl;
	return true;
}

void Machine::pressButton(int i)
{
	const vector<int> &ls = buttons[i];
	for(int ii : ls)
		lights[ii] = !lights[ii];
}

void Machine::printExpected()
{
	cout << "Expected: ";
	for(bool b: expected)
		cout << b << " ";
	cout << endl;
}

void Machine::printLights()
{
	cout << "Lights  : ";
	for(bool b: lights)
		cout << b << " ";
	cout << endl;
}

void Machine::reset()
{
	for(int i = 0; i < lights.size(); i++)
		lights[i] = false;
}

void Machine::print()
{
	cout << "Machine:" << endl;
	cout << "  ExpectedLights : ";
	for(bool b: expected)
		cout << b << " ";
	cout << endl;
	cout << "  Lights   : ";
	for(bool b: lights)
		cout << b << " ";
	cout << endl;
	cout << "  Buttons  :" << endl;
	for(vector<int> &button : buttons)
	{
		cout << "    Button : ";
		for(int i : button)
			cout << i << " ";
		cout << endl;
	}
	//cout << "  Jolts   : " << jolts << endl;
}

vector<Machine> data;
set<vector<short>> done;

void readInput(const string &fileName)
{
	data.clear();
	ReadFile inf(fileName);
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		vector<string> ll;
		Utils::tokenize(ss, "[]", ll);
		if(ll.size() == 2)
		{
			data.emplace_back();
			Machine &m = data.back();

			for(char c : ll[0])
			{
				m.lights.push_back(false);
				if(c == '.') m.expected.push_back(false);
				else if(c == '#') m.expected.push_back(true);
			}

			ss = ll[1];
			Utils::tokenize(ss, " ", ll);
			if(ll.size() > 0)
			{
				m.jolts = ll[ll.size()-1];
				ll.pop_back();

				for(string s : ll)
				{
					vector<string> mm;
					Utils::tokenize(s, "(,)", mm);
					m.buttons.emplace_back();
					for(string t : mm)
						m.buttons.back().push_back(stoi(t));
				}
			}
		}
	}
	inf.close();
}

void generateCombinationsWithRepeats(
	const vector<short> &elements, vector<short> &curCombo,
    short comboLen, vector<vector<short>> &results)
{
	if(curCombo.size() == comboLen)
	{
		vector tmp(curCombo);
		std::sort(tmp.begin(), tmp.end());
		if(done.count(tmp) == 0)
		{
			done.insert(tmp);
			results.push_back(tmp);
		}
		return;
	}
	for(int i = 0; i < elements.size(); i++)
	{
		curCombo.push_back(elements[i]);
		generateCombinationsWithRepeats(elements, curCombo, comboLen, results);
		curCombo.pop_back();
	}
}

void createList(short elementCnt, short comboLen, vector<vector<short>> &allCombos)
{
	done.clear();
	vector<short> elements;
    for(short i = 0; i < elementCnt; i++)
    	elements.push_back(i);
    vector<short> curCombo;
    generateCombinationsWithRepeats(elements, curCombo, comboLen, allCombos);
}

int doMachine(Machine &m)
{
	int buttonCnt = m.buttons.size();
	int mincnt = 999999;
	for(int ii = 1; ii <= buttonCnt; ii++)
	{
		//cout << "bcnt: " << buttonCnt << "  ecnt: " << ii << endl;
		vector<vector<short>> numList;
		createList(buttonCnt, ii, numList);
		bool solved = false;
		for(vector<short> &nums : numList)
		{
			m.reset();
			int cnt = 0;
			for(short i : nums)
			{
				m.pressButton(i);
				cnt++;
				solved = m.solved();
				if(solved)
				{
					if(cnt < mincnt) mincnt = cnt;
					break;
				}
			}
			if(solved) break;
		}
		if(solved) break;
	}
	//cout << "MINCNT = " << mincnt << endl;
	return mincnt;
}

void part1()
{
	int cnt = 0;
	ll answer1 = 0;
	for(Machine &m : data)
	{
		cnt++;
		//cout << "doMachine ************** " << cnt << endl;
		answer1 += doMachine(m);
	}
	cout << "PART1 answer = " << answer1 << endl;
}

void part2()
{
	ll answer2 = 0;
	cout << "PART2 answer = " << answer2 << endl;
}

int main()
{
	readInput("test_input.txt");
	part1();
	//readInput("test_input.txt");
	//part2();
	readInput("input.txt");
	part1();
	//readInput("input.txt");
	//part2();
	return 0;
}
