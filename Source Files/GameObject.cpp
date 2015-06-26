#include "GameObject.h"
#include "Model.h"

//GameObject that takes in a code and an id as parameters
GameObject::GameObject(char in_code, int in_id)
{
	display_code = in_code;
	id_num = in_id;
	location = CartPoint();
	std::cout << "GameObject default constructed" << std::endl;
}

//Overloaded GameObject that take in a code, an id, and a location as parameters
GameObject::GameObject(char in_code, int in_id, CartPoint in_loc)
{
	display_code = in_code;
	id_num = in_id;
	location = in_loc;
	std::cout << "GameObject constructed" << std::endl;
}

//Destructor
GameObject::~GameObject()
{
	std::cout << "GameObject destructed" << std::endl;
}

//Returns the location of the object
CartPoint GameObject::get_location()
{
	return location;
}

//Returns the id of the object
int GameObject::get_id()
{
	return id_num;
}

//Returns the state of the object
char GameObject::get_state()
{
	return state;
}

//Returns the display code of the object
char GameObject::get_type()
{
	return display_code;
}

//Returns true
bool GameObject::is_alive()
{
	return true;
}

//Shows the status of the object
void GameObject::show_status()
{
	std::cout << display_code << " with ID " << id_num << " at location " << location;
}

//Draws the object into the gameboard
void GameObject::drawself(char* grid)
{
	if (display_code != NULL && get_id() != NULL)
	{
		if (grid[0] == '.')
		{
			grid[0] = display_code;
			grid[1] = get_id() + 48;
		}
		else
		{
			grid[0] = '*';
			grid[1] = ' ';
		}
	}
	
}

//Method to save 
void GameObject::save(std::ofstream& file)
{
	file << id_num << " " << display_code << " " << state << " ";
	location.save(file);
}

//Method to restore
void GameObject::restore(std::ifstream& file, Model& model)
{
	double x, y;
	file >> id_num >> display_code >> state >> x >> y;
	location = CartPoint(x, y);
}