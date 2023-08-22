#include <iostream>
using namespace std;
template<class T>
class Stack
{
private:
	int size;
	int stk_ptr;
	int top_el;
	int new_start;
	bool full;
	T* stackArray;
public:
	Stack()
	{
		    size = 10;
			stackArray = new T[size];
			stk_ptr = 0;
			top_el = -1;
			new_start = 0;
			full = false;
		

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
		if (stk_ptr < size)
		{
			stk_ptr++;
			top_el++;
			stackArray[top_el] = val;
		}
		
		else if (stk_ptr== size || full)
		{
			
			full = true;
			stackArray[new_start] = val;
			top_el = new_start;
			new_start++;
			

		}


	}
	void pop(T& val)
	{
		if (IsEmpty())
		{
			return;
		}
		else if(stk_ptr<size && !full)
		{
			val = top();
			top_el--;
			stk_ptr--;
		}
		else if (full)
		{
			val = top();
			new_start--;
			top_el--;
			if (new_start == 0)
			{
				top_el = --stk_ptr;
				full = false;
			}
		}
	
	}
	const T& top()
	{
		return stackArray[top_el];

	}
	void display()
	{
		for (int i = stk_ptr - 1; i >= 0; i--)
		{
			cout << stackArray[i] << endl;
		}
		
	}
	
};
int main()
{
	Stack<int> s1;
	for (int i = 1; i <= 15; i++)
	{
		s1.push(i);
	}
	s1.display();
	cout << endl;
	int val;
	s1.pop(val);
	cout << val << endl;
	s1.pop(val);
	cout << val << endl;
	s1.pop(val);
	cout << val<<endl;
	s1.pop(val);
	cout << val << endl;
	s1.pop(val);
	cout << val << endl;
	s1.pop(val);
	cout << val << endl;
	s1.pop(val);
	cout << val << endl;
	s1.pop(val);
	cout << val << endl;

	



}