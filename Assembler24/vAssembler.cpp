#include "vAssembler.h"

uint32_t Assembler::decode_single_instruction(std::string line)
{
	uint32_t inst24 = 0;

	//Remove whitespace and get instruction (nuematic?)
	remove_leading_whitespace(line);
	string inst = get_first_word(line);
	std::cout << "INST TYPE = |" << inst << "|\n";

	//Get list of arguments as strings
	auto args_strings = get_argument_strings(line);
	
	//Get args as numbers
	auto args = get_arguments(args_strings);
	
	//Get instruction type and op code:
	auto search = instruction_map.find(inst);
	if (search == instruction_map.end()) {
		//Did not find instruction name:
		throw exception("ILLIGAL INSTRUCTION");
	}
	uint8_t type = search->second.type;
	uint8_t op   = search->second.op;
	inst24 |= op << 16;

	//Asseblme instruction
	if (type == R_TYPE) {
		//Decode R_type instructions
		if (args.size() != 3) { throw exception("ILLIGAL ILLIGAL_ARGUMENT"); }
		
		//Write rd, rs, rt values
		inst24 |= (args[0] << 11) & (0x1F << 11);
		inst24 |= (args[1] << 5)  & (0x1F << 5);
		inst24 |= (args[2])		  & (0x1F);
	}
	else if (type == I_TYPE) {
		//Decode I_type instructions
		if (args.size() != 1) { throw exception("ILLIGAL ILLIGAL_ARGUMENT"); }

		//Imm16
		inst24 |= args[0] & 0xFFFF;
	}
	else if (type == IR_TYPE) {
		//Decode IR_type instructions
		if (args.size() != 2) { throw exception("ILLIGAL ILLIGAL_ARGUMENT"); }

		//rd
		inst24 |= (args[0] << 11) & (0x1F << 11);

		//Imm11
		inst24 |= args[1] & 0x7FF;
	}
	return inst24;
}

std::vector<int32_t> Assembler::get_arguments(std::vector<std::string>& inst_arguments)
{
	//Only works with decimal numbers, register and label names at the moment (no hex or binary)
	std::vector<int32_t> args;
	
	for (auto& s : inst_arguments) {
		try {
			args.push_back(std::stoi(s));
		}
		catch (exception e) {
			// Test if string is label or register name
			auto lab           = label_map.find(s);
			auto reg_from_name = register_map.find(s);
			if (lab != label_map.end()) {
				args.push_back(lab->second);
			}
			else if (reg_from_name != register_map.end()) {
				args.push_back(reg_from_name->second);
			}
			else {
				throw exception("PARSING FAILED");
			}
		}
	}
	
	return args;
}

std::vector<string> Assembler::get_argument_strings(std::string line)
{
	std::vector<string> arguments;
	string inst = get_first_word(line);
	line.erase(0, inst.size());
	remove_leading_whitespace(line);
	arguments = split(line, ',');
	for (string& s : arguments) {
		remove_leading_whitespace(s);
	}
	return arguments;
}

std::vector<uint32_t> Assembler::assemble_file(std::string path)
{

	std::vector<line_holder> lines;
	std::vector<uint32_t> instructions;
	string line;
	std::ifstream file_stream(path);
	int i=1;

	//Read all lines
	while (std::getline(file_stream, line)) {
		line_holder holder;
		holder.original_line_number = i++;
		holder.line = line;
		lines.push_back(holder);
	}

	//Remove empty lines and whitespace and comments:
	for (int i = 0; i < lines.size(); i++) {
		remove_comments(lines[i].line);
		remove_leading_whitespace(lines[i].line);
		if (lines[i].line.empty()) {
			lines.erase(lines.begin() + i);
			i--;
		}
	}

	//Extract labels
	int instruction_adress = 0;
	for (int i = 0; i < lines.size(); i++) {
		//Labels are one word and ends with a semicolon
		auto words = split(lines[i].line, ' ');
		if (words.size() == 1 && words[0].back() == ':') {
			lines[i].line.pop_back();
			label_map[lines[i].line] = instruction_adress;
			lines.erase(lines.begin() + i);
			i--;
		}
		else {
			instruction_adress++;
		}
	}

	//Assemble individual instructions:
	for (line_holder& holder : lines) {
		try {
			auto inst = decode_single_instruction(holder.line);
			instructions.push_back(inst);
		}
		catch(exception e) {
			std::cout << "Failed on line " << holder.original_line_number;
			std::cout << ", reason: " << e.what() << "\n";
			break;
		}
	}

	return instructions;
}

void Assembler::write_file(const std::vector<uint32_t>& instructions)
{
	//Create stream to file
	std::ofstream file;
	file.open(std::filesystem::current_path().string() + "\\out.txt");
	file << "Asm24 machinecode file v1.0\n";
	for (const uint32_t& inst : instructions) {
		file << inst << "\n";
	}
	file.close();
}

Assembler::Assembler()
{
	// Add all instructions:
	//R-type:
	instruction_map["ADD"] = instruction_definition {0x00, R_TYPE};
	instruction_map["SUB"] = instruction_definition {0x01, R_TYPE};
	instruction_map["AND"] = instruction_definition {0x02, R_TYPE};
	instruction_map["OR"]  = instruction_definition {0x03, R_TYPE};
	instruction_map["SLT"] = instruction_definition {0x04, R_TYPE};

	//I-type
	instruction_map["JAL"] = instruction_definition{ 0xF0, I_TYPE };
	instruction_map["LTA"] = instruction_definition{ 0xF1, I_TYPE };

	//IR-type
	instruction_map["ADDI"]  = instruction_definition{ 0x40, IR_TYPE };
	instruction_map["ANDI"]  = instruction_definition{ 0x41, IR_TYPE };
	instruction_map["ORI"]   = instruction_definition{ 0x42, IR_TYPE };
	instruction_map["STORE"] = instruction_definition{ 0x43, IR_TYPE };
	instruction_map["LOAD"]  = instruction_definition{ 0x44, IR_TYPE };
	instruction_map["BZ"]    = instruction_definition{ 0x45, IR_TYPE };
	instruction_map["BNZ"]   = instruction_definition{ 0x46, IR_TYPE };
}

