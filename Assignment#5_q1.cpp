#include <iostream>
using namespace std;
class IntervalHeap {
	int hsize; //number of elements in heap;
	int maxsize; //size of the array
	int** h;
	bool flag;
public:
	IntervalHeap(int s = 100)
	{
		maxsize = s;
		hsize = 0;
		h = new int* [2];
		h[0] = new int[maxsize];//store the lower end of closed interval
		h[1] = new int[maxsize];//store the higher end of closed interval
		flag = false;
	}
	void insert(int val)
	{
		
			if (flag == false)
			{
				h[0][hsize] = val;
				flag = true;
				MinReheapUp(0,hsize);
			}
			else
			{
				if (val > h[0][hsize])
				{
					h[1][hsize] = val;
					MaxReheapUp(0,hsize);
				}
				else
				{
					int temp = h[0][hsize];
					h[0][hsize] = val;
					h[1][hsize] = temp;
					MinReheapUp(0, hsize);
					MaxReheapUp(0, hsize);
				}
				flag = false;
				hsize++;
			}
		
	}
	void MinReheapUp(int root, int bottom)
	{
		int parent;
		if (bottom > root)
		{
			parent = (bottom - 1) / 2;
			if (h[0][parent] > h[0][bottom])
			{
				swap(h[0][parent], h[0][bottom]);
				MinReheapUp(root, parent);
			}
		}
	}
	void MaxReheapUp(int root, int bottom)
	{
		int parent;
		if (bottom > root)
		{
			parent = (bottom - 1) / 2;
			if (h[1][parent] < h[1][bottom])
			{
				swap(h[1][parent], h[1][bottom]);
				MaxReheapUp(root, parent);
			}
		}
	}
	void MinReheapDown(int root, int bottom)
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
				if (h[0][leftChild] >= h[0][leftChild])
				{
					minChild = rightChild;
				}
				else
				{
					minChild = leftChild;
				}
			}
			if (h[0][root] > h[0][minChild])
			{
				swap(h[0][root], h[0][minChild]);
				MinReheapDown(minChild, bottom);
			}
		}
	}
	void MaxReheapDown(int root, int bottom)
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
				if (h[1][leftChild] <= h[1][leftChild])
				{
					minChild = rightChild;
				}
				else
				{
					minChild = leftChild;
				}
			}
			if (h[1][root] < h[1][minChild])
			{
				swap(h[1][root], h[1][minChild]);
				MaxReheapDown(minChild, bottom);
			}
		}
	}
	void del_min()
	{
		if (flag == false)
		{
			hsize--;
			h[0][0] = h[1][hsize];
			MinReheapDown(0, hsize-1);
			flag = true;
		}
		else
		{
			h[0][0] = h[0][hsize];
			flag = false;
			MinReheapDown(0, hsize-1);

		}
	}
	void del_max()
	{

		if (flag == false)
		{
			hsize--;
			h[1][0] = h[0][hsize-1];
			MaxReheapDown(0, hsize - 1);
			flag = true;
		}
		else
		{
			h[1][0] = h[0][hsize-1];
			flag = false;
			MaxReheapDown(0, hsize - 1);

		}
	}
	void print()
	{
		for (int i = 0; i < hsize; i++)
		{
			cout << h[0][i] << " , " << h[1][i] << " ";
			cout << endl;
			
		}
		if (flag == true)
		{
			cout << h[0][hsize]<<" ";
		}
	}

	};
int main()
{
	IntervalHeap h1;
	h1.insert(2);
	h1.insert(30);
	h1.insert(3);
	h1.insert(17);
	h1.insert(4);
	h1.insert(12);
	h1.insert(4);
	h1.insert(10);
	h1.insert(5);
	h1.insert(11);
	h1.insert(3);
	h1.insert(11);
	h1.insert(5);
	h1.insert(9);
	h1.insert(4);
	h1.insert(7);
	h1.insert(4);
	h1.insert(15);
	h1.insert(5);
	h1.insert(10);
	h1.insert(8);
	h1.insert(8);
	h1.insert(7);
	h1.insert(9);
	h1.insert(6);
	h1.insert(15);
	h1.print();
	h1.del_min();
	cout << endl<<endl;
	h1.print();
	h1.del_max();
	cout << endl<<endl;
	h1.print();

	system("pause");
 }