#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>
#include "Card.h"

class Board
{
private:
    int rows;
    int cols;
    std::vector<std::vector<Card>> cards;

public:
    Board(int rows, int cols);

    // Tworzenie planszy z losowo rozmieszczonymi kartami
    void initializeBoard(int rows, int cols);

    // Wyœwietlanie planszy
    void displayBoard() const;

    // Metody do uzyskiwania wymiarów planszy
    int getRows() const;
    int getCols() const;

    // Uzyskiwanie referencji do konkretnej karty
    Card& getCard(int row, int col);

    // Sprawdzanie czy wszystkie karty s¹ odkryte
    bool allCardsRevealed() const;
};
