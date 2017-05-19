#pragma once
#include "Stack.h"
#include "Syntax.h"
#include "Error.h"
#include "VariableTable.h"
#include "LoadBlock.h"
#include <stack>
#include <iostream>
#include <fstream>
using std::stack;

class Controler
{
public:
	Controler();
	~Controler();

	stack<Stack*>* currentStacks;//当前处理栈的栈
	stack<Stack*>* allStacks;//全部栈
	VariableTable variables;//变量表
	Syntax syntaxs;//语法表
	Error errors;//错误表

	Stack* curStack;//当前处理的那一个栈
	//LoadBlock curBlock;//当前处理的块
	int curLevel;//当前栈的等级
	int curRow;//当前行
	unsigned int id;//各块的id，用于寻址

	string path;//文件路径

	bool LoadInBlock();

	void popPack_order(int id);
	void popPack_reverse(int id);
	void unpacking(int id);//拆包，操作性函数
	void merge(int num,int val,string name);//合并，操作性函数
	void pushSubStack(int val, string name,int row);//插入子程序（栈）
	void leaveSubStack(int val, string name, int row);//离开当前子栈

	int contrastSyntax();//对比语法，0-没有匹配成功或生成子栈，1-拆包，2-成功合并
	void contrastError();//对比错误表报错，1.子程序完备 2.变量合法（有无重复定义） 3.语法

	int getId();
};

