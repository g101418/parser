#pragma once
#include <vector>
#include <string>
using std::vector;
using std::string;

class Controler;
class StackItem;

struct MatchItem
{
	vector<int> match_item;
};

struct SyntaxItem
{
	int id;
	int type;//0-普通，1-子程序，2-函数操作（如拆包）
	int val;
	string name;
	vector<MatchItem> match_table;//type=1不需要填
	int rearVal;
	void(*func)(Controler*, vector<StackItem*>&, SyntaxItem&);//type=2时调用,type=1时也调用
};

class Syntax
{
public:
	Syntax();
	~Syntax();

	void insert(int, int, int, string, vector<MatchItem>*, void(*func)(Controler*, vector<StackItem*>&, SyntaxItem&));

	vector<SyntaxItem> syntaxTables;
};