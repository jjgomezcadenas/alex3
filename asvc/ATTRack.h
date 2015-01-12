#ifndef ATTRACK_
#define ATTRACK_

#include <alex/AProperties.h>
#include <alex/AID.h>

namespace alex {

  class AHit;
  class ATTRack : public AProperties, public AID {
    
  public:
    
    // Constructors
    ATTRack(){};
    ATTRack(int Id, int particleId);

    ATTRack(const ATTRack& at);

    // Destructor
    ~ATTRack() {};

    // Name
    int GetParticleID() const
    {return fParticleID;}

    void SetParticleID(int pID)
    {fParticleID = pID;}

    void AddHit(const AHit* ahit);

    const std::vector<AHit*> GetHits() const
    {return fHits;}

    std::vector<AHit*> GetHits() 
    {return fHits;}


    // Information
    void DisplayInfo(std::ostream& s) const;
    
    
  private:
    int fParticleID;
    std::vector<AHit*> fHits;
    
  };

std::ostream& operator << (std::ostream& s, const alex::ATTRack& p);
}

#endif
