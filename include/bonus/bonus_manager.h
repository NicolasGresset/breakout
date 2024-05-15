#ifndef BONUS_MANAGER_H
#define BONUS_MANAGER_H

#include "bonus/bonus.h"
#include "object/object.h"
#include "utils/constants.h"
#include "utils/randomiser.h"
#include <vector>

class Brick;

/**
 * @brief A convenient class which handle Bonuses creation. We consider that a
 * bonus can be created at a brick destruction at its emplacement only if a
 * certain amount of time has passed since last bonus was created
 * the kind of bonus is uniformly randomly chosen between the kinds implemented
 *
 */
class BonusManager {
private:
  std::vector<std::shared_ptr<Bonus>> bonuses_;
  Uint64 current_time_ = 0;
  Uint64 interval_; // minium interval in milliseconds between 2 bonuses
  bool new_bonus_ = false;

  // a pointer to a vector containing textures for all bonuses
  std::shared_ptr<std::vector<texture_ptr>> textures_;

  Randomiser<int> randomiser_;

public:
  // to be called at each game iteration
  void loop(Uint64 delta);

  // to be called whenever a ball destroys a brick
  void createNewBonus(Brick &brick);
  BonusManager();
  BonusManager(std::shared_ptr<std::vector<texture_ptr>> textures,
               Uint64 interval);

  inline std::vector<std::shared_ptr<Bonus>> &getBonuses() { return bonuses_; }
};

#endif