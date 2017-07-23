
#ifndef CSVPROCESSOR_H
#define CSVPROCESSOR_H

#include <vector>
#include <string>
#include <fstream>
using namespace std;

#include "..\\BasicModule\\constant.h"

const int PATHLENGTH=128;

class CSVLine : public vector<string>
{
public:
	bool read(istream & file);
	void write(ostream & file);
};

class CSVData : public vector<CSVLine>
{
public:
	void read(istream & file);
	void write(ostream & file);
};

#endif//CSVPROCESSOR_H