#ifndef ARTRACK_
#define ARTRACK_

#include <alex/ABTrack.h>
#include <alex/ATTrack.h>

namespace alex {

  class ATTrack;
  class ARTrack : public ABTrack {
    
  public:
    
    // Constructors
    ARTrack();
    ARTrack(int id);

    ARTrack(const ARTrack& art);

    // Destructor
    ~ARTrack() {};

    // True Tracks
    const std::vector <int> GetTTrackIDs() const
    {return fTTrackIDs;}

    void AddTTrack(const ATTrack* att);

    // E Deposited
    void SetEdep(double eDep);

    // Information
    void DisplayInfo(std::ostream& s) const;
    
  
  private:
    std::vector <int> fTTrackIDs;
    
  };

std::ostream& operator << (std::ostream& s, const alex::ARTrack& art);
}

#endif
