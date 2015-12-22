#include "Player.h"

namespace Controller {

    Player::Player() {

    }

    Player::Player(const Model::Chip chip) {
        setChip(chip);
    }

    Player::~Player() {

    }

    Model::Chip Player::getChip() const {
        return _chip;
    }

    void Player::setChip(const Model::Chip chip) {
        _chip = chip;
    }

}