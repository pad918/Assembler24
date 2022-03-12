#include "Arguments.h"

Argument get_command_args(int argc, char* argv[])
{
	Argument args;

	//For vs debug
	if (argc == 1) {
		args.input_file = "test.asm";
		args.output_file = "out.txt";
		return args;
	}

	std::string current_path = std::filesystem::current_path().string();
	args.output_file = current_path + "\\out.txt";
	std::vector<std::string> arg_strings;
	for (int i = 0; i < argc; i++) {
		arg_strings.push_back(argv[i]);
		std::cout << "arg[" << i << "] = " << argv[i] << "\n";
	}

	//Should be done in modular way to make more arguments easy to implement!
	int output_arg_num=-1, input_arg_num=-1;
	for (int i = 0; i < arg_strings.size(); i++) {
		remove_leading_whitespace(arg_strings[i]);
		if (arg_strings[i].compare("-i") == 0) {
			std::cout << "input arg_num = " << i + 1 << "\n";
			input_arg_num = i + 1;
		}
		else if (arg_strings[i].compare("-o") == 0) {
			output_arg_num = i + 1;
			std::cout << "output arg_num = " << i + 1 << "\n";
		}
	}

	if (input_arg_num > 0) {
		if (input_arg_num >= arg_strings.size()) {
			throw "No Input Argument Specified\n";
		}
		args.input_file = current_path + "\\" + arg_strings[input_arg_num];
	}
	else {
		throw "No Input Argument\n";
	}
	if (output_arg_num > 0) {
		if (output_arg_num >= arg_strings.size()) {
			throw "No Output Argument Specified\n";
		}
		args.output_file = current_path + "\\" + arg_strings[output_arg_num];
	}

	return args;
}