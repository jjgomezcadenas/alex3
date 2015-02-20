#ifndef ADEBUG_
#define ADEBUG_

#include <alex/GDefs.h>
#include <alex/LogUtil.h>

// an object with Debug properties

namespace alex {

  class ADebug    {
    
  public:

    // Constructors
    ADebug(){};
    
    // Destructor
    ~ADebug(){};


    // Debug level
    std::string GetLevelDebug() const
    {return fDebug;}

    void SetLevelDebug(std::string debug);
  
    
  private:
    std::string fDebug; 

  };
 
}
#endif
