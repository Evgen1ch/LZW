#include "Coder.h"
std::map<std::string, unsigned short> Coder::dictionary = std::map<std::string, unsigned short>();
unsigned char Coder::mask = (1 << (_BITS - 8)) - 1;
unsigned char Coder::suffix = 0;
unsigned int Coder::shift = _BITS - 8;

void Coder::Code(const std::string& source, const std::string& target)
{
	//wtf? it works without initialization of dictionary
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
	char a;
	input >> a;
	std::string w(1, a);
	unsigned short code = a;

	while (!input.eof()) {

		input >> a;
		std::string wa = w + a;

		auto it = dictionary.find(wa);
		if (it != dictionary.end()) {
			w = wa;
			code = it->second;
		}
		else {
			dictionary.emplace(wa, dictionary.size());
			w = a;
			WriteCode(code, output);
			code = a;
		}
	}
	//the "tail" of message
	output << (char)(suffix << (BITS - shift));
	input.close();
	output.close();
}

void Coder::InitializeDictionaryASCII()
{
	dictionary.clear();
	for (unsigned char i = 0; i < UCHAR_MAX; i++)
	{
		dictionary.emplace(std::make_pair(std::string(1, (char)i), (unsigned short)i));
	}
	dictionary.emplace(std::make_pair(std::string(1, (char)0xff), (unsigned short)0xff));
}

void Coder::WriteCode(unsigned short code, std::ofstream& out_stream)
{
	unsigned char temp = static_cast<char>(code >> shift);
	out_stream << (char)(temp | (suffix << (BITS - shift)));
	shift += BITS - 8;

	suffix = (char)mask & static_cast<char>(code);
	mask = static_cast<unsigned char>(mask << (BITS - 8)) + ((1 << (BITS - 8)) - 1);
	if (shift == BITS) {
		shift = BITS - 8;
		mask = (1 << (BITS - 8)) - 1;
		out_stream << suffix;
	}
}

void Coder::Reset()
{
	mask = (1 << (_BITS - 8)) - 1;
	suffix = 0;
	shift = _BITS - 8;
}
