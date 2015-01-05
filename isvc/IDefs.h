#ifndef IDEFS_
#define IDEFS_
/*
 Irene dependent includes and defs
*/

#include <alex/GDefs.h>
#include <alex/TDefs.h>

#include <irene/Event.h>
#include <irene/Track.h>
#include <irene/Particle.h>


namespace alex {
typedef const irene::Particle* IParticle;
typedef std::vector<const irene::Particle*> IParticles;
}
#endif