#include "DecoderOld.h"

std::string DecoderOld::find(std::map<std::string, unsigned short>& _map, unsigned short value) {
	for (auto it = _map.begin(); it != _map.end(); ++it)
		if (it->second == value)
			return it->first;
	return "";
}

void DecoderOld::Decode(const std::string& source, const std::string& target)
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

	int old_code = ReadCode(input); 
	int new_code;
	unsigned char character = old_code;
	output << (char)old_code;
	std::string s;
	int iteration = 0;
	while (input.peek() != EOF) {
		iteration++;
		printf("%i\n", iteration);
		new_code = ReadCode(input);
		std::string new_translation = find(dictionary, new_code);

		if (new_translation != "") {
			s = new_translation;
		}
		else {
			s = find(dictionary, old_code);
			s = s + (char)character;
		}
		output << s;
		character = s[0];
		dictionary.emplace(find(dictionary, old_code) + (char)character, dictionary.size());
		old_code = new_code;
	}
	input.close();
	output.close();
}

unsigned short DecoderOld::ReadCode(std::ifstream& input_stream)
{
	//not working, the last byte is wrong
	static unsigned char byte = (char)input_stream.get();
	
	unsigned char cutter = byte << (shift - 1);
	unsigned short temp = cutter << 1;
	byte = (char)input_stream.get();

	suffix = byte >> (8 - shift);

	
	shift += codeLength - 8;
	if (shift == codeLength) {
		shift = codeLength - 8;
		byte = input_stream.get();
	}
	return temp + suffix;
}

void DecoderOld::Reset()
{
	mask = (1 << (codeLength - 8)) - 1;
	suffix = 0;
	shift = codeLength - 8;
}

void DecoderOld::InitializeDictionaryASCII()
{
	dictionary.clear();
	for (int i = 0; i < 256; i++)
	{
		dictionary.emplace(std::make_pair(std::string(1, (char)i), (unsigned short)i));
	}
}
