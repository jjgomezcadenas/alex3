
// ----------------------------------------------------------------------------
//  $Id: AID.cpp  2015-01-05 1
//
//  Author:  <gomez@mail.cern.ch>
//  Created: 5 Jan 2015
//  
//  Copyright (c) 2015 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include <alex/AID.h>


namespace alex {
void AID::DisplayInfo(std::ostream& s) const
  {
    s << std::endl;    
    s << "ID = " << fId << std::endl;
  }
}

std::ostream& operator << (std::ostream& s, const alex::AID& aid) 
{
  aid.DisplayInfo(s);
  return s; 
}