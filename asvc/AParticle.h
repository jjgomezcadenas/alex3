#ifndef APART_
#define APART_

#include <alex/AProperties.h>
#include <alex/AID.h>
#include <TVector3.h>
#include <TLorentzVector.h>
namespace alex {

  class AParticle : public AProperties, public AID {
    
  public:
    
    // Constructors
    AParticle(){};
    AParticle(int Id, std::string name, bool isPrimary, double charge, 
              TVector3 vertex, 
              TLorentzVector p4);

    AParticle(const AParticle& apart);

    // Destructor
    ~AParticle() {};

    // Name
    std::string GetName() const
    {return fName;}

    void SetName(std::string name)
    {fName = name;}

    //charge
    double GetCharge() const
    {return fCharge;}

    void SetCharge(double charge)
    {fCharge = charge;}

    // Primary
    bool GetIsPrimary() const
    {return fPrimary;}

    void SetIsPrimary(bool primary) 
    {fPrimary=primary;}
    
    //vertex
    void SetVertex(TVector3 vertex)
    {fVertex = vertex;}

    TVector3 GetVertex() const
    {return fVertex;}

    //P4
    void SetP4(TLorentzVector p4)
    {fP4 = p4;}
    
    TLorentzVector GetP4() const
    {return fP4;}

    // Mass
    double GetMass()
    {return fP4.M();}

    //p3
    TVector3 GetMomentum() const
    {return fP4.Vect();}

    // Information
    void DisplayInfo(std::ostream& s) const;
    
    
  private:
    std::string fName; // Particle name
    double charge; // Particle charge
    TLorentzVector fP4; // Particle four momentum
    TVector3 fVertex; // vertex
    bool fPrimary; // Primary
    
    
  };

std::ostream& operator << (std::ostream& s, const alex::AParticle& p);
}

#endif
