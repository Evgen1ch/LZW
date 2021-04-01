#include <iostream>
#include <vector>
#include "Coder.h"
#include "Decoder.h"

using std::cout;
using std::endl;

//sequence "aaaaaaaaaaaa" doing something weird
//need to inspect this thing and fix it
//not only this sequence - need to find bugs

//improvements TODO
//int buffer to write 2 symbols
//in decoder change map string->int to map int->string


void compare_dicts(const map<string, int>& cd, const map<int, string>& dd) {
	//Compare length
	if (cd.size() != dd.size()) {
		cout << "Sizes are different:\n"
			<< "Coder dict size: " << cd.size() << endl
			<< "Decoder dict size: " << dd.size() << endl;
		return;
	}

	//Compare contains
	for (auto pair : cd) {
		auto cd_string = pair.first;
		auto cd_int = pair.second;
		if (dd.at(cd_int) != cd_string) {
			cout << "Alarma! Difference in pair: " << cd_string << ":" << cd_int << " " << cd_int << ":" << dd.at(cd_int);
		}
	}
}

int main(int argc, char* argv[])
{
	
	Coder coder;
	Decoder decoder;

	coder.CodeNew("resourses/img.txt", "resourses/encoded.txt");
	decoder.Decode("resourses/encoded.txt", "resourses/decoded.txt");

	compare_dicts(coder.GetDict(), decoder.GetDict());

	return 0;
}
