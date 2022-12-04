#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Player {
  string name;
  int points;
  int cardToWin;

public:
  Player(string n, int p) : name(n), points(p){};

  void setPoint(int p) { this->points = this->points + p; };

  void setCardToWin(int c) { this->cardToWin = c; }

  int getPoints() { return this->points; };

  string getName() { return this->name; };

  int getCardToWin() { return this->cardToWin; };
};

class Card {
  int timesUsed;
  const int points;

public:
  Card(int n, const int p) : timesUsed(n), points(p){};

  int getCardPoints() { return this->points; };

  int getTimesUsed() { return this->timesUsed; };

  void setTimesUsed() { this->timesUsed = this->timesUsed - 1; };
};

int validateCard(int n, map<int, int *> cards) {

  int resp = n;

  if (n > 0 && n <= 10) {
    if (*(cards.find(n)->second) > 0) {
      resp = n;
      *(cards.find(n)->second) = *(cards.find(n)->second) - 1;
    }
  } else if (n > 10 && n < 14) {
    resp = 10;
    *(cards.find(10)->second) = *(cards.find(10)->second) - 1;
  } else if (n < 1 || n > 13)
    return -1;

  return resp;
}

int cardToWin(int n, map<int, int *> cards) {

  if (n > 13 || n < 0)
    return -1;
  if (*(cards.find(n)->second) < 1)
    return cardToWin(n + 1, cards);

  if (n >= 10 && n <= 13)
    return 10;
  else
    return n;
}

int main()
{
    Player john("John", 0);
    Player mary("Mary", 0);
    vector<Player> players{john, mary};

    map<int, int *> cards;
    vector<int> amountCards{4, 4, 4, 4, 4, 4, 4, 4, 4, 16};

    for (int i = 0; i < 10; i++)
        cards[i + 1] = &amountCards[i];

    int nRounds = -1;
    int initialCard = -1, initialCard2 = -1;
    int commonCard = -1;

    while (nRounds < 1 || nRounds > 8)
    {
        cin >> nRounds;
    }

    for (int i = 0; i < players.size(); i++)
    {
        while (initialCard == -1)
        {
            cin >> initialCard;
            initialCard = validateCard(initialCard, cards);
        }

        while (initialCard2 == -1)
        {
            cin >> initialCard2;
            initialCard2 = validateCard(initialCard2, cards);
        }

        players[i].setPoint(initialCard);
        players[i].setPoint(initialCard2);

        initialCard = -1;
        initialCard2 = -1;
    }

    for (int i = 0; i < nRounds; i++)
    {
        while (commonCard == -1)
        {
            cin >> commonCard;
            commonCard = validateCard(commonCard, cards);
        }

        for (int n = 0; n < players.size(); n++)
        {
            players[n].setPoint(commonCard);
        }

        commonCard = -1;
    }

    // cout << "JOHN: " << players[0].getPoints() << endl;
    // cout << "MARY: " << players[1].getPoints() << endl;

    // cards to lose
    players[0].setCardToWin(cardToWin(24 - players[0].getPoints(), cards));

    // cards to win
    players[1].setCardToWin(cardToWin(23 - players[1].getPoints(), cards));

    if (players[1].getCardToWin() + players[1].getPoints() <= 23)
    {
        if (players[1].getPoints() >= players[0].getPoints() &&
            players[1].getCardToWin() != -1 && nRounds != 8)
        {
            cout << players[1].getCardToWin() << endl;
        }
        else
            cout << players[0].getCardToWin() << endl;
    }
    else
        cout << -1 << endl;
}