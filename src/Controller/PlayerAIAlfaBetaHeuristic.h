#ifndef CONTROLLER_PLAYERAIALFABETAHEURISTIC_H_INCLUDED
#define CONTROLLER_PLAYERAIALFABETAHEURISTIC_H_INCLUDED

#include "Player.h"

namespace Controller {
    
    class PlayerAIAlfaBetaHeuristic: public Player {
        public:
            PlayerAIAlfaBetaHeuristic();
            PlayerAIAlfaBetaHeuristic(const Model::Chip chip);
            PlayerAIAlfaBetaHeuristic(const Model::Chip chip, unsigned int maxDepth);

            Model::Move getMove(const Model::Board& board);

            int evaluateMove(const Model::Board& board, Model::Move move);

        private:
            Model::Move _alfaBeta(const Model::Board& board, int maxRecursionDepth, int alpha, int beta);

            int _min(Model::Board board, Model::Move move, int recursionLeft, int alpha, int beta);
            int _max(Model::Board board, Model::Move move, int recursionLeft, int alpha, int beta);

            unsigned int _maxDepth;
    };

}


#endif