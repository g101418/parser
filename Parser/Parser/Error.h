#pragma once
#include <vector>
#include <string>
using std::vector;
using std::string;

struct ErrorItem
{
	int id;
	vector<int> match_table;
	int minLength;//-ÎÞÏÞÖÆ
	int maxLength;
	int headVal;
	string description;
};

class Error
{
public:
	Error();
	~Error();

	void insert(vector<ErrorItem>& item);

	vector<ErrorItem*> errorTables;
};

