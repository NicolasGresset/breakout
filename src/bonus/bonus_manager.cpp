#include "bonus/bonus_manager.h"
#include "bonus/bonus.h"
#include "bonus/extra_life.h"
#include "object/brick.h"
#include "object/object.h"
#include "utils/constants.h"
#include "utils/vector2D.h"
#include <SDL_stdinc.h>
#include <algorithm>
#include <memory>
#include <vector>

BonusManager::BonusManager(std::shared_ptr<std::vector<texture_ptr>> textures,
                           Uint64 interval)
    : interval_(interval), textures_(textures) {}

void BonusManager::loop(Uint64 delta) {
  current_time_ += delta;
  if (current_time_ >= interval_) {
    new_bonus_ = true;
    current_time_ -= interval_;
  }

}

void BonusManager::createNewBonus(Brick &brick) {
  if (new_bonus_) {
    std::uniform_int_distribution<int> dist_(1, Bonus::implemented_bonus_types);
    int type(dist_(random_generator_));
    switch (type) {
    case 1:
      bonuses_.push_back(std::make_shared<ExtraLife>(textures_->at(0), brick,
                                                     BONUS_WIDTH, BONUS_HEIGHT,
                                                     Vector2D(0, BONUS_SPEED)));
      break;
    default:
      break;
    }
    new_bonus_ = false;
  }
}