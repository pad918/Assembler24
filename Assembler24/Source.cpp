#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <filesystem>
#include "Arguments.h"
#include "vAssembler.h"

/*
	Arguments:
		-i input file
		-o output file

	How to hanle arguments:
		if no input file is selected ==> do nothing
		if no output file is selected, write to out.txt file
*/	

int main(int argc, char* argv[]) {
/*
TO DO :

	pseudo instructions

	global

	# include other asm files

	macros

*/
	Argument args;
	try {
		args = get_command_args(argc, argv);
		std::cout << "ARGS = " << argc << "\n";
	}
	catch (exception e) {
		std::cout << "FAILED PARTING ARGUMENTS\n";
	}

	//Print info
	std::cout << "INPUT PATH = " << args.input_file << std::endl;
	std::cout << "OUTPUT PATH = " << args.output_file << std::endl;

	Assembler asmbler;
	auto instructions = asmbler.assemble_file(args.input_file);

	asmbler.write_file(args.output_file, instructions, false);
	
	return 0;
}