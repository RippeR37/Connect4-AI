#ifndef CONTROLLER_LOGICHANDLER_H_INCLUDED
#define CONTROLLER_LOGICHANDLER_H_INCLUDED

#include "Player.h"
#include "../Model/Board.h"

#include <memory>

namespace Controller {
    
    class LogicHandler {
        public:
            LogicHandler();
            ~LogicHandler();

            LogicHandler(const LogicHandler&) = delete;
            LogicHandler& operator=(const LogicHandler&) = delete;

            bool init();
            void reset();

            bool run();

            int getCurrentPlayer() const;
            Model::GameStatus getBoardStatus() const;


        private:
            void displayResults() const;

            int _currentPlayer;
            Model::Board _board;
            std::unique_ptr<Controller::Player> _players[2];
    };

}


#endif