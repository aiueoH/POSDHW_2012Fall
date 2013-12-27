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

	// �R��string���Y���ť�
	static string trim(string str);
	// ���Φr��
	static vector<string> splitStringToVector(string str, string c);
	// char �ഫ������ 1 �� string
	static string charToString(char c);
	// ���� 1 �� string �ഫ�� char
	static char stringToChar(string str);
	static string intToString(int i);
	// �X�֨� vector (�G���o�w�g�b .h �A template ���}�g�| link error)
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
