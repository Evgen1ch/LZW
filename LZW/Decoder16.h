#pragma once
#include "global.h"

class Decoder16
{
private:
	std::map<int, std::string> dictionary;
public:
	void Decode(const std::string& source, const std::string& target);
	int ReadCode(std::ifstream&);
	void Reset();
	void InitializeDictionaryASCII();
};

