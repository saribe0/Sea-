#include "Tuna.h"
#include "Model.h"

//Default constructor
Tuna::Tuna(Model* model) : Fish('T', 10, model)
{

}

//Overloaded constructor that takes an id
Tuna::Tuna(int id, Model* model) : Fish('T', id, 10, model)
{

}

//Overloaded constructor that takes a cave as a home and an id
Tuna::Tuna(int id, Cave* home, Model* model) : Fish('T', id, home, 10, model)
{

}

//Destructor
Tuna::~Tuna()
{

}

//Returns the potential speed of the fish
double Tuna::get_speed()
{
	return (1 / size)*energy * 4;
}

//Mates the tuna with the passed in tuna
bool Tuna::start_mating(Tuna *fish_mate)
{
	if (this->is_hidden() && fish_mate->is_hidden()) //Make sure both Tunas are hidden and not mating
			if (fish_mate->home == this->home) //Make sure each of them are hidden in the same cave
				if ((this->home)->get_space() >= 10) //Makes sure there is room for a new Tuna
					if (this->size >= 40 && this->size <= 60 && fish_mate->size >= 40 && fish_mate->size <= 60) //Makes sure the Tunas are the right size
						if ((this->home)->get_inhabitants() == 2) //Makes sure the Tunas are alone
							if (this != fish_mate)
							{
								mate = fish_mate;
								std::cout << this->display_code << this->get_id() << ": I found my mate!" << std::endl;
								this->state = 'm';
								fish_mate->state = 'm';
								//So the other tuna doesn't measure two time ticks faster than this tuna
								//	as it will be updated once more than this one
								if (fish_mate->get_id() > this->get_id()) 
									fish_mate->mate_time--;
								mate_time = 0;
								return true;
							}
	
	return false;
}

//Updates the Tuna
bool Tuna::update()
{
	//If mating
	if (state == 'm')
	{
		if (mate_time < 2)
		{
			mate_time++;
		}
		else
		{
			//If two time ticks are up and its the right tuna, create a new tuna
			if (this->mate != NULL)
			{
				int id = world->get_next_Fish_id();
				(world->fish_ptrs).push_back(new Tuna(id, home, world));
				(world->active_ptrs).push_back(world->get_Fish_ptr(id));
				(world->object_ptrs).push_back(world->get_Fish_ptr(id));
				std::cout << "Tuna " << id << " was born in cave " << home->get_id() << std::endl;
			}
			this->mate = NULL;
			this->state = 'h';
			this->mate_time = 0;
			return true;
		}
	}
	return Fish::update();

	return false;
}

//Shows the Tuna's status
void Tuna::show_status()
{
	std::cout << "Tuna status: ";
	Fish::show_status();
	if (state == 'm')
		std::cout << " is mating in Cave " <<home->get_id() << std::endl;
}

//Writes class specific information to file
void Tuna::save(std::ofstream& file)
{
	Fish::save(file);

	file << mate_time << " ";

	if (mate != NULL)
		file << mate->get_id() << " ";
	else
		file << "-1" << " ";
}

//Reads class specific information from file
void Tuna::restore(std::ifstream& file, Model& model)
{
	Fish::restore(file, model);

	int ID;
	file >> mate_time >> ID;
	if (ID == -1)
		mate = NULL;
	else
		mate = model.get_Fish_ptr(ID);
}
