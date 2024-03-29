#include "Decoder.h"

void Decoder::Decode(const string& source, const string& target)
{
	InitializeDictionaryASCII();
	std::ifstream input(source, std::ios::binary);
	std::ofstream output(target, std::ios::binary);

	if (!input || !output) {
		input.close();
		output.close();
		return;
	}

	//if file is empty return
	if (input.peek() == EOF) {
		input.close();
		output.close();
		return;
	}

	int oldCode = ReadCode(input);
	int newCode;
	unsigned char character = oldCode;
	output.write((char*)&character, 1);

	int counter = 0;
	while (input.peek() != EOF)
	{
		newCode = ReadCode(input);
		auto it = dictionary.find(newCode);

		string translation;
		if (it != dictionary.end()) { // ���� � �������
			translation = it->second;
		}
		else { //��� � �������
			auto itt = dictionary.find(oldCode);			
			translation = itt->second;
			translation += (char)character;
		}

		output.write(translation.c_str(), translation.length());
		character = translation[0];
		auto oldCodeTranslation = dictionary.find(oldCode);
		string newEntry = oldCodeTranslation->second + (char)character;
		dictionary.insert(make_pair(dictionary.size(), newEntry));
		if (dictionary.size() == 4095) {
			newCode = ReadCode(input);
			auto tr = dictionary.find(newCode)->second;
			output.write(tr.c_str(), tr.length());
			codeLength = 9;
			InitializeDictionaryASCII();
			newCode = ReadCode(input);
			character = newCode;
			output.write((char*)&character, 1);
		}
		if (dictionary.size() + 1 == (1 << codeLength)) {
			codeLength++;
		}
		
		oldCode = newCode;
		
	}
	input.close();
	output.close();

	dictionary.clear();
}

int Decoder::ReadCode(ifstream& inputStream)
{
	static unsigned bit_buffer = 0;
	static int bits_read = 0;

	int result = 0;

	while (bits_read <= codeLength) 
	{
		auto a = (unsigned)inputStream.get();
		bit_buffer |=  a << (24 - bits_read);
		bits_read += 8;
	}

	result = bit_buffer >> (32 - codeLength);
	bit_buffer <<= codeLength;
	bits_read -= codeLength;
	return result;
}

void Decoder::InitializeDictionaryASCII()
{
	dictionary.clear();
	for (int i = 0; i < 256; i++)
	{
		dictionary.emplace(i, string(1, (char)i));
	}
}
