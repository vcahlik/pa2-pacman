#include "Ghost.h"
#include "Config.h"
#include "Model/Game.h"
#include "Utils.h"

Ghost::Ghost(const double speed, const NavigatorType defaultNavigatorType, const Color color, Game *game)
        : Enemy(game->getMap().getSpawnPointCoordinates(), speed, Config::GHOST_SIZE, defaultNavigatorType, game),
          baseSpeed(speed),
          defaultNavigatorType(defaultNavigatorType),
          baseColor(color),
          timer(game),
          frightenedBlinkOn(false) {
    reset();
}

void Ghost::performActions() {
    if (getState() == State::InGhostHouse) {
        return;
    }

    timer.notifyOfNextCycle();
    MovableObject::performActions();

    switch (getState()) {
        case State::Chase:
            performStateChaseActions();
            break;
        case State::Frightened:
            performStateFrightenedActions();
            break;
        case State::FrightenedEnd:
            performStateFrightenedEndActions();
            break;
        default:
            throw std::logic_error("unhandled state");
    }
}

const Ghost::State Ghost::getState() const {
    return state;
}

void Ghost::reset() {
    setState(State::InGhostHouse);
}

void Ghost::releaseFromGhostHouse() {
    if (state != State::InGhostHouse) {
        throw std::runtime_error("ghost not in ghost house");
    }

    setState(State::Chase);
}

void Ghost::frighten() {
    if (getState() != State::InGhostHouse) {
        setState(State::Frightened);
    }
}

const Color Ghost::getColor() const {
    if ((getState() == State::Frightened) ||
        (getState() == State::FrightenedEnd && !frightenedBlinkOn)) {
        return Config::GHOST_FRIGHTENED_COLOR;
    }

    return baseColor;
}

void Ghost::performStateChaseActions() {
    if (isCollision(game->getPlayer())) {
        game->getPlayer().die();
    }
}

void Ghost::performStateFrightenedActions() {
    if (isCollision(game->getPlayer())) {
        die();
    }

    timer.requestTimer(TimeoutEvent::GhostStateFrightened);
    if (timer.isTimeoutEvent(TimeoutEvent::GhostStateFrightened)) {
        setState(State::FrightenedEnd);
        return;
    }
}

void Ghost::performStateFrightenedEndActions() {
    if (isCollision(game->getPlayer())) {
        die();
    }

    timer.requestTimer(TimeoutEvent::GhostStateFrightenedEnd);
    if (timer.isTimeoutEvent(TimeoutEvent::GhostStateFrightenedEnd)) {
        setState(State::Chase);
        return;
    }

    timer.requestTimer(TimeoutEvent::GhostStateFrightenedBlink);
    if (timer.isTimeoutEvent(TimeoutEvent::GhostStateFrightenedBlink)) {
        frightenedBlinkOn = !frightenedBlinkOn;
    }
}

void Ghost::setState(const State newState) {
    timer.stopTimer(TimeoutEvent::GhostStateFrightened);
    timer.stopTimer(TimeoutEvent::GhostStateFrightenedEnd);
    timer.stopTimer(TimeoutEvent::GhostStateFrightenedBlink);

    switch (newState) {
        case State::Chase:
            switchToChaseState();
            break;
        case State::Frightened:
            switchToFrightenedState();
            break;
        case State::FrightenedEnd:
            break;
        case State::InGhostHouse:
            switchToInGhostHouseState();
            break;
        default:
            throw std::logic_error("state not handled");
    }

    this->state = newState;
}

void Ghost::die() {
    setState(State::InGhostHouse);
}

void Ghost::switchToChaseState() {
    setNavigator(defaultNavigatorType);
    speed = baseSpeed;
}

void Ghost::switchToFrightenedState() {
    setNavigator(NavigatorType::Random);
    direction = getRandomDifferentValidDirection(direction);
    speed = baseSpeed * Config::GHOST_FRIGHTENED_SPEED_RATIO;
}

void Ghost::switchToInGhostHouseState() {
    position = game->getMap().getSpawnPointCoordinates();
    direction = getRandomValidDirection();
}
