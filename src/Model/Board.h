#ifndef MODEL_BOARD_H_INCLUDED
#define MODEL_BOARD_H_INCLUDED

#include "Chip.h"
#include "GameStatus.h"
#include "Move.h"

#include <array>
#include <vector>

namespace Model {
    
    class Board {
        public:
            typedef std::array<std::array<Chip, 7>, 6> BoardArray;

        public:
            Board();
            ~Board();

            Board(const Board& board);
            Board& operator=(const Board& board);

            void reset();

            bool show() const;
            bool makeMove(const Move move, const Chip chip);

            GameStatus checkStatus() const;
            GameStatus checkStatusOnMove(const Move move, const Chip chip) const;

            bool isValid(const Move move) const;
            std::vector<const Move> getMoves() const;
            const BoardArray& getArray() const;
            GameStatus getStatus() const;

        private:
            bool checkEndConditionOnMove(const unsigned int row, const unsigned int column) const;

            unsigned int _lastMoveX;
            unsigned int _lastMoveY;

            BoardArray _array;
            GameStatus _status;
    };

}

#endif