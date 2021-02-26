#include "Decoder.h"
std::map<std::string, unsigned short> Decoder::dictionary = std::map<std::string, unsigned short>();
unsigned char Decoder::mask = (1 << (_BITS - 8)) - 1;
unsigned char Decoder::suffix = 0;
unsigned int Decoder::shift = _BITS - 8;


std::string Decoder::find(std::map<std::string, unsigned short>& _map, unsigned short value) {
	for (auto it = _map.begin(); it != _map.end(); ++it)
		if (it->second == value)
			return it->first;
	return "";
}

void Decoder::Decode(const std::string& source, const std::string& target)
{
	InitializeDictionaryASCII();
	std::ifstream input(source);
	std::ofstream output(target);

	if (!input || !output) {
		input.close();
		output.close();
		return;
	}

	//if file is empty return
	if (!input.seekg(0, std::ios::end).tellg()) {
		input.close();
		output.close();
		return;
	}

	input.seekg(0);

	int old_code = ReadCode(input); 
	int new_code;
	unsigned char character = old_code;
	output << (char)old_code;
	std::string s;

	while (input.peek() != EOF) {
		
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

unsigned short Decoder::ReadCode(std::ifstream& input_stream)
{
	//not working, the last byte is wrong
	static unsigned char byte = (char)input_stream.get();
	
	unsigned char cutter = byte << (shift - 1);
	unsigned short temp = cutter << 1;
	input_stream >> byte;

	suffix = byte >> (8 - shift);

	
	shift += _BITS - 8;
	if (shift == _BITS) {
		shift = _BITS - 8;
		input_stream >> byte;
	}
	return temp + suffix;
}

void Decoder::Reset()
{
	mask = (1 << (_BITS - 8)) - 1;
	suffix = 0;
	shift = _BITS - 8;
}

void Decoder::InitializeDictionaryASCII()
{
	dictionary.clear();
	for (unsigned char i = 0; i < UCHAR_MAX; i++)
	{
		dictionary.emplace(std::make_pair(std::string(1, (char)i), (unsigned short)i));
	}
	dictionary.emplace(std::make_pair(std::string(1, (char)0xff), (unsigned short)0xff));
}
