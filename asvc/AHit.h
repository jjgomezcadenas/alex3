#ifndef AHIT_
#define AHIT_

#include <alex/AProperties.h>
#include <alex/AID.h>

namespace alex {

  class AHit : public AProperties, public AID{
    
  public:
    
    // Constructors
    AHit(){};
    AHit(int Id, double x, double y, double z, double E); 
    AHit(int Id, TVector3 hit, double E); 
              

    AHit(const AHit& ahit);

    // Destructor
    ~AHit() {};
    
    //vertex
    void SetHit(TVector3 hit)
    {fHit = hit;}

    TVector3 GetHit() const
    {return fHit;}

    //P4
    void SetEdep(double E)
    {fE = E;}
    
    double GetEdep() const
    {return fE;}

    // Information
    void DisplayInfo(std::ostream& s) const;
    
    
  private:
    double fE; // Edep
    TVector3 fHit; // Particle four momentum
    
    
  };

std::ostream& operator << (std::ostream& s, const alex::AHit& ah);
}

#endif
