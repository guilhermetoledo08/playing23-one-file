#include <iostream>

using namespace std;

class Player
{
    string name;
    int points;

public:
    Player(string n, int p);
    void setPoint(int p);
    int getPoints();
};