#include "Board.h"

#include <functional>
#include <iostream>

namespace Model {

    Board::Board() {
        reset();

        _lastMoveX = 999;
        _lastMoveY = 999;
    }

    Board::~Board() {

    }

    Board::Board(const Board& board) {
        _array = board._array;

        _lastMoveX = board._lastMoveX;
        _lastMoveY = board._lastMoveY;
    }

    Board& Board::operator=(const Board& board) {
        _array = board._array;

        _lastMoveX = board._lastMoveX;
        _lastMoveY = board._lastMoveY;

        return *this;
    }

    void Board::reset() {
        for(auto& row : _array) {
            for(auto& slot : row) {
                slot = Chip::Empty;
            }
        }

        _status = GameStatus::InProgress;
    }

    bool Board::show() const {
        system("cls");

        for(auto& slot : _array[0]) {
            std::cout << "----";
        }
        std::cout << "|" << std::endl;

        for(auto row = _array.rbegin(); row != _array.rend(); ++row) {
            for(auto& slot : *row) {
                if(slot == Chip::Red) {
                    std::cout << "| R ";
                } else if(slot == Chip::Yellow) {
                    std::cout << "| Y ";
                } else {
                    std::cout << "|   ";
                }
            } std::cout << "|" << std::endl;

            for(auto& slot : *row) {
                std::cout << "----";
            } std::cout << "|" << std::endl;
        }

        return true;
    }

    bool Board::makeMove(const Move move, const Chip chip) {
        bool isValidMove = isValid(move);

        if(isValidMove) {
            unsigned int slotColumn = static_cast<unsigned int>(move);
            unsigned int currentHeight = 0;

            while(_array[currentHeight][slotColumn] != Chip::Empty) {
                currentHeight += 1;
            }

            _array[currentHeight][slotColumn] = chip;
            _lastMoveX = slotColumn;
            _lastMoveY = currentHeight;

            _status = checkStatus();
        }

        return isValidMove;
    }
    
    GameStatus Board::checkStatus() const {
        const unsigned int topRow = _array.size() - 1;

        if(_lastMoveX == 999 && _lastMoveY == 999) {
            return GameStatus::InProgress;

        } else {
            bool isWin = checkEndConditionOnMove(_lastMoveY, _lastMoveX);

            if(isWin) {
                return GameStatus::Won;

            } else {
                for(unsigned int i = 0; i < _array.size(); ++i) {
                    if(_array[topRow][i] == Chip::Empty)
                        return GameStatus::InProgress;
                }

                return GameStatus::Tie;
            }
        }
    }


    GameStatus Board::checkStatusOnMove(const Move move, const Chip chip) const {
        GameStatus status = _status;
        Board& thisConstless = const_cast<Board&>(*this); // we promise to clean up after ourselves
        unsigned int columnID = static_cast<unsigned int>(move);
        unsigned int rowID = 0;
        unsigned int oldX = _lastMoveX;
        unsigned int oldY = _lastMoveY;

        if(isValid(move)) {
            // Make move
            while(_array[rowID][columnID] != Chip::Empty) {
                ++rowID;
            }
            thisConstless._array[rowID][columnID] = chip; // giving promise
            thisConstless._lastMoveX = columnID;
            thisConstless._lastMoveY = rowID;

            // Check status
            status = checkStatus();

            // Retract move
            thisConstless._array[rowID][columnID] = Chip::Empty;    // fulfiling promise
            thisConstless._lastMoveX = oldX;
            thisConstless._lastMoveY = oldY;
        }

        return status;
    }

    bool Board::isValid(const Move move) const {
        unsigned int slotColumn = static_cast<unsigned int>(move);
        unsigned int topRow = _array.size() - 1;
        bool result;

        result = (_array[topRow][slotColumn] == Chip::Empty);

        return result;
    }

    std::vector<const Move> Board::getMoves() const {
        std::vector<const Move> possibleMoves;
        unsigned int topRow = _array.size() - 1;

        for(unsigned int column = 0; column < _array[0].size(); ++column) {
            if(_array[topRow][column] == Chip::Empty) {
                possibleMoves.emplace_back(static_cast<Move>(column));
            }
        }

        return possibleMoves;
    }

    const Board::BoardArray& Board::getArray() const {
        return _array;
    }

    GameStatus Board::getStatus() const {
        return _status;
    }

    bool Board::checkEndConditionOnMove(const unsigned int row, const unsigned int column) const {
        int x = static_cast<int>(column);
        int y = static_cast<int>(row);
        Chip chip = _array[y][x];

        // Helper function - checks wheter slot (x,y) is on board
        auto isOnBoard = [&, this](int x, int y) -> bool {
            bool result = true;

            if(x < 0 || x >= static_cast<int>(_array[0].size()) || y < 0 || y >= static_cast<int>(_array.size()))
                result = false;

            return result;
        };

        auto checkInDirection = [&, this](int currentX, int currentY, int dX, int dY, const Chip chip) -> int {
            int result = 0;
            
            currentX += dX;
            currentY += dY;

            while(isOnBoard(currentX, currentY) && _array[currentY][currentX] == chip) {
                ++result;
                currentX += dX;
                currentY += dY;
            }

            return result;
        };

               if(checkInDirection(x, y, 1,  0, chip) + checkInDirection(x, y, -1,  0, chip) >= 3) { /* - */
            return true;
        } else if(checkInDirection(x, y, 0,  1, chip) + checkInDirection(x, y,  0, -1, chip) >= 3) { /* | */
            return true;
        } else if(checkInDirection(x, y, 1,  1, chip) + checkInDirection(x, y, -1, -1, chip) >= 3) { /* / */
            return true;
        } else if(checkInDirection(x, y, 1, -1, chip) + checkInDirection(x, y, -1,  1, chip) >= 3) { /* \ */
            return true;
        }

        return false;
    }

}