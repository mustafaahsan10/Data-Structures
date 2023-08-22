#include <iostream>
#include <string>
#include <assert.h>
#include <fstream>
using namespace std;
template <class v>
struct HashItem
{
	int key;
	v value;
	short status;
	HashItem()
	{
		status = 0;
	}
};
template <class v>
class HashMap
{
private:
	HashItem<v>* hashArray;
	int capacity;
	int currentElements;
	virtual int getNextCandidateIndex(int key, int i)
	{
		return (key + i) % capacity;
	}
public:
	HashMap()
	{
		capacity = 10;
		currentElements = 0;
		hashArray = new HashItem<v>[capacity];
	}
	int get_capacity()
	{
		return capacity;
	}
	HashMap(int const cap)
	{
		assert(cap > 1);
		capacity = cap;
		hashArray = new HashItem<v>[capacity];
		currentElements = 0;

	}
	void create(int t)
	{
		delete[]hashArray;
		hashArray = new HashItem<v>[t];
		capacity = t;
	}
	void insert(int const k, v const val)
	{
		int i = 0;
		int index = getNextCandidateIndex(k, i);

		while (hashArray[index].status == 2)
		{
			if (i < capacity)
			{
				index = getNextCandidateIndex(k, i);
				i++;
			}
			else
			{
				return;
			}

		}
		//print();
		hashArray[index].key = k;
		hashArray[index].value = val;
		hashArray[index].status = 2;
		currentElements++;
		//print();


		float load_factor = currentElements;
		load_factor /= capacity;
		if (load_factor >= 0.75)
		{
			doubleCapacity();
		}

	}
	void print()
	{
		for (int i = 0; i < capacity; i++)
		{
			if (hashArray[i].status == 2)
			{
				cout << i << ")" << hashArray[i].key << "   " << hashArray[i].value << "  status:  " << hashArray[i].status << " ";
			}
			else
			{
				cout << i << ") " << "NULL" << "  ";
			}
		}
		cout << endl;
	}

	void doubleCapacity()
	{
		HashItem<v>* temp = new HashItem<v>[capacity];
		for (int i = 0; i < capacity; i++)
		{
			if (hashArray[i].status != 0 && hashArray[i].status != 1)
			{
				temp[i] = hashArray[i];
			}
		}
		delete[]hashArray;
		hashArray = new HashItem<v>[capacity * 2];
		HashItem<v> x;
		int index = 0;
		int ii = 0;
		for (int i = 0; i < capacity; i++)
		{
			if (temp[i].status != 0 && temp[i].status != 1)
			{
				index = temp[i].key % capacity;
				while (hashArray[index].status == 2)
				{
					index = getNextCandidateIndex(temp[i].key, ii);
					ii++;
				}
				hashArray[index] = temp[i];
			}
			else
			{
				hashArray[i] = x;
			}
		}
		capacity = capacity * 2;

	}

	bool deleteKey(int const k)
	{
		int index = k % capacity;
		int i = 1;
		while (hashArray[index].status == 2 && hashArray[index].key != k)
		{
			if (i < capacity)
			{

				index = getNextCandidateIndex(k, i);
				i++;

			}
			else
			{
				return false;
			}
		}

		if (hashArray[index].key == k && hashArray[index].status == 2)
		{

			hashArray[index].status = 1;

			currentElements--;
			return true;
		}
		else
		{
			return false;
		}

	}
	v* get(int const k)
	{
		int i = 0;
		int index = getNextCandidateIndex(k, i);
		while (hashArray[index].key != k || hashArray[index].status != 2)
		{
			if (i < capacity)
			{
				index = getNextCandidateIndex(k, i);
				i++;


			}
			else
			{
				break;
			}

		}
		if (hashArray[index].key == k && hashArray[index].status == 2)
		{
			return &hashArray[index].value;
		}
		return nullptr;

	}
	~HashMap()
	{
		delete[] hashArray;
	}
};
template <class v>
class Qhashmap :public HashMap<v>
{

	int getNextCandidateIndex(int key, int i)
	{
		int capacity = HashMap<v>::get_capacity();
		return (key + (i * i)) % capacity;
	}
};
template <class v>
class Dhashmap :public HashMap<v>
{

	int getNextCandidateIndex(int key, int i)
	{
		int capacity = HashMap<v>::get_capacity();
		int first_value = key % capacity;
		int	second_value = (2 - (key % 2));
		return (first_value + (i * second_value)) % capacity;
	}
};
void populateHash(string filename, HashMap<string>* hash)
{
	ifstream file;
	file.open("students.txt");
	int total;
	file >> total;
	//hash->create(total);
	int roll;
	string name;
	float gpa;
	for (int a = 0; a < total; a++)
	{
		file >> roll;
		file >> name;
		file >> gpa;

		hash->insert(roll, name);

	}
}

int main()
{
	HashMap<string>* map;
	map = new HashMap<string>;
	populateHash("students.txt", map);
	//map->print();
	cout << *map->get(9);
	map->deleteKey(9);
	assert(map->get(9) == nullptr);
	delete map;
	map = new Qhashmap<string>;
	populateHash("students.txt", map);
	cout << *map->get(98);
	map->deleteKey(98);
	assert(map->get(98) == nullptr);
	delete map;
	map = new Dhashmap<string>;
	populateHash("students.txt", map);
	cout << *map->get(101);
	map->deleteKey(101);
	//assert(map->get(101) == nullptr);
	delete map;
	return 0;
}