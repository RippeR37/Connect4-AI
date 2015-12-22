#ifndef CONTROLLER_PLAYERAIMINMAX_H_INCLUDED
#define CONTROLLER_PLAYERAIMINMAX_H_INCLUDED

#include "Player.h"

namespace Controller {
    
    class PlayerAIMinMax : public Player {
        public:
            PlayerAIMinMax();
            PlayerAIMinMax(const Model::Chip chip);
            PlayerAIMinMax(const Model::Chip chip, unsigned int maxDepth);

            Model::Move getMove(const Model::Board& board);

        private:
            Model::Move _minMax(const Model::Board& board, int maxRecursionDepth);

            int _min(Model::Board board, Model::Move move, int recursionLeft);
            int _max(Model::Board board, Model::Move move, int recursionLeft);

            unsigned int _maxDepth;
    };

}


#endif