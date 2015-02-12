
#ifndef PRoadFilter_
#define PRoadFilter_

namespace alex {
  class PRoadFilter {

  public:
    // You can add here public functions and variables to be used by derived algos
    
  protected:
    // Counters
	  int fNumInputEvents;    
	  int fNumOutputEvents;

    std::vector<double> fVoxelSize;
    
  };
}
#endif 
