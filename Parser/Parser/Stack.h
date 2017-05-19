#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class Stack;

class StackItem
{
public:
	int type;//0-��ͨblock��1-�ϲ���2-��ջ
	int id;
	string name;
	int val;//0,1,2
	int row;
	Stack* subStack;//��ջָ�룬2
	vector<StackItem*> subItems;//�ӿ�ָ�룬�ϲ�����,1
};

class Stack
{
public:
	Stack();
	~Stack();

	vector<StackItem*> stackItems;//��ջ�ڵ�������ͨ/�ϲ�/��ջ

	int beginRow;//��ʼ��
	string beginName;//��ʼ��
	int beginVal;//��ʼ����Ӧ����

	int endRow;//������
	string endName;//��ʼ��
	int endVal;//��ʼ����Ӧ����

	unsigned int level;//��ջ�ȼ�

	void insertItem(int type, int id, string name, int val, int row, Stack& subStack, vector<StackItem*>& subItems);
	void popItem(int id);
};

