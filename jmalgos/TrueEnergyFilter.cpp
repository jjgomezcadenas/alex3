#include "TrueEnergyFilter.hh"
#include <alex/ASvc.h>
#include <alex/ATTrack.h>

namespace alex {

  //--------------------------------------------------------------------
  bool TrueEnergyFilter::Init()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel("DEBUG");
    
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "TrueEnergyFilter::Init()" ;
    klog << log4cpp::Priority::INFO << "TrueEnergyFilter::fMinEnergy = " << fMinEnergy;

    return true;
  }

  
  //--------------------------------------------------------------------
  bool TrueEnergyFilter::Execute()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "TrueEnergyFilter::Execute()";

      
    // Get the energy in the event and compare to the minimum allowed.
    double etot = ASvc::Instance().GetTrueEventEnergy();

    if(etot < fMinEnergy) {
      klog << log4cpp::Priority::DEBUG << "TrueEnergyFilter::Event Energy: "
           << etot << " MeV. --> Cut Failed";
      return false;
    }

    else klog << log4cpp::Priority::DEBUG << "TrueEnergyFilter::Event Energy: "
              << etot << " MeV. --> Cut Passed";

  return true;
  }

  
  //--------------------------------------------------------------------
  bool TrueEnergyFilter::End()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "TrueEnergyFilter::End()";

    return true;
  }
  
}
