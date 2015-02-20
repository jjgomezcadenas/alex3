
#ifndef PALGOWriteDST_
#define PALGOWriteDST_

#include <TFile.h>
#include <TTree.h>
#include <alex/TEvent.h>

namespace alex {
  class PWriteAlexDST {
  public:
    
  protected:
    TFile* fFile; ///< ROOT file where the output is written
    TTree* fAevtTree; ///< ROOT tree where the events are stored
    TEvent* fAevent; ///< event to be stored
    
  };
}
#endif 
