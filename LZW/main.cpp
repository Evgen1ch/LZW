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


void compare_dicks(const map<string, int>& cd, const map<int, string>& dd) {
	//Compare length
	if (cd.size() != dd.size()) {
		cout << "Sizes are different:\n"
			<< "Coder dick size: " << cd.size() << endl
			<< "Decoder dick size: " << dd.size() << endl;
	}
	else {
		cout << "Dictionaries have the same size" << endl;
	}

	////Compare contains
	//if (cd.size() <= dd.size()) {
	//	for (auto pair : cd) {
	//		auto cd_string = pair.first;
	//		auto cd_int = pair.second;
	//		if (dd.at(cd_int) != cd_string) {
	//			cout << "Alarma! Difference in pair: " << cd_string << ":" << cd_int << " " << cd_int << ":" << dd.at(cd_int);
	//		}
	//	}
	//}
	//else {
	//	for (auto pair : dd) {
	//		auto dd_int = pair.first;
	//		auto dd_string = pair.second;
	//		
	//		if (cd.find(dd_string) == cd.end()) {
	//			cout << "There is no pair with key = " << dd_string << endl;
	//		}
	//		else {
	//			auto it = cd.find(dd_string);
	//			if (it->second != dd_int) {
	//				cout << "Alarma! Difference in pair: " << dd_string << ":" << dd_int << " " << it->first << ":" << it->second << endl;
	//			}
	//		}
	//		
	//	}
	//}
}

int main(int argc, char* argv[])
{
	
	Coder coder;
	Decoder decoder;

	coder.CodeNew("resources/photo_2020.jpg", "resources/encoded.txt");
	decoder.Decode("resources/encoded.txt", "resources/decoded.txt");

	compare_dicks(coder.GetDict(), decoder.GetDict());

	

	return 0;
}
