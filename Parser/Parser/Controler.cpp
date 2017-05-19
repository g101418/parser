#include "Controler.h"



Controler::Controler():curLevel(0),curRow(1),id(1),curStack(NULL)
{
}


Controler::~Controler()
{
}

bool Controler::LoadInBlock()
{
	std::ifstream fin(path);
	string name, sval;
	fin >> name >> sval;
	int val = std::stoi(sval);

	if (curStack == NULL)
	{
		Stack* newStack = new Stack();
		newStack->level = 0;
		newStack->beginName = "start";
		newStack->beginRow = 0;

		currentStacks->push(newStack);
		allStacks->push(newStack);
		curStack = currentStacks->top();
	}

	StackItem* newStackItem = new StackItem();
	newStackItem->id = getId();
	newStackItem->name = name;
	newStackItem->row = curRow;
	newStackItem->type = 0;
	newStackItem->val = val;
	curStack->stackItems.push_back(newStackItem);

	return false;
}

void Controler::popPack_order(int id)
{
	for (vector<StackItem*>::iterator it = curStack->stackItems.begin(); it != curStack->stackItems.end(); it++)
	{
		if((*it)->id==id)
		{
			curStack->stackItems.erase(it);
			return;
		}
	}
}

void Controler::popPack_reverse(int id)
{
}

void Controler::merge(int num,int val,string name)//合并必然从最后一个开始，所以只需指定数量，新块类型为1-合并后
{
	StackItem* newItem = new StackItem();
	newItem->type = 1;
	newItem->id = getId();
	newItem->val = val;
	newItem->name = name;

	for (vector<StackItem*>::reverse_iterator rit = curStack->stackItems.rbegin();
		rit != curStack->stackItems.rend(); rit++)//倒序删除
	{
		if (num == 0)
			break;
		std::advance(rit, 1);
		newItem->subItems.push_back(rit.base());//即将删除的块压入合并后块的元素中用于后期生成语法树，子块的顺序为倒序（从大到小）
		curStack->stackItems.erase(rit.base());
		std::advance(rit, -1);
		num--;
		break;
	}
	curStack->stackItems.push_back(newItem);
}

void Controler::pushSubStack(int val,string name,int row)
{
	Stack* newStack = new Stack();
	(*newStack).beginVal = val;
	(*newStack).beginName = name;
	(*newStack).beginRow = row;
	curLevel++;
	(*newStack).level = curLevel;

	StackItem* newItem = new StackItem();
	newItem->id = getId();
	newItem->type = 2;
	newItem->name = name;
	newItem->row = row;
	newItem->val = val;
	newItem->subStack = newStack;

	curStack->stackItems.push_back(newItem);

	currentStacks->push(newStack);
	allStacks->push(newStack);
	curStack = currentStacks->top();
}

void Controler::leaveSubStack(int val, string name, int row)
{
	curStack->endVal = val;
	curStack->endName = name;
	curStack->endRow = row;

	curLevel--;

	currentStacks->pop();
	curStack = currentStacks->top();
}

int Controler::contrastSyntax()//对比语法，0-没有匹配成功或生成子栈，1-拆包/插入变量，2-成功合并
{
	//main函数中已经载入block，此处无需再次载入
	StackItem* curItem = curStack->stackItems.back();//获取当前栈中最后一个item

	for (vector<SyntaxItem>::iterator it = syntaxs.syntaxTables.begin(); it != syntaxs.syntaxTables.end(); it++)
	{
		if (it->type == 1)//首先判断是不是type=1子程序类型
		{
			if (it->rearVal == curItem->val)//确实是type=1
			{
				it->func(this, curStack->stackItems,*it);//begin/end
				return 0;
			}
		}
		else if (it->type == 0 || it->type == 2)//type=0，普通块
		{
			if (it->rearVal == curItem->val)
			{
				//交替推进对比，出错则弹出
				vector<MatchItem>::reverse_iterator syn_rit = it->match_table.rbegin();//匹配表，倒序
				vector<StackItem*>::reverse_iterator stack_rit = curStack->stackItems.rbegin();//栈中块，倒序
				int ids_num = 0;//保留将要弹出的id

				while (true)
				{
					bool isMatched = false;//有些可以多个匹配
					
					for (vector<int>::iterator it = syn_rit->match_item.begin();
						it != syn_rit->match_item.begin(); it++)
						if ((*it) == (*stack_rit)->val)//
						{
							isMatched = true;
							break;
						}

					ids_num++;
					syn_rit++;
					stack_rit++;

					if (isMatched == false)
						break;
					if (syn_rit != it->match_table.rend() || stack_rit == curStack->stackItems.rend())//stack到头，syntax没到头
						break;
					if (syn_rit == it->match_table.rend() && isMatched == true)
					{
						if (it->type == 2)
						{
							it->func(this, curStack->stackItems,*it);
							return 1;
						}
						else
						{
							merge(ids_num, it->val, it->name);//合并，传入语法表中对应的val与name
							return 2;
						}
					}
				}
			}
		}
	}

	return 0;
}

void Controler::contrastError()
{

}

void Controler::unpacking(int id)//要拆之包的id
{
	for (vector<StackItem*>::reverse_iterator rit = curStack->stackItems.rbegin();
		rit != curStack->stackItems.rend(); rit++)//用来找到对应id的块
	{
		if ((*rit)->id == id)
		{
			vector<StackItem*>::reverse_iterator rrit = (*rit)->subItems.rbegin();//子块顺序为从大id到小id
			vector<StackItem*>::reverse_iterator rritend = (*rit)->subItems.rend();
			std::advance(rit, 1);
			for (; rrit != rritend; rrit++)//依次插入子块
			{
				std::advance(rrit, 1);
				curStack->stackItems.insert(rit.base(), rrit.base());
				std::advance(rrit, -1);
			}
			curStack->stackItems.erase(rit.base());//插入子块完成，弹出原合成块
		}
	}
}

int Controler::getId()
{
	id++;
	return id;
}
