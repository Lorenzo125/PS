#ifndef UpVel_h
#define UpVel_h

#include <iostream>
#include <vector>
#include <random>

#include "Population.h"

class UpVel {
public:

  static void Update_Vel(Population& pop) {

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<double> uni(0,1);

    double phi =  pop.Configuration().social_par + pop.Configuration().cognitive_par;
    double dumping = 2.0/TMath::Abs(2.0-phi-TMath::Power(TMath::Power(phi,2) - 4.0*phi,0.5)); //definizione di dumping factor per ridurre le oscillazioni

    for (size_t i=0; i<pop.Size(); ++i){
      for (size_t j=0; j<pop.AccessParticle(i).Size(); ++j){
        double cognitive = pop.Configuration().cognitive_par * uni(rng) * (pop.AccessParticle(i).ViewBestPosition(j) - pop.AccessParticle(i).ViewPosition(j));
        double social = pop.Configuration().social_par * uni(rng) * (pop.AccessParticle(0).ViewBestPosition(j) - pop.AccessParticle(i).ViewPosition(j));
        double vel = dumping*(pop.AccessParticle(i).ViewVelocity(j) + cognitive + social);
        if (vel < pop.Configuration().Vmax){
          pop.AccessParticle(i).SetVelocity(j, vel);
        }
        else {
          pop.AccessParticle(i).SetVelocity(j, pop.Configuration().Vmax);
        };
      };
    };
  };
};
#endif
