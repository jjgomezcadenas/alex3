#ifndef ATTRACK_
#define ATTRACK_

#include <alex/AProperties.h>
#include <alex/AID.h>

namespace alex {

  class AHit;
  class ATTrack : public AProperties, public AID {
    
  public:
    
    // Constructors
    ATTrack(){};
    ATTrack(int Id, int particleId);

    ATTrack(const ATTrack& att);

    // Destructor
    ~ATTrack() {};

    // Particle ID
    int GetParticleID() const
    {return fParticleID;}

    void SetParticleID(int pID)
    {fParticleID = pID;}

    // Hits
    void AddHit(const AHit* ahit);

    const std::vector<AHit*> GetHits() const
    {return fHits;}

    //std::vector<AHit*> GetHits() 
    //{return fHits;}


    // Information
    void DisplayInfo(std::ostream& s) const;
    
    
  private:
    int fParticleID;
    std::vector<AHit*> fHits;
    
  };

std::ostream& operator << (std::ostream& s, const alex::ATTrack& p);
}

#endif
