#ifndef TRTRACK_
#define TRTRACK_

#include <alex/ARTrack.h>
#include <TObject.h>

namespace alex {

  class TRTrack : public ARTrack, public TObject {
    
  public:
    
    // Constructors
    TRTrack() {};
    //ARTrack(int id);

    TRTrack(const ARTrack& art);

    // Destructor
    virtual ~TRTrack() {} ;

    ClassDef(TRTrack,1);  
  };

}

#endif
