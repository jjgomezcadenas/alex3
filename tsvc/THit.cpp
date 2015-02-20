
// ----------------------------------------------------------------------------
//  $Id: AHit.cpp  2015-01-05 1
//
//  Author:  <gomez@mail.cern.ch>
//  Created: 10 Jan 2015
//  
//  Copyright (c) 2015 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include <alex/THit.h>

ClassImp(alex::THit)

namespace alex {

	// AHit::AHit(int Id, double x, double y, double z, double E) 												
 //  {
 //  	SetID(Id);
 //  	SetPosition(TVector3(x,y,z));
 //  	SetEdep(E);
 //  }


 //  AHit::AHit(int Id, TVector3 pos, double E)            
 //  {
 //    SetID(Id);
 //    SetPosition(pos);
 //    SetEdep(E);
 //  }


 	THit::THit(const AHit& ahit)
 	{
 		SetID(ahit.GetID());
 		SetPosition(ahit.GetPosition());
    SetEdep(ahit.GetEdep());

    std::map <std::string, std::string> props = ahit.GetProperties();
    for (auto prop : props) SetProperty(prop.first, prop.second);
 	}



}