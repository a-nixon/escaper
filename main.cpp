#include <iostream>

#define NAME "escaper"
//#define LMB ~(~0U >> 1)
#define LMB 0b10000000

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
			<< "-d\tShows the byte value (in decimal) for each character.\n"
			<< "-n\tDisables line breaks.\n"
			<< "-c\tColors special characters. Optionally followed by a color sequence.\n"
			<< "-u\tDisables colored output."
			<< std::endl;
	exit(_status_);
}
void printHex(unsigned char c){
	static char buffer[3];
	sprintf(buffer, "%02X", c);
	std::cout << buffer << '\t';
}
void printDec(unsigned char c){
	static char buffer[4];
	sprintf(buffer, "%03d", c);
	std::cout << buffer << '\t';
}
/*
 * The main function...
 */
int main(int argc, char** argv){
	//Options
	char* color = const_cast<char*>(defaultRed);
	bool showBytes = false, showDec = false, breakLines = true, colored;

	//Check output destination
	//TODO
	
	//Parse options
	for(int i = 1; i < argc; ++i){
		if(argv[i][0] != '-') showHelp(1);
		switch(argv[i][1]){
			case 'b':
				showBytes = true;
				break;
			case 'd':
				showDec = true;
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
	char hrByteBuffer[8]; //byte in human readable format.
	char unicodeBuffer[4];
	std::streambuf *streamBuffer;
	streamBuffer = std::cin.rdbuf();
	unsigned char c;
	int tmp;
	unsigned int unicodeCount;
	while((tmp = streamBuffer->sbumpc()) != EOF){
		c = tmp;
		//if(showBytes) std::cout << std::setw(2) << std::setfill('0') << std::hex << (unsigned int)c << '\t';
		//if(showDec) std::cout << std::dec << ((unsigned int)c) << '\t';
		if(showBytes){
			printHex(c);
		}
		if(showDec){
			printDec(c);
		}
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
				if(showBytes || showDec){
					if((c & LMB) != 0){
						if(unicodeCount == 0){
							unsigned int i = 0;
							while((c & (LMB >> ++i)) != 0){}
							unicodeCount = i;
							std::cout << unicodeCount-- << " byte UTF sequence. "; 
							streamBuffer->sgetn(unicodeBuffer, i-1);
							unicodeBuffer[i-1] = '\0';
							std::cout << c << unicodeBuffer;
							for(int j = i-2; j >= 0; --j) streamBuffer->sputbackc(unicodeBuffer[j]);
						}else{
							--unicodeCount;
							std::cout << "unicode byte";
							//if(showBytes) printHex(c & 0b00111111);
							//if(showDec) printDec(c & 0b00111111);
						}
					}else{
						std::cout << c;
					}
				}else{
					std::cout << c;
				}
			break;
		}
		if(showBytes || showDec) std::cout << '\n';
	}
	std::cout << "^D" << std::endl; //Not needed, could be removed..
	return 0;
}
