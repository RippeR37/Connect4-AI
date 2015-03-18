#ifndef MODEL_GAMESTATUS_H_INCLUDED
#define MODEL_GAMESTATUS_H_INCLUDED

namespace Model {
    
    enum class GameStatus : unsigned int {
        InProgress,
        Tie,
        Won,
        Lose
    };

}

#endif