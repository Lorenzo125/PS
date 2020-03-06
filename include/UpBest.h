#ifndef UpBest_h
#define UpBest_h

#include <vector>
#include <random>
#include "Population.h"

class UpBest {
public:
  static void Update(Population& pop) {
    for (size_t i=0; i < pop.Size(); i++){
      if(pop.AccessParticle(i).ViewCost()<pop.AccessParticle(i).ViewBestCost())
      pop.AccessParticle(i).SetBestPosition();
    }
  };

  static void First_Update(Population& pop) {
    for (size_t i=0; i < pop.Size(); i++){
      pop.AccessParticle(i).SetBestPosition();
    }
  };

};

#endif
