// ----------------------------------------------------------------------------
//  $Id: ARTrack.cpp  2015-01-05 1
//
//  Author:  <gomez@mail.cern.ch>
//  Created: 5 Jan 2015
//  
//  Copyright (c) 2015 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include <alex/TRTrack.h>
#include <alex/ARTrack.h>


ClassImp(alex::TRTrack)

namespace alex {

  // ARTrack::ARTrack() : ABTrack::ABTrack() {
  //   fSpatialRes.SetXYZ(0., 0., 0.);
  //   fEnergyRes = 0.;
  // };


  // ARTrack::ARTrack(int id) : ABTrack::ABTrack(id) {
  //   fSpatialRes.SetXYZ(0., 0., 0.);
  //   fEnergyRes = 0.;    
  // };


  TRTrack::TRTrack(const ARTrack& art) : ARTrack(art)
  {
    //ARTrack::ARTrack(art);
  }


}

