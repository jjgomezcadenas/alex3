
#ifndef PNext100FiducialFilter_
#define PNext100FiducialFilter_

namespace alex {
  class PNext100FiducialFilter {

  public:
    // You can add here public functions and variables to be used by derived algos

  protected:
	int fNumInputEvents;    
	int fNumOutputEvents;

	// Detector sizes
    double fDetectorRadius = 534.5;
    double fDetectorLength  = 1300.;
    double fDetectorZCenter = 14.0;

    double fZPosLimit, fZNegLimit, fRadLimit;
  };
}
#endif 
