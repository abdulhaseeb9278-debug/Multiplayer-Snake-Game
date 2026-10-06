#include <iostream>
#include <vector>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <cctype>

using namespace std;

void SetColor(int color)
{
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        color
    );
}

void GotoRowCol(int r, int c)
{
    COORD pos = { (SHORT)c, (SHORT)r };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

enum Direction {
    Up, Down, Right, Left
};

struct Position {
    int rp, cp;
};

struct Snake {
    vector<Position> Ps;
    int Size;
    Direction D;
    int Score;
    char L_Key;
    char R_Key;
    char U_Key;
    char D_Key;
};

void _initSnake(vector<Snake> &Snakes, int NoOfSnakes, int Rows, int Cols)
{
    for (int i = 0; i < NoOfSnakes; i++) {

        Snakes[i].Ps.resize(3);

        for (int j = 0; j < 3; j++) {
            Snakes[i].Ps[j].rp = (Rows / 2) - i;
            Snakes[i].Ps[j].cp = (Cols / 2) - j;
        }

        Snakes[i].Score = 0;
        Snakes[i].D = Right;
        Snakes[i].Size = 3;

        for (int x = 0; x < NoOfSnakes; x++) {

            if (x == 0) {
                Snakes[x].L_Key = 'A';
                Snakes[x].R_Key = 'D';
                Snakes[x].U_Key = 'W';
                Snakes[x].D_Key = 'S';
            }

            if (x == 1) {
                Snakes[x].L_Key = 'V';
                Snakes[x].R_Key = 'N';
                Snakes[x].U_Key = 'G';
                Snakes[x].D_Key = 'B';
            }

            if (x == 2) {
                Snakes[x].L_Key = 'J';
                Snakes[x].R_Key = 'L';
                Snakes[x].U_Key = 'I';
                Snakes[x].D_Key = 'K';
            }
        }

        for (int y = 0; y < NoOfSnakes; y++) {
            Snakes[i].Score = 0;
        }
    }
}

void printSnakes(vector<Snake> &Snakes, int numberOfSnakes)
{
    for (int i = 0; i < numberOfSnakes; i++) {

        for (int j = 0; j < Snakes[i].Ps.size(); j++) {

            GotoRowCol(
                Snakes[i].Ps[j].rp,
                Snakes[i].Ps[j].cp
            );

            SetColor(i + 10);

            cout << "@";
        }
    }
}

void EraseSnakes(vector<Snake>& Snakes, int numberOfSnakes)
{
    for (int i = 0; i < numberOfSnakes; i++) {

        for (int j = 0; j < Snakes[i].Ps.size(); j++) {

            GotoRowCol(
                Snakes[i].Ps[j].rp,
                Snakes[i].Ps[j].cp
            );

            cout << " ";
        }
    }
}

void MoveSnake(
    vector<Snake>& Snakes,
    int numberOfSnakes,
    int Rows,
    int Cols
)
{
    for (int i = 0; i < numberOfSnakes; i++) {

        for (
            int j = Snakes[i].Ps.size() - 1;
            j - 1 >= 0;
            j--
        ) {
            Snakes[i].Ps[j] = Snakes[i].Ps[j - 1];
        }

        switch (Snakes[i].D) {

        case Left:

            Snakes[i].Ps[0].cp--;

            if (Snakes[i].Ps[0].cp == -1) {
                Snakes[i].Ps[0].cp = Cols - 1;
            }

            break;

        case Right:

            Snakes[i].Ps[0].cp++;

            if (Snakes[i].Ps[0].cp == Cols) {
                Snakes[i].Ps[0].cp = 0;
            }

            break;

        case Up:

            Snakes[i].Ps[0].rp--;

            if (Snakes[i].Ps[0].rp == -1) {
                Snakes[i].Ps[0].rp = Rows - 1;
            }

            break;

        case Down:

            Snakes[i].Ps[0].rp++;

            if (Snakes[i].Ps[0].rp == Rows) {
                Snakes[i].Ps[0].rp = 0;
            }

            break;
        }
    }
}

void ChangeDirection(
    vector<Snake>& Snakes,
    int numberOfSnakes,
    int Rows,
    int Cols,
    char K
)
{
    for (int i = 0; i < Snakes.size(); i++) {

        if (K == Snakes[i].L_Key && Snakes[i].D != Right) {
            Snakes[i].D = Left;
        }

        else if (K == Snakes[i].R_Key && Snakes[i].D != Left) {
            Snakes[i].D = Right;
        }

        else if (K == Snakes[i].U_Key && Snakes[i].D != Down) {
            Snakes[i].D = Up;
        }

        else if (K == Snakes[i].D_Key && Snakes[i].D != Up) {
            Snakes[i].D = Down;
        }
    }
}

void DisplayFood(
    vector<Snake>& Snakes,
    Position &FoodPosition,
    char FoodSymbol,
    int Rows,
    int Cols
)
{
    bool FoodAppearanceOnSnakes = true;

    while (FoodAppearanceOnSnakes)
    {
        FoodAppearanceOnSnakes = false;

        FoodPosition.rp = rand() % Rows;
        FoodPosition.cp = rand() % Cols;

        for (int i = 0; i < Snakes.size(); i++) {

            for (int j = 0; j < Snakes[i].Ps.size(); j++) {

                if (
                    Snakes[i].Ps[j].rp == FoodPosition.rp &&
                    Snakes[i].Ps[j].cp == FoodPosition.cp
                ) {
                    FoodAppearanceOnSnakes = true;
                    break;
                }
            }
        }
    }

    GotoRowCol(
        FoodPosition.rp,
        FoodPosition.cp
    );

    SetColor(rand() % 25 + 12);

    cout << FoodSymbol;
}

void EraseFood(Position& FoodPosition)
{
    GotoRowCol(
        FoodPosition.rp,
        FoodPosition.cp
    );

    cout << " ";
}

void SnakeEatsFood(
    vector<Snake>& Snakes,
    int numberOfSnakes,
    Position &FoodPosition,
    char FoodSymbol,
    int Rows,
    int Cols
)
{
    for (int i = 0; i < numberOfSnakes; i++) {

        {
            bool FoodEaten = false;

            if (
                Snakes[i].Ps[0].rp == FoodPosition.rp &&
                Snakes[i].Ps[0].cp == FoodPosition.cp
            )
            {
                FoodEaten = true;

                Snakes[i].Score = Snakes[i].Score + 10;

                EraseFood(FoodPosition);

                if (FoodEaten == true) {

                    Snakes[i].Ps.resize(
                        Snakes[i].Ps.size() + 1
                    );

                    for (
                        int x = Snakes[i].Ps.size();
                        x - 1 >= 1;
                        x--
                    ) {
                        Snakes[i].Ps[x - 1] =
                            Snakes[i].Ps[x - 2];
                    }

                    Snakes[i].Ps[0].rp =
                        FoodPosition.rp;

                    Snakes[i].Ps[0].cp =
                        FoodPosition.cp;

                    DisplayFood(
                        Snakes,
                        FoodPosition,
                        FoodSymbol,
                        Rows,
                        Cols
                    );
                }
            }
        }
    }
}

bool GameEnd(vector<Snake> &Snakes)
{
    bool IsSnakeDead = false;

    for (int i = 0; i < Snakes.size() - 1; i++) {

        for (int j = 0; j < Snakes[i].Ps.size(); j++) {

            for (
                int k = 0;
                k < Snakes[i + 1].Ps.size();
                k++
            ) {

                if (
                    Snakes[i].Ps[j].rp ==
                        Snakes[i + 1].Ps[k].rp &&
                    Snakes[i].Ps[j].cp ==
                        Snakes[i + 1].Ps[k].cp
                ) {
                    IsSnakeDead = true;
                }
            }
        }
    }

    return IsSnakeDead;
}

int main()
{
    int numberOfPlayers;

    int Rows = 30, Cols = 120;

    Position FoodPosition;

    char FoodSymbol = '$';

    GotoRowCol(
        Rows / 2,
        (Cols / 2) - 12
    );

    cout << "Welcome to Snake Game" << endl;

    GotoRowCol(
        (Rows / 2) + 1,
        (Cols / 2) - 12
    );

    cout << "How many players are playing? ";

    while (true) {

        cin >> numberOfPlayers;

        if (
            numberOfPlayers > 0 &&
            numberOfPlayers <= 5
        ) {
            break;
        }

        else
            cout << "Number of player limit exceeded! Try again";
    }

    system("cls");

    vector<Snake> Snakes(numberOfPlayers);

    _initSnake(
        Snakes,
        numberOfPlayers,
        Rows,
        Cols
    );

    DisplayFood(
        Snakes,
        FoodPosition,
        FoodSymbol,
        Rows,
        Cols
    );

    while (true) {

        printSnakes(
            Snakes,
            numberOfPlayers
        );

        if (_kbhit()) {

            char k = _getch();

            k = toupper(k);

            ChangeDirection(
                Snakes,
                numberOfPlayers,
                Rows,
                Cols,
                k
            );
        }

        Sleep(100);

        EraseSnakes(
            Snakes,
            numberOfPlayers
        );

        MoveSnake(
            Snakes,
            numberOfPlayers,
            Rows,
            Cols
        );

        if (GameEnd(Snakes) == true) {

            cout << "You Lose";

            Sleep(1000);

            system("cls");

            for (int i = 0; i < Snakes.size(); i++) {

                cout << "Player "
                     << i + 1
                     << " Score: "
                     << Snakes[i].Score
                     << endl;
            }

            return 0;
        }

        SnakeEatsFood(
            Snakes,
            numberOfPlayers,
            FoodPosition,
            FoodSymbol,
            Rows,
            Cols
        );
    }

    return 0;
}
