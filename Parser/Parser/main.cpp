#include "Controler.h"

Controler controler;

void init();

int main()
{
	init();//��ʼ��

	///�����﷨�ϲ�
	while (true)
	{
		if (controler.LoadInBlock() == false)//����block
			break;

		while (controler.contrastSyntax() != 0);//0-û��ƥ��ɹ���������ջ��1-���/���������2-�ɹ��ϲ�
	}

	///�������
	controler.contrastError();

	return 0;
}

void init()
{
	Controler controler;
	controler.path = "example.aaa";//ȷ�������ļ�·��������

	vector<MatchItem>* newBeginMatchItem = new vector<MatchItem>();
	MatchItem* newBeginMatchInt = new MatchItem;

	newBeginMatchInt->match_item.push_back(10);//�ȼ���begin��10
	newBeginMatchItem->push_back(newBeginMatchInt);
	void(*beginFunc)(Controler*, vector<StackItem*>&, SyntaxItem&);

	controler.syntaxs.insert(1, 1, -1, "begin", newBeginMatchItem, beginFunc);
}

void beginFunc(Controler* controler, vector<StackItem*>& stackItems, SyntaxItem& ths)
{
	controler->curStack->stackItems.pop_back();//�������һ��
	controler->pushSubStack(ths.val, ths.name, controler->curRow);
}