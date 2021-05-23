#include <vector>

#include "Coder.h"
#include "Decoder.h"
#include "LzwTimer.h"


using std::cout;
using std::endl;

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
	LzwTimer timer;

	cout << "--------------------------(CODING)--------------------------" << endl;
	timer.start();
	coder.CodeNew("resources/aaa.jpg", "resources/encoded.txt");
	timer.end();
	cout << "-------------------------(DECODING)-------------------------" << endl;
	timer.start();
	decoder.Decode("resources/encoded.txt", "resources/out.jpg");
	timer.end();

	
	system("pause");
	return 0;
}
