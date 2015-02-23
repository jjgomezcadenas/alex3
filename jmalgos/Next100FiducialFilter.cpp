#include "Next100FiducialFilter.hh"
#include <alex/ASvc.h>
#include <alex/ATTrack.h>
#include <alex/AHit.h>

namespace alex {

  //--------------------------------------------------------------------
  bool Next100FiducialFilter::Init()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);
    
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "Next100FiducialFilter::Init()";
    klog << log4cpp::Priority::INFO << "Next100FiducialFilter::fVoidGap = " << fVoidGap << " mm";
    klog << log4cpp::Priority::INFO << "Next100FiducialFilter::fMinEnergy = " << fMinEnergy << " MeV";

    fNumInputEvents = fNumOutputEvents = 0;

    fZPosLimit = fDetectorLength/2. + fDetectorZCenter - fVoidGap;
    fZNegLimit = -fDetectorLength/2. + fDetectorZCenter + fVoidGap;
    fRadLimit  = fDetectorRadius - fVoidGap;

    return true;
  }

  
  //--------------------------------------------------------------------
  bool Next100FiducialFilter::Execute()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "Next100FiducialFilter::Execute()";

    fNumInputEvents += 1;

    double vetoE = 0.;
    const std::vector <ATTrack*> ttracks = ASvc::Instance().GetTTracks();
    for (auto track : ttracks) {
      const std::vector<AHit*> hits = track->GetHits();
      for (auto hit : hits) {
        TVector3 pos = hit->GetPosition();
        double rad = sqrt(pow(pos.X(),2) + pow(pos.Y(),2));

        if ((pos.Z() > fZPosLimit) ||  // near positive endcap
            (pos.Z() < fZNegLimit) ||  // near negative endcap
            (rad > fRadLimit) ) {      // near cylindrical surface  
          vetoE += hit->GetEdep();
        }
      }
    }

    if (vetoE > 0.) fNext100FiducialFilter_VetoEdep_H1->Fill(vetoE);

    if(vetoE > fMinEnergy) {
      klog << log4cpp::Priority::DEBUG << "Next100FiducialFilter::Veto Energy: "
           << vetoE << " MeV. --> Cut Failed";
      return false;
    }

    else klog << log4cpp::Priority::DEBUG << "Next100FiducialFilter::Veto Energy: "
              << vetoE << " MeV. --> Cut Passed";


  fNumOutputEvents += 1;

  return true;
  }

  
  //--------------------------------------------------------------------
  bool Next100FiducialFilter::End()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "Next100FiducialFilter::End()";
    klog << log4cpp::Priority::INFO << "Next100FiducialFilter::fNumInputEvents:  " << fNumInputEvents;
    klog << log4cpp::Priority::INFO << "Next100FiducialFilter::fNumOutputEvents: " << fNumOutputEvents;

    return true;
  }

}
