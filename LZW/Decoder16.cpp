#include "Decoder16.h"

void Decoder16::Decode(const std::string& source, const std::string& target)
{
	InitializeDictionaryASCII();
	std::ifstream input(source, std::ios::binary);
	std::ofstream output(target, std::ios::binary);

	if (!input || !output) {
		input.close();
		output.close();
		return;
	}

	if (input.peek() == EOF) return;

	int prev = -1;
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
		/*if (new_code == dictionary.size()) {

		}
		else {

		}*/
		std::string new_translation = dictionary.find(new_code)->second;

		if (new_translation != "") {
			s = new_translation;
		}
		else {
			s = dictionary.find(old_code)->second;
			s = s + (char)character;
		}
		output << s;
		character = s[0];
		dictionary.emplace(dictionary.size(), dictionary.find(old_code)->second + (char)character);
		old_code = new_code;
	}

	input.close();
	output.close();
}

int Decoder16::ReadCode(std::ifstream& input_stream)
{
	unsigned short result;
	input_stream.read((char*)&result, sizeof(short));
	return (int)result;
}

void Decoder16::Reset()
{
}

void Decoder16::InitializeDictionaryASCII()
{
	dictionary.clear();
	for (unsigned char i = 0; i < UCHAR_MAX; i++)
	{
		dictionary.emplace(std::make_pair((unsigned short)i, std::string(1, (char)i)));
	}
	dictionary.emplace(std::make_pair((unsigned short)0xff, std::string(1, (char)0xff)));
}
