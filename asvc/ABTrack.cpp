// ----------------------------------------------------------------------------
//  $Id: ABTrack.cpp  2015-01-05 1
//
//  Author:  <gomez@mail.cern.ch>
//  Created: 5 Jan 2015
//  
//  Copyright (c) 2015 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include "ABTrack.h"
#include <alex/VectorOperations.h>

#include <iostream>

namespace alex {

  ABTrack::ABTrack() 
  {
    SetID(-1);
    fEdep = 0.;
  }


	ABTrack::ABTrack(int id) 
  {
  	SetID(id);
    fEdep = 0.;
  }

  ABTrack::~ABTrack()
  {
    VDelete(fHits);
    delete fExtremes.first;
    delete fExtremes.second;
  }
  
  ABTrack::ABTrack(const ABTrack& abt)
  {
 		SetID(abt.GetID());

 		VDelete(fHits);
    const std::vector<AHit*> hits = abt.GetHits();
    for (auto hit : hits) AddHit(hit);

    SetExtremes(abt.GetExtremes());
    fEdep = abt.GetEdep();

    std::map <std::string, std::string> props = abt.GetProperties();
    for (auto prop : props) SetProperty(prop.first, prop.second);
  }


  void ABTrack::AddHit(const AHit* ahit)
  {
    fHits.push_back(new AHit(*ahit));
    fEdep += ahit->GetEdep();
  }
	  
// Extremes
  void ABTrack::SetExtreme1(const AHit* ahit) 
  {
    fExtremes.first = new AHit(*ahit);
  }

  void ABTrack::SetExtreme2(const AHit* ahit) 
  {
    fExtremes.second = new AHit(*ahit);
  }

  const AHit* ABTrack::GetHit(int id) const 
  {
    const std::vector<AHit*> hits = GetHits();
    for (auto hit : hits)
    {
      if (hit->GetID() == id) return hit;
    }
    std::cout << "ABTrack::ERROR: Hit ID "  << id << " does NOT EXIST !!" << std::endl;
    exit(0);
  }


  void ABTrack::SetExtremes(const std::pair<AHit*, AHit*> extremes) {
    SetExtreme1(new AHit(*extremes.first));
    SetExtreme2(new AHit(*extremes.second));
  }


  void ABTrack::DisplayInfo(std::ostream& s) const
  {
   	s << std::endl;    
   	s << "*** TTrack ID: " << GetID() << std::endl;
    s << "* EnergyDep: " << GetEdep() << std::endl;
    TVector3 pos1 = GetExtreme1()->GetPosition();
    TVector3 pos2 = GetExtreme2()->GetPosition();
    s << "* Extreme1:" << PrintTVector3(pos1)
      << "  Extreme2:" << PrintTVector3(pos2);
   	s << "* Hits Collection: " <<  std::endl;
    const std::vector<AHit*> hits = GetHits();
    for (auto hit : hits) hit->DisplayInfo(s);
  }

}


std::ostream& operator << (std::ostream& s, const alex::ABTrack& abt) 
{
  abt.DisplayInfo(s);
  return s;
}
