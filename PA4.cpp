/*Main: Creates a model, view, and gamecommand object and runs the program.
	Continually asks for user input until decide to quit*/

#include "View.h"
#include "Model.h"
#include "GameCommand.h"
#include <string>
#include <istream>

void print_header();

int main()
{
	//Print header information
	print_header();	

	//Initializes model, view, gamecommand and input variables
	Model *model = new Model();
	View *view = new View();
	GameCommand *commander;
	
	//Setup input variables
	std::stringstream input;
	std::string buf;

	//Print initial object information
	model->show_status();

	//Main loop
	do
	{
		//Prints grid
		model->display(*view);
		
		//Gets user input, saves it to a stream, and passes it to the gamecommand object commander
		std::cout << "Enter command: ";
		std::getline(std::cin, buf);
		std::cout << buf << std::endl;
		input << buf;
		commander = new GameCommand(input, *model);

		//Clears input buffer to prepare it for next command
		input.str(std::string());
		input.clear();

	} while ((*commander).command != 'q');

	delete view;
	delete commander;	
	return 0;
}

//Prints a header containing class and assignment
void print_header()
{
	std::cout << "EC327: Introduction to Software Engineering" << std::endl;
	std::cout << "Fall 2014" << std::endl << "Programming Assignment 4" << std::endl;
}
