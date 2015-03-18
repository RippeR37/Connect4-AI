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

            const bool show() const;
            const bool makeMove(const Move move, const Chip chip);
            const GameStatus checkStatus(const Chip playersChip) const;

            const bool isValid(const Move move) const;
            const std::vector<const Move> getMoves() const;
            const BoardArray& getArray() const;

        private:
            BoardArray _array;
    };

}

#endif