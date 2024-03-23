#include <iomanip>
#include <iostream>

/*
 * Prints the help text then exits with exit code _status_.
 */
void showHelp(int _status_){
	//TODO
	exit(_status_);
}
/*
 * The main function...
 */
int main(int argc, char** argv){
	//Parse options
	bool showBytes = false;
	bool breakLines = true;
	for(int i = 1; i < argc; ++i){
		if(argv[i][0] != '-') showHelp(1);
		switch(argv[i][1]){
			case 'b':
				showBytes = true;
				break;
			case 'n':
				breakLines = false;
				break;
			case 'h':
				showHelp(0);
				break; //Unneccessary
			case '\0':
				std::cout << ":3" << std::endl;
				return 0;
			default:
				showHelp(1);
				break; //Unneccessary
		}
	}
	//Read and reprint
	std::streambuf *buffer;
	buffer = std::cin.rdbuf();
	char c;
	while((c = buffer->sbumpc()) != EOF){
		if(showBytes) std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)c << '\t';
		switch(c){ //Escape non-printing characters.
			case '\e':
				std::cout << "\\e";
				break;
			case '\n':
				std::cout << "\\n";
				if(!showBytes && breakLines) std::cout << '\n';
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
			default: //Assume printing character and print.
				std::cout << c;
			break;
		}
		if(showBytes) std::cout << '\n';
	}
	std::cout << "^D" << std::endl; //Not needed, could be removed..
	return 0;
}
