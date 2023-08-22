#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <conio.h>
#include <cstdlib>
#include<windows.h>
#define PI 3.14159265
using namespace std;
template <class T>
class node
{
public:
	T data;
	node<T>* next;
	node()
	{
		next = NULL;
	}
};
template <class T>
class queue
{
private:
	node<T>* front;
	node<T>* rear;
	int size;
public:
	queue()
	{
		front = NULL;
		rear = NULL;
		size = 0;
	}
	bool isempty()
	{
		if (size == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool enqueue(T val)
	{
		node<T>* temp = new node<T>;
		temp->data = val;
		if (!isempty())
		{

			rear->next = temp;
			rear = temp;
			temp->next = NULL;

		}
		else
		{
			rear = temp;
			rear->next = NULL;
			front = rear;
		}
		size++;
		return true;
	}
	bool dequeue()
	{
		node<T>* temp = new node<T>;
		temp = front;

		if (!isempty())
		{
			if (front == rear)
			{
				delete temp;
				front = NULL;
				rear = NULL;
			}
			else
			{
				front = front->next;
				delete temp;

			}
			size--;
		}
		else
		{
			return false;
		}
		return true;
	}
	int get_size()
	{
		return size;

	}
	T get_front()
	{
		node<T>* temp = new node<T>;
		temp = front;
		return(temp->data);
	}
	T get_rear()
	{
		node<T>* temp = new node<T>;
		temp = rear;
		return(temp->data);
	}
	void display()
	{

		node<T>* temp;
		temp = front;
		while (temp != NULL)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
	}

};

int jospheus(queue<int> &q1,int k)
{
	int val;
	int val2;
	if (q1.get_size() > 1)
	{
		for (int i = 1; i < k; i++)
		{
			val = q1.get_front();
			q1.dequeue();
			q1.enqueue(val);
		}
		val2 = q1.get_front();
		q1.dequeue();
		cout << val2<<" ";
		return val2;

	}


	
}
int main()
{
	sf::Clock clock;
	sf::Time tim;
	tim = clock.getElapsedTime();
	sf::Time t1 = sf::seconds(100.0);
	clock.restart();
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Jospheus Problem");
	int n;
	int k;
	srand((unsigned int)time(NULL));
	
	queue<int> q1;

	cout << "enter the number of people: ";
	cin >> n;
	cout << "enter the number of people to be skipped: ";
	cin >> k;
	const int s = (rand()%n)+1;
	for (int i = 1; i <= n; i++)
	{
		q1.enqueue(i);
	}
	int val;
	for (int i = 1; i <= s; i++)
	{
		val = q1.get_front();
		q1.dequeue();
		q1.enqueue(val);
	}
		
	sf::Font font;
	if (!font.loadFromFile("chunk.otf"))
	{
		cout << "issue in font";
	}
	sf::Text text;
	text.setFont(font);
	sf::CircleShape shape(40.f);
	const float BigCircle = 100.f;
	int num_of_circle = 360 / n;
	int getch();
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear();
		
		int count = 1;
		text.setFillColor(sf::Color::Black);
		for (int i = 0; i < 360; i += num_of_circle)
		{
			    text.setString(to_string(count));
				shape.setFillColor(sf::Color::Green);
				shape.setOrigin(shape.getLocalBounds().width / 2, shape.getLocalBounds().height / 2);
				shape.setPosition(window.getSize().x / 2 + BigCircle * cos(i * PI / 180), window.getSize().y / 2 + BigCircle * sin(i * PI / 180));
				shape.move(BigCircle * cos(i * PI / 180), BigCircle * sin(i * PI / 180));
				//shape.move(-BigCircle * cos(i * PI / 180), -BigCircle * sin(i * PI / 180));
				text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
				text.setPosition(window.getSize().x / 2 + BigCircle * cos(i * PI / 180), window.getSize().y / 2 + BigCircle * sin(i * PI / 180));
				text.move(BigCircle * cos(i * PI / 180), BigCircle * sin(i * PI / 180));
				
				window.draw(shape);
				window.draw(text);
				
				count++;
			
			
		}
		count = 1;
		int index = 1;
		for (int i = 0; i < 360; i += num_of_circle)
		{

			shape.setOrigin(shape.getLocalBounds().width / 2, shape.getLocalBounds().height / 2);
			shape.setPosition(window.getSize().x / 2 + BigCircle * cos(i * PI / 180), window.getSize().y / 2 + BigCircle * sin(i * PI / 180));
			shape.move(BigCircle * cos(i * PI / 180), BigCircle * sin(i * PI / 180));
			if (index == s)
			{

				
				shape.setFillColor(sf::Color::Yellow);
				window.draw(shape);


			}
			text.setString(to_string(count));
			text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
			text.setPosition(window.getSize().x / 2 + BigCircle * cos(i * PI / 180), window.getSize().y / 2 + BigCircle * sin(i * PI / 180));
			text.move(BigCircle * cos(i * PI / 180), BigCircle * sin(i * PI / 180));
			window.draw(text);

			index++;
			count++;


		}
		window.display();
		getch();
		window.display();
		while (q1.get_size()>1)
			{
				count = 1;
				index = 1;
				int value = jospheus(q1, k);
				for (int i = 0; i < 360; i += num_of_circle)
				{
					shape.setOrigin(shape.getLocalBounds().width / 2, shape.getLocalBounds().height / 2);
					shape.setPosition(window.getSize().x / 2 + BigCircle * cos(i * PI / 180), window.getSize().y / 2 + BigCircle * sin(i * PI / 180));
					shape.move(BigCircle * cos(i * PI / 180), BigCircle * sin(i * PI / 180));
					text.setString(to_string(count));
					text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
					text.setPosition(window.getSize().x / 2 + BigCircle * cos(i * PI / 180), window.getSize().y / 2 + BigCircle * sin(i * PI / 180));
					text.move(BigCircle * cos(i * PI / 180), BigCircle * sin(i * PI / 180));
					
					if (index == value)
					{
						shape.setFillColor(sf::Color::Red);
						window.draw(shape);
						window.draw(text);
						window.display();
						getch();
						
						
						break;
						
						
					}
					index++;
					count++;
				}
				window.display();
			} 
		window.display();
		getch();
		break;
		
    }
}