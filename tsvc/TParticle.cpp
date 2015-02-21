
// ----------------------------------------------------------------------------
//  $Id: AParticle.cpp  2015-01-05 1
//
//  Author:  <gomez@mail.cern.ch>
//  Created: 5 Jan 2015
//  
//  Copyright (c) 2015 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include <alex/TParticle.h>
#include <alex/AParticle.h>

ClassImp(alex::TParticle)


namespace alex {

	// AParticle::AParticle(int Id, std::string name, 
	// 										bool isPrimary, double charge, 
 //         							TVector3 vertex, 
 //         							TLorentzVector p4,
 //                      int motherID)
 //  {
 // 		SetID(Id);
 //  	SetParticleName(name);
 //  	SetIsPrimary(isPrimary);
 // 		SetCharge(charge);
 // 		SetVertex(vertex);
 //  	SetP4(p4);
 //    SetMotherID(motherID);
 //  }


  TParticle::TParticle(const AParticle& apart) : AParticle(apart)
  {
    //AParticle::AParticle(apart);
  	// SetID(apart.GetID());
  	// SetParticleName(apart.GetParticleName());
  	// SetIsPrimary(apart.GetIsPrimary());
  	// SetCharge(apart.GetCharge());
  	// SetVertex(apart.GetVertex());
  	// SetP4(apart.GetP4());
   //  SetMotherID(apart.GetMotherId());

   //  std::map <std::string, std::string> props = apart.GetProperties();
   //  for (auto prop : props) SetProperty(prop.first, prop.second);
  }

}

