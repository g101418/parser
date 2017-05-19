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
	int type;//0-��ͨ��1-�ӳ���2-����������������
	int val;
	string name;
	vector<MatchItem> match_table;//type=1����Ҫ��
	int rearVal;
	void(*func)(Controler*, vector<StackItem*>&, SyntaxItem&);//type=2ʱ����,type=1ʱҲ����
};

class Syntax
{
public:
	Syntax();
	~Syntax();

	void insert(int, int, int, string, vector<MatchItem>*, void(*func)(Controler*, vector<StackItem*>&, SyntaxItem&));

	vector<SyntaxItem> syntaxTables;
};