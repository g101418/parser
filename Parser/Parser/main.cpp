#include "Controler.h"

Controler controler;

void init();

int main()
{
	init();//初始化

	///处理语法合并
	while (true)
	{
		if (controler.LoadInBlock() == false)//加载block
			break;

		while (controler.contrastSyntax() != 0);//0-没有匹配成功或生成子栈，1-拆包/插入变量，2-成功合并
	}

	///处理错误
	controler.contrastError();

	return 0;
}

void init()
{
	Controler controler;
	controler.path = "example.aaa";//确定读入文件路径及名称

	vector<MatchItem>* newBeginMatchItem = new vector<MatchItem>();
	MatchItem* newBeginMatchInt = new MatchItem;

	newBeginMatchInt->match_item.push_back(10);//先假设begin是10
	newBeginMatchItem->push_back(newBeginMatchInt);
	void(*beginFunc)(Controler*, vector<StackItem*>&, SyntaxItem&);

	controler.syntaxs.insert(1, 1, -1, "begin", newBeginMatchItem, beginFunc);
}

void beginFunc(Controler* controler, vector<StackItem*>& stackItems, SyntaxItem& ths)
{
	controler->curStack->stackItems.pop_back();//弹出最后一块
	controler->pushSubStack(ths.val, ths.name, controler->curRow);
}