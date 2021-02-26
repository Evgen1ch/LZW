#pragma once
#include "global.h"
class Coder
{
private: 
	static const int _BITS = BITS;
	static std::map<std::string, unsigned short> dictionary;

	static unsigned char mask;
	static unsigned char suffix;
	static unsigned int shift;
	
public:
	static void Code(const std::string& source, const std::string& target);
	static void WriteCode(unsigned short code, std::ofstream& out_stream);
	static void Reset();
	static void InitializeDictionaryASCII();
};

