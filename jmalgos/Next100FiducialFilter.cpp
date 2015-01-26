#include "Next100FiducialFilter.hh"
#include <alex/ASvc.h>
#include <alex/ATTrack.h>

namespace alex {

  //--------------------------------------------------------------------
  bool Next100FiducialFilter::Init()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel("INFO");
    
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "Next100FiducialFilter::Init()" ;
    klog << log4cpp::Priority::INFO << "Next100FiducialFilter::fVoidGap = " << fVoidGap << " mm";
    klog << log4cpp::Priority::INFO << "Next100FiducialFilter::fMinEnergy = " << fMinEnergy << " MeV";

    return true;
  }

  
  //--------------------------------------------------------------------
  bool Next100FiducialFilter::Execute()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "Next100FiducialFilter::Execute()";

    // TO BE REPLACED TO A MORE PROPER PLACE
    double fDetectorRadius = 534.5;
    double fDetectorLength  = 1300.;
    double fDetectorZCenter = 14.0;
    double z_pos_limit = fDetectorLength/2. + fDetectorZCenter;
    double z_neg_limit = -fDetectorLength/2. + fDetectorZCenter;
    /////////////////////////////////////////

    double vetoE = 0.;
    const std::vector <ATTrack*> ttracks = ASvc::Instance().GetTTracks();
    for (auto track : ttracks) {
      const std::vector<AHit*> hits = track->GetHits();
      for (auto hit : hits) {
        TVector3 pos = hit->GetPosition();
        double rad = sqrt(pow(pos.X(),2) + pow(pos.Y(),2));

        if ((pos.Z() > z_pos_limit - fVoidGap) ||  // near positive endcap
            (pos.Z() < z_neg_limit + fVoidGap) ||  // near negative endcap
            (rad > fDetectorRadius - fVoidGap) ) { // near cylindrical surface  
          vetoE += hit->GetEdep();
        }
      }
    }


    if(vetoE > fMinEnergy) {
      klog << log4cpp::Priority::DEBUG << "Next100FiducialFilter::Veto Energy: "
           << vetoE << " MeV. --> Cut Failed";
      return false;
    }

    else klog << log4cpp::Priority::DEBUG << "Next100FiducialFilter::Veto Energy: "
              << vetoE << " MeV. --> Cut Passed";

  return true;
  }

  
  //--------------------------------------------------------------------
  bool Next100FiducialFilter::End()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "Next100FiducialFilter::End()";

    return true;
  }

}
