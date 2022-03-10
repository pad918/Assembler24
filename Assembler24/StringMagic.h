#pragma once
#include <string>
#include <vector>
using namespace std;

void remove_leading_whitespace(string& input);

//void remove_all_whitespace(string& input);

void remove_comments(string& input);

string get_first_word(string& input);

vector<string> split(string& input, char separator);