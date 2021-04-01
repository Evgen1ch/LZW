#pragma once
#include "global.h"

class DecoderOld
{
private:
	int codeLength = BITS;
	std::map<std::string, unsigned short> dictionary = std::map<std::string, unsigned short>();

	unsigned char mask = (1 << (codeLength - 8)) - 1;
	unsigned char suffix = 0;
	unsigned int shift = codeLength - 8;
public:
	void Decode(const std::string& source, const std::string& target);
	unsigned short ReadCode(std::ifstream&);
	std::string find(std::map<std::string, unsigned short>& _map, unsigned short value);
	void Reset();
	void InitializeDictionaryASCII();
};

