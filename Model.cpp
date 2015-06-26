#include "Model.h"


//Constructor creates 2 caves, 3 coral reefs and 2 fish
//Also creates 4 dynamic arrays to hold pointers to all these objects
Model::Model()
{
	time = 0;

	//Initialize objects
	cave_ptrs.push_back(new Cave(1, CartPoint(5, 1)));
	cave_ptrs.push_back(new Cave(2, CartPoint(6, 2)));

	reef_ptrs.push_back(new CoralReef(1, CartPoint(1, 20)));
	reef_ptrs.push_back(new CoralReef(2, CartPoint(20, 1)));
	reef_ptrs.push_back(new CoralReef(3, CartPoint(20, 20)));

	fish_ptrs.push_back(new Tuna(1, get_Cave_ptr(1), this));
	fish_ptrs.push_back(new Tuna(2, get_Cave_ptr(2), this));
	fish_ptrs.push_back(new Tuna(3, get_Cave_ptr(2), this));
	fish_ptrs.push_back(new Shark(4, this));
	fish_ptrs.push_back(new Shark(5, this));

	//Put all objects in object_ptrs list and active_ptrs list
	for (std::list<Cave*>::iterator cave = cave_ptrs.begin(); cave != cave_ptrs.end(); ++cave)
		object_ptrs.push_back(*cave);
	for (std::list<CoralReef*>::iterator reef = reef_ptrs.begin(); reef != reef_ptrs.end(); ++reef)
		object_ptrs.push_back(*reef);
	for (std::list<Fish*>::iterator fish = fish_ptrs.begin(); fish != fish_ptrs.end(); ++fish)
		object_ptrs.push_back(*fish);

	for (std::list<GameObject*>::iterator ob = object_ptrs.begin(); ob != object_ptrs.end(); ++ob)
		if ((*ob)->get_state() != 'x')
			active_ptrs.push_back(*ob);

	//Sharknado only put in active_ptrs list
	active_ptrs.push_back(Sharknado::getInstance(this));

	std::cout << "Model default constructed" << std::endl;
}

//Destructor deletes all objects created in constructor
Model::~Model()
{
	//Starts by printing the Sharknados wrath and deleting those fish objects
	Sharknado::getInstance(this)->print_fish_swept_away();
	Sharknado::getInstance(this)->deleteSweptFish();

	//Deletes all other game objects
	for (std::list<GameObject*>::iterator ob = object_ptrs.begin(); ob != object_ptrs.end(); ++ob)
		delete *ob;
	std::cout << "Model Destructed" << std::endl;

	//Deletes sharknado
	delete Sharknado::getInstance(this);
}

//Returns the pointer to the fish with the passed in ID
Fish* Model::get_Fish_ptr(int id_num)
{
	for (std::list<Fish*>::iterator fish = fish_ptrs.begin(); fish != fish_ptrs.end(); ++fish)
		if ((*fish)->get_id() == id_num)
			return (*fish);
	return NULL;
}

//Returns the pointer to the Coral Reef with the passed in ID
CoralReef* Model::get_CoralReef_ptr(int id_num)
{
	for (std::list<CoralReef*>::iterator reef = reef_ptrs.begin(); reef != reef_ptrs.end(); ++reef)
		if ((*reef)->get_id() == id_num)
			return (*reef);
	return NULL;
}

//Returns the pointer to the Cave with the passed in ID
Cave* Model::get_Cave_ptr(int id_num)
{
	for (std::list<Cave*>::iterator cave = cave_ptrs.begin(); cave != cave_ptrs.end(); ++cave)
		if ((*cave)->get_id() == id_num)
			return (*cave);
	return NULL;
}

//Adds the object at the end of the proper list
void Model::add_new_object(GameObject* object)
{
	object_ptrs.push_back(object);
	active_ptrs.push_back(object);

	char type = object->get_type();
	
	//Figures out the type and dynamically casts it so it can be put in the proper list
	switch (type)
	{
	case 'R':
		if (CoralReef* reef = dynamic_cast<CoralReef*>(object))
			reef_ptrs.push_back(reef);
		break;
	case 'c':
		if (Cave* cave = dynamic_cast<Cave*>(object))
			cave_ptrs.push_back(cave);
		break;
	case 'T':
		if (Tuna* tuna = dynamic_cast<Tuna*>(object))
			fish_ptrs.push_back(tuna);
		break;
	case 'S':
		if (Shark* shark = dynamic_cast<Shark*>(object))
			fish_ptrs.push_back(shark);
		break;
	}
}

//Returns next available fish ID
int Model::get_next_Fish_id()
{
	int i = 1;
	do{
		if (get_Fish_ptr(i) == NULL)
			return i;
		else
			i++;
	} while (get_Fish_ptr(i) != NULL);
	return i;
}

//Updates all the objects by calling each of their update functions
bool Model::update()
{
	time++;
	bool at_least_one_true = false;

	//Loops through all active objects
	std::list<GameObject*>::iterator ob = active_ptrs.begin();
	while (ob != active_ptrs.end())
	{
		//Each object is updated
		if ((*ob)->update())
		{
			at_least_one_true = true;
		}
		//If the object is a Tuna, try to mate it
		if (Tuna* tuna1 = dynamic_cast<Tuna*>(*ob)) 
		{
			for (std::list<Fish*>::iterator fish = fish_ptrs.begin(); fish != fish_ptrs.end(); ++fish)
				if (Tuna* tuna2 = dynamic_cast<Tuna*>(*fish))
					tuna1->start_mating(tuna2);
		}
		//If the object is dead, remove it and increment the iterator
		if ((*ob)->get_state() == 'x')
		{
			active_ptrs.erase(ob++);
			std::cout << "Model: Dead object removed" << std::endl;
		}
		//If not dead, just incremenet the iterator
		else 
			++ob;
	}

	return at_least_one_true;
}

//Shows the status of every object on the gameboard
void Model::show_status()
{
	std::cout << "---Fish---" << std::endl;
	for (std::list<Fish*>::iterator fish = fish_ptrs.begin(); fish != fish_ptrs.end(); ++fish)
		(*fish)->show_status();
	std::cout << "---Cave---" << std::endl;
	for (std::list<Cave*>::iterator cave = cave_ptrs.begin(); cave != cave_ptrs.end(); ++cave)
		(*cave)->show_status();
	std::cout << "---Reef---" << std::endl;
	for (std::list<CoralReef*>::iterator reef = reef_ptrs.begin(); reef != reef_ptrs.end(); ++reef)
		(*reef)->show_status();
}


//Prints the time and calls the plot and draw function of the view class to print the gameboard
void Model::display(View& view)
{
	std::cout << "Time: " << time << std::endl;
	view.clear();
	for (std::list<GameObject*>::iterator act = active_ptrs.begin(); act != active_ptrs.end(); ++act)
		view.plot(*act);
	view.draw();
}


//Writes model information to file
void Model::save(std::ofstream& file)
{
	//Writes model specific information and creates a key
	file << time << " " << active_ptrs.size() << std::endl;
	for (std::list<GameObject*>::iterator ob = active_ptrs.begin(); ob != active_ptrs.end(); ++ob)
	{
		file << (*ob)->get_type() << " " << (*ob)->get_id() << " ";
		if ((*ob)->get_type()=='x')
			Sharknado::getInstance(this)->save(file);
	}

	//Goes through all objects and calls their respective save functions
	file << std::endl;
	for (std::list<GameObject*>::iterator ob = active_ptrs.begin(); ob != active_ptrs.end(); ++ob)
		if ((*ob)->get_type() != 'x')
			{
				(*ob)->save(file);
				file << std::endl;
			}
}

//Reads a model from file
void Model::restore(std::ifstream& file)
{
	//Prints fish swept away before restoration
	Sharknado::getInstance(this)->print_fish_swept_away();

	int ptrs_length;
	file >> time >> ptrs_length;

	//Clears lists and deletes objects in preperation for restored ones
	cave_ptrs.clear();
	reef_ptrs.clear();
	fish_ptrs.clear();
	active_ptrs.clear();
	for (std::list<GameObject*>::iterator ob = object_ptrs.begin(); ob != object_ptrs.end(); ++ob)
		delete *ob;
	object_ptrs.clear();

	//Goes through key and creates all objects
	char type;
	int id;
	for (int i = 0; i < ptrs_length; i++)
	{
		file >> type >> id;
		switch (type)
		{
		case 'c':
		{
			Cave *cave = new Cave(id);
			cave_ptrs.push_back(cave);
			active_ptrs.push_back(cave);
			object_ptrs.push_back(cave);
		}
			break;
		case 'C':
		{
			Cave *cave = new Cave(id);
			cave_ptrs.push_back(cave);
			active_ptrs.push_back(cave);
			object_ptrs.push_back(cave);
		}
			break;
		case 'R':
		{
			CoralReef *reef = new CoralReef(id);
			reef_ptrs.push_back(reef);
			active_ptrs.push_back(reef);
			object_ptrs.push_back(reef);
		}
			break;
		case 'r':
		{
			CoralReef *reef = new CoralReef(id);
			reef_ptrs.push_back(reef);
			active_ptrs.push_back(reef);
			object_ptrs.push_back(reef);
		}
			break;
		case 'T':
		{
			Tuna *tuna = new Tuna(id, this);
			fish_ptrs.push_back(tuna);
			active_ptrs.push_back(tuna);
			object_ptrs.push_back(tuna);
		}
			break;
		case 'S':
		{
			Shark *shark = new Shark(id, this);
			fish_ptrs.push_back(shark);
			active_ptrs.push_back(shark);
			object_ptrs.push_back(shark);
		}
			break;
		case 'x':
		{
			active_ptrs.push_back(Sharknado::getInstance(this));
			Sharknado::getInstance(this)->restore(file, *this); //Restore sharknado immediately
		}
			break;
		}
	}

	//Restores all objects except Sharknado which is already restored
	for (std::list<GameObject*>::iterator ob = object_ptrs.begin(); ob != object_ptrs.end(); ++ob)
		(*ob)->restore(file, *this);
}