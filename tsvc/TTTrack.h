#ifndef TTTRACK_
#define TTTRACK_

#include <alex/ATTrack.h>
#include <TObject.h>


namespace alex {

  class TTTrack : public ATTrack, public TObject {
    
  public:
    
    // Constructors
    TTTrack() {};
    //ATTrack(int id, int particleId);

    TTTrack(const ATTrack& att);

    // Destructor
    virtual ~TTTrack() {} ; // hits destroyed in the base class


    ClassDef(TTTrack,1);
    
  };

}

#endif
