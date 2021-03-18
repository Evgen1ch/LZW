#include "Coder16.h"

void Coder16::Code(const std::string& source, const std::string& target)
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

	char a;
	a = input.get();
	std::string w(1, a);
	int code = a;

	while (input.peek() != EOF)
	{
		a = input.get();
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
	WriteCode(code, output);
	input.close();
	output.close();
}

void Coder16::WriteCode(int code, std::ofstream& out_stream)
{
	unsigned short temp = code;
	out_stream.write((char*)&temp, 2);
}

void Coder16::Reset()
{
}

void Coder16::InitializeDictionaryASCII()
{
	dictionary.clear();
	for (unsigned char i = 0; i < UCHAR_MAX; i++)
	{
		dictionary.emplace(std::make_pair(std::string(1, (char)i), (unsigned short)i));
	}
	dictionary.emplace(std::make_pair(std::string(1, (char)0xff), (unsigned short)0xff));
}
