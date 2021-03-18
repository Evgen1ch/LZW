#include "global.h"
#include <vector>
#include <iostream>

void initialize_dictionary_ascii(std::map<std::string, unsigned short>& dict)
{
	dict.clear();
	for (unsigned char i = 0; i < UCHAR_MAX; i++)
	{
		dict.emplace(std::make_pair(std::string(1, (char)i), (unsigned short)i));
	}
	dict.emplace(std::make_pair(std::string(1, (char)0xff), (unsigned short)0xff));
}

void code(std::ifstream& input, std::map<std::string, unsigned short>& dictionary, std::vector<unsigned short>& output_codes)
{
	if (!input) return;

	char a;
	input >> a;
	std::string w(1, a);
	unsigned short code = a;

	while (!input.eof())
	{
		input >> a;
		std::string wa = w + a;
		auto it = dictionary.find(wa);

		if (it != dictionary.end()) //if dictionary contains the string
		{
			w = wa;
			code = it->second;
		}
		else //dictionary not contains the string
		{
			dictionary.emplace(wa, dictionary.size());
			std::cout << wa << std::endl;
			w = a;
			output_codes.push_back(code);
			code = a;
		}
	}
	output_codes.push_back(code);
}

void compress_16(std::vector<unsigned short>& codes, const std::string& filename)
{
	std::ofstream out(filename);
	if (!out) return;

	for (auto c : codes)
	{
		out.write(reinterpret_cast<char*>(&c), sizeof(c));
	}
	out.close();
}

void compress(std::vector<unsigned short>& codes, std::ofstream& out_stream)
{
	if (codes.size() == 0) return;
	if (!out_stream) return;
	if (BITS < 9) return;

	const int in_size = 11;
	const int out_size = ((BITS * in_size) / 8) + 1;
	unsigned char* out = new unsigned char[out_size];

	unsigned char mask = (1 << (BITS - 8)) - 1;
	unsigned char suffix = 0;
	unsigned int shift = BITS - 8;
	unsigned int out_c = 0;

	for (int i = 0; i < 11; i++)
	{
		unsigned char temp = static_cast<char>(codes[i] >> shift);
		out[out_c] = (char)temp | (suffix << (BITS - shift));
		out_c++;
		shift += BITS - 8;

		suffix = (char)mask & static_cast<char>(codes[i]);
		mask = static_cast<unsigned char>(mask << (BITS - 8)) + ((1 << (BITS - 8)) - 1);
		if (shift == BITS) {
			shift = BITS - 8;
			mask = (1 << (BITS - 8)) - 1;
			out[out_c] = suffix;
			out_c++;
		}
	}
	out[out_size - 1] = suffix << (BITS - shift);


	out_stream.write((char*)out, out_size);														//TODO rewrite. store whole file uses a lot of memery. Write every byte when coded, not together.

	std::cout << "Total size: " << out_size;
}

std::vector<unsigned short>& decompress(std::ifstream& in_stream)
{
	if (!in_stream) {
		return *(new std::vector<unsigned short>());
	}


	std::vector<unsigned short>& input_codes = *(new std::vector<unsigned short>());
	int shift = BITS - 8;
	unsigned char suffix = 0;

	unsigned char input;
	in_stream >> input;
	unsigned short current_code;

	while (!in_stream.eof()) {
		unsigned char temp = input << (shift - 1);
		current_code = (unsigned short)temp << 1;

		in_stream >> input;
		suffix = input >> (8 - shift);

		if (!in_stream.eof()) {
			input_codes.push_back(current_code + suffix);
		}
		shift++;
		if (shift == BITS) {
			shift = BITS - 8;
			in_stream >> input;
		}
	}

	return input_codes;
}

void decode(std::ofstream& output_stream, std::vector<unsigned short>& input_codes)
{
	std::map<std::string, unsigned short> dictionary;
	initialize_dictionary_ascii(dictionary);
	std::string total_code;
	for (auto old_code : input_codes) {

	}
}