// ----------------------------------------------------------------------------
//  $Id: LinkDef.h 9556 2014-01-14 22:24:14Z gomez $
//
//  Author:  <JJ>
//  Created: 14 Feb 2015
//  
//  Copyright (c) 2015 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ namespace alex+;
#pragma link C++ class alex::THit+;
#pragma link C++ class alex::TParticle+;
#pragma link C++ class alex::TEvent+;
// #pragma link C++ class alex::AID+;
// #pragma link C++ class alex::AProperties+;
// #pragma link C++ class alex::ABTrack+;
// #pragma link C++ class alex::ATTrack+;
// #pragma link C++ class alex::ARTrack+;
// #pragma link C++ class alex::AParticle+;

// #pragma link C++ class std::pair<alex::AHit*,alex::AHit*>+;

#endif
