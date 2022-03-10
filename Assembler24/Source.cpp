#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <filesystem>
#include "vAssembler.h"

/*
INFO:
	MIPS:	16 instruktioner
			64 byte
	asm24:	19 instruktioner (ADDI med två register finns inte)
			57 byte
			ca 11% mindre minne, men 19% fler instruktioner 
*/	

int main(int argc, char* argv[]) {
/*
TO DO :
	Spara som en fil, välbart namn på filen

*/
	
	std::cout << "ARGS = " << argc << "\n";
	//
	if (argc >= 3) {
		//Print help information:
		printf("Illigal arguments. \nValid arguments:\n\t-i\tInput file\n\t-o\toutput file\n");
		return 1;
	}
	
	std::string path = std::filesystem::current_path().string() + "\\";
	if (argc > 1) {
		std::string input_file(argv[1]);
		//std::string output_file(argv[2]);
		path += input_file;
	}
	
	if (argc <= 1) {
		path = "C:/Users/mansa/source/repos/Assembler24/Assembler24/test.asm";
	}
	std::cout << path << "\n";
	Assembler asmbler;
	auto instructions = asmbler.assemble_file(path);

	for (uint32_t& ins : instructions) {
		std::printf("Inst = %x\n", ins);
	}
	asmbler.write_file(instructions);
	
	return 0;
}