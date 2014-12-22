#ifndef IDEFS_
#define IDEFS_
/*
 typedefs for Irene
*/

#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <map>


#include <TMath.h>
#include <TVector3.h>
#include <TLorentzVector.h>

#include <irene/Event.h>
#include <irene/Track.h>
#include <irene/Particle.h>


namespace alex {
typedef std::pair<TLorentzVector,double> IHit;
typedef std::vector<std::pair<TLorentzVector,double> > IHits;
typedef const irene::Particle* IParticle;
typedef std::vector<const irene::Particle*> IParticles;

}
#endif