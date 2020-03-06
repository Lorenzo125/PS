#ifndef Move_h
#define Move_h

#include <vector>
#include <random>

#include "Population.h"

class Move {
public:
  static void Change(Population& pop) {
    for (size_t i=0; i<pop.Size();++i){
      for(size_t j=0; j<pop.AccessParticle(i).Size(); ++j){
        if (pop.AccessParticle(i).ViewPosition(j)+pop.AccessParticle(i).ViewVelocity(j) >= pop.Configuration().ParDomain.ViewParMax(j))
        pop.AccessParticle(i).SetPosition(j, pop.Configuration().ParDomain.ViewParMax(j));
        if (pop.AccessParticle(i).ViewPosition(j)+pop.AccessParticle(i).ViewVelocity(j) <= pop.Configuration().ParDomain.ViewParMin(j))
        pop.AccessParticle(i).SetPosition(j, pop.Configuration().ParDomain.ViewParMin(j));
        if (pop.AccessParticle(i).ViewPosition(j)+pop.AccessParticle(i).ViewVelocity(j) > pop.Configuration().ParDomain.ViewParMin(j) && pop.AccessParticle(i).ViewPosition(j)+pop.AccessParticle(i).ViewVelocity(j) < pop.Configuration().ParDomain.ViewParMax(j))
        pop.AccessParticle(i).SetPosition(j,pop.AccessParticle(i).ViewPosition(j)+pop.AccessParticle(i).ViewVelocity(j));
      };
    }
  };
};

#endif
