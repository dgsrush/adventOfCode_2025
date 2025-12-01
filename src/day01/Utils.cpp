#include"Utils.h"
#include<algorithm>
#include<cstdio>
#include<io.h>
#include<iostream>
#include<sys/stat.h>
#include<dirent.h>
#include<functional>

std::string Utils::toString(int i)
{
	char buf[100];
	snprintf(buf, 100, "%d", i);
	std::string ss(buf);
	return ss;
}

std::string Utils::toString(unsigned int i)
{
	char buf[100];
	snprintf(buf, 100, "%d", i);
	std::string ss(buf);
	return ss;
}

std::string Utils::toString(long lng)
{
	char buf[100];
	snprintf(buf, 100, "%ld", lng);
	std::string ss(buf);
	return ss;
}

std::string Utils::toString(unsigned long lng)
{
	char buf[100];
	snprintf(buf, 100, "%ld", lng);
	std::string ss(buf);
	return ss;
}

std::string Utils::toString(unsigned long long lng)
{
	char buf[100];
	snprintf(buf, 100, "%ld", lng);
	std::string ss(buf);
	return ss;
}

std::string Utils::toString(float f)
{
	char buf[100];
	snprintf(buf, 100, "%.2f", f);
	std::string ss(buf);
	return ss;
}

std::string Utils::toString(double d)
{
	char buf[100];
	snprintf(buf, 100, "%.2f", d);
	std::string ss(buf);
	return ss;
}

std::string Utils::toString(char c)
{
	char buf[2];
	buf[0] = c;
	buf[1] = 0;
	std::string ss(buf);
	return ss;
}

//////////////////////////////////////////////////

void Utils::replaceAll(std::string &sstr, const std::string &from, const std::string &to)
{
	if(from.empty()) return;
	std::string wsRet;
	wsRet.reserve(sstr.length());
	size_t start_pos = 0, pos;
	while((pos = sstr.find(from, start_pos)) != std::string::npos)
	{
		wsRet += sstr.substr(start_pos, pos - start_pos);
		wsRet += to;
		pos += from.length();
		start_pos = pos;
	}
	wsRet += sstr.substr(start_pos);
	sstr.swap(wsRet);
}

//////////////////////////////////////////////////

void Utils::tokenize(const std::string &str, const std::string &delims, std::vector<std::string> &ll, bool returnDelims)
{
	ll.clear();
	std::string tok("");
	int len = str.length();
	for(int i = 0; i < len; i++)
	{
		std::string chr = toString(str[i]);
		if(delims.find(chr) != std::string::npos)
		{
			if(tok.length() > 0)
			{
				ll.push_back(tok);
				tok = "";
			}
			if(returnDelims)
				ll.push_back(chr);
		}
		else
			tok += chr;
	}
	if(tok.length() > 0)
		ll.push_back(tok);
}

void Utils::tokenizeInt(const std::string &str, const std::string &delims, std::vector<int> &output, bool returnDelims)
{
	std::vector<std::string> ll;
	tokenize(str, delims, ll, returnDelims);
	for(std::string ss : ll)
		output.push_back(std::stoi(ss));
}

void Utils::tokenizeLong(const std::string &str, const std::string &delims, std::vector<long> &output, bool returnDelims)
{
	std::vector<std::string> ll;
	tokenize(str, delims, ll, returnDelims);
	for(std::string ss : ll)
		output.push_back(std::stol(ss));
}

//////////////////////////////////////////////////

bool Utils::startsWith(const std::string &inp, const std::string &start)
{
	if(inp.find(start) == 0) return true;
	return false;
}

bool Utils::endsWith(const std::string &inp, const std::string &end)
{
	int pos = inp.length() - end.length();
	if(pos < 0) return false;
	int fnd = inp.rfind(end);
	if(fnd == pos) return true;
	return false;
}

std::string Utils::toUpperCase(const std::string &inp)
{
	std::string ss(inp);
	std::transform(ss.begin(), ss.end(), ss.begin(), ::toupper);
	return ss;
}

std::string Utils::toLowerCase(const std::string &inp)
{
	std::string ss(inp);
	std::transform(ss.begin(), ss.end(), ss.begin(), ::tolower);
	return ss;
}

bool Utils::equalsIgnoreCase(const std::string &s1, const std::string &s2)
{
	std::string ss1(s1);
	std::string ss2(s2);
	ss1 = toLowerCase(ss1);
	ss2 = toLowerCase(ss2);
	return ss1 == ss2;
}

std::string Utils::trim(const std::string &s)
{
	return ltrim(rtrim(s));
}

std::string Utils::ltrim(const std::string &ss)
{
	std::string s(ss);
	std::function<bool(unsigned char c)> is = Utils::isSpace;
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not_fn(is)));
	return s;
}

std::string Utils::rtrim(const std::string &ss)
{
	std::string s(ss);
	std::function<bool(unsigned char c)> is = Utils::isSpace;
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not_fn(is)).base(), s.end());
	return s;
}

int Utils::indexOf(const std::string &inp, const std::string &fnd)
{
	return inp.find(fnd);
}

bool Utils::contains(const std::string &inp, const std::string &fnd)
{
	if(indexOf(inp, fnd) >= 0) return true;
	return false;
}

bool Utils::isSpace(unsigned char c)
{
	if(c == ' ') return true;
	return false;
}

void Utils::removeAllSpaces(std::string &s)
{
	s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
}

std::string & Utils::digitToString(int i)
{
	static std::array<std::string,10> strValues={"","1","2","3","4","5","6","7","8","9"};
	return strValues[i];
}

char Utils::digitToChar(int i)
{
	static std::array<char,10> strValues={'0','1','2','3','4','5','6','7','8','9'};
	return strValues[i];
}

int Utils::charToDigit(char c)
{
	char buf[2];
	buf[0] = c;
	buf[1] = 0;
	return atoi(buf);
}
