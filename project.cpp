#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <iterator>
#include <vector>
#include <list>
#include <deque>

unsigned int const SIZE = 64;
unsigned int const SQUARE_SIZE = 8;
double const k = 1;
double const J = 1;


class Grid {
private:
    std::deque<int> spins;
    double H = 0;
    double T = 0;
    int M = 0;
    double E = 0;

public:
    Grid() {
        srand((int)time(0));

        for (unsigned i = 0; i < SIZE; i++) {
            for (unsigned j = 0; j < SIZE; j++) {
                spins.push_back(((rand() / (double)RAND_MAX >= 0.5) - 1) * 2 + 1);
                M += spins[i * SIZE + j];
            }
        }

        for (unsigned i = 0; i < SIZE; i++) {
            for (unsigned j = 0; j < SIZE; j++) {
                if (i != 0) {
                    E += -J * spins[i * SIZE + j] * spins[(i - 1) * SIZE + j];
                }
                else if (i != SIZE) {
                    E += -J * spins[i * SIZE + j] * spins[(i + 1) * SIZE + j];
                }
                if (j != 0) {
                    E += -J * spins[i * SIZE + j] * spins[i * SIZE + j -1];
                }
                else if (j != SIZE) {
                    E += -J * spins[i * SIZE + j] * spins[i * SIZE + j +1];
                }
                E -= H * M;
            }
        }
    }

    void print() {
        for (unsigned i = 0; i < SIZE; i++) {
            for (unsigned j = 0; j < SIZE; j++) {
                std::cout << spins[i * SIZE + j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << M << " " << E << std::endl;
    }

    void metropolis()
    {
        int x, y;
        for (int i = 0; i < SIZE * SIZE * 100; i++)
        {   
            int sum = 0;
            double dE = 0;
            x = rand() % SIZE;
            y = rand() % SIZE;
            if (y != 0) {
                sum += spins[(y - 1) * SIZE + x];
            }
            else if (y != SIZE-1) {
                sum += spins[(y + 1) * SIZE + x];
            }
            if (x != 0) {
                sum += spins[y * SIZE + x - 1];
            }
            else if (x != SIZE-1) {
                sum += spins[y * SIZE + x + 1];
            }

            dE += 2 * J * spins[y * SIZE + x] *sum + 2 * H * spins[y * SIZE + x];

           

            if (dE <= 0 || (rand() / (double)RAND_MAX) < exp(-dE / (k * T)))
            {   
                spins[y * SIZE + x] = -spins[y * SIZE + x];
                M += 2 * spins[y * SIZE + x];
                E += dE;
            }
        }
        std::cout << "T = " << T << " H = " << H << " M = " << M << std::endl;
    }

    std::deque<sf::RectangleShape> drawing_data() {
        std::deque<sf::RectangleShape> rectangles;

        for (unsigned i = 0; i < SIZE; i++) {
            for (unsigned j = 0; j < SIZE; j++) {
                sf::RectangleShape to_push(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
                to_push.setPosition((float)SQUARE_SIZE * j, (float)SQUARE_SIZE * i);
                if (spins[i * SIZE + j] == 1) {
                    to_push.setFillColor(sf::Color::Green);
                }
                else if (spins[i * SIZE + j] == -1) {
                    to_push.setFillColor(sf::Color::Red);
                }
                else {
                    to_push.setFillColor(sf::Color::White);
                }
                
                rectangles.push_back(to_push);
            }
        }
        return rectangles;
    }

    void enter_T() {
        std::cout << "New T: ";
        std::cin >> T;
        std::cout << std::endl;
    }

    void enter_H() {
        std::cout << "New H: ";
        std::cin >> H;
        std::cout << std::endl;
    }
};

void graphics() {
    Grid grid = Grid();
    sf::RenderWindow window(sf::VideoMode(SIZE * SQUARE_SIZE, SIZE * SQUARE_SIZE), "Simulation");
    /*sf::RenderWindow window2(sf::VideoMode(400, 400), "Options");*/
    window.setVerticalSyncEnabled(true);

    grid.metropolis();
    std::deque<sf::RectangleShape> rectangles = grid.drawing_data();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::T) {
                    grid.enter_T();
                }
                if (event.key.code == sf::Keyboard::H) {
                    grid.enter_H();
                }
            }
        }

        window.clear();
        for (unsigned i = 0; i < SIZE * SIZE; i++) {
            window.draw(rectangles[i]);
        }
        window.display();

        grid.metropolis();
        rectangles = grid.drawing_data();
    }
}


int main()
{   
    graphics();
    return 0;
}
