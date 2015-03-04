#include "RoadCharacterizer.hh"
#include <alex/ISvc.h>
#include <alex/PSvc.h>
#include <alex/ASvc.h>
#include <alex/ARTrack.h>
#include <alex/AHit.h>

#include <alex/VectorOperations.h>


#include <TVector.h>
#include <TMatrix.h>

namespace alex {

  //--------------------------------------------------------------------
  bool RoadCharacterizer::Init()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "RoadCharacterizer::Init()";

    return true;
  }

  
  //--------------------------------------------------------------------
  bool RoadCharacterizer::Execute()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "RoadCharacterizer::Execute()";

    // Getting Reconstructed Tracks
    std::vector <ARTrack*> rTracks = ASvc::Instance().GetRTracks();


    // Dealing with number of RTracks
    int numRTracks = rTracks.size();
    fRoadCharacterizer_NumRTracks_H1->Fill(numRTracks);
    klog << log4cpp::Priority::DEBUG << "RoadCharacterizer::Number of RTracks: " << numRTracks;


    // Dealing with the Hottest (== More Energetic) RTrack
    double maxEdep = 0.;
    ARTrack* hRTrack;
    for (auto rTrack: rTracks) {
      double eDep = rTrack->GetEdep();
      klog << log4cpp::Priority::DEBUG << "RoadCharacterizer::RTrack " << rTrack->GetID()
           << " Energy: " << eDep;
      if (eDep > maxEdep) {
        maxEdep = eDep;
        hRTrack = rTrack;
      }
    }

    int numHits = hRTrack->GetHits().size();
    int numOrdHits = hRTrack->GetOrdHits().size();

    klog << log4cpp::Priority::DEBUG << "RoadCharacterizer::Hottest RTrack ID: " << hRTrack->GetID()
         << "  with Energy: " << maxEdep << "  NumHits: " << numHits 
         << "  NumOrdHits: " << numOrdHits;

    fRoadCharacterizer_EnergyHRTrack_H1->Fill(maxEdep); 
    fRoadCharacterizer_VoxelsHRTrack_H1->Fill(hRTrack->GetHits().size());
    fRoadCharacterizer_MPVoxelsHRTrack_H1->Fill(numOrdHits);


    // Dealing with the 2nd Hottest (== 2nd More Energetic) RTrack
    if (rTracks.size() > 1) {
      double maxEdep2 = 0.;
      ARTrack* hRTrack2;
      for (auto rTrack: rTracks) {
        double eDep = rTrack->GetEdep();
        if ((eDep > maxEdep2) && (eDep != maxEdep)) {
          maxEdep2 = eDep;
          hRTrack2 = rTrack;
        }
      }

      int numHits = hRTrack2->GetHits().size();
      int numOrdHits = hRTrack2->GetOrdHits().size();

      klog << log4cpp::Priority::DEBUG << "RoadCharacterizer::2nd Hottest RTrack ID: " << hRTrack2->GetID()
           << "  with Energy: " << maxEdep2 << "  NumHits: " << numHits 
           << "  NumOrdHits: " << numOrdHits;

      fRoadCharacterizer_EnergyHRTrack2_H1->Fill(maxEdep2);
      fRoadCharacterizer_EnergyHRTracks_H2->Fill(maxEdep, maxEdep2);
    }
    else {
      klog << log4cpp::Priority::DEBUG << "RoadCharacterizer::2nd Hottest RTrack ID: NOT EXIST.";
    }

    return true;
  }

  

  //--------------------------------------------------------------------
  bool RoadCharacterizer::End()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "RoadCharacterizer::End()";

    return true;
  }

}
