#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
#include<cmath>
#include"ReadFile.h"
#include"Utils.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::set;

typedef unsigned long long ull;

class Point
{
public:
	Point(long xx, long yy, long zz) : x(xx), y(yy), z(zz) {}
	void print() { cout << "Point: " << x << " " << y << " " << z << endl; }
	double distance(const Point &Point);
	long x, y, z;
};

double Point::distance(const Point &pt)
{
    double dx = pt.x - x;
    double dy = pt.y - y;
    double dz = pt.z - z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

vector<Point> data;
vector<set<int>> junctions;

void readInput(const std::string &fileName)
{
	data.clear();
	junctions.clear();
	ReadFile inf(fileName);
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) break;
		std::vector<long> coords;
		Utils::tokenizeLong(ss, ",", coords);
		if(coords.size() == 3)
			data.emplace_back(coords[0], coords[1], coords[2]);
	}
	inf.close();
}

void printJunctions()
{
	cout << "Junctions:" << endl;
	for(set<int> st : junctions)
	{
		cout << "Size: " << st.size() << ":  ";
		for(int i : st)
			cout << i << " ";
		cout << endl;
	}
}

void part1(int loops)
{
	map<double, vector<int>> distances;

	for(int i = 0; i < data.size(); i++)
	{
		for(int j = i + 1; j < data.size(); j++)
		{
			double dist = data[i].distance(data[j]);
			distances.emplace(dist, vector<int>{i,j});
		}
	}

	int cnt = 0;
	std::map<double, vector<int>>::iterator it;
	for(it = distances.begin(); it != distances.end(); it++)
	{
		int indx1 = it->second[0];
		int indx2 = it->second[1];

		set<int> *s1 = nullptr;
		set<int> *s2 = nullptr;
		for(set<int> &st : junctions)
		{
			if(st.count(indx1) == 1)
				s1 = &st;
			if(st.count(indx2) == 1)
				s2 = &st;
			if(s1 != nullptr && s2 != nullptr) break;
		}

		if(s1 == nullptr && s2 == nullptr)
		{
			set<int> ss;
			ss.insert(indx1);
			ss.insert(indx2);
			junctions.push_back(ss);
		}
		else if(s1 != nullptr && s2 == nullptr)
			s1->insert(indx2);
		else if(s2 != nullptr && s1 == nullptr)
			s2->insert(indx1);
		else if(s1 != nullptr && s2 != nullptr && s1 != s2)
		{
			for(int i : *s2)
				s1->insert(i);
			s2->clear();
		}

		cnt++;
		if(cnt == loops) break;
	}

	vector<int> ll;
	for(set<int> st : junctions)
		ll.push_back(st.size());
	std::sort(ll.begin(), ll.end(), std::greater<int>());
	ull answer1 = ll[0] * ll[1] * ll[2];

	cout << "PART1 answer = " << answer1 << endl;
}

bool isDone(unsigned long long cnt)
{
	for(set<int> st : junctions)
		if(cnt == st.size())
			return true;
	return false;
}

void part2()
{
	map<double, vector<int>> distances;
	int cnt = data.size();

	for(int i = 0; i < data.size(); i++)
	{
		for(int j = i + 1; j < data.size(); j++)
		{
			double dist = data[i].distance(data[j]);
			distances.emplace(dist, vector<int>{i,j});
		}
	}

	ull answer2 = 0;

	std::map<double, vector<int>>::iterator it;
	for(it = distances.begin(); it != distances.end(); it++)
	{
		int indx1 = it->second[0];
		int indx2 = it->second[1];

		set<int> *s1 = nullptr;
		set<int> *s2 = nullptr;
		for(set<int> &st : junctions)
		{
			if(st.count(indx1) == 1)
				s1 = &st;
			if(st.count(indx2) == 1)
				s2 = &st;
			if(s1 != nullptr && s2 != nullptr) break;
		}

		if(s1 == nullptr && s2 == nullptr)
		{
			set<int> ss;
			ss.insert(indx1);
			ss.insert(indx2);
			junctions.push_back(ss);
		}
		else if(s1 != nullptr && s2 == nullptr)
			s1->insert(indx2);
		else if(s2 != nullptr && s1 == nullptr)
			s2->insert(indx1);
		else if(s1 != nullptr && s2 != nullptr && s1 != s2)
		{
			for(int i : *s2)
				s1->insert(i);
			s2->clear();
		}

		if(isDone(cnt))
		{
			answer2 = (ull)data[indx1].x * (ull)data[indx2].x;
			break;
		}
	}

	cout << "PART2 answer = " << answer2 << endl;
}

int main()
{
	readInput("test_input.txt");
	part1(10);
	readInput("test_input.txt");
	part2();
	readInput("input.txt");
	part1(1000);
	readInput("input.txt");
	part2();
	return 0;
}
