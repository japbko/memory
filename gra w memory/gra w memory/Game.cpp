#include "Game.h"

Game::Game(int rows, int cols, const std::string& playerName1, const std::string& playerName2)
    : board(rows, cols), player1(playerName1), player2(playerName2), currentPlayer(&player1) {}

void Game::clearTerminal()
{
    system("cls"); // Windows
}

// Rozpocz�cie rozgrywki

void Game::startGame()
{
    while (!board.allCardsRevealed())
    {
        clearTerminal();
        board.displayBoard();
        std::cout << "Kolej gracza: " << currentPlayer->getName() << std::endl;
        makeMove();
        switchPlayer();
    }
    displayWinner();
}

// Wykonywanie ruch�w

void Game::makeMove()
{
    bool validMove = false;
    while (!validMove)
    {
        try
        {
            int row1, col1, row2, col2;

            std::cout << "Podaj wsp�rz�dne pierwszej karty (wiersz i kolumna odzielone spacj�, np. 1 3): ";
            if (!(std::cin >> row1 >> col1))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("Nieprawid�owe dane wej�ciowe.");
            }
            if (row1 < 0 || row1 >= board.getRows() || col1 < 0 || col1 >= board.getCols())
            {
                throw std::invalid_argument("Nieprawid�owe wsp�rz�dne pierwszej karty.");
            }
            if (board.getCard(row1, col1).isRevealed())
            {
                throw std::invalid_argument("Pierwsza karta jest ju� odkryta. Wybierz inn� kart�.");
            }

            std::cout << "Podaj wsp�rz�dne drugiej karty (wiersz i kolumna odzielone spacj�, np. 1 3): ";
            if (!(std::cin >> row2 >> col2))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("Nieprawid�owe dane wej�ciowe.");
            }
            if (row2 < 0 || row2 >= board.getRows() || col2 < 0 || col2 >= board.getCols())
            {
                throw std::invalid_argument("Nieprawid�owe wsp�rz�dne drugiej karty.");
            }
            if (board.getCard(row2, col2).isRevealed())
            {
                throw std::invalid_argument("Druga karta jest ju� odkryta. Wybierz inn� kart�.");
            }
            if (row1 == row2 && col1 == col2)
            {
                throw std::invalid_argument("Nie mo�esz wybra� tej samej karty dwa razy.");
            }

            // Odkrycie wybranych kart
            board.getCard(row1, col1).reveal();
            board.getCard(row2, col2).reveal();
            clearTerminal();
            board.displayBoard();

            // Sprawdzenie, czy karty s� takie same
            if (board.getCard(row1, col1).getSymbol() == board.getCard(row2, col2).getSymbol())
            {
                std::cout << "Brawo! Znalaz�e� par�!" << std::endl;
                currentPlayer->addPoint();
            }
            else
            {
                std::cout << "Karty s� r�ne. Zakrywamy je ponownie." << std::endl;
                board.getCard(row1, col1).hide();
                board.getCard(row2, col2).hide();
            }

            std::string choice, filename;
            std::cout << "Czy chcesz zapisa�(t/n): ";
            std::cin >> choice;
            if (choice == "t")
            {
                std::cout << "Podaj nazw� pliku pod jak� ma by� zapisana gra: ";
                std::cin >> filename;
                saveGame(filename);
            }
            clearTerminal();

            validMove = true;
        }
        catch (const std::invalid_argument& e)
        {
            std::cerr << "B��d: " << e.what() << " Spr�buj ponownie." << std::endl;
        }
    }
}

// Zmiana Gracza

void Game::switchPlayer()
{
    currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
}

// Wy�wietlenie wynik�w

void Game::displayWinner()
{
    std::cout << "Gra zako�czona!" << std::endl;
    std::cout << player1.getName() << " zdoby�(a) " << player1.getScore() << " punkt�w." << std::endl;
    std::cout << player2.getName() << " zdoby�(a) " << player2.getScore() << " punkt�w." << std::endl;

    if (player1.getScore() > player2.getScore())
    {
        std::cout << "Zwyci�zca: " << player1.getName() << "!" << std::endl;
    }
    else if (player2.getScore() > player1.getScore())
    {
        std::cout << "Zwyci�zca: " << player2.getName() << "!" << std::endl;
    }
    else
    {
        std::cout << "Remis!" << std::endl;
    }
}

// Zapis gry

void Game::saveGame(const std::string& filename)
{
    std::ofstream outFile(filename);
    if (!outFile)
    {
        std::cerr << "Nie uda�o si� otworzy� pliku do zapisu!" << std::endl;
        return;
    }

    outFile << board.getRows() << ' ' << board.getCols() << std::endl;

    for (int i = 0; i < board.getRows(); ++i)
    {
        for (int j = 0; j < board.getCols(); ++j)
        {
            outFile << board.getCard(i, j).getSymbol() << ' '
                << board.getCard(i, j).isRevealed() << ' ';
        }
        outFile << std::endl;
    }

    outFile << player1.getName() << ' ' << player1.getScore() << std::endl;
    outFile << player2.getName() << ' ' << player2.getScore() << std::endl;

    outFile << (currentPlayer == &player1 ? "1" : "2") << std::endl;

    std::cout << "Gra zosta�a zapisana do pliku: " << filename << std::endl;
    outFile.close();
}

// Wczytaj gre

void Game::loadGame(const std::string& filename)
{
    std::ifstream inFile(filename);
    if (!inFile)
    {
        std::cerr << "Nie uda�o si� otworzy� pliku do wczytania!" << std::endl;
        return;
    }

    int rows, cols;
    inFile >> rows >> cols;
    board = Board(rows, cols);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            char symbol;
            bool revealed;
            inFile >> symbol >> revealed;
            board.getCard(i, j).setSymbol(symbol);
            if (revealed)
            {
                board.getCard(i, j).reveal();
            }
        }
    }

    std::string name1, name2;
    int score1, score2;
    inFile >> name1 >> score1 >> name2 >> score2;
    player1 = Player(name1);
    player2 = Player(name2);
    while (score1--)
        player1.addPoint();
    while (score2--)
        player2.addPoint();

    int currentPlayerNum;
    inFile >> currentPlayerNum;
    currentPlayer = (currentPlayerNum == 1) ? &player1 : &player2;

    std::cout << "Gra zosta�a wczytana z pliku: " << filename << std::endl;
    inFile.close();
}
