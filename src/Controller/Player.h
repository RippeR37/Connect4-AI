#ifndef CONTROLLER_PLAYER_H_INCLUDED
#define CONTROLLER_PLAYER_H_INCLUDED

#include "../Model/Board.h"
#include "../Model/Chip.h"
#include "../Model/Move.h"

namespace Controller {
    
    class Player {
        public:
            Player();
            Player(const Model::Chip chip);
            virtual ~Player();

            Player(const Player&) = delete;
            Player& operator=(const Player&) = delete;

            virtual const Model::Move getMove(const Model::Board& board) = 0;

            const Model::Chip getChip() const;

        private:
            void setChip(const Model::Chip chip);

            Model::Chip _chip;

        private:
            friend class LogicHandler;
    };

}


#endif