#pragma once
#include "global.h"

class Coder16
{
private:
	std::map<std::string, int> dictionary;
public:
	void Code(const std::string& source, const std::string& target);
	void WriteCode(int code, std::ofstream& out_stream);
	void Reset();
	void InitializeDictionaryASCII();
};

