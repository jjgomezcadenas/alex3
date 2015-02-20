
// ----------------------------------------------------------------------------
//  $Id: ADebug.cpp  2015-01-05 1
//
//  Author:  <gomez@mail.cern.ch>
//  Created: 5 Jan 2015
//  
//  Copyright (c) 2015 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include <alex/ADebug.h>


namespace alex {
void ADebug::SetLevelDebug(std::string debug)
  {
    fDebug = debug;  
    SetDebugLevel(debug);  
  }
}
