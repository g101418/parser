#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class Stack;

class StackItem
{
public:
	int type;//0-普通block，1-合并后，2-子栈
	int id;
	string name;
	int val;//0,1,2
	int row;
	Stack* subStack;//子栈指针，2
	vector<StackItem*> subItems;//子块指针，合并后用,1
};

class Stack
{
public:
	Stack();
	~Stack();

	vector<StackItem*> stackItems;//本栈内的所有普通/合并/子栈

	int beginRow;//开始行
	string beginName;//开始符
	int beginVal;//开始符对应代码

	int endRow;//结束行
	string endName;//开始符
	int endVal;//开始符对应代码

	unsigned int level;//该栈等级

	void insertItem(int type, int id, string name, int val, int row, Stack& subStack, vector<StackItem*>& subItems);
	void popItem(int id);
};

