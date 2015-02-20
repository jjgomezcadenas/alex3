#ifndef ABTRACK_
#define ABTRACK_

#include <alex/GDefs.h>
#include <alex/AProperties.h>
#include <alex/AID.h>
#include <alex/ADebug.h>

namespace alex {

  class AHit;
  
  class ABTrack : public AProperties, public AID, public ADebug {
    
  public:
    
    // Constructors
    ABTrack();
    ABTrack(int id);

    ABTrack(const ABTrack& abt);

    // Destructor
    virtual ~ABTrack();

    // Hits
    void AddHit(AHit* ahit);

    const std::vector<AHit*> GetHits() const
    {return fHits;}

    //std::vector<AHit*> GetHits() 
    //{return fHits;}

     AHit* GetHit(int id) const;
 
    // Extremes
    void SetExtreme1(AHit* ahit);

    AHit* GetExtreme1() const {
      return fExtremes.first;
    };

    void SetExtreme2(AHit* ahit) ;
    
    AHit* GetExtreme2() const {
      return fExtremes.second;
    };

    const std::pair<AHit*, AHit*> GetExtremes() const {
      return fExtremes;
    };

    // Energy Deposited
    double GetEdep() const {
      return fEdep;
    };

    // Information
    void DisplayInfo(std::ostream& s) const;
    std::string PrintInfo() const; 
    
    
  protected:
    std::vector<AHit*> fHits;
    std::pair<AHit*, AHit*> fExtremes;
    
    double fEdep;
    bool fSetExtreme1;
    bool fSetExtreme2;


  };

std::ostream& operator << (std::ostream& s, const alex::ABTrack& abt);
}

#endif
