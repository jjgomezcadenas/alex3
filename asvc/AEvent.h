// ----------------------------------------------------------------------------
///  \file   AEvent.h
///  \brief  Used for persistency
///
///  \author   <paola.ferrario@ific.uv.es> // gomez@mail.cern.ch
///  \date     14 Feb 2013 // Feb 2015
///  \version  $Id: Event.h 9914 2014-07-13 07:51:27Z gomez $
///
///  Copyright (c) 2013 NEXT Collaboration
// ----------------------------------------------------------------------------

#ifndef AEVENT_H_
#define AEVENT_H_

#include <iostream>
#include <TObject.h>
#include <TObjArray.h>


namespace alex {
  class AParticle;
  class ATTrack;
  class ARTrack;

  /// Persistent class
  
  class AEvent : public TObject {
    
  public: 
    /// Constructor
    AEvent();
    AEvent(int id);
    /// Copy Constructor
    AEvent(const AEvent& right);
    /// Destructor
    ~AEvent();

  private:

    //std::vector <alex::AParticle*> fParticles;
    //std::vector <alex::ATTrack*> fTTracks;
    //std::vector <alex::ARTrack*> fRTracks;

    TObjArray* fParticles; ///< particles
    TObjArray* fTTracks; ///< true tracks
    TObjArray* fRTracks; ///< reconstructed tracks
    int fEventID; ///< unique identificative number

   

  public:

    AEvent& operator=(const AEvent& right);
    
    void AddParticle(AParticle* apart);
    std::vector <AParticle*> GetParticles() const;

    void AddTTrack(ATTrack* att);
    std::vector <ATTrack*> GetTTracks() const;

    void AddRTrack(ARTrack* art);
    std::vector <ARTrack*> GetRTracks() const;

    //const TObjArray* GetSensorHits() const;

    void SetID(int id); 
    int GetID() const {return fEventID;}

    void AClear();

    void AInfo(std::ostream& s) const;


   
    ClassDef(AEvent,1);
    
  };

   

} // end namespace irene

std::ostream& operator << (std::ostream& s, const alex::AEvent& ev);

#endif // EVENT_H_
