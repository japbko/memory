#pragma once

#include <string>

class Player {
private:
    std::string name;   // Nazwa gracza
    int score;          // Aktualna liczba punkt�w gracza

public:
    // Konstruktor przyjmuj�cy nazw� gracza i inicjuj�cy punkty na zero
    Player(const std::string& playerName);

    // Funkcja do zdobywania punkt�w (np. po znalezieniu pary kart)
    void addPoint();

    // Funkcja zwracaj�ca aktualn� punktacj� gracza
    int getScore() const;

    // Funkcja zwracaj�ca nazw� gracza
    std::string getName() const;
};

