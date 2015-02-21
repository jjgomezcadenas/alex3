
// ----------------------------------------------------------------------------
///  \file   TEvent.cpp
///  \brief  Used for persistency
///
///  \author   <JJ>
///  \date     14 Feb 2013 // Feb 2015
///  \version  $Id: Event.h 9914 2014-07-13 07:51:27Z gomez $
///
///  Copyright (c) 2015 NEXT Collaboration
// ----------------------------------------------------------------------------

#include <alex/TEvent.h>
#include <alex/TParticle.h>
#include <alex/AParticle.h>
#include <alex/ATTrack.h>
#include <alex/ARTrack.h>
#include <alex/TTTrack.h>
#include <alex/TRTrack.h>


ClassImp(alex::TEvent)

namespace alex {

  // AEvent::AEvent() : fEventID(0)
  // {
  //   fParticles = 0;
  //   fTTracks = 0; ///< true tracks
  //   fRTracks = 0;
     
  // }

  TEvent::TEvent() : fEventID(0), fTrueEventEnergy(0),fRecEventEnergy(0)
  { 
    fParticles = new TObjArray(); ///< particles
    fTTracks = new TObjArray(); ///< true tracks
    fRTracks = new TObjArray();
  }

  // AEvent::AEvent(const AEvent& right)
  // {
  //   *this = right;
  // } 

  // AEvent& AEvent::operator=(const AEvent& right) 
  // {
  //   if (this != &right) 
  //   {
  //     fParticles = (TObjArray*)right.fParticles->Clone();
  //     fTTracks = (TObjArray*)right.fTTracks->Clone();
  //     fRTracks = (TObjArray*)right.fRTracks->Clone();
    
  //     fEventID = right.fEventID;
  //   }

  //   return *this;
  // }



  TEvent::~TEvent() 
  {
    ClearEvent();  
    delete fParticles;
    delete fTTracks;
    delete fRTracks;	
  }
  void TEvent::AddParticle(const AParticle* apart)
  {
    fParticles->AddLast(new TParticle(*apart));
  }
  void TEvent::AddTTrack(const ATTrack* att)
  {
    fTTracks->AddLast(new TTTrack(*att));
  }

  void TEvent::AddRTrack(const ARTrack* art)
  {
    fRTracks->AddLast(new TRTrack(*art));
  }

  // std::vector <AParticle*> AEvent::GetParticles() const
  // {
  //   std::vector <AParticle*> particles;
  //   size_t n_ipart = fParticles->GetEntries();

  //   for (size_t ip = 0; ip< n_ipart; ++ip) 
  //   {
  //     AParticle* apart = dynamic_cast<AParticle*> (fParticles->At(ip));
  //     particles.push_back(apart);
  //   }

  //   return particles;
  // }

  // std::vector <ATTrack*> AEvent::GetTTracks() const
  // {
  //   std::vector <ATTrack*> particles;
  //   size_t n_ipart = fTTracks->GetEntries();

  //   for (size_t ip = 0; ip< n_ipart; ++ip) 
  //   {
  //     ATTrack* apart = dynamic_cast<ATTrack*> (fTTracks->At(ip));
  //     particles.push_back(apart);
  //   }

  //   return particles;
  // }

  // std::vector <ARTrack*> AEvent::GetRTracks() const
  // {
  //   std::vector <ARTrack*> particles;
  //   size_t n_ipart = fRTracks->GetEntries();

  //   for (size_t ip = 0; ip< n_ipart; ++ip) 
  //   {
  //     ARTrack* apart = dynamic_cast<ARTrack*> (fRTracks->At(ip));
  //     particles.push_back(apart);
  //   }

  //   return particles;
  // }
  
  void TEvent::ClearEvent()
  {
    if (fParticles) 
      fParticles->Delete();
     	
    if (fTTracks) 
      fTTracks->Delete(); 
     
    if (fRTracks)   
      fRTracks->Delete();
   
  }

  

} // end namespace 


