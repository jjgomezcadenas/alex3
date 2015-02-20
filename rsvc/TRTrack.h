#ifndef ARTRACK_
#define ARTRACK_

#include <alex/ABTrack.h>

namespace alex {

  class ARTrack : public ABTrack {
    
  public:
    
    // Constructors
    ARTrack();
    ARTrack(int id);

    ARTrack(const ARTrack& art);

    // Destructor
    ~ARTrack() ;

    // True Tracks
    const std::vector <int> GetTTrackIDs() const
    {return fTTrackIDs;}

    void AddTTrackID(int id);

    // E Deposited
    void SetEdep(double eDep);

    // Hits
    void AddOrdHit(AHit* ahit);

    const std::vector<AHit*> GetOrdHits() const
    {return fOrdHits;}

    // Spatial Resolution
    void SetSpatialRes(TVector3 res);
    const TVector3 GetSpatialRes() const {return fSpatialRes;}

    // Energy Resolution
    void SetEnergyRes(double res);
    const double GetEnergyRes() const {return fEnergyRes;}

    // Information
    void DisplayInfo(std::ostream& s) const;
    std::string PrintInfo() const; 
    
  
  private:
    // Vector of TTrack IDs that generated the RTrack
    std::vector <int> fTTrackIDs;

    // Vector of ordered hits in the main path
    std::vector<AHit*> fOrdHits;

    // Spatial Resolution
    TVector3 fSpatialRes;

    // Energy Resolution
    double fEnergyRes;  

    ClassDef(ARTrack,1);  
  };

std::ostream& operator << (std::ostream& s, const alex::ARTrack& art);
}

#endif
