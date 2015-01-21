#ifndef ABTRACK_
#define ABTRACK_

#include <alex/AProperties.h>
#include <alex/AHit.h>
#include <alex/AID.h>

namespace alex {

  class AHit;
  class ABTrack : public AProperties, public AID {
    
  public:
    
    // Constructors
    ABTrack();
    ABTrack(int id);

    ABTrack(const ABTrack& abt);

    // Destructor
    ~ABTrack();

    // Hits
    void AddHit(const AHit* ahit);

    const std::vector<AHit*> GetHits() const
    {return fHits;}

    //std::vector<AHit*> GetHits() 
    //{return fHits;}

    const AHit* GetHit(int id) const;
 
    // Extremes
    void SetExtreme1(const AHit* ahit);

    const AHit* GetExtreme1() const {
      return fExtremes.first;
    };

    void SetExtreme2(const AHit* ahit) ;
    
    const AHit* GetExtreme2() const {
      return fExtremes.second;
    };

    void SetExtremes(const std::pair<AHit*, AHit*> extremes);
    
    const std::pair<AHit*, AHit*> GetExtremes() const {
      return fExtremes;
    };

    // Energy Deposited
    double GetEdep() const {
      return fEdep;
    };

    // Information
    void DisplayInfo(std::ostream& s) const;
    
    
  private:
    std::vector<AHit*> fHits;
    std::pair<AHit*, AHit*> fExtremes;
    
  protected:
    double fEdep;
    
  };

std::ostream& operator << (std::ostream& s, const alex::ABTrack& abt);
}

#endif
