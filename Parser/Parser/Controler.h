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

	stack<Stack*>* currentStacks;//��ǰ����ջ��ջ
	stack<Stack*>* allStacks;//ȫ��ջ
	VariableTable variables;//������
	Syntax syntaxs;//�﷨��
	Error errors;//�����

	Stack* curStack;//��ǰ�������һ��ջ
	//LoadBlock curBlock;//��ǰ����Ŀ�
	int curLevel;//��ǰջ�ĵȼ�
	int curRow;//��ǰ��
	unsigned int id;//�����id������Ѱַ

	string path;//�ļ�·��

	bool LoadInBlock();

	void popPack_order(int id);
	void popPack_reverse(int id);
	void unpacking(int id);//����������Ժ���
	void merge(int num,int val,string name);//�ϲ��������Ժ���
	void pushSubStack(int val, string name,int row);//�����ӳ���ջ��
	void leaveSubStack(int val, string name, int row);//�뿪��ǰ��ջ

	int contrastSyntax();//�Ա��﷨��0-û��ƥ��ɹ���������ջ��1-�����2-�ɹ��ϲ�
	void contrastError();//�Աȴ������1.�ӳ����걸 2.�����Ϸ��������ظ����壩 3.�﷨

	int getId();
};

