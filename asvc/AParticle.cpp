
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
              							TLorentzVector p4) 
  	{
  		SetID(Id);
  		SetName(name);
  		SetIsPrimary(isPrimary);
  		SetCharge(charge);
  		SetVertex(vertex);
  		SetP4(p4);
  	}

  	AParticle::AParticle(const AParticle& apart)
  	{
  		SetID(apart.GetID());
  		SetName(apart.GetName());
  		SetIsPrimary(apart.GetIsPrimary());
  		SetCharge(apart.GetCharge());
  		SetVertex(apart.GetVertex());
  		SetP4(apart.GetP4());
  	}
	void AParticle::DisplayInfo(std::ostream& s) const
  	{
    	s << std::endl;    
    
    	s << "ID = " << GetID() << std::endl;
    	s << "Is primary = " << GetIsPrimary() << std::endl;
    	s << "Name = " << GetName()  << std::endl;
    	s << "Charge = " << GetCharge()  << std::endl;
    	s << "Mass = " << GetMass()  << std::endl;
    	s << "Vertex = " << PrintTVector3(GetVertex())  
                       << std::endl;
    	s << "Momentum = " << PrintTVector3(GetMomentum())  
                       << std::endl;
    	s << "4-Momentum = " << PrintTLorentzVector(GetP4())
                       << std::endl;
    	s << "Properties = " << DisplayProperties()  
                       << std::endl;
  	}
}

std::ostream& operator << (std::ostream& s, const alex::AParticle& ap) 
{
  ap.DisplayInfo(s);
  return s; 
}