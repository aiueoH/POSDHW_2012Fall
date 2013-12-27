#ifndef TOOL_H_
#define TOOL_H_

#include "Globle.h"

#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Tool
{
public:
	Tool(void);
	~Tool(void);

	// 刪除string中頭尾空白
	static string trim(string str);
	// 切割字串
	static vector<string> splitStringToVector(string str, string c);
	// char 轉換成長度 1 的 string
	static string charToString(char c);
	// 長度 1 的 string 轉換成 char
	static char stringToChar(string str);
	static string intToString(int i);
	// 合併兩 vector (逼不得已寫在 .h ， template 分開寫會 link error)
	template <typename T>
	static vector<T> mergeVector(vector<T> vectorA, vector<T> vectorB)
	{
		vector <T> vectorTmp = vectorA;
		vectorTmp.reserve(vectorA.size() + vectorB.size());
		vectorTmp.insert(vectorTmp.end(), vectorB.begin(), vectorB.end());
		return vectorTmp;
	}
};

#endif
