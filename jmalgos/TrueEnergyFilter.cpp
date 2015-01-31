#include "TrueEnergyFilter.hh"
#include <alex/ASvc.h>
#include <alex/ATTrack.h>

namespace alex {

  //--------------------------------------------------------------------
  bool TrueEnergyFilter::Init()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel("INFO");
    
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "TrueEnergyFilter::Init()" ;
    klog << log4cpp::Priority::INFO << "TrueEnergyFilter::fMinEnergy = " << fMinEnergy;
    klog << log4cpp::Priority::INFO << "TrueEnergyFilter::fMaxEnergy = " << fMaxEnergy;

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
    fTrueEnergyFilter_EdepBefore_H1->Fill(etot);

    if( (etot < fMinEnergy) || (etot > fMaxEnergy) ) {
      klog << log4cpp::Priority::DEBUG << "TrueEnergyFilter::Event Energy: "
           << etot << " MeV. --> Cut Failed";
      return false;
    }

    else {
      klog << log4cpp::Priority::DEBUG << "TrueEnergyFilter::Event Energy: "
              << etot << " MeV. --> Cut Passed";
      fTrueEnergyFilter_EdepAfter_H1->Fill(etot);
    } 

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
