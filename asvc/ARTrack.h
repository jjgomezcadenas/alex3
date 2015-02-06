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

    // Information
    void DisplayInfo(std::ostream& s) const;
    std::string PrintInfo() const; 
    
  
  private:
    std::vector <int> fTTrackIDs;
    std::vector<AHit*> fOrdHits;
    
  };

std::ostream& operator << (std::ostream& s, const alex::ARTrack& art);
}

#endif
