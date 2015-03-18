#include "Board.h"

namespace Model {

    Board::Board() {
        reset();
    }

    Board::~Board() {

    }

    Board::Board(const Board& board) {
        _array = board._array;
    }

    Board& Board::operator=(const Board& board) {
        _array = board._array;

        return *this;
    }

    void Board::reset() {
        for(auto& row : _array) {
            for(auto& slot : row) {
                slot = Chip::Empty;
            }
        }
    }

    const bool Board::show() const {
        // 

        return true;
    }

    const bool Board::makeMove(const Move move, const Chip chip) {
        bool isValidMove = isValid(move);

        if(isValidMove) {
            // make it
        }

        return isValidMove;
    }

    const GameStatus Board::checkStatus(const Chip playersChip) const {
        return GameStatus::InProgress;
    }

    const bool Board::isValid(const Move move) const {
        return true;
    }

    const std::vector<const Move> Board::getMoves() const {
        std::vector<const Move> possibleMoves;

        // 

        return possibleMoves;
    }

    const Board::BoardArray& Board::getArray() const {
        return _array;
    }

}