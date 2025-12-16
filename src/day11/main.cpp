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

class Device
{
public:
	Device() {}
	Device(string d) : deviceName(d) {}
	void print();
	string deviceName;
	vector<string> devices;
	set<string> setDevices;
};

void Device::print()
{
	cout << "Device: " << deviceName << " =";
	for(string dev : devices)
		cout << " " << dev;
	cout << endl;
}

//////////////////////////////////////////////////

map<string, Device> data;
set<string> keys;

void printDevices()
{
	for(string key : keys)
		data[key].print();
}

void readInput(const std::string &fileName)
{
	data.clear();
	keys.clear();
	ReadFile inf(fileName);
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		std::vector<std::string> vv;
		Utils::tokenize(ss, ": ", vv);
		if(vv.size() > 1)
		{
			string id = vv[0];
			keys.insert(id);
			data.emplace(id, id);
			for(int i = 1; i < vv.size(); i++)
			{
				data[vv[0]].devices.push_back(vv[i]);
				data[vv[0]].setDevices.insert(vv[i]);
			}
		}
	}
	inf.close();
}

ll calc(string from, string to)
{
	ll answer1 = 0;
	queue<string> todo;
	todo.push(from);
	while(!todo.empty())
	{
		string &devName = todo.front();
		todo.pop();
		Device &dev = data[devName];
		if(dev.devices.size() == 1 && dev.devices[0] == to)
			answer1++;
		else
		{
			for(string &dname : dev.devices)
				todo.push(dname);
		}
	}
	return answer1;
}

void part1()
{
	ll answer1 = calc("you", "out");
	cout << "PART1 answer = " << answer1 << endl;
}

//////////////////////////////////////////////////

void part2()
{
	//ll p1 = calc("svr", "fft");
	//ll p2 = calc("fft", "dac");
	//ll p3 = calc("dac", "out");

	//ll p1 = calc("svr", "dac");
	//ll p2 = calc("dac", "fft");
	//ll p3 = calc("fft", "out");

	//ll answer2 = p1 * p2 * p3;
	//cout << "PART2 answer = " << answer2 << endl;
}

int main()
{
	readInput("test_input.txt");
	part1();
	//readInput("test_input_p2.txt");
	//part2();
	readInput("input.txt");
	part1();
	//readInput("input.txt");
	//part2();
	return 0;
}
