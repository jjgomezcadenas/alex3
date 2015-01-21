#ifndef APROP_
#define APROP_

#include <alex/TDefs.h>

namespace alex {

  class AProperties {
    
  public:

    // Constructors
    AProperties(){};

    // Destructor
    ~AProperties(){};

    // Properties
    std::map <std::string, std::string> GetProperties() const
    {return fProperties;}
    
    std::string GetProperty(std::string name) 
    {return fProperties[name];}
    
    void SetProperty(std::string name, std::string value)
    {fProperties[name]=value;}

    // Information
    void DisplayInfo(std::ostream& s) const;

    std::string DisplayProperties() const;

  private:
    std::map <std::string, std::string> fProperties; // Properties if needed 
    
  };
}
std::ostream& operator << (std::ostream& s, const alex::AProperties& ap);

#endif
