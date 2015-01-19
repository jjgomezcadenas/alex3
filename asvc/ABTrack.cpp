// ----------------------------------------------------------------------------
//  $Id: ABTrack.cpp  2015-01-05 1
//
//  Author:  <gomez@mail.cern.ch>
//  Created: 5 Jan 2015
//  
//  Copyright (c) 2015 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include "ABTrack.h"
#include "AHit.h"
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


  ABTrack::ABTrack(const ABTrack& abt)
  {
 		SetID(abt.GetID());

 		VDelete(fHits);
    std::vector<AHit*> hits = abt.GetHits();
    for (auto hit : hits) AddHit(hit);

    SetExtremes(abt.GetExtremes());
    fEdep = abt.GetEdep();
  }


  void ABTrack::AddHit(const AHit* ahit)
  {
    fHits.push_back(new AHit(*ahit));
    fEdep += ahit->GetEdep();
  }
	  

  const AHit* ABTrack::GetHit(int hitId) const {
    std::vector<AHit*> hits = GetHits();
    for (auto hit : hits)
    {
      if (hit->GetID() == hitId) return hit;
    }
    std::cout << "ABTrack::ERROR: No existe hit: " << hitId << std::endl;
    exit(0);
  }


  void ABTrack::SetExtremes(const std::pair<AHit*, AHit*> extremes) {
    SetExtreme1(extremes.first);
    SetExtreme2(extremes.second);
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