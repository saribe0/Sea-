#include "GameCommand.h"
#include "Model.h"
#include "InputHandling.h"

//Constructor inputs a stream and model and directs program to correct function
GameCommand::GameCommand(std::stringstream& input, Model& model)
{
	try
	{
		user_input = &input;
		*user_input >> command;
		switch (command)
		{
		case 's':
			do_swim_command(model);
			break;
		case 'S':
			save(model);
			break;
		case 'R':
			restore(model);
			break;
		case 'e':
			do_eat_command(model);
			break;
		case 'f':
			do_float_command(model);
			break;
		case 'z':
			do_zoom_command(model);
			break;
		case 'g':
			do_go_command(model);
			break;
		case 'r':
			do_run_command(model);
			break;
		case 'a':
			do_attack_command(model);
			break;
		case 'n':
			handle_new_command(model);
			break;
		case 'q':
			model.~Model();
			break;
		default:
			throw InvalidInput("Not a proper command");
			break;
		}
	}
	catch (InvalidInput& except)
	{
		std::cout << "Invalid Input - " << except.msg_ptr << std::endl;
	}
}

//Processes new command
void GameCommand::handle_new_command(Model& model)
{
	if (!(*user_input >> type))
		throw InvalidInput("Expecting a character as a type");

	//Processess new command for different types of objects
	//Error checks for proper input before creating the new object
	switch (type)
	{
	//Coral Reef
	case 'r':
	{
		if (!(*user_input >> ID >> x >> y))
			throw InvalidInput("Was expecting three integers after type");
		if (model.get_CoralReef_ptr(ID) != (CoralReef*)NULL)
			throw InvalidInput("That ID is already in use");
		if (x > 20 || x < 0 || y>20 || y < 0)
			throw InvalidInput("Not a valid location");

		CoralReef *reef = new CoralReef(ID, CartPoint(x, y));
		model.add_new_object(reef);
		std::cout << "Created a new reef with id " << ID << " at (" << x << ", " << y << ")" << std::endl;
	}
		break;
	//Cave
	case 'c':
	{
		if (!(*user_input >> ID >> x >> y))
			throw InvalidInput("Was expecting three integers after type");
		if (model.get_Cave_ptr(ID) != (Cave*)NULL)
			throw InvalidInput("That ID is already in use");
		if (x > 20 || x < 0 || y>20 || y < 0)
			throw InvalidInput("Not a valid location");

		Cave *cave = new Cave(ID, CartPoint(x, y));
		model.add_new_object(cave);
		std::cout << "Created a new cave with id " << ID << " at (" << x << ", " << y << ")" << std::endl;
	}
		break;
	//Tuna
	case 't':
	{
		if (!(*user_input >> ID >> ID2))
			throw InvalidInput("Was expecting two integers after type");
		if (model.get_Fish_ptr(ID) != (Fish*)NULL)
			throw InvalidInput("That ID is already in use");
		if (model.get_Cave_ptr(ID2) == (Cave*)NULL)
			throw InvalidInput("Not a valid cave");

		Tuna *tuna = new Tuna(ID, model.get_Cave_ptr(ID2), &model);
		model.add_new_object(tuna);
		std::cout << "Created a new tuna with id " << ID << " at " << model.get_Cave_ptr(ID2)->get_location() << std::endl;
	}
		break;
	//Shark
	case 's':
	{
		if (!(*user_input >> ID))
			throw InvalidInput("Was expecting one integer after type");
		if (model.get_Fish_ptr(ID) != (Fish*)NULL)
			throw InvalidInput("That ID is already in use");

		Shark *shark = new Shark(ID, &model);
		model.add_new_object(shark);
		std::cout << "Created a new shark with id " << ID << " at " << model.get_Fish_ptr(ID)->get_location() << std::endl;
	}
		break;

	default:
		throw InvalidInput("Not a valid type");
		break;
	}

}

//Processes attack command
//Error checks then calls attack command
void GameCommand::do_attack_command(Model& model)
{
	if (!(*user_input >> ID >> ID2))
		throw InvalidInput("Was expecting two integers");
	Fish* fish1 = model.get_Fish_ptr(ID);
	Fish* fish2 = model.get_Fish_ptr(ID2);
	if (fish1 == (Fish*)NULL && fish2 == (Fish*)NULL)
		throw InvalidInput("Invalid ID for both fish");
	else if (fish1 == (Fish*)NULL)
		throw InvalidInput("Invalid Predator Fish ID");
	else if (fish2 == (Fish*)NULL)
		throw InvalidInput("Invalid ID for fish being attacked");
	else
		fish1->start_attack(fish2);
}

//Processes swim to location command
//Error checks then calls swim command
void GameCommand::do_swim_command(Model& model)
{
	if (!(*user_input >> ID >> x >> y))
		throw InvalidInput("Was expecting three integers");

	Fish* fish = model.get_Fish_ptr(ID);
	if (fish == (Fish*)NULL)
		throw InvalidInput("Invalid fish ID");
	else
		fish->start_swimming(CartPoint(x,y));
}

//Processes eat at reef command
//Error checks then calls eat command
void GameCommand::do_eat_command(Model& model)
{
	if (!(*user_input >> ID >> ID2))
		throw InvalidInput("Was expecting two integers");

	Fish* fish = model.get_Fish_ptr(ID);
	CoralReef* reef = model.get_CoralReef_ptr(ID2);
	if (fish == (Fish*)NULL && reef == (CoralReef*)NULL)
		throw InvalidInput("Invalid ID for fish and reef");
	else if (fish == (Fish*)NULL)
		throw InvalidInput("Invalid fish ID");
	else if (reef == (CoralReef*)NULL)
		throw InvalidInput("Invalid reef ID");
	else
		fish->start_eating(reef);
}

//Processes float in place command
//Error checks then calls float command
void GameCommand::do_float_command(Model& model)
{
	if (!(*user_input >> ID))
		throw InvalidInput("Was expecting an integer");

	Fish* fish = model.get_Fish_ptr(ID);
	if (fish == (Fish*)NULL)
		throw InvalidInput("Invalid Fish ID");
	else
		fish->float_in_place();
}

//Processes zoom home command
//Error checks then calls zoom command
void GameCommand::do_zoom_command(Model& model)
{
	if (!(*user_input >> ID >> ID2))
		throw InvalidInput("Was expecting two integers");

	Fish* fish = model.get_Fish_ptr(ID);
	Cave* cave = model.get_Cave_ptr(ID2);
	if (fish == (Fish*)NULL && cave == (Cave*)NULL)
		throw InvalidInput("Invalid ID for fish and cave");
	else if (fish == (Fish*)NULL)
		throw InvalidInput("Invalid fish ID");
	else if (cave == (Cave*)NULL)
		throw InvalidInput("Invalid cave ID");
	else
		fish->start_hiding(cave);
}

//Processes go forward in time one tick command
void GameCommand::do_go_command(Model& model)
{
	std::cout << "Advancing one tick" << std::endl;
	model.update();
	model.show_status();
}

//Processes run to next event command
void GameCommand::do_run_command(Model& model)
{
	std::cout << "Advancing to next event" << std::endl;
	bool running = false;
	int iterations = 0;

	do
	{
		running = model.update();
		iterations++;
	} while (!running && iterations < 5);
	model.show_status();
}

//Writes program information to a file
void GameCommand::save(Model& model)
{
	std::string filename;
	if (!(*user_input >> filename))
		throw InvalidInput("Was expecting a string");
	std::ofstream file;
	file.open(filename.c_str());
	model.save(file);
	file.close();
}

//Restores program from save file
void GameCommand::restore(Model& model)
{
	std::string filename;
	if (!(*user_input >> filename))
		throw InvalidInput("Was expecting a string");
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw InvalidInput("No file with that name");
	model.restore(file);
	file.close();
}