#pragma once
#include "global.h"

class Coder
{
private: 
	int codeLength = 9;
	map<string, int> dictionary = map<string, int>();

	unsigned char mask = (1 << (codeLength - 8)) - 1;
	unsigned char suffix = 0;
	unsigned int shift = codeLength - 8;
public:
	void Code(const string& source, const string& target);
	void CodeNew(const string& source, const string& target);
	void WriteCode(unsigned short code, ofstream& outStream);
	void WriteCodeNew(unsigned short code, ofstream& outStream);
	void Reset();
	void InitializeDictionaryASCII();

	const map<string, int>& GetDict() {
		return dictionary;
	}
};

