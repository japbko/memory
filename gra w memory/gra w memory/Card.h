#pragma once

class Card
{
private:
    char symbol;
    bool revealed;

public:
    Card(char symbol = ' ');

    // Zwracanie symbolu karty (jesli odkryta)
    char getSymbol() const;

    // Sprawdzenie czy karta jest odkryta
    bool isRevealed() const;

    // Odkrycie karty
    void reveal();

    // Zakrycie karty
    void hide();

    void setSymbol(char newSymbol);
};
