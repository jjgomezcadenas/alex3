#include "GoodRoadFilter.hh"
#include <alex/ISvc.h>
#include <alex/PSvc.h>
#include <alex/ASvc.h>
#include <alex/ARTrack.h>
#include <alex/VectorOperations.h>

#include <TVector.h>
#include <TMatrix.h>

namespace alex {

  //--------------------------------------------------------------------
  bool GoodRoadFilter::Init()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);
    
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "GoodRoadFilter::Init()";
    klog << log4cpp::Priority::INFO << "GoodRoadFilter::Minimum Energy of Hottest RTrack = " << fEmin;

    fNumInputEvents = fNumOutputEvents = 0;

    return true;
  }

  
  //--------------------------------------------------------------------
  bool GoodRoadFilter::Execute()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "GoodRoadFilter::Execute()";

    fNumInputEvents += 1;

    // Getting with the Hottest (== More Energetic) RTrack
    std::vector <ARTrack*> rTracks = ASvc::Instance().GetRTracks();
    double maxEdep = 0.;
    ARTrack* hRTrack;
    for (auto rTrack: rTracks) {
      double eDep = rTrack->GetEdep();
      klog << log4cpp::Priority::DEBUG << "GoodRoadFilter::RTrack " << rTrack->GetID()
           << " Energy: " << eDep;
      if (eDep > maxEdep) {
        maxEdep = eDep;
        hRTrack = rTrack;
      }
    }

    fGoodRoadFilter_EnergyHRTrack_H1->Fill(maxEdep);

    if (maxEdep >= fEmin) {
      klog << log4cpp::Priority::DEBUG << "GoodRoadFilter::RTrack " << hRTrack->GetID()
           << " Energy: " << maxEdep << "  ->  Filter Passed";
      fNumOutputEvents += 1;
      return true;      
    }
    else {
      klog << log4cpp::Priority::DEBUG << "GoodRoadFilter::RTrack " << hRTrack->GetID()
           << " Energy: " << maxEdep << "  ->  Filter Failed";
      return false;      
    }

    return true;
  }

  
  //--------------------------------------------------------------------
  bool GoodRoadFilter::End()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "GoodRoadFilter::End()";
    klog << log4cpp::Priority::INFO << "GoodRoadFilter::fNumInputEvents:  " << fNumInputEvents;
    klog << log4cpp::Priority::INFO << "GoodRoadFilter::fNumOutputEvents: " << fNumOutputEvents;

    return true;
  }
}
