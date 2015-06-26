#include "Shark.h"
#include "Model.h"
#include <stdlib.h>

//Default constructor
Shark::Shark(Model* model) : Fish('S', 20, model)
{
	attack_strength = 2;
	range = 1;
	//std::cout << "Shark Constructed" << std::endl;
}

//Overloaded constructor that takes an id and randomizes the position
Shark::Shark(int id, Model* model) : Fish('S', id, rand_cartpoint(model), 20, model)
{
	attack_strength = 2;
	range = 1;
}

//Overloaded constructor which takes an id and the initial position of the Shark
Shark::Shark(int id, CartPoint loc, Model* model) : Fish('S', id, loc, 20, model)
{
	attack_strength = 2;
	range = 1;
	std::cout << "Shark Constructed" << std::endl;
}

//Destructor
Shark::~Shark()
{

}

//Returns a random point (seeded by the model's time)
CartPoint Shark::rand_cartpoint(Model* model)
{
	srand(model->time);
	return CartPoint(rand() % 20, rand() % 20);
	//return CartPoint(6, 3);
}

//Returns the potential speed of the fish
double Shark::get_speed()
{
	return (1 / size)*energy * 8;
}

//Starts attacking another fish
void Shark::start_attack(Fish *target)
{
	if (is_alive())
	{
		//If the fish is close enough, attack it
		if (cart_distance(location, target->get_location()) <= range)
		{
			std::cout << display_code << get_id() << ": Chomp!" << std::endl;
			this->target = target;
			state = 'a';
			target->get_bitten(attack_strength);
		}
		else
			std::cout << display_code << get_id() << ": Fish are friends, not food" << std::endl;
	}
}

//Updates the Tuna
bool Shark::update()
{
	switch (state)
	{
	case 'x':
		break;

	case 's':
		break;

	case 'a': //attacking
		if (cart_distance(location, target->get_location()) > range) //fish is too far away
		{
			std::cout << "Darn! It escaped" << std::endl;
			target = NULL;
			state = 's';
			return true;
		}
		else //fish is close enough
		{
			std::cout << display_code << get_id() << ": Chomp!" << std::endl;
			target->get_bitten(attack_strength);
			
			if (target->get_state() == 'x') //fish is killed
			{
				std::cout << "I triumph" << std::endl;
				energy += 5;
				state = 's';
				return true;
			}
		}
		break;
	case 'e': //eating at a coral reef which is impossible
		break;
	}
	return false;
}

//Shows the Tuna's status
void Shark::show_status()
{
	std::cout << "Shark status: ";
	GameObject::show_status();

	switch (state)
	{
	case 'a':
		std::cout << " is attacking Fish " << target->get_id() << std::endl;
		break;
	case 's':
		std::cout << " has a speed of: " << get_speed() << " and is heading to: " << destination << std::endl;
		break;
	case 'f':
		std::cout << " is floating. Has a size of: " << size << " and energy of: " << energy << std::endl;
		break;
	default:
		std::cout << std::endl;
	}
}

//Writes class specific information to file
void Shark::save(std::ofstream& file)
{
	Fish::save(file);

	file << attack_strength << " " << range << " ";

	if (target != NULL)
		file << target->get_id() << " ";
	else
		file << "-1" << " ";
}

//Reads class specific information from file
void Shark::restore(std::ifstream& file, Model& model)
{
	Fish::restore(file, model);

	int ID;
	file >> attack_strength >> range >> ID;
	if (ID == -1)
		target = NULL;
	else
		target = model.get_Fish_ptr(ID);
}

