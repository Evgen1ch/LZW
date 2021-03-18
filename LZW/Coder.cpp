#include "Coder.h"
std::map<std::string, unsigned short> Coder::dictionary = std::map<std::string, unsigned short>();
unsigned char Coder::mask = (1 << (_BITS - 8)) - 1;
unsigned char Coder::suffix = 0;
unsigned int Coder::shift = _BITS - 8;

void Coder::Code(const std::string& source, const std::string& target)
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

	unsigned char a;
	a = input.get();
	std::string w(1, a);
	unsigned short code = a;

	while (input.peek() != EOF) {

		a = input.get();
		std::string wa = w + (char)a;

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
	WriteCode(code, output);
	output << (char)(suffix << (_BITS - shift));
	input.close();
	output.close();
}

void Coder::InitializeDictionaryASCII()
{
	dictionary.clear();
	for (int i = 0; i < 256; i++)
	{
		dictionary.emplace(std::make_pair(std::string(1, (char)i), (unsigned short)i));
	}
}

void Coder::WriteCode(unsigned short code, std::ofstream& out_stream)
{
	unsigned char temp = static_cast<char>(code >> shift);
	out_stream << (char)(temp | (suffix << (_BITS - shift)));
	shift += _BITS - 8;

	suffix = (char)mask & static_cast<char>(code);
	mask = static_cast<unsigned char>(mask << (_BITS - 8)) + ((1 << (_BITS - 8)) - 1);
	if (shift == _BITS) {
		shift = _BITS - 8;
		mask = (1 << (_BITS - 8)) - 1;
		out_stream << suffix;
	}
}

void Coder::Reset()
{
	mask = (1 << (_BITS - 8)) - 1;
	suffix = 0;
	shift = _BITS - 8;
}
