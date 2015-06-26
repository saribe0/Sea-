#include "CoralReef.h"
#include <iostream>

//Default constructor. Creates a reef at (0,0)
CoralReef::CoralReef() : GameObject('R', 0)
{
	state = 'f';
	amount = 100;
	std::cout << "CoralReef default constructed" << std::endl;
}

//Constructor that only takes an id
CoralReef::CoralReef(int id) : GameObject('R', id)
{
	state = 'f';
	amount = 100;
	std::cout << "CoralReef default constructed" << std::endl;
}

//Overloaded constructor which gives the reef the inputed id and location
CoralReef::CoralReef(int in_id, CartPoint in_loc) : GameObject('R', in_id, in_loc)
{
	state = 'f';
	amount = 100;
	std::cout << "CoralReef constructed" << std::endl;
}

//Destructor
CoralReef::~CoralReef()
{
	std::cout << "CoralReef destructed" << std::endl;
}

//Returns true if the reef is out of food
bool CoralReef::is_empty()
{
	return (amount == 0);
}

//Provides food. Returns the amount provided and subtracts it from the reef's amount
double CoralReef::provide_food(double amount_to_provide)
{
	if (amount >= amount_to_provide)
	{
		amount = amount - amount_to_provide;
		return amount_to_provide;
	}
	else
	{
		double temp = amount;
		amount = 0;
		return temp;
	}
}

//Updates the state of the reef. State depends on whether the reef has food left
bool CoralReef::update()
{
	if (amount == 0 && state != 'e')
	{
		state = 'e';
		display_code = 'r';
		std::cout << "CoralReef " << get_id() << "has been depleted of food" << std::endl;
		return true;
	}
	else
		return false;
}

//Prints the status of the reef
void CoralReef::show_status()
{ 
	std::cout << "CoralReef Status: ";
	GameObject::show_status();
	std::cout << " containing food " << amount << std::endl;
}

//Writes class specific information to file
void CoralReef::save(std::ofstream& file)
{
	GameObject::save(file);
	file << amount << " ";
}

//Reads class specific information from file
void CoralReef::restore(std::ifstream& file, Model& model)
{
	GameObject::restore(file, model);
	file >> amount;
}
