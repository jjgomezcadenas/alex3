#include "TrueEnergyFilter.hh"
#include <alex/ASvc.h>
#include <alex/ATTrack.h>

namespace alex {

  //--------------------------------------------------------------------
  bool TrueEnergyFilter::Init()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);
    
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "TrueEnergyFilter::Init()" ;
    klog << log4cpp::Priority::INFO << "TrueEnergyFilter::fMinEnergy = " << fMinEnergy;
    klog << log4cpp::Priority::INFO << "TrueEnergyFilter::fMaxEnergy = " << fMaxEnergy;

    fNumInputEvents = fNumOutputEvents = 0;

    return true;
  }

  
  //--------------------------------------------------------------------
  bool TrueEnergyFilter::Execute()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "TrueEnergyFilter::Execute()";

    fNumInputEvents += 1;

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

  fNumOutputEvents += 1;

  return true;
  }

  
  //--------------------------------------------------------------------
  bool TrueEnergyFilter::End()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "TrueEnergyFilter::End()";
    klog << log4cpp::Priority::INFO << "TrueEnergyFilter::fNumInputEvents:  " << fNumInputEvents;
    klog << log4cpp::Priority::INFO << "TrueEnergyFilter::fNumOutputEvents: " << fNumOutputEvents;

    return true;
  }

}
