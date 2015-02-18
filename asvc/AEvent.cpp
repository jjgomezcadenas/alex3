
// ----------------------------------------------------------------------------
///  \file   AEvent.cpp
///  \brief  Used for persistency
///
///  \author   <paola.ferrario@ific.uv.es> // gomez@mail.cern.ch
///  \date     14 Feb 2013 // Feb 2015
///  \version  $Id: Event.h 9914 2014-07-13 07:51:27Z gomez $
///
///  Copyright (c) 2013 NEXT Collaboration
// ----------------------------------------------------------------------------

#include <alex/AEvent.h>
#include <alex/AParticle.h>
#include <alex/ATTrack.h>
#include <alex/ARTrack.h>


ClassImp(alex::AEvent)

namespace alex {

  AEvent::AEvent() : fEventID(0)
  {
    fParticles = 0;
    fTTracks = 0; ///< true tracks
    fRTracks = 0;
     
  }

  AEvent::AEvent(int id) : fEventID(id) 
  { 
    fParticles = new TObjArray(); ///< particles
    fTTracks = new TObjArray(); ///< true tracks
    fRTracks = new TObjArray();
  }

  AEvent::AEvent(const AEvent& right)
  {
    *this = right;
  } 

  AEvent& AEvent::operator=(const AEvent& right) 
  {
    if (this != &right) 
    {
      fParticles = (TObjArray*)right.fParticles->Clone();
      fTTracks = (TObjArray*)right.fTTracks->Clone();
      fRTracks = (TObjArray*)right.fRTracks->Clone();
    
      fEventID = right.fEventID;
    }

    return *this;
  }



  AEvent::~AEvent() {
    AClear();  
    delete fParticles;
    delete fTTracks;
    delete fRTracks;	
  }
  void AEvent::AddParticle(AParticle* apart)
  {
    fParticles->AddLast(apart);
  }
  void AEvent::AddTTrack(ATTrack* att)
  {
    fTTracks->AddLast(att);
  }

  void AEvent::AddRTrack(ARTrack* art)
  {
    fRTracks->AddLast(art);
  }

  std::vector <AParticle*> AEvent::GetParticles() const
  {
    std::vector <AParticle*> particles;
    size_t n_ipart = fParticles->GetEntries();

    for (size_t ip = 0; ip< n_ipart; ++ip) 
    {
      AParticle* apart = dynamic_cast<AParticle*> (fParticles->At(ip));
      particles.push_back(apart);
    }

    return particles;
  }

  std::vector <ATTrack*> AEvent::GetTTracks() const
  {
    std::vector <ATTrack*> particles;
    size_t n_ipart = fTTracks->GetEntries();

    for (size_t ip = 0; ip< n_ipart; ++ip) 
    {
      ATTrack* apart = dynamic_cast<ATTrack*> (fTTracks->At(ip));
      particles.push_back(apart);
    }

    return particles;
  }

  std::vector <ARTrack*> AEvent::GetRTracks() const
  {
    std::vector <ARTrack*> particles;
    size_t n_ipart = fRTracks->GetEntries();

    for (size_t ip = 0; ip< n_ipart; ++ip) 
    {
      ARTrack* apart = dynamic_cast<ARTrack*> (fRTracks->At(ip));
      particles.push_back(apart);
    }

    return particles;
  }
  
  void AEvent::AClear()
  {
    if (fParticles) 
      fParticles->Delete();
     	
    if (fTTracks) 
      fTTracks->Delete(); 
     
    if (fRTracks)   
      fRTracks->Delete();
   
    fEventID = 0;
  }

  
  void AEvent::AInfo(std::ostream& s) const
  {
    s << std::endl;    
    s << "event number = " << GetID() << std::endl;
  
  }

} // end namespace irene

std::ostream& operator << (std::ostream& s, const alex::AEvent& ev) {
  ev.AInfo(s);
  return s; 
}
