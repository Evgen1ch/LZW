#include <iostream>
#include <vector>
#include "Coder.h"
#include "Decoder.h"
#include "global.h"

//sequence "aaaaaaaaaaaa" doing something weird
//need to inspect this thing and fix it
//not only this sequence - need to find bugs

//improvements TODO
//int buffer to write 2 symbols
//in decoder change map string->int to map int->string




int main(int argc, char* argv[])
{
	
	Coder coder;
	Decoder decoder;

	coder.Code("resourses/source.txt", "resourses/encoded.txt");
	decoder.Decode("resourses/encoded.txt", "resourses/decoded.txt");
	return 0;
}
