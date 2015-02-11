
#ifndef PEnergySmearer_
#define PEnergySmearer_

#include "TRandom3.h"


namespace alex {

  class PEnergySmearer {

  public:
    // You can add here public functions and variables to be used by derived algos

  protected:
    const double fQbb = 2.45783;
    const double fFWHM2Sigma = 2.3548;

    TRandom3* fRand;
  };
}

#endif 
