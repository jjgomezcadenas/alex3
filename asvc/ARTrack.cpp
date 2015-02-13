// ----------------------------------------------------------------------------
//  $Id: ARTrack.cpp  2015-01-05 1
//
//  Author:  <gomez@mail.cern.ch>
//  Created: 5 Jan 2015
//  
//  Copyright (c) 2015 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include "ARTrack.h"
#include <alex/VectorOperations.h>
#include <alex/LogUtil.h>

#include <iostream>

namespace alex {

  ARTrack::ARTrack() : ABTrack::ABTrack() {
    fSpatialRes.SetXYZ(0., 0., 0.);
    fEnergyRes = 0.;
  };


  ARTrack::ARTrack(int id) : ABTrack::ABTrack(id) {
    fSpatialRes.SetXYZ(0., 0., 0.);
    fEnergyRes = 0.;    
  };


  ARTrack::ARTrack(const ARTrack& art) : ABTrack::ABTrack(art)
  {
    std::vector <int> ids = art.GetTTrackIDs();
 		for (auto tid: ids) AddTTrackID(tid);
    fSpatialRes = art.GetSpatialRes();
    fEnergyRes = art.GetEnergyRes();
  }


  ARTrack::~ARTrack()
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "ARTrack::~ARTrack()" ;
    klog << log4cpp::Priority::DEBUG << "clearing ordered hit vector" ;
    fOrdHits.clear();
  }
  

  void ARTrack::AddOrdHit(AHit* ahit)
  {
    fOrdHits.push_back(ahit);
  }


  void ARTrack::AddTTrackID(int id)
  {
    fTTrackIDs.push_back(id);
  }


  void ARTrack::SetEdep(double eDep)
  {
    fEdep = eDep;
  }

  
  void ARTrack::SetSpatialRes(TVector3 res)
  {
    fSpatialRes = res;
  }


  void ARTrack::SetEnergyRes(double res)
  {
    fEnergyRes = res;
  }

	  
  void ARTrack::DisplayInfo(std::ostream& s) const
  {
    ABTrack::DisplayInfo(s);

    s << "* " << GetOrdHits().size() << " main Path Hits: ";
    for (auto hit: GetOrdHits()) s << hit->GetID() << ", ";
    s << std::endl;

    if(GetTTrackIDs().size() >0)
   	  s << "* Origin: TTrack IDs: " << VPrint(GetTTrackIDs()) << std::endl;

    s << "* Spatial Resolution [mm]:" << PrintTVector3(GetSpatialRes());
    s << "* Energy  Resolution: " << GetEnergyRes() << " \%";
  }


  std::string ARTrack::PrintInfo() const
  {
    std::stringstream s;
    DisplayInfo(s);
    return s.str();
  }

}


std::ostream& operator << (std::ostream& s, const alex::ARTrack& art) 
{
  art.DisplayInfo(s);
  return s; 
}
