#include "PlayerAIRandom.h"

namespace Controller {

    PlayerAIRandom::PlayerAIRandom() : Player() {

    }

    PlayerAIRandom::PlayerAIRandom(const Model::Chip chip) : Player(chip) {

    }

    Model::Move PlayerAIRandom::getMove(const Model::Board& board) {
        auto validMoves = board.getMoves();
        
        return validMoves[std::rand() % validMoves.size()];
    }

}