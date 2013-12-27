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
	while (index != -1) // -1 是沒找到東西時的回傳值
	{
		if (index != 0) // c 不在第一個 代表不為空字串 可存入
			strs.push_back(Tool::trim(str.substr(0, index)));
		if (str.length() > index + 1) // c 之後還有字串
			str = str.substr(index + 1); // 將 c 之前的字串刪掉(包含c也刪掉)
		else // c 後面沒有字串
			break;
		index = str.find(c); // 找下一個
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