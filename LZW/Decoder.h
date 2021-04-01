#pragma once
#include "global.h"

class Decoder
{
private:
	int codeLength = 9;
	map<int, string> dictionary = map<int, string>();

public:
	void Decode(const string& source, const string& target);
	int ReadCode(ifstream& inputStream);
	void InitializeDictionaryASCII();

	const map<int, string>& GetDict() {
		return dictionary;
	}
};

