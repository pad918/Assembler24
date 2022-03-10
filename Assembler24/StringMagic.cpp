#include "StringMagic.h"

void remove_leading_whitespace(string& input)
{
	//Leadning
	for (int i = 0; i < input.size(); i++) {
		char temp = input.at(i);
		if (temp == ' ' || temp == '\t' || temp=='\n') {
			input.erase(input.begin() + i);
			i--;
		}
		else {
			break;
		}
	}
	//Ending
	for (int i = input.size() - 1; i>=0 ; i--) {
		char temp = input.at(i);
		if (temp == ' ' || temp == '\t' || temp == '\n') {
			input.erase(input.begin() + i);
		}
		else {
			break;
		}
	}
}

void remove_comments(string& input)
{
	int first_pos = -1;
	for (int i = 0; i < input.size(); i++) {
		if (input.at(i) == '#') {
			first_pos = i;
			break;
		}
	}
	if (first_pos >= 0) {
		input.erase(first_pos, input.size() - first_pos);
	}
}

string get_first_word(string& input)
{
	string word = "";
	for (auto & c : input) {
		if (c != ' ' && c != '\t')
			word.push_back(c);
		else
			break;
	}
	return word;
}

vector<string> split(string& input, char separator)
{
	vector<string> strings;
	string tmp = "";
	for (int i = 0; i < input.size(); i++) {
		if (input.at(i) != separator) {
			tmp.push_back(input.at(i));
		}
		else {
			if (tmp.size() > 0)
				strings.push_back(tmp);
			tmp = "";
		}
	}
	if (tmp.size() > 0)
		strings.push_back(tmp);
	return strings;
}
