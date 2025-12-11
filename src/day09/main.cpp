#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<cmath>
#include<climits>
#include"ReadFile.h"
#include"Utils.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::set;

typedef long long ll;

class Cell
{
public:
	Cell() : r(0), c(0) {}
	Cell(ll rr, ll cc) : r(rr), c(cc) {}
	void print() { cout << "Cell: " << r << " " << c << endl; }
	string getKey() { return std::to_string(r) + ":" + std::to_string(c); }
	ll rectSize(Cell &c);
	ll r, c;
};

ll Cell::rectSize(Cell &cell)
{
	long long cc = cell.c - c;
	long long rr = cell.r - r;
	ll w = std::abs(cc) + 1;
	ll h = std::abs(rr) + 1;
	return w * h;
}

vector<Cell> redData;
set<string> redDataCont;
set<string> greenData;
string getKey(ll r, ll c) { return std::to_string(r) + ":" + std::to_string(c); }

bool pointin(const Cell *pp)
{
	int j = 0, xi, yi, xj, yj;
	bool oddnodes = false;
	int cnt = redData.size();
	for(int i = 0; i < cnt; i++)
	{
		j++;
		if(j == cnt) j = 0;
		xi = redData[i].c;
		yi = redData[i].r;
		xj = redData[j].c;
		yj = redData[j].r;
		if(yi < pp->r && yj >= pp->r || yj < pp->r && yi >= pp->r)
		{
			if(xi + (pp->r - yi) / (yj - yi) * (xj - xi) < pp->c)
				oddnodes =! oddnodes;
		}
	}
	return oddnodes;
}

bool redContains(ll r, ll c)
{
	string key = getKey(r, c);
	if(redDataCont.count(key) == 1) return true;
	return false;
}

bool greenContains(ll r, ll c)
{
	string key = getKey(r, c);
	if(greenData.count(key) == 1) return true;
	return false;
}

void readInput(const std::string &fileName)
{
	redData.clear();
	redDataCont.clear();
	greenData.clear();
	ReadFile inf(fileName);
	string ss;
	while(inf.readLine(ss))
	{
		if(ss.empty()) continue;
		std::vector<std::string> cols;
		Utils::tokenize(ss, ",", cols);
		if(cols.size() == 2)
		{
			ll row = stoll(cols[1]);
			ll col = stoll(cols[0]);
			redData.emplace_back(row, col);
			redDataCont.insert(getKey(row, col));
		}
	}
	inf.close();
}

void part1()
{
	ll answer1 = 0;
	for(int i = 0; i < redData.size(); i++)
	{
		for(int j = i + 1; j < redData.size(); j++)
		{
			ll ii = redData[i].rectSize(redData[j]);
			if(ii > answer1) answer1 = ii;
		}
	}
	cout << "PART1 answer = " << answer1 << endl;
}

void part2()
{
	ll answer2 = 0;

	for(int i = 0; i < redData.size(); i++)
	{
		Cell red1 = redData[i];
		Cell red2;
		if((i + 1) == redData.size())
			red2 = redData[0];
		else
			red2 = redData[i + 1];

		if(red1.r == red2.r)
		{
			int c1 = red1.c;
			int c2 = red2.c;
			if(c1 > c2)
			{
				c1 = red2.c;
				c2 = red1.c;
			}
			for(int j = c1 + 1; j < c2; j++)
				greenData.insert(getKey(red1.r, j));
		}
		else
		{
			int r1 = red1.r;
			int r2 = red2.r;
			if(r1 > r2)
			{
				r1 = red2.r;
				r2 = red1.r;
			}
			for(int j = r1 + 1; j < r2; j++)
				greenData.insert(getKey(j, red1.c));
		}
	}

	for(int i = 0; i < redData.size(); i++)
	{
		for(int j = i + 1; j < redData.size(); j++)
		{
			ll x1 = redData[i].c;
			ll y1 = redData[i].r;
			ll x2 = redData[j].c;
			ll y2 = redData[j].r;

			Cell p1(y1, x1);
			Cell p2(y1, x2);
			Cell p3(y2, x1);
			Cell p4(y2, x2);

			if(!pointin(&p1) && !redContains(p1.r, p1.c) && !greenContains(p1.r, p1.c))
				continue;
			if(!pointin(&p2) && !redContains(p2.r, p2.c) && !greenContains(p2.r, p2.c))
				continue;
			if(!pointin(&p3) && !redContains(p3.r, p3.c) && !greenContains(p3.r, p3.c))
				continue;
			if(!pointin(&p4) && !redContains(p4.r, p4.c) && !greenContains(p4.r, p4.c))
				continue;

			if(x1 > x2) { ll tmp = x1; x1 = x2; x2 = tmp; }
			if(y1 > y2) { ll tmp = y1; y1 = y2; y2 = tmp; }

			bool bad = false;
			for(ll xx = x1; xx < x2; xx++)
			{
				Cell point1(y1, xx);
				if(!pointin(&point1) && !redContains(y1, xx) && !greenContains(y1, xx))
				{
					bad = true;
					break;
				}
				Cell point2(y2, xx);
				if(!pointin(&point2) && !redContains(y2, xx) && !greenContains(y2, xx))
				{
					bad = true;
					break;
				}
			}
			if(bad) continue;
			for(ll yy = y1; yy < y2; yy++)
			{
				Cell point1(yy, x1);
				if(!pointin(&point1) && !redContains(yy, x1) && !greenContains(yy, x1))
				{
					bad = true;
					break;
				}
				Cell point2(yy, x2);
				if(!pointin(&point2) && !redContains(yy, x2) && !greenContains(yy, x2))
				{
					bad = true;
					break;
				}
			}
			if(!bad)
			{
				ll ii = redData[i].rectSize(redData[j]);
				if(ii > answer2) answer2 = ii;
			}
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
