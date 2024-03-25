#include <iomanip>
#include <iostream>

#define NAME "escaper"

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
void showHelp(int _status_){ //Needs to be better.
	std::cout << "Usage: " NAME " [flags]\n\n" NAME " is an output debugging tool. "
			<< NAME " reads from stdin and escapes special characters before writing to stdout.\n\n"
			<< "-h\tShow this help text.\n"
			<< "-b\tShows the byte value (in hex) for each character.\n"
			<< "-n\tDisables line breaks.\n"
			<< "-c\tColors special characters. Optionally followed by a color sequence.\n"
			<< "-u\tDisables colored output."
			<< std::endl;
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
				std::cout << NAME " reads from stdin by default.\n\n";
				showHelp(0);
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
			case '\e': //ESC
				if(colored) std::cout << "\e[" << color << "\\e" << colorReset;
				else std::cout << "\\e";
				break;
			case '\n': //LF
				if(colored) std::cout << "\e[" << color << "\\n" << colorReset;
				else std::cout << "\\n";
				if(!showBytes && breakLines) std::cout << '\n';
				break;
			case '\a': //BEL
				if(colored) std::cout << "\e[" << color << "\\a" << colorReset;
				else std::cout << "\\a";
				break;
			case '\b': //BS
				if(colored) std::cout << "\e[" << color << "\\b" << colorReset;
				else std::cout << "\\b";
				break;
			case '\f': //FF
				if(colored) std::cout << "\e[" << color << "\\f" << colorReset;
				else std::cout << "\\f";
				break;
			case '\r': //CR
				if(colored) std::cout << "\e[" << color << "\\r" << colorReset;
				else std::cout << "\\r";
				break;
			case '\t': //TAB
				if(colored) std::cout << "\e[" << color << "\\t" << colorReset;
				else std::cout << "\\t";
				break;
			case '\v': //VT
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
