#include "Sharknado.h"
#include "Model.h"

//Returns the only instance of the Sharknado that can be made
Sharknado* Sharknado::getInstance(Model* mod)
{
	static Sharknado* instance = new Sharknado(mod);
	return instance;
}

//Constructor takes the model as a parameter
Sharknado::Sharknado(Model* model) : GameObject('x', 0)
{
	world = model;
	swept_away.clear();
}

//Destructor
Sharknado::~Sharknado()
{
	std::cout << "Sharknado destructed" << std::endl;
}

//Returns true
bool Sharknado::is_alive()
{
	return true;
}

//Deletes all the fish that were swept away by the Sharknado
void Sharknado::deleteSweptFish()
{
	for (std::list<Fish*>::iterator fish = swept_away.begin(); fish != swept_away.end(); ++fish)
		delete *fish;
}

//Prints all the fish swept away by the Sharknado
void Sharknado::print_fish_swept_away()
{
	int num = 1;
	std::cout << "----------The History of Sharknado's Wrath----------" << std::endl;
	for (std::list<Fish*>::iterator fish = swept_away.begin(); fish != swept_away.end(); ++fish)
		std::cout << "(" << num++ << ")" << " - " << (*fish)->get_type() << (*fish)->get_id() << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
}

//Checks the Sharknado clock and acts accordingly
bool Sharknado::update()
{
	//5 time ticks before the Sharknado's coming
	if (world->time % 15 == 10)
	{
		std::cout << "The Sharknado is coming!" << std::endl;
		return true;
	}

	//Sharknado's comeing
	else if (world->time % 15 == 0)
	{
		std::cout << "The Sharknado is upon us!" << std::endl;

		//Goes through all fish
		std::list<Fish*>::iterator fish = world->fish_ptrs.begin();
		while (fish != world->fish_ptrs.end())
		{
			//Fish that aren't hidden or mating (which are essentially hidden)
			if (!((*fish)->is_hidden()) && (*fish)->get_state() != 'm')
			{
				//Add to Sharknado's lists to keep track of what it sweeps away
				swept_away.push_back(*fish);
				swept_away_once.push_back(*fish);

				//Removes the fish from active pointers, object pointers, and fish pointers
				for (std::list<GameObject*>::iterator ob = world->object_ptrs.begin(); ob != world->object_ptrs.end(); ++ob)
					if ((*ob)->get_type() == (*fish)->get_type() && (*ob)->get_id() == (*fish)->get_id())
					{
						world->object_ptrs.erase(ob++);
						break;
					}
				for (std::list<GameObject*>::iterator ob = world->active_ptrs.begin(); ob != world->active_ptrs.end(); ++ob)
					if ((*ob)->get_type() == (*fish)->get_type() && (*ob)->get_id() == (*fish)->get_id())							
					{
						world->active_ptrs.erase(ob++);
						break;
					}
				world->fish_ptrs.erase(fish++);
			}
			else
				++fish;
		}

		//After all fish are either hiding, mating, or swept up, displays what it just claimed
		std::cout << "----------The Sharknado Claimed----------" << std::endl; 
		int num = 1;
		for (std::list<Fish*>::iterator fish = swept_away_once.begin(); fish != swept_away_once.end(); ++fish)
			std::cout << "(" << num++ << ")" << " - " << (*fish)->get_type() << (*fish)->get_id() << std::endl;
		std::cout << "-----------------------------------------" << std::endl;

		//Clears the list that contains the fish claimed during a single coming of the Sharknado
		swept_away_once.clear();
		return true;
	}
	return false;
}

//Method to save
void Sharknado::save(std::ofstream& file)
{
	file << swept_away.size() << " ";
	for (std::list<Fish*>::iterator fish = swept_away.begin(); fish != swept_away.end(); ++fish)
		file << (*fish)->get_type() << " " << (*fish)->get_id() << " ";
}

//Method to restore
void Sharknado::restore(std::ifstream& file, Model&model)
{
	int num;
	swept_away.clear();
	file >> num;
	for (int i = 0; i < num; i++)
	{
		char type;
		int id;
		file >> type >> id;
		switch (type)
		{
		case 'T':
		{
			Tuna* tuna = new Tuna(id, world);
			swept_away.push_back(tuna);
		}
			break;
		case 'S':
		{
			Shark* shark = new Shark(id, world);
			swept_away.push_back(shark); 
		}
			break;
		default:
			break;
		}
	}
}

