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

#ifndef TEVENT_H_
#define TEVENT_H_

#include <alex/TDefs.h>
#include <TObject.h>
#include <TObjArray.h>


namespace alex {
  class TParticle;
  class AParticle;
  //class ATTrack;
  //class ARTrack;

  /// Persistent class
  
  class TEvent : public TObject {
    
  public: 
    /// Constructor
    TEvent();
    //AEvent(int id);
    /// Copy Constructor
    //AEvent(const AEvent& right);
    /// Destructor
    virtual ~TEvent();

  private:

    TObjArray* fParticles; ///< particles
    //TObjArray* fTTracks; ///< true tracks
    //TObjArray* fRTracks; ///< reconstructed tracks
    int fEventID; ///< unique identificative number

    double fTrueEventEnergy;
    double fRecEventEnergy;


  public:

    //TEvent& operator=(const TEvent& right);
    
    void AddParticle(const AParticle* apart);
    //std::vector <AParticle*> GetParticles() const;

    // void AddTTrack(const ATTrack* att);
    // std::vector <ATTrack*> GetTTracks() const;

    // void AddRTrack(const ARTrack* art);
    // std::vector <ARTrack*> GetRTracks() const;

    //const TObjArray* GetSensorHits() const;

    void SetID(int id) {fEventID = id;} 
    int GetID() const {return fEventID;}

    double GetTrueEventEnergy() const {return fTrueEventEnergy;}
    double GetRecEventEnergy() const {return fRecEventEnergy;}
    void SetRecEventEnergy(double e) {fRecEventEnergy=e;}
    void SetTrueEventEnergy(double e) {fTrueEventEnergy=e;}

    void ClearEvent();

   
    ClassDef(TEvent,1);
    
  };

   

} // end namespace irene


#endif // EVENT_H_
