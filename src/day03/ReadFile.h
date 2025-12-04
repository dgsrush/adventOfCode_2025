#pragma once

#include<string>
#include<fstream>

class ReadFile
{
public:
	ReadFile(const std::string &flname);
	~ReadFile();
	bool readLine(std::string &);
	void close();
	bool isOk();
	bool isEof();

private:
	std::string filename;
	std::ifstream inf;
	bool ok;
};
