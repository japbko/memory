#include "Board.h"

Board::Board(int rows, int cols) : rows(rows), cols(cols) // do ogarniecia
{
    initializeBoard(rows, cols);
}

// Tworzenie planszy z losowo rozmieszczonymi kartami

void Board::initializeBoard(int rows, int cols)
{
    std::vector<Card> deck;
    char symbol = 'A';

    // Tworzenie par kart
    for (int i = 0; i < (rows * cols) / 2; ++i)
    {
        deck.push_back(Card(symbol));
        deck.push_back(Card(symbol));
        ++symbol;
    }

    // Mieszanie kart
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::random_shuffle(deck.begin(), deck.end());

    // Tworzenie dwuwymiarowej tablicy
    int index = 0;
    cards.resize(rows, std::vector<Card>(cols));
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cards[i][j] = deck[index++];
        }
    }
}

// Wyœwietlanie planszy

void Board::displayBoard() const
{
    std::cout << "  ";
    for (int j = 0; j < cards[0].size(); ++j)
    {
        std::cout << j << " "; 
    }
    std::cout << std::endl;

    for (int i = 0; i < cards.size(); ++i)
    {
        std::cout << i << " ";
        for (int j = 0; j < cards[i].size(); ++j)
        {
            std::cout << cards[i][j].getSymbol() << " ";
        }
        std::cout << std::endl;
    }
}

// Metody do uzyskiwania wymiarów planszy

int Board::getRows() const { return rows; }
int Board::getCols() const { return cols; }

// Uzyskiwanie referencji do konkretnej karty

Card& Board::getCard(int row, int col)
{
    return cards[row][col];
}

// Sprawdzanie czy wszystkie karty s¹ odkryte

bool Board::allCardsRevealed() const
{
    for (const auto& row : cards)
    {
        for (const auto& card : row)
        {
            if (!card.isRevealed())
            {
                return false;
            }
        }
    }
    return true;
}
