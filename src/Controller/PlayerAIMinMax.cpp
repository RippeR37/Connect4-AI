#include "PlayerAIMinMax.h"

#include <iostream>
#include <climits>

namespace Controller {

    PlayerAIMinMax::PlayerAIMinMax() : Player() {

    }

    PlayerAIMinMax::PlayerAIMinMax(const Model::Chip chip) : PlayerAIMinMax(chip, 7) {

    }
    
    PlayerAIMinMax::PlayerAIMinMax(const Model::Chip chip, unsigned int maxDepth) : Player(chip) {
        _maxDepth = 7;
    }

    Model::Move PlayerAIMinMax::getMove(const Model::Board& board) {
        Model::Move result = _minMax(board, _maxDepth);

        //system("pause");

        return result;
    }

    Model::Move PlayerAIMinMax::_minMax(const Model::Board& board, int maxRecursionDepth) {
        std::vector<Model::Move> bestMoves = { Model::Move::Slot4 };
        Model::Move result;
        int bestValue = INT_MIN;
        int currentValue;

        for(auto move : board.getMoves()) {
            currentValue = _min(board, move, maxRecursionDepth);

            if(bestValue < currentValue) {
                bestValue = currentValue;
                bestMoves.clear();
                bestMoves.push_back(move);
            } else if(bestValue == currentValue) {
                bestMoves.push_back(move);
            }

            std::cout << "Ruch #" << static_cast<unsigned int>(move) + 1 << " = " << currentValue << std::endl;
        }

        result = bestMoves.at(std::rand() % bestMoves.size());

        return result;
    }
    
    int PlayerAIMinMax::_min(Model::Board board, Model::Move move, int recursionLeft) {
        if(recursionLeft == 0)
            return 0;

        board.makeMove(move, getChip());

        if(board.getStatus() == Model::GameStatus::Won) {
            return INT_MAX - (_maxDepth - recursionLeft);

        } else if(board.getStatus() == Model::GameStatus::Tie) {
            return 0;

        } else {
            int bestValue = INT_MAX;
            int currentValue = 0;

            for(auto move : board.getMoves()) {
                currentValue = _max(board, move, recursionLeft - 1);
            
                if(bestValue > currentValue)
                    bestValue = currentValue;
            }

            return bestValue;
        }
    }

    int PlayerAIMinMax::_max(Model::Board board, Model::Move move, int recursionLeft) {
        if(recursionLeft == 0)
            return 0;

        board.makeMove(
            move, 
            (getChip() == Model::Chip::Red) ? 
                Model::Chip::Yellow :
                Model::Chip::Red
        );

        if(board.getStatus() == Model::GameStatus::Won) {
            return INT_MIN + (_maxDepth - recursionLeft);

        } else if(board.getStatus() == Model::GameStatus::Tie) {
            return 0;

        } else {
            int bestValue = INT_MIN;
            int currentValue = 0;

            for(auto move : board.getMoves()) {
                currentValue = _min(board, move, recursionLeft - 1);
            
                if(bestValue < currentValue)
                    bestValue = currentValue;
            }

            return bestValue;
        }
    }


}