#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <Windows.h>
#include <MMsystem.h>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

//Function Prototypes
int RandomRoll(); //Rolling a random number from 2-7
void WaitFor(const int steps); //Wait for number of steps function (60 steps per second)
int RollSlots(int userBet, int playerChips, int slotNum[], int ct1, int ct2);
void QuitSlots();
void SetColour(int colour);
void DrawSlots(int slotNum[], int c3, int cf, int anim);
void DrawTitle(int c1);
void DrawMystery();
string DrawNumber(int num, int line);

int main()
{
	//Variables
	long long int playerChips = 2000;
	string menuInput = "";
	string betInput = "";
	string shopInput = "";
	int menuChoice = 0;
	int userBet = 0;
	int gameState = 0;
	int slotNum[3] = { 3, 5, 7 };
	int shopChoice = 0;
	bool itemOwned[5] = { 1,0,0,0,0 };
	int themeCol1 = 27;
	int themeCol2 = 177;

	SetColour(15);
	
	srand(time(0)); //Seeding the randomness

	while ((menuChoice < 1) || (menuChoice > 4) || (gameState == 0)) //Menu
	{
		system("cls");
		menuChoice = 0;
		userBet = 0;
		SetColour(15);
		cout << endl;
		DrawTitle(themeCol1);
		cout << endl;
		SetColour(14);
		cout << " Player's Chips: $" << playerChips << endl << endl;
		SetColour(15);
		cout << " 1) Play Slots" << endl;
		cout << " 2) Quit Slot Machine" << endl;
		cout << " 3) View Credits" << endl;
		cout << " 4) Shop" << endl << endl;
		SetColour(15);
		cout << " What do you want to do? ";
		getline(cin, menuInput);
		menuChoice = atoi(menuInput.c_str());
		menuInput = "";

		if (playerChips > 5000000000000) //To prevent overflow
		{
			playerChips = 5000000000000;
		}
		if (playerChips <= 0)
		{
			
			PlaySound(TEXT("BAD_01.wav"), NULL, SND_ASYNC);
			system("cls");
			cout << endl;
			cout << " You have gambled away everything." << endl;
			WaitFor(90);
			system("cls");
			cout << endl;
			cout << " You have gambled away everything.." << endl;
			WaitFor(90);
			system("cls");
			cout << endl;
			cout << " You have gambled away everything..." << endl;
			WaitFor(90);
			system("cls");
			cout << endl;
			PlaySound(TEXT("BAD_01.wav"), NULL, SND_ASYNC);
			cout << " This is only a game, so you get to have your chips reset." << endl;
			WaitFor(90);
			system("cls");
			cout << endl;
			cout << " This is only a game, so you get to have your chips reset.." << endl;
			WaitFor(90);
			system("cls");
			cout << endl;
			cout << " This is only a game, so you get to have your chips reset..." << endl;
			WaitFor(90);
			system("cls");
			cout << endl;
			PlaySound(TEXT("BAD_01.wav"), NULL, SND_ASYNC);
			cout << " Just remember-" << endl;
			WaitFor(120);
			system("cls");
			SetColour(12);
			cout << endl;
			PlaySound(TEXT("BAD_01.wav"), NULL, SND_ASYNC);
			cout << " If you gamble like this in real life" << endl;
			WaitFor(120);
			SetColour(15);
			system("cls");
			SetColour(12);
			cout << endl;
			PlaySound(TEXT("BAD_01.wav"), NULL, SND_ASYNC);
			cout << " If you gamble like this in real life you go to hell" << endl;
			WaitFor(120);
			SetColour(15);
			system("cls");
			SetColour(12);
			cout << endl;
			PlaySound(TEXT("BAD_01.wav"), NULL, SND_ASYNC);
			cout << " If you gamble like this in real life you go to hell BEFORE you die..." << endl;
			WaitFor(140);
			SetColour(64);
			for (int psa = 0; psa < 40; ++psa)
			{ 
				PlaySound(TEXT("BAD_01.wav"), NULL, SND_ASYNC);
				system("cls");
				SetColour(64);
				cout << endl;
				cout << " If you gamble like this in real life you go to hell BEFORE you die..." << endl;
				WaitFor(4);
				SetColour(12);
				system("cls");
				SetColour(12);
				cout << endl;
				cout << " If you gamble like this in real life you go to hell BEFORE you die..." << endl;
				WaitFor(4);
				SetColour(64);
			}
			SetColour(15);
			playerChips = 2000;
			menuChoice = 0;
		}
		if (menuChoice == 1)
		{
			while ((userBet == 0) || (userBet > playerChips) || (playerChips > 0))
			{
				system("cls");
				cout << endl;
				SetColour(14);
				cout << " Player's Chips: $" << playerChips << endl << endl;
				SetColour(15);
				DrawSlots(slotNum, themeCol1, themeCol1, 1); //Drawing the slots
				cout << endl;
				cout << " Enter your Bet: ";

				getline(cin, betInput);
				userBet = atoi(betInput.c_str());

				if ((userBet <= playerChips) && (userBet > 0))
				{
					playerChips -= userBet;
					PlaySound(TEXT("SM_01.wav"), NULL, SND_ASYNC);
					playerChips = RollSlots(userBet, playerChips, slotNum, themeCol1, themeCol2);
					break;
				}
				if ((userBet <= 0))
				{
					system("cls");
					PlaySound(TEXT("ERROR_01.wav"), NULL, SND_ASYNC);
					cout << endl;
					cout << " You have to bet some money." << endl;
					WaitFor(90);
				}
				else
				{
					system("cls");
					PlaySound(TEXT("ERROR_01.wav"), NULL, SND_ASYNC);
					cout << endl;
					cout << " You don't have that much." << endl;
					WaitFor(90);
				}
			}
		}
		else if (menuChoice == 2) //Quitting Slot Machine
		{
			QuitSlots();
			break;
		}
		else if (menuChoice == 3) //Credits
		{
			while (menuChoice == 3)
			{
				for (int cr = 5; cr >= 0; cr -= 1)
				{ 
					system("cls");
					cout << endl << endl;
					SetColour(10 + cr);
					cout << " ---------------------------------------------------------" << endl;
					cout << " |  Programming, Art, and Sound by John Bu. August 2017. |" << endl;
					cout << " ---------------------------------------------------------" << endl << endl;
					WaitFor(40);
				}
				menuChoice = 0;
			}
		}
		else if (menuChoice == 4) //Shop Menu
		{
			system("cls");
			cout << endl;
			SetColour(14);
			cout << " Player's Chips: $" << playerChips << endl << endl;
			SetColour(15);
			cout << " Welcome to the shop! What would you like to purchase?" << endl << endl;
			SetColour(11);
			cout << " 1) Blue Theme          Owned" << endl;
			SetColour(14);
			if (itemOwned[1] == 0)
			{
				cout << " 2) Yellow Theme        $5,000" << endl;
			}
			else
			{
				cout << " 2) Yellow Theme        Owned" << endl;
			}
			SetColour(10);
			if (itemOwned[2] == 0)
			{
				cout << " 3) Green Theme         $10,000" << endl;
			}
			else
			{
				cout << " 3) Green Theme         Owned" << endl;
			}
			SetColour(12);
			if (itemOwned[3] == 0)
			{
				cout << " 4) Red Theme           $50,000" << endl;
			}
			else
			{
				cout << " 4) Red Theme           Owned" << endl;
			}
			SetColour(13);
			if (itemOwned[4] == 0)
			{
				cout << " 5) Mystery Item        $100,000" << endl << endl;
			}
			else
			{
				cout << " 5) Mystery Item        Owned" << endl;
			}
			SetColour(15);
			cout << " 6) Go Back" << endl << endl;
			cout << " What do you want? ";
			getline(cin, shopInput);
			shopChoice = atoi(shopInput.c_str());

			if (shopChoice == 1) //Blue (Default) Theme
			{
				PlaySound(TEXT("BUY_01.wav"), NULL, SND_ASYNC);
				themeCol1 = 27;
				themeCol2 = 177;
			}
			else if(shopChoice == 2) //Yellow Theme
			{
				if (itemOwned[1] == 0)
				{
					if (playerChips >= 5000)
					{
						playerChips -= 5000;
						itemOwned[1] = 1;
					}
					else
					{
						system("cls");
						PlaySound(TEXT("ERROR_01.wav"), NULL, SND_ASYNC);
						cout << endl;
						cout << " You can't afford that!" << endl;
						WaitFor(120);
					}
				}
				if(itemOwned[1] == 1)
				{
					PlaySound(TEXT("BUY_01.wav"), NULL, SND_ASYNC);
					themeCol1 = 110;
					themeCol2 = 232;
				}
			}
			else if (shopChoice == 3) //Green Theme
			{
				if (itemOwned[2] == 0)
				{
					if (playerChips >= 10000)
					{
						playerChips -= 10000;
						itemOwned[2] = 1;
					}
					else
					{
						system("cls");
						PlaySound(TEXT("ERROR_01.wav"), NULL, SND_ASYNC);
						cout << endl;
						cout << " You can't afford that!" << endl;
						WaitFor(120);
					}
				}
				if (itemOwned[2] == 1)
				{
					PlaySound(TEXT("BUY_01.wav"), NULL, SND_ASYNC);
					themeCol1 = 42;
					themeCol2 = 162;
				}
			}
			else if (shopChoice == 4) //Red Theme
			{
				if (itemOwned[3] == 0)
				{
					if (playerChips >= 50000)
					{
						playerChips -= 50000;
						itemOwned[3] = 1;
					}
					else
					{
						system("cls");
						PlaySound(TEXT("ERROR_01.wav"), NULL, SND_ASYNC);
						cout << endl;
						cout << " You can't afford that!" << endl;
						WaitFor(120);
					}
				}
				if (itemOwned[3] == 1)
				{
					PlaySound(TEXT("BUY_01.wav"), NULL, SND_ASYNC);
					themeCol1 = 76;
					themeCol2 = 196;
				}
			}
			else if (shopChoice == 5) //Mystery Item
			{
				if (itemOwned[4] == 0)
				{
					if (playerChips >= 100000)
					{
						playerChips -= 100000;
						itemOwned[4] = 1;
					}
					else
					{
						system("cls");
						PlaySound(TEXT("ERROR_01.wav"), NULL, SND_ASYNC);
						cout << endl;
						cout << " You can't afford that!" << endl;
						WaitFor(180);
					}
				}
				if (itemOwned[4] == 1)
				{
					DrawMystery();
				}
			}
			else if (shopChoice == 6)
			{
				menuChoice = 0;
			}
			
		}
		else if (menuChoice == 80085) //Money Cheat
		{
			system("cls");
			PlaySound(TEXT("BAD_01.wav"), NULL, SND_ASYNC);
			cout << endl;
			SetColour(12);
			cout << " Naughty..." << endl;
			SetColour(15);
			WaitFor(120);
			playerChips *= 100;
		}
		else
		{
			menuChoice = 0;
		}
	}

	system("cls");

	return (0);
}

int RandomRoll()
{
	//Function to roll a number between 2 and 7
	int num = (rand() % 6) + 2;
	return num;
}

void WaitFor(const int steps)
{
	//Function to wait for a certain number of steps (60 steps per second)
	Sleep(steps*(1000/60));
}

int RollSlots(int userBet, int playerChips, int slotNum[], int ct1, int ct2)
{
	int rollSpeed = 5;
	int fSpeed = 4;
	int fAmount = 15;
	
	for (int sr = 0; sr < 65; ++sr)
	{
		rollSpeed = sr/5;
		system("cls");
		cout << endl;
		SetColour(14);
		cout << " Player's Chips: $" << playerChips << endl << endl;
		SetColour(15);
		slotNum[0] = RandomRoll();
		slotNum[1] = RandomRoll();
		slotNum[2] = RandomRoll();
		DrawSlots(slotNum, ct1, ct1, 2); //Drawing the slots
		cout << endl;
		cout << " Your Bet: $" << userBet << endl << endl;
		WaitFor(rollSpeed);
		rollSpeed = 2;
	}
	

	if ((slotNum[0] == 7) && (slotNum[1] == 7) && (slotNum[2] == 7)) //if 777 is rolled
	{
		
		for (int fl = 0; fl < fAmount+20; ++fl)
		{
			PlaySound(TEXT("WIN_01.wav"), NULL, SND_LOOP | SND_ASYNC);
			system("cls");
			cout << endl;
			SetColour(14);
			cout << " Player's Chips: $" << playerChips << endl << endl;
			SetColour(15);
			DrawSlots(slotNum, ct1, ct1, 1); //Drawing the slots
			cout << endl;
			cout << " You won 10x your bet!!!";
			WaitFor(fSpeed);
			system("cls");
			cout << endl;
			SetColour(14);
			cout << " Player's Chips: $" << playerChips << endl << endl;
			SetColour(15);
			DrawSlots(slotNum, ct1, ct2, 1); //Drawing the slots
			cout << endl;
			cout << " You won 10x your bet!!!";
			WaitFor(fSpeed);
		}
		PlaySound(NULL, NULL, NULL);
		return (playerChips += (userBet * 10));
	}
	else if ((slotNum[0] == slotNum[1]) && (slotNum[1] == slotNum[2]) && (slotNum[0] == slotNum[2])) //if all of the numbers are the same and not 7's
	{
		
		for (int fl = 0; fl < fAmount+10; ++fl)
		{
			PlaySound(TEXT("WIN_01.wav"), NULL, SND_LOOP | SND_ASYNC);
			system("cls");
			cout << endl;
			SetColour(14);
			cout << " Player's Chips: $" << playerChips << endl << endl;
			SetColour(15);
			DrawSlots(slotNum, ct1, ct1, 1); //Drawing the slots
			cout << endl;
			cout << " You won 5x your bet!!";
			WaitFor(fSpeed);
			system("cls");
			cout << endl;
			SetColour(14);
			cout << " Player's Chips: $" << playerChips << endl << endl;
			SetColour(15);
			DrawSlots(slotNum, ct1, ct2, 1); //Drawing the slots
			cout << endl;
			cout << " You won 5x your bet!!";
			WaitFor(fSpeed);
		}
		PlaySound(NULL, NULL, NULL);
		return (playerChips += (userBet * 5));
	}
	else if ((slotNum[0] == slotNum[1]) || (slotNum[1] == slotNum[2]) || (slotNum[0] == slotNum[2])) //if only 2 of the numbers are the same
	{
		PlaySound(TEXT("WIN_01.wav"), NULL, SND_LOOP | SND_ASYNC);
		for (int fl = 0; fl < fAmount; ++fl)
		{
			system("cls");
			cout << endl;
			SetColour(14);
			cout << " Player's Chips: $" << playerChips << endl << endl;
			SetColour(15);
			DrawSlots(slotNum, ct1, ct1, 1); //Drawing the slots
			cout << endl;
			cout << " You won 3x your bet!";
			WaitFor(fSpeed);
			system("cls");
			cout << endl;
			SetColour(14);
			cout << " Player's Chips: $" << playerChips << endl << endl;
			SetColour(15);
			DrawSlots(slotNum, ct1, ct2, 1); //Drawing the slots
			cout << endl;
			cout << " You won 3x your bet!";
			WaitFor(fSpeed);
		}
		PlaySound(NULL, NULL, NULL);
		return (playerChips += (userBet * 3));
	}
	else
	{
		PlaySound(TEXT("FAIL_01.wav"), NULL, SND_ASYNC);
		system("cls");
		cout << endl;
		SetColour(14);
		cout << " Player's Chips: $" << playerChips << endl << endl;
		SetColour(15);
		DrawSlots(slotNum, ct1, ct1, 1); //Drawing the slots
		cout << endl;

		cout << " You lost...";
		WaitFor(240);
		return (playerChips);
	}

	return (0);
}

void QuitSlots()
{
	system("cls");
	cout << endl;
	cout << " Good.";
	WaitFor(90);
	system("cls");
	cout << endl;
	cout << " Good..";
	WaitFor(90);
	system("cls");
	cout << endl;
	cout << " Good...";
	WaitFor(90);
}

void SetColour(int colour)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
}

string DrawNumber(int num, int line)
{
	string numString = "";

	if (num == 2)
	{
		switch (line)
		{
			case 1: numString = " __ ";
					return numString;
			case 2: numString = " __|";
					return numString;
			case 3: numString = "|__ ";
					return numString;
		}
		// " __ "
		// " __|"
		// "|__ "
	}
	if (num == 3)
	{
		switch (line)
		{
			case 1: numString = " __ ";
				return numString;
			case 2: numString = " __|";
				return numString;
			case 3: numString = " __|";
				return numString;
		}
		// " __ "
		// " __|"
		// " __|"
	}
	if (num == 4)
	{ 
		switch (line)
		{
			case 1: numString = "    ";
				return numString;
			case 2: numString = "|__|";
				return numString;
			case 3: numString = "   |";
				return numString;
		}
		// "    "
		// "|__|"
		// "   |"
	}
	if (num == 5)
	{
		switch (line)
		{
			case 1: numString = " __ ";
				return numString;
			case 2: numString = "|__ ";
				return numString;
			case 3: numString = " __|";
				return numString;
		}
		// " __ "
		// "|__ "
		// " __|"
	}
	if (num == 6)
	{
		switch (line)
		{
			case 1: numString = " __ ";
				return numString;
			case 2: numString = "|__ ";
				return numString;
			case 3: numString = "|__|";
				return numString;
		}
		// " __ "
		// "|__ "
		// "|__|"
	}
	if (num == 7)
	{
		switch (line)
		{
			case 1: numString = " __ ";
				return numString;
			case 2: numString = "   |";
				return numString;
			case 3: numString = "   |";
				return numString;
		}
		// " __ "
		// "   |"
		// "   |"
	}

	return ("");
}

void DrawSlots(int slotNum[], int c3, int cf, int anim)
{
	int c1 = 120; //Colour 1
	int c2 = 135; //Colour 2
	//int c3 = 27;  //Slot Numbers Colour
	int c4 = 127; //Slot++ Colour
	int cd = 15;  //Default Black

	SetColour(cd);
	cout << "   ";
	SetColour(c1);
	cout << "|              |" << endl;
	SetColour(cd);
	cout << "  ";
	SetColour(c1);
	cout << "|     ";
	SetColour(c4);
	cout << "SLOTS++";
	SetColour(c1);
	cout << "    |" << endl;
	SetColour(cd);
	cout << " ";
	SetColour(c1);
	cout << "|__________________|";
	
	if (anim == 1)
	{
		SetColour(cd);
		cout << "  ";
		SetColour(c3);
		cout << "[]" << endl;
		SetColour(cd);
	}
	else
	{
		cout << endl;
	}

	for (int dn = 1; dn <= 3; ++dn)
	{
		SetColour(cd);
		cout << " ";
		SetColour(c2);
		cout << "| ";
		SetColour(cf);
		cout << DrawNumber(slotNum[0], dn);
		SetColour(c2);
		cout << "  ";
		SetColour(cf);
		cout << DrawNumber(slotNum[1], dn);
		SetColour(c2);
		cout << "  ";
		SetColour(cf);
		cout << DrawNumber(slotNum[2], dn);
		SetColour(c2);
		cout << " |";
		if (anim == 1)
		{ 
			SetColour(cd);
			cout << "  ";
			SetColour(c2);
			cout << "||" << endl;
		}
		else
		{
			cout << endl;
		}
	}

	SetColour(cd);
	cout << " ";
	SetColour(c2);
	cout << "|_";
	SetColour(cf);
	cout << "    ";
	SetColour(c2);
	cout << "__";
	SetColour(cf);
	cout << "    ";
	SetColour(c2);
	cout << "__";
	SetColour(cf);
	cout << "    ";
	SetColour(c2);
	cout << "_|";

	if (anim == 1)
	{
		SetColour(cd);
		cout << "  ";
		SetColour(c2);
		cout << "||" << endl;
	}
	else
	{
		SetColour(cd);
		cout << "  ";
		SetColour(c3);
		cout << "[]" << endl;
	}

	SetColour(cd);
	cout << " ";
	SetColour(c1);
	cout << "|                  |";
	SetColour(c2);
	cout << "__||" << endl;

	for (int db = 0; db < 4; ++db)
	{
		SetColour(cd);
		cout << " ";
		SetColour(c1);
		cout << "|<><><><><><><><><>|" << endl;
	}

	SetColour(cd);
	cout << " ";
	SetColour(c1);
	cout << "|__________________|" << endl;
	SetColour(cd);
	cout << " ";
	SetColour(c2);
	cout << "|                  |" << endl;
	SetColour(cd);
	cout << " ";
	SetColour(c2);
	cout << "|__________________|" << endl;
	SetColour(cd);
}

void DrawTitle(int c1)
{
	SetColour(15);
	cout << " ";
	SetColour(c1);
	cout << "-----------------------------------------------------" << endl;
	SetColour(15);
	cout << " ";
	SetColour(c1);
	cout << "|   ++++  +      +++++  +++++   ++++                |" << endl;
	SetColour(15);
	cout << " ";
	SetColour(c1);
	cout << "|  +      +      +   +    +    +        +      +    |" << endl;
	SetColour(15);
	cout << " ";
	SetColour(c1);
	cout << "|   +++   +      +   +    +     +++   +++++  +++++  |" << endl;
	SetColour(15);
	cout << " ";
	SetColour(c1);
	cout << "|      +  +      +   +    +        +    +      +    |" << endl;
	SetColour(15);
	cout << " ";
	SetColour(c1);
	cout << "|  ++++   +++++  +++++    +    ++++                 |" << endl;
	SetColour(15);
	cout << " ";
	SetColour(c1);
	cout << "-----------------------------------------------------" << endl;
	SetColour(15);
}

void DrawMystery()
{
	int animSpeed = 40;
	system("cls");
	cout << endl;
	SetColour(11);
	cout << " You knew this was going to happen..." << endl;
	WaitFor(150);

	PlaySound(TEXT("MYSTERY_01.wav"), NULL, SND_ASYNC);

	system("cls");
	cout << endl;
	cout << " You knew this was going to happen..." << endl;
	WaitFor(150);

	for (int rr = 0; rr < 10; ++rr)
	{
		system("cls");
		cout << endl;
		SetColour(14);
		cout << "          THANK YOU FOR PLAYING!!        " << endl << endl;
		SetColour(11);
		cout << "                                         " << endl;
		cout << "               |||||||||||               " << endl;
		cout << "              |||||||||||||              " << endl;
		cout << "             ||||       ||||             " << endl;
		cout << "              || __   __ ||              " << endl;
		cout << "              || -- | -- ||              " << endl;
		cout << "               |   /_|   |               " << endl;
		cout << "               |  _   _  |               " << endl;
		cout << "                |  '''  |                " << endl;
		cout << "                 |_____|                 " << endl;
		cout << "                   |   |                 " << endl;
		cout << "           |-----||     ||-----|         " << endl;
		cout << "          |       ''---''       |        " << endl;
		cout << "      ___|              ___      |       " << endl;
		cout << "     [   ]             [   ]_    |       " << endl;
		cout << "     [   ]|    |       [   ] |   |       " << endl;
		cout << "     [___] |   |       [___]  |  |       " << endl;
		cout << "       |    | |           |    | |       " << endl;
		cout << "        |    |             |    |        " << endl << endl;
		SetColour(15);
		cout << "   Never Gonna Give You Up: Rick Astley  " << endl;
		WaitFor(animSpeed-20);

		system("cls");
		cout << endl;
		SetColour(14);
		cout << "          THANK YOU FOR PLAYING!!        " << endl << endl;
		SetColour(11);
		cout << "               |||||||||||               " << endl;
		cout << "              |||||||||||||              " << endl;
		cout << "             ||||       ||||             " << endl;
		cout << "              || --   __ ||              " << endl;
		cout << "              || -- | -- ||              " << endl;
		cout << "               |   /_|   |               " << endl;
		cout << "               |  _   _  |               " << endl;
		cout << "                |  '''  |                " << endl;
		cout << "                 |_____|                 " << endl;
		cout << "                  |   |                  " << endl;
		cout << "                  |   |                  " << endl;
		cout << "          |-----||     ||-----|          " << endl;
		cout << "         |       ''---''       |         " << endl;
		cout << "     ___|              ___      |        " << endl;
		cout << "    [   ]             [   ]_    |        " << endl;
		cout << "    [   ]|    |       [   ] |   |        " << endl;
		cout << "    [___] |   |       [___]  |  |        " << endl;
		cout << "      |    | |           |    | |        " << endl;
		cout << "       |    |             |    |         " << endl << endl;
		SetColour(15);
		cout << "   Never Gonna Give You Up: Rick Astley  " << endl;
		WaitFor(animSpeed-10);

		system("cls");
		cout << endl;
		SetColour(14);
		cout << "          THANK YOU FOR PLAYING!!        " << endl << endl;
		SetColour(11);
		cout << "                                         " << endl;
		cout << "               |||||||||||               " << endl;
		cout << "              |||||||||||||              " << endl;
		cout << "             ||||       ||||             " << endl;
		cout << "              || __   __ ||              " << endl;
		cout << "              || -- | -- ||              " << endl;
		cout << "               |   /_|   |               " << endl;
		cout << "               |  _   _  |               " << endl;
		cout << "                |  '''  |                " << endl;
		cout << "                 |_____|                 " << endl;
		cout << "                 |   |                   " << endl;
		cout << "         |-----||     ||-----|           " << endl;
		cout << "        |       ''---''       |          " << endl;
		cout << "       |      ___              |___      " << endl;
		cout << "       |    _[   ]             [   ]     " << endl;
		cout << "       |   | [   ]      |     |[   ]     " << endl;
		cout << "       |  |  [___]       |   | [___]     " << endl;
		cout << "       | |    |           | |    |       " << endl;
		cout << "        |    |             |    |        " << endl << endl;
		SetColour(15);
		cout << "   Never Gonna Give You Up: Rick Astley  " << endl;
		WaitFor(animSpeed-20);

		system("cls");
		cout << endl;
		SetColour(14);
		cout << "          THANK YOU FOR PLAYING!!        " << endl << endl;
		SetColour(11);
		cout << "               |||||||||||               " << endl;
		cout << "              |||||||||||||              " << endl;
		cout << "             ||||       ||||             " << endl;
		cout << "              || __   __ ||              " << endl;
		cout << "              || -- | -- ||              " << endl;
		cout << "               |   /_|   |               " << endl;
		cout << "               |  _   _  |               " << endl;
		cout << "                |  '''  |                " << endl;
		cout << "                 |_____|                 " << endl;
		cout << "                  |   |                  " << endl;
		cout << "                  |   |                  " << endl;
		cout << "          |-----||     ||-----|          " << endl;
		cout << "         |       ''---''       |         " << endl;
		cout << "        |      ___              |___     " << endl;
		cout << "        |    _[   ]             [   ]    " << endl;
		cout << "        |   | [   ]      |     |[   ]    " << endl;
		cout << "        |  |  [___]       |   | [___]    " << endl;
		cout << "        | |    |           | |    |      " << endl;
		cout << "         |    |             |    |       " << endl << endl;
		SetColour(15);
		cout << "   Never Gonna Give You Up: Rick Astley  " << endl;
		WaitFor(animSpeed-10);
	}
	
}
