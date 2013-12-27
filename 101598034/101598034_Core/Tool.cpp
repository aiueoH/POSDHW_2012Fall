#include "Tool.h"

Tool::Tool(void)
{
}


Tool::~Tool(void)
{
}

string Tool::trim(string str)
{
	if (str.length() == 0)
		return str;

	unsigned int indexStart = 0, indexEnd = 0;
	for (unsigned int i = 0; i < str.length(); i++)
		if (str[i] != ' ')
		{
			indexStart = i;
			break;
		}
	for (unsigned int i = str.length() - 1; i >= indexStart; i--)
		if (str[i] != ' ')
		{
			indexEnd = i;
			break;
		}
	return str.substr(indexStart, indexEnd - indexStart + 1);
	
}

vector<string> Tool::splitStringToVector(string str, string c)
{
	vector<string> strs;
	unsigned int index = str.find(c);
	while (index != -1) // -1 �O�S���F��ɪ��^�ǭ�
	{
		if (index != 0) // c ���b�Ĥ@�� �N�����Ŧr�� �i�s�J
			strs.push_back(Tool::trim(str.substr(0, index)));
		if (str.length() > index + 1) // c �����٦��r��
			str = str.substr(index + 1); // �N c ���e���r��R��(�]�tc�]�R��)
		else // c �᭱�S���r��
			break;
		index = str.find(c); // ��U�@��
	}
	if (str != "")
		strs.push_back(Tool::trim(str)); 
	return strs;
}

string Tool::charToString(char c)
{
	return string(1, c);
}

char Tool::stringToChar(string str)
{
	return str[0];
}

string Tool::intToString(int i)
{
	stringstream ss;
	ss << i;
	return ss.str();
}