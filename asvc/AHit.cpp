
// ----------------------------------------------------------------------------
//  $Id: AHit.cpp  2015-01-05 1
//
//  Author:  <gomez@mail.cern.ch>
//  Created: 10 Jan 2015
//  
//  Copyright (c) 2015 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include "AHit.h"

#include <iostream>

namespace alex {
	  AHit::AHit(int Id, double x, double y, double z, double E) 
														
  	{
  		SetID(Id);
  		SetHit(TVector3(x,y,z));
  		SetEdep(E);
  	}

    AHit::AHit(int Id, TVector3 hit, double E) 
                            
    {
      SetID(Id);
      SetHit(hit);
      SetEdep(E);
    }

  	AHit::AHit(const AHit& ahit)
  	{
  		SetID(ahit.GetID());
  		SetHit(ahit.GetHit());
      SetEdep(ahit.GetEdep());
  	}
	void AHit::DisplayInfo(std::ostream& s) const
  	{
    	s << std::endl;    
    
    	s << "ID = " << GetID() << std::endl;
    	s << "Edep = " << GetEdep()  << std::endl;
    	s << "Hit = " << PrintTVector3(GetHit())  
                       << std::endl;
  	}
}

std::ostream& operator << (std::ostream& s, const alex::AHit& ap) 
{
  ap.DisplayInfo(s);
  return s; 
}