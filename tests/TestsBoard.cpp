#include "../src/Model/Board.h"

#include <gtest/gtest.h>


TEST(testBoard, testBoardSize) {
    Model::Board board;

    // Test height of board
    ASSERT_EQ(6, board.getArray().size());

    // Test width of each row
    for(int y = 0; y < 6; ++y) {
        ASSERT_EQ(7, board.getArray()[y].size());
    }
}

TEST(testBoard, testEmptyOnInitialization) {
    Model::Board board;

    // Test if each of board's slot is empty
    for(unsigned int y = 0; y < board.getArray().size(); ++y) {
        for(unsigned int x = 0; x < board.getArray()[y].size(); ++x) {
            ASSERT_EQ(Model::Chip::Empty, board.getArray()[y][x]);
        }
    }
}

TEST(testBoard, testEmptyAfterReset) {
    Model::Board board;

    // Make some moves
    board.makeMove(Model::Move::Slot3, Model::Chip::Yellow);
    board.makeMove(Model::Move::Slot2, Model::Chip::Red);

    // Reset board
    board.reset();

    // Check if whole board is empty
    for(unsigned int y = 0; y < board.getArray().size(); ++y) {
        for(unsigned int x = 0; x < board.getArray()[y].size(); ++x) {
            ASSERT_EQ(Model::Chip::Empty, board.getArray()[y][x]);
        }
    }
}

TEST(testBoard, testInProgressOnInitialization) {
    Model::Board board;

    ASSERT_EQ(Model::GameStatus::InProgress, board.checkStatus(Model::Chip::Yellow));
    ASSERT_EQ(Model::GameStatus::InProgress, board.checkStatus(Model::Chip::Red));
}