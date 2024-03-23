#include <cstring>
#include <iomanip>
#include <iostream>

int main(int argc, char** argv){
	bool showBytes = false;
	if(argc > 1) if(strcmp(argv[1], "-b") == 0) showBytes = true;
	std::streambuf *buffer;
	buffer = std::cin.rdbuf();
	char c;
	while((c = buffer->sbumpc()) != EOF){
		if(showBytes) std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)c << '\t';
		switch(c){
			case '\e':
				std::cout << "\\e";
				break;
			case '\n':
				std::cout << "\\n";
				if(!showBytes) std::cout << '\n';
				break;
			case '\a':
				std::cout << "\\a";
				break;
			case '\b':
				std::cout << "\\b";
				break;
			case '\f':
				std::cout << "\\f";
				break;
			case '\r':
				std::cout << "\\r";
				break;
			case '\t':
				std::cout << "\\t";
				break;
			case '\v':
				std::cout << "\\v";
				break;
			default:
				std::cout << c;
			break;
		}
		if(showBytes) std::cout << '\n';
	}
	std::cout << "^D" << std::endl;
	return 0;
}
