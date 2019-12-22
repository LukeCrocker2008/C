#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const int ROW = 15;
const int COL = 30;

void DisplayChart(char [ROW][COL]);
void CheckSeat(char [ROW][COL], int [], int&);
void DisplaySeats(char [ROW][COL]);

int main()
{
	char choice = 'M'; // Default: Menu
	char seats[15][30];
	int rowPrice[15];
	int totalSales = 0;
	ifstream inFile;
	inFile.open("rowprices.txt");
	for(int i = 0; i < ROW; i++)
		inFile >> rowPrice[i];
	inFile.close();

	for(int i = 0; i < ROW; i++) // Initialize Seat Chart
	{
		for (int j = 0; j < COL; j++)
		{
			seats[i][j] = '#'; // Available seat
		}
	}

	do {
		switch (choice)
		{
			case 'M' : DisplayChart(seats);
					   cout << "Main Menu" << endl;
					   cout << "Select Option: " << endl;
					   cout << "(A) Check & Purchase Seat" << endl;
					   cout << "(B) Display Ticket Sales in Total" << endl;
					   cout << "(C) Display Number of Seats" << endl;
					   cout << "(D) Exit Program" << endl << endl;
					   cout << "Option: ";
					   cin >> choice;
					   cout << endl;
					   break;
			case 'A' : CheckSeat(seats, rowPrice, totalSales);
					   choice = 'M'; 
					   break;
			case 'B' : cout << "The total amount in ticket sales is $" << totalSales << endl << endl;
					   system("Pause");
					   choice = 'M'; 
					   break;
			case 'C' : DisplaySeats(seats);
					   choice = 'M'; 
					   break;
			case 'D' : choice = 'M'; 
					   break;
			default	 : cout << "ERROR: Incorrect Option! Type exact character into option!" << endl;
					   choice = 'M';
					   break;
		}
		system("CLS");
	} while (choice != 'D');
	return 0;
}

void DisplayChart(char seats[ROW][COL])
{
	cout << right << setw(31) << "Seats" << endl;
	cout << right << setw(43) << "012345678901234567890123456789" << endl;
	for(int i = 0; i < ROW; i++)
	{
		cout << "Row " << left << setw(9) << (i+1); 
		for(int j = 0; j < COL; j++)
		{
			cout << seats[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void CheckSeat(char seats[ROW][COL], int rowPrice[], int& totalSales)
{
	int i, j;
	cout << "Enter Seat Row # followed by Column # separated by space: ";
	cin >> i >> j;
	if (i > 0 && i <= ROW && j > 0 && j <= COL)
	{
		if(seats[i-1][j-1] != '*')
		{
			int purchase;
			cout << "This seat is available on row " << i << " and column " << j << "." << endl;
			cout << "The cost of this row is $" << rowPrice[i-1] << ". Do you want to purchase? (Enter 1 for \"Yes\") ";
			cin >> purchase;
			cout << endl;
			if(purchase == 1)
			{
				totalSales += rowPrice[i-1];
				seats[i-1][j-1] = '*';
				cout << "The seat is now sold." << endl << endl;
			} else { cout << "Keep looking!" << endl << endl; }
		}	else { cout << "The seat is already taken." << endl << endl; }
	} else { cout << "That seat does not exist." << endl << endl; }
	system("Pause");
}

void DisplaySeats(char seats[ROW][COL])
{
	int availableSeats = ROW * COL;
	int seatsSold = 0;
	int seatsPerRow[15];
	for(int i = 0; i < ROW; i++)
	{
		seatsPerRow[i] = 0;
		for(int j = 0; j < COL; j++)
		{
			if(seats[i][j] == '*')
			{
				availableSeats--;
				seatsSold++;
				seatsPerRow[i]++;
			}
		}
	}
	cout << "Total Available Seats: " << availableSeats << endl;
	cout << "Total Seats Sold: " << seatsSold << endl << endl;
	cout << "Total Seats Sold Per Row" << endl;
	for (int i = 0; i < ROW; i++)
		cout << "Row " << right << setw(2) << (i+1) << ": " << seatsPerRow[i] << endl;
	cout << endl;
	system("Pause");
}
