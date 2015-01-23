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
    AHit(int Id, TVector3 pos, double E);
    
    AHit(const AHit& ahit);

    // Destructor
    ~AHit() {};
    
    // Position
    void SetPosition(TVector3 pos)
    {fPos = pos;}

    TVector3 GetPosition() const
    {return fPos;}

    // Energy Deposited
    void SetEdep(double E)
    {fE = E;}
    
    double GetEdep() const
    {return fE;}

    // Information
    void DisplayInfo(std::ostream& s) const;
    std::string PrintInfo() const; 
    
    
  private:
    double fE; // Hit Edep
    TVector3 fPos; // Hit position
    
    
  };

std::ostream& operator << (std::ostream& s, const alex::AHit& ah);
}

#endif
