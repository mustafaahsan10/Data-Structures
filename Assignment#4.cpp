#include<iostream>
#include<conio.h>
#include<string>
using namespace std;
class Student
{
	string firstname;
	string secondname;
	int batch;
	string department;
	float cgpa;
public:
	Student() 
	{
	}
	Student(string firstname, string secondname, int batch, string department, float cgpa)
	{
		this->firstname = firstname;
		this->secondname = secondname;
		this->batch = batch;
		this->department = department;
		this->cgpa = cgpa;
		cout << "Name: " << firstname << " " << secondname << endl << "Batch: " << batch << endl << "Department: " << department << endl << "CGPA: " << cgpa << endl;


	}
	friend ostream& operator << (ostream& out, Student obj)
	{
		out << "Name: " << obj.firstname << " " << obj.secondname << endl << "Batch: " << obj.batch << endl << "Department: " << obj.department << endl << "CGPA: " << obj.cgpa << endl;
		return out;
	}
	
	~Student()
	{
	}
};

template<typename K, typename V>
struct Node
{
	K data;
	V value;
	Node* left;
	Node* right;
	Node()
	{
		left = NULL;
		right = NULL;
	}
	
};
template<typename K, typename V>
class BST
{
private:
	Node<K,V>* root;
public:
	BST()
	{
		root = NULL;
	}
	BST(BST& bt)
	{
		PostOrderConst(bt.root);
	}
	void PostOrderConst(Node<K, V>* rot)
	{
		PostOrderConstmake(rot);
	}
	void PostOrderConstmake(Node<K, V>* treenode)
	{
		if (treenode != NULL) {
			PostOrderConstmake(treenode->left);
			PostOrderConstmake(treenode->right);
			insert(treenode->data);

		}
	}
	void printLevelOrder(Node<K,V>* root)
	{
		int h = height(root);
		int i;
		for (i = 1; i <= h; i++)
			printCurrentLevel(root, i);
	}
	void printCurrentLevel(Node<K, V>* root, int level)
	{
		if (root == NULL)
			return;
		if (level == 1)
			cout << root->data << " ";
		else if (level > 1) {
			printCurrentLevel(root->left, level - 1);
			printCurrentLevel(root->right, level - 1);
		}
	}
	int height(Node<K, V>* node)
	{
		if (node == NULL)
			return 0;
		else {
			/* compute the height of each subtree */
			int lheight = height(node->left);
			int rheight = height(node->right);

			/* use the larger one */
			if (lheight > rheight) {
				return (lheight + 1);
			}
			else {
				return (rheight + 1);
			}
		}
	}
	bool insert(int val,V value)
	{

		Node<K,V>* newnode = new Node<K,V>;
		if (search_only(val))
		{
			search(val);
			return false;
		}
		else
		{


			if (root == NULL)
			{

				newnode->data = val;
				newnode->left = NULL;
				newnode->right = NULL;
				root = newnode;
				return true;
			}
			else
			{
				newnode = insert_at_new(root, val, value);
			}
			search(val);
		}
		return true;

	}
	Node<K,V>* insert_at_new(Node<K,V>* curr, int value, V value_node)
	{
		Node<K,V>* newnode = new Node<K,V>;
		if (value > curr->data)
		{
			if (curr->right == NULL)
			{

				newnode->data = value;
				newnode->value = value_node;
				newnode->left = NULL;
				newnode->right = NULL;
				curr->right = newnode;
			}
			else
			{

				insert_at_new(curr->right, value, value_node);
			}
		}
		else if (value < curr->data)
		{
			if (curr->left == NULL)
			{
				newnode->data = value;
				newnode->value = value_node;
				newnode->left = NULL;
				newnode->right = NULL;
				curr->left = newnode;
			}
			else
			{
				insert_at_new(curr->left, value, value_node);
			}
		}
		else if (value == curr->data)
		{
			return NULL;
		}
		return newnode;
	}
	void to_root(Node<K,V>* curr)
	{
		Node<K,V>* parent;
		Node<K,V>* grand_parent;
		parent = root;
		int count;
		while (curr != root)
		{
			parent = get_parent(root, curr->data);


			if (parent == root)
			{
				if (curr == parent->left)
				{
					rotate_right(parent); // Right Rotation
				}
				else
				{
					rotate_left(parent);  // Left Rotation
				}

			}
			else
			{
				parent = get_parent(root, curr->data);
				grand_parent = get_parent(root, parent->data);

				if ((curr == parent->left) && (parent == grand_parent->left))
				{

					rotate_right(grand_parent);  //Right Right Rotation
					rotate_right(parent);
				}
				else if ((curr == parent->right) && (parent == grand_parent->right))
				{
					rotate_left(grand_parent); //Left Left Rotation
					rotate_left(parent);
				}
				else if ((curr == parent->left) && (parent == grand_parent->right))
				{
					rotate_right(parent);        //Right Left Rotation
					rotate_left(grand_parent);

				}
				else if ((curr == parent->right) && (parent == grand_parent->left))
				{
					rotate_left(parent);         //Left Right Rotation
					rotate_right(grand_parent);

				}

			}

		}
		if (curr == root)
		{
			return;
		}
	}
	void rotate_right(Node<K,V>* curr)
	{
		Node<K,V>* new_p = curr->left;
		Node<K,V>* temp = new_p->right;
		Node<K,V>* p = get_parent(root, curr->data);
		new_p->right = curr;
		if (curr == root)
		{
			root = new_p;
		}
		else
		{
			if (p->left == curr)
			{
				p->left = new_p;
			}
			else
			{
				p->right = new_p;
			}
		}
		curr->left = temp;




	}
	void rotate_left(Node<K,V>* curr)
	{
		Node<K,V>* new_p = curr->right;
		Node<K,V>* temp = new_p->left;
		Node<K,V>* p = get_parent(root, curr->data);
		new_p->left = curr;
		if (curr == root)
		{
			root = new_p;
		}
		else
		{
			if (p->right == curr)
			{
				p->right = new_p;
			}
			else
			{
				p->left = new_p;
			}
		}
		curr->right = temp;

	}
	Node<K,V>* get_parent(Node<K,V>* curr, int value)
	{
		if (curr == NULL)
			return NULL;

		if (curr->left == NULL && curr->right == NULL)
			return NULL;

		if ((curr->left != NULL && curr->left->data == value) || (curr->right != NULL && curr->right->data == value))
			return curr;

		if (curr->data > value)
			return get_parent(curr->left, value);

		if (curr->data < value)
			return get_parent(curr->right, value);


	}
	Node<K,V>* search(Node<K,V>* node, K d)
	{

		if (node->left == nullptr && node->right == nullptr)
			return node;
		else if (node->data == d)
		{
			return node;
		}
		else if (node->data > d)
		{
			return search(node->left, d);
		}
		else if (node->data < d)
		{

			return search(node->right, d);
		}

	}
	bool search(K d)
	{

		if (root)
		{
			Node<K,V>* found = search(root, d);
			to_root(found);



		}
		return true;
	}
	void PreOrder()
	{
		PreOrder(root);
	}
	void PreOrder(Node<K,V>* treenode)

	{
		if (treenode != NULL) {
			visit(treenode);
			PreOrder(treenode->left);
			PreOrder(treenode->right);
		}
	}
	void InOrder()
	{
		InOrder(root);
	}
	void InOrder(Node<K,V>* treenode)

	{
		if (treenode != NULL) {
			InOrder(treenode->left);
			visit(treenode);
			InOrder(treenode->right);
		}
	}
	void PostOrder()
	{
		PostOrder(root);
	}
	void PostOrder(Node<K,V>* treenode)

	{
		if (treenode != NULL) {
			PostOrder(treenode->left);

			PostOrder(treenode->right);
			visit(treenode);
		}
	}
	void visit(Node<K,V>* treenode)
	{
		cout << "Roll Number: "<<treenode->data << " "<<endl;
		cout << treenode->value;
	}
	bool deleteR(K d)
	{
		if (!search_only(d))
		{
			search(d);
			return false;
		}
		else
		{
			deleteR(d, root);
			return true;
		}

	}
	void deleteR(K d, Node<K,V>*& node) {

		if (d > node->data)

			deleteR(d, node->right);

		else if (d < node->data)

			deleteR(d, node->left);

		else

			deleteNode(node);

	}
	void deleteNode(Node<K,V>*& node) {

		K d;
		Node<K,V>* temp;

		temp = node;
		Node<K,V>* pa = get_parent(root, temp->data);
		if (node->left == NULL) {
			node = node->right;
			delete temp;

		}
		else if (node->right == NULL) {
			node = node->left;
			delete temp;

		}
		else
		{

			getPredecessor(node->left, &d);
			node->data = d;
			deleteR(d, node->left);

		}
		to_root(pa);


	}
	void getPredecessor(Node<K,V>* node, K* data)
	{

		while (node->right != NULL)
			node = node->right;

		*data = node->data;

	}
	Node<K,V>* search_only(Node<K,V>* node, K d)
	{
		if (node == nullptr)
			return nullptr;
		else if (node->data == d)
			return node;
		else if (node->data > d)
			return search_only(node->left, d);
		else if (node->data < d)
			return search_only(node->right, d);
	}
	bool search_only(K d)
	{
		if (root)
		{
			Node<K, V>* found = search_only(root, d);
			if (found)
			{
				return true;
			}
			return false;
		}
		return false;
	}
	bool update_value(K old_key,K new_key,V new_value)
	{
		if (old_key == new_key)
		{
			Node<K, V>* new_node;
			new_node = search_only(root, old_key);
			if (new_node)
			{
				new_node->value = new_value;
				return true;
			}
			else
			{
				cout << "No student with that roll number exists!";
				return false;
			}
		}
		else
		{
			if (search_only(new_key))
			{
				cout << "New roll number already exists!";
			}
			else
			{
				Node<K, V>* new_node;
				new_node = search_only(root, old_key);
				if (new_node)
				{
					new_node->value = new_value;
					new_node->data = new_key;              
					return true;
				}
				else
				{
					cout << "No student with that roll number exists!";
					return false;
				}

			}
		}
	}
	Node<K,V>* get_root()
	{
		Node<K,V>* curr = root;
		return curr;
	}
	~BST()
	{
		deleting(root);
	}
	void deleting(Node<K,V>* root)
	{
		if (root)
		{
			deleting(root->left);
			deleting(root->right);
			delete root;
		}
	}

};

class StudentList
{
private:
	BST<int, Student>* lst;
public:
	StudentList()
	{
		lst = new BST<int, Student>;
	}
	bool addnewstudent(int rollnumber, string firstname, string secondname, int batch, string department, float cgpa)
	{
		Student s(firstname, secondname, batch, department, cgpa);
		lst->insert(rollnumber, s);
		return true;
		

	}

	bool deletestudent(int rollnum)
	{
		
			if (lst->deleteR(rollnum))
			{
				cout << "Successfully deleted!" << endl;
				return true;
			}
			cout << "Not found!" << endl;
			return false;
		
	}
	bool updateStudent(int oldRollNumber, int newRollNumber, string newFirstName, string newLastName, int newBatch, string newDepartment, float newCgpa)
	{
		Student new_s(newFirstName, newLastName, newBatch, newDepartment, newCgpa);
		lst->update_value(oldRollNumber, newRollNumber, new_s);
		return true;

	}
	void printallstudent()
	{
		lst->InOrder();
	}

};



int main()
{
	//BST<int,Student> bt;
	//bt.insert(13);
	//bt.insert(7);
	//bt.insert(25);
	//bt.insert(15);
	//bt.insert(39);
	//bt.insert(14);
	//bt.insert(17);

	////bt.InOrder();
	//cout << endl;
	//bt.get_root().printTree(bt.get_root(), NULL, 0);
	//cout << endl;
	//cout << endl;
	//bt.deleteR(16);
	//cout << endl;
	//printTree(bt.get_root(), NULL, 0);
	//cout << endl;
	//cout << endl;
	/*cout << endl;
	cout << endl;
	Node<K,V>* tem = bt.search(bt.get_root(), 14);
	bt.to_root(tem);
	cout << endl;
	cout << endl;
	printTree(bt.get_root(), NULL, 0);*/
	/*tem = bt.search(bt.get_root(), 25);
	bt.rotate_right(tem);
	cout << endl;
	cout << endl;
	printTree(bt.get_root(), NULL, 0);
	tem = bt.search(bt.get_root(), 13);
	bt.rotate_left(tem);
	cout << endl;
	cout << endl;
	printTree(bt.get_root(), NULL, 0);*/



	StudentList SL;
	string firstname, newfirstname;
	string secondname, newsecondname;
	string department, newdepartment;
	float cgpa, newcgpa;
	int batch, newbatch;
	int rollnumber, newrollnumber;
	char option;
	do
	{
		system("CLS");
		SL.printallstudent();
		cout << "Press I to insert a student" << endl;
		cout << "Press S to Search a student" << endl;
		cout << "Press D to Delete a student" << endl;
		cout << "Press U to Update a student" << endl;
		cout << "Press P to print all students by roll number" << endl;
		cout << "Press E to exit" << endl;
		cout << "Enter choice: ";
		cin >> option;
		switch (option)
		{
		case 'I':
			cout << "What roll number do you want to insert: ";
			cin >> rollnumber;
			cout << "First Name: ";
			cin >> firstname;
			cout << "Second Name: ";
			cin >> secondname;
			cout << "Department: ";
			cin >> department;
			cout << "Batch: ";
			cin >> batch;
			cout << "CGPA: ";
			cin >> cgpa;
			if (SL.addnewstudent(rollnumber, firstname, secondname, batch, department, cgpa))
			{
				cout << "Inserted successfully!" << endl;
			}
			else
			{
				cout << "Duplicate Found!" << endl;
			}
			
			break;
		/*case 2:
			cout << "What do you want to search: ";
			cin >> rollnumber;
			SL.se(rollnumber);
			_getch();
			break;*/
		case 'D':
			cout << "What roll number do you want to delete: ";
			cin >> rollnumber;
			SL.deletestudent(rollnumber);
			break;
		case 'U':
			cout << "What roll number do you want to change: ";
			cin >> rollnumber;
			cout << "What roll number do you want it to be: ";
			cin >> newrollnumber;
			cout << "First Name: ";
			cin >> newfirstname;
			cout << "Second Name: ";
			cin >> newsecondname;
			cout << "Department: ";
			cin >> newdepartment;
			cout << "Batch: ";
			cin >> newbatch;
			cout << "CGPA: ";
			cin >> newcgpa;
			SL.updateStudent(rollnumber, newrollnumber, newfirstname, newsecondname, newbatch, newdepartment, newcgpa);
			break;
		case 'P':
			SL.printallstudent();
			break;
		case 'E':
			break;
		}
	} while (option != 'E');

	


	system("pause");
	return 0;
}