#pragma once
#include <string>
using std::string;
class LoadBlock
{
public:
	string name;//读取的块的符号，名字
	int val;//读取的块的标识

	LoadBlock& operator=(const LoadBlock& block)
	{
		this->name = block.name;
		this->val = block.val;
		return *this;
	}
	bool operator==(const LoadBlock& block)const
	{
		if (this->name == block.name && this->val == block.val)
			return true;
		else
			return false;
	}
};