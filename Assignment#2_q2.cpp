#include <iostream>
using namespace std;
template<class T>
class Stack 
{
private:
	int size;
	int stk_ptr;
	int top_el;
	T* stackArray;
	bool flip;
	int rev_ptr;
public:
	Stack(int s=0)
	{
		if (s >= 0)
		{
			stackArray = new T[s];
			stk_ptr = 0;
			top_el = -1;
			size = s;
			flip = false;
		}
		else
		{
			size = 0;
			stk_ptr = 0;
			top_el = -1;
			stackArray = NULL;
			flip = false;
		}
		rev_ptr = 0;

	}
	~Stack()
	{
		delete[] stackArray;
	}
	bool IsEmpty()
	{
		if (stk_ptr == 0)
		{
			return true;
		}
		return false;
	}
	void push(const T& val)
	{
		if (!flip)
		{
			//top_el = stk_ptr;

			if (stk_ptr < size)
			{
				stk_ptr++;
				top_el++;
				stackArray[top_el] = val;
			}
			else if (size == 0)
			{

				stackArray = new T[1];
				stackArray[0] = val;
				top_el = 0;
				size = 1;
				stk_ptr = 1;

			}
			else if (stk_ptr == size)
			{
				T* temp = new T[size * 2];
				for (int i = 0; i < stk_ptr; i++)
				{
					temp[i] = stackArray[i];
				}
				size = size * 2;
				stk_ptr++;
				top_el++;
				temp[top_el] = val;
				stackArray = temp;

			}
		}
		else
		{
			if (rev_ptr > 0)
			{
				rev_ptr--;
				stackArray[rev_ptr] = val;
			}
			else if (rev_ptr == 0)
			{
				cout << "Array full";
			}
		}
		
		
		
	}
	void pop(T& val)
	{
		if (IsEmpty())
		{
			return;
		}
		else if (stk_ptr >= size / 2 ) 
		{
			
			if (flip)
			{
				/*T temp_el = stackArray[0];
				for (int i = 1; i < stk_ptr; i++)
				{
					stackArray[i - 1] = stackArray[i];
				}
				stackArray[top_el] = temp_el;*/
				top_el = rev_ptr;
				val = top();
				rev_ptr++;

			}
			else
			{
				top_el = stk_ptr-1;
				val = top();
				stk_ptr--;
			}
		}
		else
		{
			T* temp = new T[size / 2];
			for (int i = 0; i < stk_ptr; i++)
			{
				temp[i] = stackArray[i];
			}
			
			size = size / 2; 
			stackArray = temp;
			if (flip)
			{
				/*T temp_el = stackArray[0];
				for (int i = 1; i < stk_ptr; i++)
				{
					stackArray[i - 1] = stackArray[i];
				}
				stackArray[top_el] = temp_el;*/
				top_el = rev_ptr;
				val = top();
				rev_ptr++;
				
			}
			else
			{
				top_el = stk_ptr;
				val = top();
				stk_ptr--;
			}
			
		}
	

	}
	const T& top()
	{
		return stackArray[top_el];

	}
	void display()
	{
		for (int i = stk_ptr - 1; i >= rev_ptr; i--)
		{
			cout << stackArray[i] << endl;
		}
	}
	void flip_function()
	{
		flip = !flip;
	}
};
int main()
{
	int val;
	Stack<int> s1(10);
	s1.push(1);
	s1.push(2);
	s1.push(3);
	s1.push(4);
	s1.push(5);
	s1.push(6);
	cout << "BEFORE REVERSE\n";
	s1.display();
	cout << endl<<endl;
	s1.flip_function();
	s1.pop(val);
	
	cout << "NUMBER POPPED AFTER REVERSE\n";
	cout << val<<endl;
	s1.flip_function();
	s1.pop(val);
	cout << "NUMBER POPPED AFTER REVERSE\n";
	cout << val;
	cout << endl<<endl;
	cout << "STACK NOW:\n";
	s1.display();
	cout << endl;
	
	
	


}
