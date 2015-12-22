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

TEST(testBoard, testStatusOnInitialization) {
    Model::Board board;

    ASSERT_EQ(Model::GameStatus::InProgress, board.getStatus());
}

TEST(testBoard, testValidMovesWhenPossible) {
    Model::Board board;

    for(unsigned int row = 0; row < board.getArray().size(); ++row) {
        for(unsigned int slot = 0; slot < board.getArray()[row].size(); ++slot) {
            bool isPossible = board.isValid(static_cast<Model::Move>(slot));
            bool moveMade = board.makeMove(static_cast<Model::Move>(slot), Model::Chip::Red);
            ASSERT_TRUE(isPossible);
            ASSERT_TRUE(moveMade);
        }
    }

    for(unsigned int slot = 0; slot < board.getArray()[0].size(); ++slot) {
        bool isPossible = board.isValid(static_cast<Model::Move>(slot));
        bool moveMade = board.makeMove(static_cast<Model::Move>(slot), Model::Chip::Red);
        ASSERT_FALSE(isPossible);
        ASSERT_FALSE(moveMade);
    }
}