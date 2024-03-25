#include <iomanip>
#include <iostream>

/*
 * THe default color to use when coloring output.
 */
const char* defaultRed = "31m";
/*
 * The ANSI escape sequence to reset the color (and everything else).
 */
const char* colorReset = "\e[0m";

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
	//Options
	char* color = const_cast<char*>(defaultRed);
	bool showBytes = false, breakLines = true, colored;

	//Check output destination
	//TODO
	
	//Parse options
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
			case 'c':
				colored = true;
				if(i+1 < argc){
					if(argc && argv[i+1][0] == '-') continue;
					color = const_cast<char*>(argv[++i]);
				}
				break;
			case 'u':
				colored = false;
				break;
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
				if(colored) std::cout << "\e[" << color << "\\e" << colorReset;
				else std::cout << "\\e";
				break;
			case '\n':
				if(colored) std::cout << "\e[" << color << "\\n" << colorReset;
				else std::cout << "\\n";
				if(!showBytes && breakLines) std::cout << '\n';
				break;
			case '\a':
				if(colored) std::cout << "\e[" << color << "\\a" << colorReset;
				else std::cout << "\\a";
				break;
			case '\b':
				if(colored) std::cout << "\e[" << color << "\\b" << colorReset;
				else std::cout << "\\b";
				break;
			case '\f':
				if(colored) std::cout << "\e[" << color << "\\f" << colorReset;
				else std::cout << "\\f";
				break;
			case '\r':
				if(colored) std::cout << "\e[" << color << "\\r" << colorReset;
				else std::cout << "\\r";
				break;
			case '\t':
				if(colored) std::cout << "\e[" << color << "\\t" << colorReset;
				else std::cout << "\\t";
				break;
			case '\v':
				if(colored) std::cout << "\e[" << color << "\\v" << colorReset;
				else std::cout << "\\v";
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
