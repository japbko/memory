#include "Player.h"

// Konstruktor przyjmuj�cy nazw� gracza i inicjuj�cy punkty na zero

Player::Player(const std::string& playerName) : name(playerName), score(0) {}

// Funkcja do zdobywania punkt�w (np. po znalezieniu pary kart)

void Player::addPoint() {
    ++score;
}

// Funkcja zwracaj�ca aktualn� punktacj� gracza

int Player::getScore() const {
    return score;
}

// Funkcja zwracaj�ca nazw� gracza

std::string Player::getName() const {
    return name;
}
