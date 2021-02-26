#pragma once
#include "global.h"

class Decoder
{
private:
	static const int _BITS = BITS;
	static std::map<std::string, unsigned short> dictionary;

	static unsigned char mask;
	static unsigned char suffix;
	static unsigned int shift;
public:
	static void Decode(const std::string& source, const std::string& target);
	static unsigned short ReadCode(std::ifstream&);
	static std::string find(std::map<std::string, unsigned short>& _map, unsigned short value);
	static void Reset();
	static void InitializeDictionaryASCII();
};

