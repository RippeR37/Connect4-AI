#include "PlayerHuman.h"

#include <iostream>

namespace Controller {

    PlayerHuman::PlayerHuman() : Player() {

    }

    PlayerHuman::PlayerHuman(const Model::Chip chip) : Player(chip) {

    }

    Model::Move PlayerHuman::getMove(const Model::Board& board) {
        int column = 0;

        do {
            std::cout << "Podaj kolumne (1-7): ";
            std::cin >> column;
        } while(column < 1 || column > 7);

        return static_cast<Model::Move>(column - 1);
    }

}