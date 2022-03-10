#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <filesystem>
#include "StringMagic.h"


typedef struct {
	int original_line_number;
	string line;
} line_holder;

typedef struct {
	uint8_t op;
	uint8_t type;
} instruction_definition;

enum inst_type{I_TYPE, IR_TYPE, R_TYPE};

class Assembler{
public:
	Assembler();
	std::unordered_map<std::string, uint32_t> label_map;
	
	std::unordered_map<std::string, uint8_t> register_map = {{"$zero", 0}, {"$0", 0}, {"$at", 1}, {"$v0", 2}, {"$v1", 3}, {"$a0", 4}, {"$a1", 5},
	{"$a2", 6}, {"$a3", 7}, {"$t0", 8}, {"$t1", 9}, {"$t2", 10}, {"$t3", 11},{"$t4", 12},{"$t5", 13},{"$t6", 14},{"$t7", 15}, {"$s0", 16},
	{"$s1", 17},{"$s2", 18},{"$s3", 19},{"$s4", 20},{"$s5", 21},{"$s6", 22},{"$s7", 23},{"$t8", 24},{"$t9", 25},{"$k0", 26}, {"$k1", 27}, 
	{"$gp", 28}, {"$sp", 29},{"$fp", 30}, {"$ra", 31} };
	
	std::unordered_map<std::string, instruction_definition> instruction_map;

	std::vector<std::string> R_type = { "ADD", "SUB", "SLT", "AND", "OR" };
	std::vector<std::string> IR_type = { "ADDI", "AND", "OR", "STORE", "LOAD", "BZ", "BNZ"};
	std::vector<std::string> I_type = { "JAL", "LTA" };
	
	uint32_t decode_single_instruction(std::string line);
	
	std::vector<int32_t> get_arguments(std::vector<std::string>& inst_arguments);
	std::vector<string> get_argument_strings(std::string line);
	
	std::vector<uint32_t> assemble_file(std::string path);
	void write_file(const std::vector<uint32_t>& instructions);
};