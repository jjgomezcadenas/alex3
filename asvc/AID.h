#ifndef AID_
#define AID_

#include <alex/GDefs.h>

// an object with an ID

namespace alex {

  class AID {
    
  public:

    // Constructors
    AID(){};
    
    // Destructor
    ~AID(){};

    // ID
    int GetID() const
    {return fId;}

    void SetID(int id)
    {fId = id;}

    // Information
    void DisplayInfo(std::ostream& s) const;
    
  private:
    int fId; // Unique identification number 
  };
}
std::ostream& operator << (std::ostream& s, const alex::AID& aid);

#endif
