
#ifndef PRoadStudy_
#define PRoadStudy_

#include <alex/ARTrack.h>


namespace alex {
  class PRoadStudy {

  public:
    // You can add here public functions and variables to be used by derived algos
    
  protected:
    // Computes Minimum Distance between 2 ARTracks
    double GetMinDistance(ARTrack* trk1, ARTrack* trk2);

  };

}
#endif 
