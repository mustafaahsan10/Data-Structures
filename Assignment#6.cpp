#include <iostream>
#include <list>
#include <string>
#include <queue>
#include <cstdlib>
#include <time.h>
#include <stack>
#include <fstream>
#include <conio.h>
#include <assert.h>
using namespace std;

class V
{
	string type;
	int ID;
public:
	V() {}
	V(string type, int ID) 
	{
		this->type = type;
		this->ID = ID;
		
	}
	V(const V& temp)
	{
		type = temp.type;
		ID = temp.ID;

	}
	int get_id()
	{
		return ID;
	}
	string get_type()
	{
		return type;
	}
	~V() {}
};
class g_node
{
	V vert;
	int weight;
	bool visited;
public:
	g_node()
	{
		visited = false;
	}
	g_node(const V& temp, int w)
	{
		vert= temp;
		weight = w;
		visited = false;

	}
	V get_vert()
	{
		return vert;
	}
	int get_id()
	{
		return vert.get_id();
	}
	int get_weight()
	{
		return weight;
	}
	string get_type()
	{
		return vert.get_type();
	}
	void set_bool(bool flag)
	{
		visited = flag;
	}
	bool get_bool()
	{
		return visited;
	}
	
	~g_node() {}
};
ostream& operator << (ostream& out,  g_node& c)
{
	out << "---" << c.get_weight() << "--->" << c.get_id() << "(" << c.get_type() << ") ";
	return out;

}
class Graph
{
public:
	list<g_node>* adj_list;
	int edge_no;
	V* all_vertices;
	int curr_v;
	int toal_vert;

	Graph() 
	{
		all_vertices = NULL;
		adj_list=NULL;
		curr_v = 0;
		edge_no = 0;
	}
	bool create_edge(int sid, int did, int w)
	{
		V s_id;
		V d_id;
		bool flag = false;
		for (int i = 0; i < curr_v; i++)
		{
			if (all_vertices[i].get_id() == sid)
			{
				s_id = all_vertices[i];
				//cout << sid<<":  \n";
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			return flag;
		}
		for (int i = 0; i < curr_v; i++)
		{
			if (all_vertices[i].get_id() == did)
			{
				d_id = all_vertices[i];
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			return flag;
		}
		g_node g1(s_id, w);
		g_node g2(d_id, w);
		add_node(sid, g2);
		add_node(did, g1);
	}
	void add_node(int g1,g_node &g2)
	{
		adj_list[g1].push_back(g2);
	}
	void create_adjlist(int e)
	{
		adj_list= new list<g_node>[e+4];
		all_vertices = new V[e];
		toal_vert = e + 4;
		
	}
	void create_vlist()
	{
		
	}
	V* get_vert_arr()
	{
		return all_vertices;
	}
	void addvert(V v)
	{
		V* temp_v = new V[curr_v + 6];
		for (int i = 0; i <curr_v; i++)
		{
			temp_v[i] = all_vertices[i];
		}
		delete[]all_vertices;
		all_vertices = temp_v;
		all_vertices[curr_v] = v;
		curr_v++;
		if (curr_v == toal_vert)
		{
			list<g_node>* temp = new list<g_node>[curr_v + 12];


			for (int i = 1; i <= curr_v; i++)
			{
				std::list<g_node>::iterator it = temp[i].begin();
				for (auto j = adj_list[i].begin(); j != adj_list[i].end(); ++j)
				{
					if (it != temp[i].end())
					{


						it = j;
						i++;
					}
					else
					{
						break;
					}



				}
			}

			for (int i = 1; i <= curr_v; i++)
			{
				adj_list[i].clear();
			}
			adj_list = temp;

		}
	}
	bool in_vert_list(V v)
	{
		for (int i = 0; i < curr_v; i++)
		{
			if (all_vertices[i].get_id() == v.get_id())
			{
				return true;
			}
		}
		return false;
	}
	void print() {
		for (int i = 1; i <=curr_v; i++)
		{
			cout <<all_vertices[i-1].get_id() <<"(" << all_vertices[i - 1].get_type()<< ")" << ":   ";
			for (auto j = adj_list[i].begin(); j != adj_list[i].end(); ++j) {

				cout << *j<<" ";
			}
			cout << endl;
		}
		
	}
	int get_curr()
	{
		return curr_v;
	}
	void populate_graph(string file_name)
	{
		ifstream file;
		file.open("input.txt");
		int vertices;
		file >> vertices;
		int ver_ID;
		toal_vert = vertices;
		string type;
		create_adjlist(vertices);
	
		for (int a = 0; a < vertices; a++)
		{
			file >> ver_ID;
			file >> type;
			V v(type, ver_ID);
			addvert(v);
		}
		int edge;
		int s_id;
		int d_id;
		int weight;
		file >> edge;
		edge_no = edge;
		
		for (int a = 0; a < edge; a++)
		{
			file >> s_id;
			file >> d_id;
			file >> weight;
			create_edge(s_id, d_id, weight);



		}
		print();
	}

	
};
struct HeapItem
{
	V source;
	V dest;
	int key;
};
class MinHeap
{
	
private:

	HeapItem* arr;
	int capacity;
	int totalItems;

	void ReheapUp(int root, int bottom)
	{
		int parent;
		if (bottom > root)
		{
			parent = (bottom - 1) / 2;
			if (arr[parent].key > arr[bottom].key)
			{
				swap(arr[parent], arr[bottom]);
				ReheapUp(root, parent);
			}
		}
	}


	void ReheapDown(int root, int bottom)
	{
		int minChild, rightChild, leftChild;
		leftChild = 2 * root + 1;
		rightChild = 2 * root + 2;
		if (leftChild <= bottom)
		{
			if (leftChild == bottom)
			{
				minChild = leftChild;
			}
			else
			{
				if (arr[leftChild].key >= arr[rightChild].key)
				{
					minChild = rightChild;
				}
				else
				{
					minChild = leftChild;
				}
			}
			if (arr[root].key > arr[minChild].key)
			{
				swap(arr[root], arr[minChild]);
				ReheapDown(minChild, bottom);
			}
		}
	}

public:
	MinHeap()
	{
		arr = nullptr;
		capacity = 0;
		totalItems = 0;
	}
	void create(int cap)
	{
		capacity = cap;
		arr = new HeapItem[capacity];
	}
	MinHeap(int _capacity)
	{
		assert(_capacity >= 1);

		arr = new  HeapItem[_capacity];
		capacity = _capacity;
		totalItems = 0;
	}
	void print() {
		if (isEmpty())
			return;
		for (int i = 0; i < totalItems; i++) {
			cout << arr[i].key << " ";
		}
		cout << endl;
	}
	void insert(V src,V dst,int w)
	{
		if (totalItems == capacity)
		{
			if (arr == nullptr)
			{
				arr = new HeapItem[1];
				capacity = 1;
				return;
			}

			int newCapacity = capacity * 2;
			HeapItem* newArr = new HeapItem[newCapacity];

			for (int i = 0; i < totalItems; i++)
			{
				newArr[i] = arr[i];
			}

			if (arr != nullptr)
				delete arr;

			capacity = newCapacity;
			arr = newArr;
		}
		arr[totalItems].source = src;
		arr[totalItems].dest = dst;
		arr[totalItems].key = w;
		ReheapUp(0,totalItems);
		totalItems++;



	}
	HeapItem extract_min()
	{
		HeapItem v;
		v = arr[0];
		arr[0] = arr[totalItems - 1];
		totalItems--;
		ReheapDown(0,totalItems);
		return v;
	}

	bool isEmpty() const
	{
		return (totalItems == 0);
	}
	void destr()
	{
		if (arr != nullptr)
		{
			delete[]arr;
			arr = nullptr;
			capacity = 0;
			totalItems = 0;
		}

	}

	~MinHeap()
	{
		destr();
	}

};
V id_to_vert(int id,V* a,int size)
{
	for (int i = 0; i <size ; i++)
	{
		if (a[i].get_id() == id)
		{
			return a[i];
		}
	}
}
void save_to_file(Graph g,string file_name)
{
	ofstream myfile;
	myfile.open(file_name);
	myfile << g.curr_v;
	myfile << endl;
	for (int i = 0; i < g.curr_v; i++)
	{
		myfile << g.all_vertices[i].get_id()<<" "<< g.all_vertices[i].get_type();
		myfile << endl;
	}
	myfile << g.edge_no;
	myfile << endl;
	for (int i = 1; i <=g.curr_v; i++)
	{
		for (auto j = g.adj_list[i].begin(); j != g.adj_list[i].end(); ++j)
		{
			
				myfile << i << " " << j->get_id() << " " << j->get_weight();
				myfile << endl;
			
		}
	}
	myfile.close();
}
void shortest_path(Graph g,int s)
{
	Graph temp_g;
	temp_g.create_adjlist(g.get_curr()+5);
	V* a = g.get_vert_arr();
	MinHeap mh(g.edge_no);
	int count = 0;
	for(int i = s; i <=g.curr_v;)
	{
		if (count > g.curr_v-2)
		{
			break;
		}
		
		V src = id_to_vert(i, a, g.get_curr());
		for (auto j = g.adj_list[i].begin(); j != g.adj_list[i].end(); ++j) 
		{
			V dest = j->get_vert();
			if (!temp_g.in_vert_list(dest))
			{
				mh.insert(src, dest, j->get_weight());
			}
			
		}
		HeapItem min_edge = mh.extract_min();
		temp_g.addvert(min_edge.source);

		temp_g.addvert(min_edge.dest);
		cout << min_edge.source.get_id() << "(" << min_edge.source.get_type() << ")" << "--"<< min_edge.key << "-->" << min_edge.dest.get_id() << "(" << min_edge.dest.get_type() << ")";
		temp_g.create_edge(min_edge.source.get_id(), min_edge.dest.get_id(), min_edge.key);
		temp_g.edge_no++;
		count++;
		i = min_edge.dest.get_id();
		//temp_g.print();
		cout << endl;
	}
	_getch();
}

int main()
{
	Graph g;
	int choice = 0;
	do
	{
		system("cls");
		g.print();
		cout << "Press 1 Input a graph from a file\n";
		cout << "Press 2 Save a graph in a file\n";
		cout << "Press 3 Add a vertex in existing graph G\n";
		cout << "Press 4 Add an edge in existing graph G\n";
		cout << "Press 5 Print the shortest path\n";
		cout << "Press -1 to Exit\n";
		cin >> choice;
		if (choice == 1)
		{
			string input_file;
			cout << "enter the name of the file: ";
			cin >> input_file;
			g.populate_graph(input_file+".txt");

		}
		else if (choice == 2)
		{
			string output_file;
			cout << "enter the name of the file: ";
			cin >> output_file;
			save_to_file(g, output_file+".txt");
		}
		else if (choice == 3)
		{
			string type;
			int ID;
			cout << "enter the type of the vertice: ";
			cin >> type;
			cout << "enter the ID: ";
			cin >> ID;
			V v(type, ID);
			g.addvert(v);

		}
		else if (choice == 4)
		{
			int src_id;
			int dest_id;
			int weight;
			cout << "enter the ID of the source: ";
			cin >> src_id;
			cout << "enter the ID of the destination: ";
			cin >> dest_id;
			cout << "enter the weight of the edge: ";
			cin >> weight;
			if (!g.create_edge(src_id, dest_id, weight))
			{
				cout << "Vertice not in graph\n";
			}
		}
		else if (choice == 5)
		{
			int start;
			cout << "enter start position: ";
			cin >> start;
			shortest_path(g,start);
		}
		else if (choice == -1)
		{
			break;
		}
	} while (choice!=-1);

	system("pause");
	return 0;
}