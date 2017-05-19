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

void Controler::merge(int num,int val,string name)//�ϲ���Ȼ�����һ����ʼ������ֻ��ָ���������¿�����Ϊ1-�ϲ���
{
	StackItem* newItem = new StackItem();
	newItem->type = 1;
	newItem->id = getId();
	newItem->val = val;
	newItem->name = name;

	for (vector<StackItem*>::reverse_iterator rit = curStack->stackItems.rbegin();
		rit != curStack->stackItems.rend(); rit++)//����ɾ��
	{
		if (num == 0)
			break;
		std::advance(rit, 1);
		newItem->subItems.push_back(rit.base());//����ɾ���Ŀ�ѹ��ϲ�����Ԫ�������ں��������﷨�����ӿ��˳��Ϊ���򣨴Ӵ�С��
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

int Controler::contrastSyntax()//�Ա��﷨��0-û��ƥ��ɹ���������ջ��1-���/���������2-�ɹ��ϲ�
{
	//main�������Ѿ�����block���˴������ٴ�����
	StackItem* curItem = curStack->stackItems.back();//��ȡ��ǰջ�����һ��item

	for (vector<SyntaxItem>::iterator it = syntaxs.syntaxTables.begin(); it != syntaxs.syntaxTables.end(); it++)
	{
		if (it->type == 1)//�����ж��ǲ���type=1�ӳ�������
		{
			if (it->rearVal == curItem->val)//ȷʵ��type=1
			{
				it->func(this, curStack->stackItems,*it);//begin/end
				return 0;
			}
		}
		else if (it->type == 0 || it->type == 2)//type=0����ͨ��
		{
			if (it->rearVal == curItem->val)
			{
				//�����ƽ��Աȣ������򵯳�
				vector<MatchItem>::reverse_iterator syn_rit = it->match_table.rbegin();//ƥ�������
				vector<StackItem*>::reverse_iterator stack_rit = curStack->stackItems.rbegin();//ջ�п飬����
				int ids_num = 0;//������Ҫ������id

				while (true)
				{
					bool isMatched = false;//��Щ���Զ��ƥ��
					
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
					if (syn_rit != it->match_table.rend() || stack_rit == curStack->stackItems.rend())//stack��ͷ��syntaxû��ͷ
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
							merge(ids_num, it->val, it->name);//�ϲ��������﷨���ж�Ӧ��val��name
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

void Controler::unpacking(int id)//Ҫ��֮����id
{
	for (vector<StackItem*>::reverse_iterator rit = curStack->stackItems.rbegin();
		rit != curStack->stackItems.rend(); rit++)//�����ҵ���Ӧid�Ŀ�
	{
		if ((*rit)->id == id)
		{
			vector<StackItem*>::reverse_iterator rrit = (*rit)->subItems.rbegin();//�ӿ�˳��Ϊ�Ӵ�id��Сid
			vector<StackItem*>::reverse_iterator rritend = (*rit)->subItems.rend();
			std::advance(rit, 1);
			for (; rrit != rritend; rrit++)//���β����ӿ�
			{
				std::advance(rrit, 1);
				curStack->stackItems.insert(rit.base(), rrit.base());
				std::advance(rrit, -1);
			}
			curStack->stackItems.erase(rit.base());//�����ӿ���ɣ�����ԭ�ϳɿ�
		}
	}
}

int Controler::getId()
{
	id++;
	return id;
}
