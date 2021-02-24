#include "Coder.h"
unsigned char Coder::mask = (1 << (BITS - 8)) - 1;
unsigned char Coder::suffix = 0;
unsigned int Coder::shift = _BITS - 8;

void Coder::Code(const std::string& source, const std::string& target)
{
	std::ifstream input(source);
	std::ofstream output(target);

	if (!input || !output) {
		return;
	}

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
			//write code to output
			code = a;
		}
	}
	//write code to output, but need to prevent double write of one code
}

void Coder::WriteCode(unsigned short code)
{
}

void Coder::Reset()
{
	mask = (1 << (BITS - 8)) - 1;
	suffix = 0;
	shift = BITS - 8;
}
