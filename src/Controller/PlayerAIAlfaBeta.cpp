#include "PlayerAIAlfaBeta.h"

#include <iostream>
#include <climits>

namespace Controller {

    PlayerAIAlfaBeta::PlayerAIAlfaBeta() : Player() {

    }

    PlayerAIAlfaBeta::PlayerAIAlfaBeta(const Model::Chip chip) : PlayerAIAlfaBeta(chip, 7) {

    }
    
    PlayerAIAlfaBeta::PlayerAIAlfaBeta(const Model::Chip chip, unsigned int maxDepth) : Player(chip) {
        _maxDepth = maxDepth;
    }

    Model::Move PlayerAIAlfaBeta::getMove(const Model::Board& board) {
        Model::Move result = _alfaBeta(board, _maxDepth, INT_MIN, INT_MAX);

        system("pause");

        return result;
    }

    Model::Move PlayerAIAlfaBeta::_alfaBeta(const Model::Board& board, int maxRecursionDepth, int alpha, int beta) {
        std::vector<Model::Move> bestMoves = { Model::Move::Slot4 };
        Model::Move result;
        int bestValue = alpha;
        int currentValue = bestValue;

        for(auto move : board.getMoves()) {
            currentValue = _min(board, move, maxRecursionDepth, alpha, beta);

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
    
    int PlayerAIAlfaBeta::_min(Model::Board board, Model::Move move, int recursionLeft, int alpha, int beta) {
        if(recursionLeft == 0)
            return 0;

        board.makeMove(move, getChip());

        if(board.getStatus() == Model::GameStatus::Won) {
            return INT_MAX - (_maxDepth - recursionLeft);

        } else if(board.getStatus() == Model::GameStatus::Tie) {
            return 0;

        } else {
            for(auto move : board.getMoves()) {
                beta = std::min(beta, _max(board, move, recursionLeft - 1, alpha, beta));
                
                if(alpha >= beta)
                    break;
            }

            return beta;
        }
    }

    int PlayerAIAlfaBeta::_max(Model::Board board, Model::Move move, int recursionLeft, int alpha, int beta) {
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
            for(auto move : board.getMoves()) {
                alpha = std::max(alpha, _min(board, move, recursionLeft - 1, alpha, beta));

                if(alpha >= beta)
                    break;
            }

            return alpha;
        }
    }


}