#ifndef RANDOMISER_H
#define RANDOMISER_H

#include <random>

// Allows creation of random integrers between min and max included
template <typename T> class Randomiser {
private:
  std::mt19937 random_generator_;
  std::conditional_t<std::is_integral<T>::value,
                     std::uniform_int_distribution<T>,
                     std::uniform_real_distribution<T>>
      distribution_;

public:
  Randomiser() {} ;
  Randomiser(T min, T max) : distribution_(min, max) {
    random_generator_.seed(std::random_device()());
  }

  inline T generate() { return distribution_(random_generator_); }
};

#endif