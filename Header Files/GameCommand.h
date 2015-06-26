/*This class is for processing user inputs. The constructor takes a stream
	which contains a command and processes it for the Model that was also
	passed through.*/

#include "Model.h"
#include "sstream"

#ifndef GameCommand_h
#define GameCommand_h

class GameCommand
{
private:
	int ID, ID2, x, y;
	char type;
	std::stringstream *user_input;

	//Processes new command
	void handle_new_command(Model& model);

	//Processes swim to location command
	void do_swim_command(Model& model);

	//Processes go forward in time one tick command
	void do_go_command(Model& model);
	
	//Processes run to next event command
	void do_run_command(Model& model);
	
	//Processes eat at reef command
	void do_eat_command(Model& model);
	
	//Processes float in place command
	void do_float_command(Model& model);

	//Processes zoom home command
	void do_zoom_command(Model& model);

	//Processes attack command
	void do_attack_command(Model& model);

	//Writes program information to a file
	void save(Model& model);

	//Restores program from save file
	void restore(Model& model);

public:
	char command;

	//Constructor inputs a stream and model and directs program to correct function
	GameCommand(std::stringstream& input, Model& model);

};
#endif
