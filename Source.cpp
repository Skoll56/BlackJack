#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <windows.h>


//This struct is based on code by Andrew Watson
struct Deck
{
	char m_suit[9], m_colour[6], m_name[6];
	int m_value, m_drawNo;
	bool m_inHand, m_isDealt;
};

void Shuffle(Deck *wCard);
int Deal(Deck *wCard);


int main()
{
	srand(time(NULL)); //Setting seed

// Initialising the deck of cards. This code is mostly written by Andrew Watson.
	Deck Card[52] = { 0 };
	for (int suit = 0; suit < 52; suit += 13)
	{
		for (int i = 0; i < 13; i++)
		{
			if (i > 9)
			{
				Card[suit + i].m_value = 10;
			}

			else if (i > 0)
			{
				Card[suit + i].m_value = i + 1;
			}
			else 
			{
				Card[suit + i].m_value = 11;
			}
			if (suit == 0) {
				strcpy_s(Card[suit + i].m_suit, "Spades");
				strcpy_s(Card[suit + i].m_colour, "Black");
			}
			if (suit == 13) {
				strcpy_s(Card[suit + i].m_suit, "Diamonds");
				strcpy_s(Card[suit + i].m_colour, "Red");
			}
			if (suit == 26) {
				strcpy_s(Card[suit + i].m_suit, "Clubs");
				strcpy_s(Card[suit + i].m_colour, "Black");
			}
			if (suit == 39) {
				strcpy_s(Card[suit + i].m_suit, "Hearts");
				strcpy_s(Card[suit + i].m_colour, "Red");
			}

			switch (i)
			{
			case 0: {strcpy_s(Card[suit + i].m_name, "Ace"); break; }
			case 1: {strcpy_s(Card[suit + i].m_name, "Two"); break; }
			case 2: {strcpy_s(Card[suit + i].m_name, "Three"); break; }
			case 3: {strcpy_s(Card[suit + i].m_name, "Four"); break; }
			case 4: {strcpy_s(Card[suit + i].m_name, "Five"); break; }
			case 5: {strcpy_s(Card[suit + i].m_name, "Six"); break; }
			case 6: {strcpy_s(Card[suit + i].m_name, "Seven"); break; }
			case 7: {strcpy_s(Card[suit + i].m_name, "Eight"); break; }
			case 8: {strcpy_s(Card[suit + i].m_name, "Nine"); break; }
			case 9: {strcpy_s(Card[suit + i].m_name, "Ten"); break; }
			case 10: {strcpy_s(Card[suit + i].m_name, "Jack"); break; }
			case 11: {strcpy_s(Card[suit + i].m_name, "Queen"); break; }
			case 12: {strcpy_s(Card[suit + i].m_name, "King"); break; }
			default: break;
			}
		}
	}

	// End of Initialising Deck

	//Intro to game

	char intro;
	bool quit = false;
	do
	{
		std::cout << "Welcome to Blackjack! Please select one of the following options by entering the corresponding number: " << std::endl;
		std::cout << "1- Play Game" << std::endl
			<< "2- Rules (You cannot re-visit this later, so please ensure you have read them)" << std::endl
			<< "3- Exit" << std::endl;
		std::cin >> intro;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(90000, '\n');
		}
		else std::cin.ignore(90000, '\n');

		switch (intro)
		{
			case '1': 
			{
				system("CLS");
				break;
			}
			case '2': 
			{
				std::cout << "-The aim of the game is to accumulate a higher point total than the dealer, but without going over 21. You compute your score by adding the values of your individual cards.\n-The cards 2 through 10 have their face value, J, Q, and K are worth 10 points each and, finally, the Ace is worth either 1 or 11 points." << std::endl;
				std::cout << "-You will be dealt two cards, and as will the dealer. One of the dealer's cards will be on display. You will then get to bet on your hand. \n-After betting, you can either 'Stand' (Continue with your current hand) or 'Hit' (Take another card) but if you go over a total of 21 points, you go bust and automatically lose, unless the dealer is bust." << std::endl;
				std::cout << "-The dealer will always hit until his hand is at least a total value of 17." << std::endl;
				std::cout << "-Winning gives you 2x your bet (Or 2.5x if you win with blackjack)\n-Aces are automatically calculated to be 1 or 11 based on which is better for you." << std::endl;
				system("PAUSE");
				system("CLS");
				break;
			}
			case '3': 
			{
				quit = true; 
				system("CLS");
				break;
			}
			default: 
			{
				system("CLS");
				std::cout << "Invalid Input." << std::endl; break;
			}
		}
	} 
	while (intro != '1' && quit == false);
	//End of Intro

	float money = 100;
	int drawnum;
	Card[0].m_drawNo = -1; //This is a running tally variable which can be passed into functions with the struct. It keeps track of which card # we're on.
	// Needed variables to be used outside the game loop below


	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Start of Game Loop ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	system("CLS");
	if (quit == false)
	{
		Shuffle(Card);
	}
	// Shuffle the Deck at the start of the game

	while (money > 0 && quit == false)
	{
		int pHand = 0; // Score total
		Deck Draw[14] = { 0 }; // Keeps the drawn cards
		int goAgain = 0; // End menu
		int selection = 0; // First menu
		int dHand = 0; // Dealer score total
		bool pBlackJack = false;
		bool dBlackJack = false;
		bool dBust = false, pBust = false;
		float bet = 0;
		int win = 0;
		int count = 0;
		int tally = 12;
		int pTally = 0;
		int acePhand = 0;
		int aceDhand = 0;
		bool flag = false;
		for (int i = 0; i < 52; i++)
		{
			Card[i].m_inHand = false;
		}

		// Resetting the variables involved in each round ^

		std::cout << "Starting the round!" << std::endl;
		std::cout << "You have drawn the following cards: ... \n" << std::endl;
		for (int i = 0; i < 2; i++)
		{
			drawnum = Deal(Card);
			std::cout << "[" << Card[drawnum].m_name << " Of " << Card[drawnum].m_suit << "]" << std::endl;
			pHand = pHand + Card[drawnum].m_value;
			if (Card[drawnum].m_value == 11)
			{
				acePhand++;
			}
			Draw[pTally] = Card[drawnum];
			pTally++;
		}
		std::cout << std::endl;
		system("PAUSE");
		std::cout << "~~~~~~~~~" << std::endl;

		/*Dealer's Stuff goes here*/
		std::cout << "Dealer has drawn the following cards: ...\n" << std::endl;
		for (int i = 0; i < 2; i++)
		{
			drawnum = Deal(Card);
			dHand = dHand + Card[drawnum].m_value;
			if (Card[drawnum].m_value == 11) { aceDhand++; }
			Draw[tally] = Card[drawnum];
			tally++;
		}
		std::cout << "[" << Card[drawnum].m_name << " of " << Card[drawnum].m_suit << "]" << " and a hidden 'Hole' card\n" << std::endl;
		system("PAUSE");


		/* Player's turn*/
		if (pHand == 21)
		{
			pBlackJack = true;
		}

		do
		{
			system("CLS");
			flag = false;
			if (count > 0) { std::cout << "Invalid Input" << std::endl; }
			std::cout << "Your total amount of money currently is: $" << money << std::endl;
			std::cout << "Please enter an amount you would like to bet for this round: $";
			std::cin >> bet;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(90000, '\n');
			}
			else { flag = true; }
			count++;
		} while (bet <= 0 || bet > money || flag == false);

		money = money - bet;
		system("CLS");
		do
		{
			if (pBlackJack == true)
			{
				std::cout << "~You have blackjack !!~" << std::endl;
			}
			std::cout << "Your current hand is worth: " << pHand << " points." << std::endl;
			std::cout << "You have bet: $" << bet << std::endl;
			std::cout << "Your hand is: " << std::endl;
			for (int i = 0; i < pTally; i++)
			{
				std::cout << "[" << Draw[i].m_name << " of " << Draw[i].m_suit << "]" << std::endl;
			}
			if (pBlackJack == false)
			{
				std::cout << "Would you like to: \n1- Stand \n2- Hit \n3- Quit the game" << std::endl;
				std::cin >> selection;
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(90000, '\n');
				}
				else std::cin.ignore(90000, '\n');
				switch (selection)
				{
				case 1:
				{
					break;
				}
				case 2:
				{
					drawnum = Deal(Card);
					pHand = pHand + Card[drawnum].m_value;
					if (Card[drawnum].m_value == 11) { acePhand++; }
					while (acePhand > 0 && pHand > 21)
					{
						pHand -= 10;
						acePhand--;
					}
					Draw[pTally] = Card[drawnum];
					pTally++;
					std::cout << "You have drawn the: [" << Card[drawnum].m_name << " of " << Card[drawnum].m_suit << "]" << std::endl;
					if (pHand > 21)
					{
						pBust = true;
						std::cout << "You've gone bust !" << std::endl;
					}
					system("PAUSE");
					system("CLS");
					break;
				}
				case 3:
				{
					quit = true; break;
				}
				default:
				{
					std::cin.clear();
					system("CLS");
					std::cout << "Invalid Input" << std::endl;
					break;
				}
				}
			}
			else { std::cout << "You must stand this round." << std::endl; system("PAUSE"); }

		} while (selection != 1 && pBust == false && quit == false && pBlackJack == false);
		system("CLS");


			/*Dealers turn*/
			if (quit == false)
			{
				if (dHand == 21) { dBlackJack = true; }
				std::cout << "The Dealer's card was the: [" << Draw[13].m_name << " of " << Draw[13].m_suit << "]" << std::endl;
				std::cout << "The Dealer's 'Hole' card was the: [" << Draw[12].m_name << " of " << Draw[12].m_suit << "]" << std::endl;
				while (dHand < 17 && pBust == false)
				{
					drawnum = Deal(Card);
					dHand = dHand + Card[drawnum].m_value;
					if (Card[drawnum].m_value == 11) { aceDhand++; }
					while (aceDhand > 0 && dHand > 21)
					{
						dHand -= 10;
						aceDhand--;
					}
					std::cout << "The dealer hits. They have drawn the: [" << Card[drawnum].m_name << " of " << Card[drawnum].m_suit << "]" << std::endl;
				}
				if (dHand > 21)
				{
					std::cout << "The dealer has gone bust!" << std::endl;
					dBust = true;
				}
				else
				{
					std::cout << "The dealer stands." << std::endl;
				}

				/*Comparing hands and calculating a winner*/
				system("PAUSE");
				system("CLS");
				std::cout << "End of round." << std::endl;
				std::cout << "The dealer has: ";
				if (dBust == true) { std::cout << "Gone bust!"; }
				else if (dBlackJack == true) { std::cout << "Got a BlackJack!"; }
				else { std::cout << dHand << " points!"; }
				std::cout << std::endl;

				std::cout << "~~~~~" << std::endl;
				std::cout << "You have: ";
				if (pBust == true) { std::cout << "Gone bust!"; }
				else if (pBlackJack == true) { std::cout << "Got a BlackJack!"; }
				else { std::cout << pHand << " points!"; }
				std::cout << std::endl;
				system("PAUSE");

				std::cout << "~~~~" << std::endl;
				if (pBlackJack == true && dBlackJack == false)
				{
					win = 1;     //Win 1 = BlackJack win
				}
				else if (pBust == false && dBust == true)
				{
					win = 2;    // Generic win
				}
				else if (pHand > dHand && pBust == false)
				{
					win = 2;
				}
				else if (pBlackJack == true && dBlackJack == true)
				{
					win = 0;   //Tie
				}
				else if (pBust == true && dBust == true)
				{
					win = 0;
				}
				else if (pHand == dHand)
				{
					win = 0;
				}
				else { win = -1; }  // Else, if not a win or a tie, a loss.

				if (win > 0) { std::cout << "You have won !"; }
				else if (win == 0) { std::cout << "It's a draw !"; }
				else { std::cout << "The Dealer has Won!"; }
				std::cout << std::endl;

				switch (win)
				{
				case 0:
				{
					money += bet;
					break;
				}
				case 1:
				{
					money += (bet * 2.5);
					break;
				}
				case 2:
				{
					money += (bet * 2);
					break;
				}
				default:
				{
					break;
				}
				}

				std::cout << "Your new total funds are: $" << money << std::endl;
				system("PAUSE");
				system("CLS");

				while (goAgain != 1 && goAgain != 2 && money != 0)
				{
					std::cout << "Would you like to:\n1- Play again\n2- Exit" << std::endl;
					std::cin >> goAgain;
					if (std::cin.fail())
					{
						std::cin.clear();
						std::cin.ignore(90000, '\n');
					}
					else std::cin.ignore(90000, '\n');
					switch (goAgain)
					{
					case 1:
					{
						break;
					}
					case 2:
					{
						quit = true;
						break;
					}
					default:
					{
						system("CLS");
						std::cout << "Invalid Input" << std::endl;
						break;
					}
					}
				}
			}
		}
	std::cout << "The game has ended. Thanks for playing ! You have finished with: $" << money << std::endl;

		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End of Game Loop ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	system("PAUSE");
	return 0;
}

//Start of Shuffle Function
void Shuffle(Deck *_Card)
{
	Deck Placeholder;
	int holdNo = _Card[0].m_drawNo;
	for (int i = 0; i < 52; i++)
	{
		int swapper = (rand()*69-37/2) % 52;
		Placeholder = _Card[i];
		_Card[i] = _Card[swapper];
		_Card[swapper] = Placeholder;
		if (_Card[i].m_inHand == false) { _Card[i].m_isDealt = false; }
	}
	std::cout << "~~~~~~~~~~~~~~~~~~\nShuffled the deck!\n~~~~~~~~~~~~~~~~~~" <<std::endl;
	_Card[0].m_drawNo = holdNo;  // This line hold the counters I'm storing in Card[0] to prevent them being moved when I shuffle the deck.
}
//End of Shuffle Function

//Start of Dealing Function
int Deal(Deck *_Card)
{
	int drawnum = 0;
	do
	{
		if (_Card[0].m_drawNo == 51)
		{
			_Card[0].m_drawNo = 0;
			Shuffle(_Card);
		}
		else 
		{
			_Card[0].m_drawNo++;
		}
		drawnum = _Card[0].m_drawNo;
	} while (_Card[drawnum].m_isDealt == true); // Specifically prevents drawing a hand that intentionally wasn't shuffled after use (Because the deck was shuffled during the turn)
	_Card[drawnum].m_inHand = true;
	_Card[drawnum].m_isDealt = true;
	return drawnum;
}
//End of dealing function