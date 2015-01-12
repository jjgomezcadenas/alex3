
// ----------------------------------------------------------------------------
//  $Id: ATTRack.cpp  2015-01-05 1
//
//  Author:  <gomez@mail.cern.ch>
//  Created: 5 Jan 2015
//  
//  Copyright (c) 2015 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include "ATTRack.h"
#include "AHit.h"
#include <alex/VectorOperations.h>

#include <iostream>

namespace alex {
	  ATTRack::ATTRack(int Id, int particleID) 
  	{
  		SetID(Id);
  		SetParticleID(particleID);
  	}

  	ATTRack::ATTRack(const ATTRack& at)
  	{
  		SetID(at.GetID());
  		SetParticleID(at.GetParticleID());
  		VDelete(fHits);

      std::vector<AHit*> hits = at.GetHits();
      for (auto hit : hits)
      {
        AddHit(hit);
      }
  	}

    void ATTRack::AddHit(const AHit* ahit)
    {
      fHits.push_back(new AHit(*ahit));
    }
	  
    void ATTRack::DisplayInfo(std::ostream& s) const
  	{
    	s << std::endl;    
    
    	s << "ID = " << GetID() << std::endl;
    	s << "Particle ID = " << GetParticleID() << std::endl;
    	s << "Hits: " <<  std::endl;

      const std::vector<AHit*> hits = GetHits();
      for (auto hit : hits)
      {
        s << hit <<  std::endl;
      }
  	}
}

std::ostream& operator << (std::ostream& s, const alex::ATTRack& ap) 
{
  ap.DisplayInfo(s);
  return s; 
}