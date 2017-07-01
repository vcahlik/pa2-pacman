#include "Cherry.h"
#include "Config.h"
#include "Model/Game.h"

Cherry::Cherry(Game *game)
        : ScoreBonus(Position(), Config::CHERRY_SIZE, Config::CHERRY_SCORE_BONUS, game),
          timer(game) {
    // Place on random position
    position = getCenteredPosition(game->getMap().getRandomCompatibleCoord(*this));

    timer.requestTimer(TimeoutEvent::CherryLifetime);
}

void Cherry::performActions() {
    ScoreBonus::performActions();

    timer.notifyOfNextCycle();

    if (timer.isTimeoutEvent(TimeoutEvent::CherryLifetime)) {
        state = State::Removed;
    }
}
