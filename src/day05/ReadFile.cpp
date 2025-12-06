#include"ReadFile.h"

ReadFile::ReadFile(const std::string &flname) : filename(flname)
{
	ok = true;
	inf.open(filename, std::ios::in);
	if(!inf.good()) ok = false;
	if(inf.fail()) ok = false;
}

ReadFile::~ReadFile()
{
	inf.close();
}

bool ReadFile::isOk()
{
	return ok;
}

bool ReadFile::isEof()
{
	return inf.eof();
}

//returns true if not EOF
bool ReadFile::readLine(std::string &ss)
{
	ss.clear();
	if(!ok) return false;
	if(inf.eof()) return false;
	std::getline(inf, ss);
	return true;
}

void ReadFile::close()
{
	inf.close();
}
