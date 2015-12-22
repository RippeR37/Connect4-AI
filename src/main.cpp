#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Controller/LogicHandler.h"

void testAI(Controller::LogicHandler& logic) {
    int win[2] = { 0, 0 };
    int gamesNumber = 50;

    for(int i = 0; i < gamesNumber; ++i) {    
        logic.init();
        logic.run();

        if(logic.getBoardStatus() == Model::GameStatus::Won) {
            win[logic.getCurrentPlayer()]++;
        }

        logic.reset();
    }

    system("cls");
    std::cout << "Wygrane #0: " << win[0] << std::endl;
    std::cout << "Wygrane #1: " << win[1] << std::endl;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    Controller::LogicHandler gameLogic;

    bool doTestAI = false;

    if(doTestAI) {
        testAI(gameLogic);
    } else {
        gameLogic.init();
        gameLogic.run();
    }

    system("pause");

    return 0;
}