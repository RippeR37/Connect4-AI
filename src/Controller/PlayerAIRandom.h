#ifndef CONTROLLER_PLAYERAIRANDOM_H_INCLUDED
#define CONTROLLER_PLAYERAIRANDOM_H_INCLUDED

#include "Player.h"

namespace Controller {
    
    class PlayerAIRandom : public Player {
        public:
            PlayerAIRandom();
            PlayerAIRandom(const Model::Chip chip);

            Model::Move getMove(const Model::Board& board);
    };

}


#endif