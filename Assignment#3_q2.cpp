#include <iostream>
#include <conio.h>
#include <queue>
#include <cstdlib>
#include <string>
using namespace std;
int dice_roll()
{
	srand(time(0));
	return (rand() % 6) + 1;
}
bool addscore(queue<int> &score,string play)
{
	int roll = dice_roll();
	int new_score = roll + score.front();
	cout << endl << play << " got " << roll << " and the total score is now " << new_score << endl;
	if (new_score == 20)
	{
		cout << "\nCONGRATULATION....There is a ladder at 20 so score is now 40\n";
		new_score = 40;
	}
	else if (new_score == 60)
	{
		cout << "\nCONGRATULATION....There is a ladder at 60 so score is now 75\n";
		new_score = 75;
	}
	else if (new_score == 50)
	{
		cout << "\nSSSS.....There is a snake at 50 so score is now 40\n";
		new_score = 40;
	}
	else if (new_score == 90)
	{
		cout << "\nSSSS.....There is a snake at 90 so score is now 79\n";
		new_score = 79;
	}


	score.pop();
	if (new_score == 100)
	{
		cout << play << " has won the game\n";
		return 0;
	}
	else if (new_score > 100)
	{
		new_score = new_score - roll;
		score.push(new_score);
	}
	else
	{
		score.push(new_score);
	}

	return 1;
}
int main()
{
	queue<string> players;
	queue<string> winners;
	queue<int> score;
	int num_play;
	int getch();
	cout << "\n---------WELCOME TO SNAKES AND LADDER GAME------------\n";
	cout << "\nEnter the number of players: \n";
	cin >> num_play;
	cout << endl;
	string name;
	for (int i = 1; i <= num_play; i++)
	{
		cout << "enter the name of player " << i << ": " << endl;
		cin >> name;
		players.push(name);
	}
	for (int i = 1; i <= num_play; i++)
	{
		score.push(0);
	}
	string player_turn;
	while (winners.size()!=(num_play-1))
	{
		player_turn = players.front();
		players.pop();
		cout << "\nIt is " << player_turn << " turn\n";
		cout << "Press any key to continue: ";
		getch();
		bool flag = addscore(score, player_turn);
		if (flag)
		{
			players.push(player_turn);
		}
		else
		{
			winners.push(player_turn);
		}
	}
	int count = 1;
	while (!winners.empty())
	{
		cout << endl<<count << " position: " << winners.front() << endl;
		winners.pop();
		count++;
	}
	system("pause");
	return 0;
}
