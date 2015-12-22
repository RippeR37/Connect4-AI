#include "PlayerAIAlfaBetaHeuristic.h"

#include <iostream>
#include <climits>

namespace Controller {

    PlayerAIAlfaBetaHeuristic::PlayerAIAlfaBetaHeuristic() : Player() {

    }

    PlayerAIAlfaBetaHeuristic::PlayerAIAlfaBetaHeuristic(const Model::Chip chip) : PlayerAIAlfaBetaHeuristic(chip, 7) {

    }
    
    PlayerAIAlfaBetaHeuristic::PlayerAIAlfaBetaHeuristic(const Model::Chip chip, unsigned int maxDepth) : Player(chip) {
        _maxDepth = maxDepth;
    }

    Model::Move PlayerAIAlfaBetaHeuristic::getMove(const Model::Board& board) {
        Model::Move result = _alfaBeta(board, _maxDepth, INT_MIN, INT_MAX);

        //system("pause");

        return result;
    }

    int PlayerAIAlfaBetaHeuristic::evaluateMove(const Model::Board& board, Model::Move move) {
        int result = 0;
        int moveCollumn = static_cast<int>(move) + 1;
        int moveRow = 0;

        // Preferuj srodek
        if(moveCollumn > 4) {
            result += 8 - moveCollumn;
        } else {
            result += moveCollumn;
        }

        // Preferuj niskie
        while(board.getArray()[moveRow][moveCollumn - 1] != Model::Chip::Empty) {
            ++moveRow;
        }
        result += 6 - moveRow;

        return result;
    }

    Model::Move PlayerAIAlfaBetaHeuristic::_alfaBeta(const Model::Board& board, int maxRecursionDepth, int alpha, int beta) {
        std::vector<Model::Move> bestMoves = { Model::Move::Slot4 };
        std::vector<Model::Move> resultMoves = { Model::Move::Slot4 };
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

        std::cout << " --- " << std::endl;

        if(bestValue == 0) {
            for(auto move : bestMoves) {
                currentValue = evaluateMove(board, move);
                std::cout << "Ruch #" << static_cast<unsigned int>(move) + 1 << " = " << currentValue << " (0)" << std::endl;

                if(currentValue > bestValue) {
                    resultMoves.clear();
                    resultMoves.push_back(move);
                    bestValue = currentValue;
                } else if(currentValue == bestValue) {
                    resultMoves.push_back(move);
                }
            }
            result = resultMoves.at(std::rand() % resultMoves.size());

        } else {
            result = bestMoves.at(std::rand() % bestMoves.size());
        }

        return result;
    }
    
    int PlayerAIAlfaBetaHeuristic::_min(Model::Board board, Model::Move move, int recursionLeft, int alpha, int beta) {
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

    int PlayerAIAlfaBetaHeuristic::_max(Model::Board board, Model::Move move, int recursionLeft, int alpha, int beta) {
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