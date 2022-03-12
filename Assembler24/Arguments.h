#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include "StringMagic.h"

typedef struct {
	std::string input_file;
	std::string output_file;
} Argument;

Argument get_command_args(int argc, char* argv[]);

