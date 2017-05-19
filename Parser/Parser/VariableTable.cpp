#include "VariableTable.h"


VariableTable::VariableTable()
{
}


VariableTable::~VariableTable()
{
}

void VariableTable::insert(string name, int level, int row)
{
	VarItem* item = new VarItem();
	item->name = name;
	item->level = level;
	item->row = row;

	varItems.push_back(item);
}

bool VariableTable::check(string name, int level, int row)
{
	for (vector<VarItem>::iterator it = varItems.begin(); it != varItems.end(); it++)
	{
		if (name == it->name && level >= it->level&&row >= it->row)
			return true;
	}
	return false;
}
