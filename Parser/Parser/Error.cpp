#include "Error.h"


Error::Error()
{
}


Error::~Error()
{
}

void Error::insert(vector<ErrorItem>& item)
{
	errorTables.push_back(item);
}

