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
        if (pop.AccessParticle(i).ViewPosition(j)+pop.AccessParticle(i).ViewVelocity(j) >= pop.Configuration().ParDomain.ViewParMax(j)){ //mi assicuro che particella non possa uscire dal dominio
          pop.AccessParticle(i).SetPosition(j, pop.Configuration().ParDomain.ViewParMax(j));
        }
        else if (pop.AccessParticle(i).ViewPosition(j)+pop.AccessParticle(i).ViewVelocity(j) <= pop.Configuration().ParDomain.ViewParMin(j)){
          pop.AccessParticle(i).SetPosition(j, pop.Configuration().ParDomain.ViewParMin(j));
        }
        else
        pop.AccessParticle(i).SetPosition(j,pop.AccessParticle(i).ViewPosition(j)+pop.AccessParticle(i).ViewVelocity(j)); //aggiungo alla posizione attuale la velocità
      };
    };
  };
};

#endif
