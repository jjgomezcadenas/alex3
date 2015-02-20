#ifndef THIT_
#define THIT_

#include <alex/AHit.h>
#include <TObject.h>

namespace alex {

  class THit : public AHit,public TObject {
    
  public:
    
    // Constructors
    THit(){};
    //THit(int Id, double x, double y, double z, double E); 
    //THit(int Id, TVector3 pos, double E);
    
    THit(const AHit& ahit);
    //THit(const THit& ahit);

    // Destructor
    virtual ~THit() {};

    
    ClassDef(THit,1);
  };

}

#endif
