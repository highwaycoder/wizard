#include "wizard.h"
#include <iostream>
#include <string>
#include <vector>

using namespace wiz;

int main(void)
{
	IParser* parser = create_parser();
	std::string input_string;
	std::cout << ">> ";
		std::cout.flush();
	while(std::getline(std::cin,input_string))
	{
		std::vector<std::string> commands;
		std::stringstream input_stream(input_string);
		std::string command;
		while(std::getline(input_stream,command,';'))
		{
			commands.push_back(command);
		}
		for(std::vector<std::string>::iterator i = commands.begin(); i != commands.end(); ++i)
		{
			std::cout << ">> parsing line: " << *i << std::endl;
			parser->parse(*i);
			std::cout << ">> output: " << std::endl;
			std::cout << parser->generate_code();
		}
		std::cout << ">> ";
		std::cout.flush();
	}
	std::cout << std::endl;
	
	parser->shutdown();
	return 0;
}
