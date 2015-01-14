
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
  	SetPosition(TVector3(x,y,z));
  	SetEdep(E);
  }

  AHit::AHit(int Id, TVector3 pos, double E)            
  {
    SetID(Id);
    SetPosition(pos);
    SetEdep(E);
  }

 	AHit::AHit(const AHit& ahit)
 	{
 		SetID(ahit.GetID());
 		SetPosition(ahit.GetPosition());
     SetEdep(ahit.GetEdep());
 	}

  void AHit::DisplayInfo(std::ostream& s) const
 	{
   	s << "  Hit ID: " << GetID();
   	s << "  Edep: " << GetEdep();
   	s << "  Position: " << PrintTVector3(GetPosition());
 	}

}

std::ostream& operator << (std::ostream& s, const alex::AHit& ap) 
{
  ap.DisplayInfo(s);
  return s; 
}