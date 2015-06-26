#include "Fish.h"
#include "Cave.h"
#include "Model.h"

//Default constructor creates a fish with a certain code and size
Fish::Fish(char display_code, int siz, Model* model) :GameObject(display_code, 0)
{
	world = model;
	state = 'f';
	energy = 15;
	this->size = size;
	prefeast_size = size;
	destination = CartPoint();
	reef = NULL;
	home = NULL;
	std::cout << "Fish default constructed" << std::endl;
}

//Constructor that creates a fish with a display code, id, and size
Fish::Fish(char display_code, int id, int size, Model* model) : GameObject(display_code, id)
{
	world = model;
	state = 'f';
	energy = 15;
	this->size = size;
	prefeast_size = size;
	destination = CartPoint();
	reef = NULL;
	home = NULL;
	std::cout << "Fish constructed" << std::endl;
}

//Constructor that creates a fish that starts in and with a given cave 
//	as its home, a certain display code, and a size
Fish::Fish(char display_code, int in_id, Cave* home, int size, Model* model) : GameObject(display_code, in_id, (*home).get_location())
{
	world = model;
	energy = 15;
	this->size = size;
	prefeast_size = size;
	destination = CartPoint();
	reef = NULL;
	Fish::home = home;
	if (home->hide_fish(this))
		state = 'h';
	std::cout << "Fish constructed" << std::endl;
}

//Constructor that creates a fish that starts in a location that is not
//	a cave, has a certain display code, and a size
Fish::Fish(char display_code, int in_id, CartPoint loc, int size, Model* model) :GameObject(display_code, in_id, loc)
{
	world = model;
	energy = 15;
	this->size = size;
	prefeast_size = size;
	destination = CartPoint();
	reef = NULL;
	home = NULL;
	state = 'f';
	std::cout << "Fish constructed" << std::endl;
}

//Destructor
Fish::~Fish()
{

	std::cout << "Fish destructed" << std::endl;
}

//Updates the location of the fish. Either arrives or keeps swimming
bool Fish::update_loc()
{
	if (fabs(destination.x - location.x) <= fabs(delta.x) && (fabs(destination.y - location.y) <= fabs(delta.y)))
	{
		location = destination;
		std::cout << display_code << get_id() << ": I'm there!" << std::endl;
		return true;
	}
	else
	{
		location = location + delta;
		std::cout << display_code << get_id() << ": just keep swimming..." << std::endl;
		return false;
	}
}

//Sets the destination of the fish and the increments for it to move at
void Fish::setup_destination(CartPoint dest)
{
	destination = dest;
	if (cart_distance(dest, get_location()) != 0)
		delta = (dest - get_location())*(get_speed() / cart_distance(dest, get_location()));
	else
		delta = CartVector();
}

//Returns true if fish is alive, false if dead
bool Fish::is_alive()
{
	if (this->state == 'x')
	{
		std::cout << display_code << get_id() << ": Dead." << std::endl;
		return false;
	}
	else
		return true;
}

//Takes away from a fishes energy (health). Can kill the fish or just hurt it
void Fish::get_bitten(int attack_strength)
{
	if (is_alive())
	{
		energy -= attack_strength;
		std::cout << display_code << get_id() << ": Ouch!" << std::endl;
		if (energy <= 0)
		{
			std::cout << "Oh no, I've become chum!" << std::endl;
			state = 'x';
		}
	}
}

//Returns the size of the fish
double Fish::get_size()
{
	return size;
}

//Returns true if the fish is hidden, false if not
bool Fish::is_hidden()
{
	if (state == 'h')
		return true;
	else
		return false;
}

//Default for attacking
void Fish::start_attack(Fish*attacker)
{
	if (is_alive())
	{
		std::cout << "I cannot attack." << std::endl;
	}
}

//Default for mating
bool Fish::start_mating(Fish*mate)
{
	if (is_alive())
	{
		std::cout << "I cannot mate" << std::endl;
		return false;
	}
}

//Tells the fish to start swimming to a destination
void Fish::start_swimming(CartPoint dest)
{
	if (is_alive())
	{
		if (is_hidden())
			home->release_fish(this);
		setup_destination(dest);
		state = 's';
		std::cout << "Swimming " << get_id() << " to " << dest << std::endl;
		std::cout << display_code << get_id() << ": On my way" << std::endl;
	}
}

//Tells the fish to start eating from a given reef
void Fish::start_eating(CoralReef *destReef)
{
	if (is_alive())
	{
		if (is_hidden())
			home->release_fish(this);
		reef = destReef;
		setup_destination(reef->get_location());
		state = 'o';
		std::cout << "Fish " << get_id() << " eating at CoralReef " << destReef->get_id();
		if (home != NULL)
			std::cout << " and returning back to Cave " << home->get_id() << std::endl;
		else
			std::cout << std::endl;
		std::cout << display_code << get_id() << ": Food here I come!" << std::endl;
	}
}

//Tells the fish to hide in a given cave and starts the process
void Fish::start_hiding(Cave *destCave)
{
	if (is_alive())
	{
		if (is_hidden())
			home->release_fish(this);
		home = destCave;
		setup_destination(home->get_location());
		state = 'z';
		std::cout << "Fish " << get_id() << " swimming to Cave " << home->get_id() << std::endl;
		std::cout << display_code << get_id() << ": Off to safety" << std::endl;
	}
}

//Tells the fish to float in place without moving
void Fish::float_in_place()
{
	if (is_alive())
	{
		if (is_hidden())
			home->release_fish(this);
		state = 'f';
		std::cout << "Stopping " << get_id() << std::endl;
		std::cout << display_code << get_id() << ": Resting my fins" << std::endl;
	}
}

//Updates the fish's state
bool Fish::update()
{
	switch (state)
	{
		case 'f' : //floating, does nothing
			break;
		case 's': //swimming
			if (update_loc())
			{
				state = 'f'; //if arrived, start floating
				return true;
			}
			break;
		case 'o': //outbound to a coral reef to eat
			if (update_loc())
			{
				std::cout << display_code << get_id() << ": Starting to dine at a coral reef" << std::endl;
				prefeast_size = size;
				state = 'e'; //if arrived at the reef, start eating
				return true;
			}
			break;
		case 'e': //eating at a coral reef
			if (size >= 2 * prefeast_size)
			{
				if (home != NULL)
				{
					setup_destination(home->get_location());
					std::cout << display_code << get_id() << ": I'm full. I'm heading home" << std::endl;
					state = 'z'; //if full, start zooming home
					return true;
				}
				else
				{
					std::cout << display_code << get_id() << ": I'm full but don't have a home" << std::endl;
					state = 'f'; //if full but without a home, start floating
					return true;
				}
			}
			double food;
			food = reef->provide_food();
			size += food / 2;
			if (food/2 != 0)
				std::cout << display_code << get_id() << ": Grew to size " << get_size() << std::endl;
			if (food == 0 && size < prefeast_size * 2)
			{
				std::cout << display_code << get_id() << ": This reef has no more food for me..." << std::endl;
				state = 'f'; //if reef runs out of food, start floating
			}
			break;
		case 'z' : //zooming home
			if (update_loc())
			{
				if (home->hide_fish(this))
				{
					state = 'h'; //if home, start hiding if theres room
					std::cout << display_code << get_id() << ": I am hidden and safe" << std::endl;
					return true;
				}
				else
				{
					state = 'p'; //if home, start panicking if theres no room
					std::cout << display_code << get_id() << ": Help! My home cave is full" <<std::endl;
					return true;
				}
			}
			break;
		case 'p': //panicking, does nothing
			break;
		case 'x': //dead
			break;
		case 'h': //hidden
			energy = 3 * energy / 4;
			if (energy < 5)
			{
				home->release_fish(this);
				state = 'x'; //if energy is low enough, declare fish dead
			}
			break;
	}
	return false;
}

//Prints the status of the fish
void Fish::show_status()
{
	GameObject::show_status();
	switch (state)
	{
		case 'f':
			std::cout << " is floating. Has a size of: " << size << " and energy of: " << energy << std::endl;
			break;
		case 's':
			std::cout << " has a speed of: " << get_speed() << " and is heading to: " << destination << std::endl;
			break;
		case 'o':
			std::cout << " is outbound to Reef: " << reef->get_id() << " with a speed of " << get_speed() << std::endl;
			break;
		case 'e':
			std::cout << " is eating at Reef " << reef->get_id() << std::endl;
			break;
		case 'z':
			std::cout << " is swimming to Cave " << home->get_id() << " with a speed of " << get_speed() << std::endl;
			break;
		case 'p':
			std::cout << " is panicked!!!! And has a size of " << get_size() << std::endl;
			break;
		case 'h':
			std::cout << " is hidden in Cave " << home->get_id() << std::endl;
			break;
		case 'x':
			std::cout << " is dead." << std::endl;
			break;
		default:
			break;
	}
}

//Saves class specific information to file
void Fish::save(std::ofstream& file)
{
	GameObject::save(file);

	file << energy << " " << size << " " << prefeast_size << " ";
	destination.save(file);
	delta.save(file);

	if (reef != NULL)
		file << reef->get_id() << " ";
	else
		file << "-1" << " ";
	
	if (home != NULL)
		file << home->get_id() << " ";
	else
		file << "-1" << " ";
}

//Method to restore
void Fish::restore(std::ifstream& file, Model& model)
{
	GameObject::restore(file, model);

	world = &model;
	double x, y;
	file >> energy >> size >> prefeast_size >> x >> y;
	destination = CartPoint(x, y);
	file >> x >> y;
	delta = CartVector(x, y);
	int ID1, ID2;
	file >> ID1 >> ID2;
	if (ID1 == -1)
		reef = NULL;
	else
		reef = model.get_CoralReef_ptr(ID1);
	if (ID2 == -1)
		home = NULL;
	else
		home = model.get_Cave_ptr(ID2);
}
