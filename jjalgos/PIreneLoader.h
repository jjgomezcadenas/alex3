
#ifndef PIreneLoader_
#define PIreneLoader_

namespace irene
{
	class Track;
}


namespace alex {
	class ABTrack;

  class PIreneLoader {

  public:
    // You can add here public functions and variables to be used by derived algos
    void FillHits(const irene::Track* iTrack, ABTrack* track);
  protected:
    // You can add here functions and variables to be used by derived algos
    int fTracks, fParticles;
  };
}
#endif 
