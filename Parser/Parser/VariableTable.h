#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class VarItem
{
public:
	string name;
	int level;
	int row;
};

class VariableTable
{
public:
	VariableTable();
	~VariableTable();

	void insert(string name, int level, int row);
	bool check(string name, int level, int row);
private:
	vector<VarItem> varItems;
};

