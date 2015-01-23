
// ----------------------------------------------------------------------------
//  $Id: AParticle.cpp  2015-01-05 1
//
//  Author:  <gomez@mail.cern.ch>
//  Created: 5 Jan 2015
//  
//  Copyright (c) 2015 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include "AParticle.h"

#include <iostream>

namespace alex {

	AParticle::AParticle(int Id, std::string name, 
											bool isPrimary, double charge, 
         							TVector3 vertex, 
         							TLorentzVector p4,
                      int motherID)
  {
 		SetID(Id);
  	SetName(name);
  	SetIsPrimary(isPrimary);
 		SetCharge(charge);
 		SetVertex(vertex);
  	SetP4(p4);
    SetMotherID(motherID);
  }


  AParticle::AParticle(const AParticle& apart)
  {
  	SetID(apart.GetID());
  	SetName(apart.GetName());
  	SetIsPrimary(apart.GetIsPrimary());
  	SetCharge(apart.GetCharge());
  	SetVertex(apart.GetVertex());
  	SetP4(apart.GetP4());

    std::map <std::string, std::string> props = apart.GetProperties();
    for (auto prop : props) SetProperty(prop.first, prop.second);
  }


	void AParticle::DisplayInfo(std::ostream& s) const
  { 
   	s << "* Particle " << GetID() << ": " << GetName();
    s << "  Charge: " << GetCharge() << "  Mass: " << GetMass() << std::endl;
   	s << "  Primary: " << GetIsPrimary() << " -> Mother ID: " << GetMotherId() << std::endl;
   	s << "  Initial Vertex: " << PrintTVector3(GetVertex());
    s << "  Initial 4-Momentum: " << PrintTLorentzVector(GetP4());
    s << "  Initial Kinetic E: " << GetEkin() << std::endl;
   	s << "  Properties: " << std::endl << DisplayProperties();
  }


  std::string AParticle::PrintInfo() const
  {
    std::stringstream s;
    DisplayInfo(s);
    return s.str();
  }

}


std::ostream& operator << (std::ostream& s, const alex::AParticle& ap) 
{
  ap.DisplayInfo(s);
  return s; 
}
