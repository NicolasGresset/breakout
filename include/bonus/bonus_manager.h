#ifndef BONUS_MANAGER_H
#define BONUS_MANAGER_H

#include "bonus/bonus.h"
#include "object/object.h"
#include "utils/constants.h"
#include <random>
#include <vector>

class Brick;

/** A bonus can be created each time a time is destroyed and a certain amount of
 * time has passed*/
class BonusManager {
private:
  std::vector<std::shared_ptr<Bonus>> bonuses_;
  Uint64 current_time_ = 0;
  Uint64 interval_; // minium interval in milliseconds between 2 bonuses
  bool new_bonus_ = false;
  std::mt19937 random_generator_;

  // a pointer to a vector containing textures for all bonuses
  std::shared_ptr<std::vector<texture_ptr>> textures_;

public:
  // to be called at each game iteration
  void loop(Uint64 delta);

  // to be called whenever a ball destroys a brick
  void createNewBonus(Brick &brick);
  BonusManager();
  BonusManager(std::shared_ptr<std::vector<texture_ptr>> textures,
               Uint64 interval);

  inline std::vector<std::shared_ptr<Bonus>>& getBonuses() { return bonuses_; }
};

#endif