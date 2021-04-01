#include "Coder.h"

void Coder::Code(const string& source, const string& target)
{
	InitializeDictionaryASCII();
	ifstream input(source, ios::binary);
	ofstream output(target, ios::binary);

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
	string w(1, a);
	unsigned short code = a;

	while (input.peek() != EOF) {

		a = input.get();
		string wa = w + (char)a;

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
	output << (char)(suffix << (codeLength - shift));
	input.close();
	output.close();
}

void Coder::CodeNew(const string& source, const string& target)
{
	InitializeDictionaryASCII();
	ifstream input(source, ios::binary);
	ofstream output(target, ios::binary);

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
	string w(1, a);
	unsigned short code = a;

	while (input.peek() != EOF) {

		a = input.get();
		string wa = w + (char)a;

		auto it = dictionary.find(wa);
		if (it != dictionary.end()) {
			w = wa;
			code = it->second;
		}
		else {
			dictionary.emplace(wa, dictionary.size());
			w = a;
			WriteCodeNew(code, output);
			code = a;
		}
		if (dictionary.size() == (1 << codeLength)) {
			codeLength++;
		}
	}
	//the "tail" of message
	WriteCodeNew(code, output, true);
	//WriteCodeNew(0, output);
	input.close();
	output.close();
}

void Coder::InitializeDictionaryASCII()
{
	dictionary.clear();
	for (int i = 0; i < 256; i++)
	{
		dictionary.emplace(make_pair(string(1, (char)i), i));
	}
}

void Coder::WriteCode(unsigned short code, ofstream& outStream)
{
	unsigned char temp = static_cast<char>(code >> shift);
	outStream << (char)(temp | (suffix << (codeLength - shift)));
	shift += codeLength - 8;

	suffix = (char)mask & static_cast<char>(code);
	mask = static_cast<unsigned char>(mask << (codeLength - 8)) + ((1 << (codeLength - 8)) - 1);
	if (shift == codeLength) {
		shift = codeLength - 8;
		mask = (1 << (codeLength - 8)) - 1;
		outStream << suffix;
	}
}

void Coder::WriteCodeNew(unsigned short code, ofstream& outStream, bool flush)
{
	static unsigned bit_buffer = 0;
	static int bits_written = 0;

	bit_buffer |= (unsigned) code << (32 - codeLength - bits_written);
	bits_written += codeLength;

	while (bits_written >= 8) {
		outStream << (char)(bit_buffer >> 24);
		bit_buffer <<= 8;
		bits_written -= 8;
	}
	if (flush) {
		outStream << (char)(bit_buffer >> 24);
		bit_buffer = 0;
		bits_written = 0;
	}
}

void Coder::Reset()
{
	mask = (1 << (codeLength - 8)) - 1;
	suffix = 0;
	shift = codeLength - 8;
}
