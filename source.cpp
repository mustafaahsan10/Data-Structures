#include <iostream>
using namespace std;
template <typename T>
struct node
{
	T data;
	node* next;
};
template <class T>
class sorted_set
{
private:
	node<T>* head;
	node<T>* tail;
public:
	sorted_set()
	{
		head = NULL;
		tail = NULL;
	}
	void insert(T const data)
	{
		node<T>* new_el = new node<T>;
		node<T>* current ;
		node<T>* prev = NULL;
		new_el->data = data;
		new_el->next = NULL;
		current = head;

		while (current != NULL)
		{
			if (data == current->data) // checking if data already present
			{
				cout << data<<" already in the list\n";
				return;
			}
			current = current->next;
		}
		current = head;
		if (head == NULL) // check if list is empty
		{
			head = new_el;
		}
		else
		{
			while (current != NULL && current->data < data) //running till the node thats data greater than the one being inserted
			{

				prev = current;
				current = current->next;

			}
			new_el->next = current; // adding the data after the current node in ascending order
			if (current == head) 
			{
				head = new_el; // check if the new data is smaller than the one in head node
			}
			else
			{
				prev->next = new_el; //new data is inserted after the previous pointed node
			}

			
			
		}

	}
	void Delete(int const index)
	{
		int in = index - 1;
		node<T>* current = new node<T>;
		node<T>* prev = new node<T>;
		current = head;
		int count = 0;
		
			while (current != NULL && count < in) // counting the number of nodes till the one to be deleted
			{
				prev = current;
				current = current->next;
				count++;
			}
			if (current != NULL && in == count)
			{
				if (current == head)
				{
					head = current->next; // if the node to be deleted is the head
				}
				else
				{
					prev->next = current->next; // the previous node now points to node after the current one,removing current node
				}
				delete current; //delete current node from memory
			}
			
		



	}
	void print()
	{
		node<T>* current = new node<T>;
		current = head;
		while (current != NULL) // printing all nodes data till NULL
		{
			cout << current->data << "  ";
			current = current->next;
		}
	}
	void Union(sorted_set<T>& l2)
	{
		node<T>* current_1 = head;
		node<T>* prev_1 = NULL;
		node<T>* current_2 = l2.head;
		if (current_2 != NULL)
		{
			if (current_1 != NULL)
			{


				insert(current_2->data);// using the insert function to determine the head of union list

				prev_1 = current_1;
				current_1 = current_1->next;
				current_2 = current_2->next;

				while (current_2 != NULL && current_1 != NULL) // running the loop till any of list ends
				{

					if (current_1->data > current_2->data)
					{
						node<T>* temp = new node<T>;
						temp->data = current_2->data; // save the data from second list in a temporary node 
						temp->next = current_1;// store it before the node having a larger data
						prev_1->next = temp;
						prev_1 = temp;


					}
					else if (current_1->data == current_2->data) // if data being compared are equal then move to next comparision
					{
						prev_1 = current_1;
						current_1 = current_1->next;
					}
					else
					{
						prev_1 = current_1;
						current_1 = current_1->next;
						continue; //dont move to next element of 2nd list if it is not placed in union list or an equal element has been found


					}
					current_2 = current_2->next;	//move to next element of 2nd list
				}
				current_2 = l2.head;
				while (current_2 != NULL) // if not all elements at end of 2nd list have been placed in the union list
				{
					if (current_2->data > prev_1->data)// place the elements after the end of 1st list
					{
						node<T>* temp = new node<T>;
						temp->data = current_2->data;
						temp->next = current_1;
						prev_1->next = temp;
					}
					current_2 = current_2->next;
				}
			}
			else
			{
				head = l2.head;
			}
		}
	}
	void rotate(int k)
	{
		node<T>* current1;
		node<T>* current2 =NULL;
		node<T>* new_head =NULL;
		current1 = head;
		int size = 0;
		int index = 0;
		if (k == 0) // if the number of nodes to be rotated is 0, return the list as it is
		{
			return;
		}
		
		while (current1 != NULL) // calculating the size of the linked list
		{
			current1 = current1->next;
			size++;
		}
		if (k > size || k < 0) // checking the boundary conditions

		{
			cout << "enter a valid value";
			return;

		}
		current1 = head;
		while (current1 != NULL && index<k-1) // running the loop till node from where list is to be rotated
		{
			index++;
			current1 = current1->next;
			
		}
		if (current1 != NULL)
		{
			new_head = current1->next; // node after the rotated nodes is the new head
			current2 = current1;
		}
		while (current2->next != NULL) // traversing the rest of the list
		{
			current2 = current2->next;

		}
		
			current2->next = head; //old head node becomes part of list after the rotated nodes
			head = new_head; 
			current1->next = NULL;
		



	}
	void reverse()
	{
		
		node<T>* current = head;
		node<T>* prev = NULL;
		node<T>* temp = NULL;
		while (current != NULL)
		{
			
			temp = current; // storing the current node in temporary pointer
			current = current->next;
			temp->next = prev; // temporary pointer now points to node before the current node store in temporary pointer
			prev = temp; 
		}
		head = prev; // the node judt before NULL become the head
	}
	
	~sorted_set()
	{
		
		node<T>* curr = new node<T>;
		node<T>	* prev = new node<T>;
			curr = head;
			while (curr != NULL)
			{
				prev = curr->next;
				delete curr;
				curr = prev;
			}
		
	}

};

int main()
{
	sorted_set<int> l1;
	sorted_set<int> l2;

	int option, num;
	do
	{
		cout << "Enter 1 to insert value in 1st linked list." << endl;
		cout << "Enter 2 to insert value in 2nd linked list." << endl;
		cout << "Enter 3 to print 1st linked list." << endl;
		cout << "Enter 4 to print 2nd linked list." << endl;
		cout << "Enter 5 to delete value from 1st linked list." << endl;
		cout << "Enter 6 to delete value from 2st linked list." << endl;
		cout << "Enter 7 for union of 1st and 2nd linked list in 1st list." << endl;
		cout << "Enter 8 to reverse 1st linked list." << endl;
		cout << "Enter 9 to rotate 1st linked list." << endl;
		cout << "Enter -1 to quit" << endl;
		cin >> option;
		switch (option)
		{
		case 1:
			cout << "Enter the value you want to insert: ";
			cin >> num;
			l1.insert(num);
			break;
		case 2:
			cout << "Enter the value you want to insert: ";
			cin >> num;
			l2.insert(num);
		case 3:
			l1.print();
			cout << endl;
			break;
		case 4:
			l2.print();
			cout << endl;
			break;
		case 5:
			cout << "Enter the index you want to delete: ";
			cin >> num;
			l1.Delete(num);
			break;
		case 6:
			cout << "Enter the index you want to delete: ";
			cin >> num;
			l2.Delete(num);
			break;
		case 7:
			l1.Union(l2);
			break;
		case 8:
			l1.reverse();
			break;
		case 9:
			cout << "enter the amount of nodes to be rotated: ";
			cin >> num;
			l1.rotate(num);
			break;
		}
	} while (option != -1);


	return 0;
}