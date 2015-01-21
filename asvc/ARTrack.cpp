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

#include <iostream>

namespace alex {

  ARTrack::ARTrack() : ABTrack::ABTrack() {};


  ARTrack::ARTrack(int id) : ABTrack::ABTrack(id) {};


  ARTrack::ARTrack(const ARTrack& art) : ABTrack::ABTrack(art)
  {
    std::vector <int> ids = art.GetTTrackIDs();

 		for (auto tid: ids) AddTTrackID(tid);
  }


  void ARTrack::AddTTrackID(int id)
  {
    fTTrackIDs.push_back(id);
  }


  void ARTrack::SetEdep(double eDep)
  {
    fEdep = eDep;
  }

	  
  void ARTrack::DisplayInfo(std::ostream& s) const
  {
    ABTrack::DisplayInfo(s);
   	s << "* Origin: TTrack IDs: " << VPrint(GetTTrackIDs()) << std::endl;
  }
}


std::ostream& operator << (std::ostream& s, const alex::ARTrack& art) 
{
  art.DisplayInfo(s);
  return s; 
}
