#include "Cave.h"
#include "Fish.h"
#include "Model.h"

//Default constructor for a cave. Location (0,0)
Cave::Cave() : GameObject('c', 0)
{
	space = 100;
	state = 'e';
	inhabitants = 0;
	std::cout << "Cave default constructed" << std::endl;
}

//Constructor that only takes an id
Cave::Cave(int id) : GameObject('c', 0)
{
	space = 100;
	state = 'e';
	inhabitants = 0;
	std::cout << "Cave default constructed" << std::endl;
}

//Constructor for a cave at given location and id
Cave::Cave(int in_id, CartPoint in_loc) : GameObject('c', in_id, in_loc)
{
	space = 100;
	state = 'e';
	inhabitants = 0;
	std::cout << "Cave constructed" << std::endl;
}

//Destructor
Cave::~Cave()
{
	std::cout << "Cave destructed" << std::endl;
}

//Returns the space left in the cave
double Cave::get_space()
{
	return space;
}

//Returns the number of inhabitants in the cave
int Cave::get_inhabitants()
{
	return inhabitants;
}

//Attempts to hide a fish. If there is room, returns true and reduces the 
//	space in the cave. IF not, returns false.
bool Cave::hide_fish(Fish* fish_to_hide)
{
	if (fish_to_hide->is_hidden())
		return false;
	else if (space >= fish_to_hide->get_size())
	{
		space = space - fish_to_hide->get_size();
		inhabitants++;
		return true;
	}
	else
		return false;
}

//Attempts to release a fish. If the fish is hidden, increases the size of
//	the cave and returns true. If not, returns false.
bool Cave::release_fish(Fish* fish_to_release)
{
	if (fish_to_release->is_hidden())
	{
		space = space + fish_to_release->get_size();
		inhabitants--;
		return true;
	}
	else
		return false;
}

//Updates the state of the cave depending on the space left in the cave
bool Cave::update()
{
	if (space == 0 && state != 'p')
	{
		state = 'p';
		display_code = 'C';
		std::cout << "Cave " << get_id() << " is packed like sardines" << std::endl;
		return true;
	}
	if (space != 0 && state == 'p')
	{
		state = 'e';
		display_code = 'c';
		return true;
	}
	else
		return false;
}

//Prints the status of the cave including how much space is left in the cave
void Cave::show_status()
{
	std::cout << "Cave Status: ";
	GameObject::show_status();
	std::cout << " has a space of " << space << std::endl;
}

//Writes class specific information to file
void Cave::save(std::ofstream& file)
{
	GameObject::save(file);
	file << space << " " << inhabitants << " ";
}

//Reads class specific information from file
void Cave::restore(std::ifstream& file, Model& model)
{
	GameObject::restore(file, model);
	file >> space >> inhabitants;
}