#ifndef CONTROLLER_PLAYERHUMAN_H_INCLUDED
#define CONTROLLER_PLAYERHUMAN_H_INCLUDED

#include "Player.h"

namespace Controller {
    
    class PlayerHuman : public Player {
        public:
            PlayerHuman();
            PlayerHuman(const Model::Chip chip);

            Model::Move getMove(const Model::Board& board);
    };

}


#endif