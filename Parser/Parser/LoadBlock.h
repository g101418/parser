#pragma once
#include <string>
using std::string;
class LoadBlock
{
public:
	string name;//��ȡ�Ŀ�ķ��ţ�����
	int val;//��ȡ�Ŀ�ı�ʶ

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