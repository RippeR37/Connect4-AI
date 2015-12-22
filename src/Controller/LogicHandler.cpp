#include "LogicHandler.h"
#include "PlayerHuman.h"

#include "PlayerAIRandom.h"
#include "PlayerAIMinMax.h"
#include "PlayerAIAlfaBeta.h"
#include "PlayerAIAlfaBetaHeuristic.h"

#include <iostream>

namespace Controller {

    LogicHandler::LogicHandler() {
        init();
    }

    LogicHandler::~LogicHandler() {
        reset();
    }

    bool LogicHandler::init() {
        _players[0].reset(new Controller::PlayerHuman(Model::Chip::Red));

        // Jeœli gracz #1 ma byæ sterowany przez AI, to ustaw go tutaj
        //_players[0].reset(new Controller::PlayerAIMinMax(Model::Chip::Red));
        
        /**
         * Wybierz typ AI tutaj (random, MinMax, Alfa-Beta, Alfa-Beta z funkcj¹ heurystyczn¹)
         */
        switch( 3 ) {
            case 0: _players[1].reset(new Controller::PlayerAIRandom(Model::Chip::Yellow)); break;
            case 1: _players[1].reset(new Controller::PlayerAIMinMax(Model::Chip::Yellow, 7)); break;
            case 2: _players[1].reset(new Controller::PlayerAIAlfaBeta(Model::Chip::Yellow, 9)); break;
            case 3: _players[1].reset(new Controller::PlayerAIAlfaBetaHeuristic(Model::Chip::Yellow, 9)); break;
        }

        // Jeœli zaczynaæ ma gracz #2, to odkomentuj t¹ liniê
        // std::swap(_players[0], _players[1]);

        return true;
    }

    void LogicHandler::reset() {
        _board.reset();
    }

    bool LogicHandler::run() {
        Model::Move move;
        _currentPlayer = 1;

        while(_board.getStatus() == Model::GameStatus::InProgress) {
            _board.show();

            _currentPlayer = 1 - _currentPlayer;

            do {
                move = _players[_currentPlayer]->getMove(_board);
            } while(_board.isValid(move) == false);

            _board.makeMove(move, _players[_currentPlayer]->getChip());
        }

        displayResults();

        return true;
    }

    int LogicHandler::getCurrentPlayer() const {
        return _currentPlayer;
    }

    Model::GameStatus LogicHandler::getBoardStatus() const {
        return _board.getStatus();
    }

    void LogicHandler::displayResults() const {
        _board.show();

        if(_board.getStatus() == Model::GameStatus::Tie) {
            std::cout << "Remis!" << std::endl;
        } else {
            std::cout << "Gracz #" << _currentPlayer + 1 << " wygral!" << std::endl;
        }
    }

}