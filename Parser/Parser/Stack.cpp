#include "Stack.h"


Stack::Stack()
{
}


Stack::~Stack()
{
}

void Stack::insertItem(int type, int id, string name, int val, int row, Stack & subStack, vector<StackItem*>& subItems)
{
	StackItem* newItem = new StackItem();
	newItem->id = id;
	newItem->type = type;
	newItem->name = name;
	newItem->val = val;
	newItem->subStack = &subStack;
	newItem->subItems = subItems;
	stackItems.push_back(newItem);
}

void Stack::popItem(int id)
{
	for (vector<StackItem*>::reverse_iterator rit = stackItems.rbegin(); rit != stackItems.rend(); rit++)
	{
		if ((*rit)->id == id)
		{
			std::advance(rit, 1);
			stackItems.erase(rit.base());
			return ;
		}
	}
}
