#include "Syntax.h"


Syntax::Syntax()
{
}


Syntax::~Syntax()
{
}

void Syntax::insert(int id,int type,int val,string name,vector<MatchItem>* matchItem
	,void(*func)(Controler*,vector<StackItem*>&, SyntaxItem&))
{
	SyntaxItem* newItem = new SyntaxItem();
	newItem->id = id;
	newItem->type = type;
	newItem->val = val;
	newItem->name = name;
	for (vector<MatchItem>::iterator it = matchItem->begin(); it != matchItem->end(); it++)
	{
		vector<int>* newInts = new vector<int>;
		for (vector<int>::iterator ite = (*it).match_item.begin(); ite != (*it).match_item.end(); ite++)
		{
			newInts->push_back(*ite);
		}
		if (!newInts->empty())
		{
			newItem->match_table.push_back(newInts);
		}
	}
	newItem->func = func;
	newItem->rearVal = newItem->match_table.back().match_item.back();

	syntaxTables.push_back(newItem);
}
