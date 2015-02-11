#include "SmearedEnergyFilter.hh"
#include <alex/ASvc.h>
#include <alex/ATTrack.h>

namespace alex {

  //--------------------------------------------------------------------
  bool SmearedEnergyFilter::Init()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel("INFO");
    
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "SmearedEnergyFilter::Init()" ;
    klog << log4cpp::Priority::INFO << "SmearedEnergyFilter::fMinEnergy = " << fMinEnergy;
    klog << log4cpp::Priority::INFO << "SmearedEnergyFilter::fMaxEnergy = " << fMaxEnergy;

    fNumInputEvents = fNumOutputEvents = 0;

    return true;
  }

  
  //--------------------------------------------------------------------
  bool SmearedEnergyFilter::Execute()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "SmearedEnergyFilter::Execute()";

    fNumInputEvents += 1;

    double etot = ASvc::Instance().GetRecEventEnergy();
    fSmearedEnergyFilter_EdepBefore_H1->Fill(etot);

    if( (etot < fMinEnergy) || (etot > fMaxEnergy) ) {
      klog << log4cpp::Priority::DEBUG << "SmearedEnergyFilter::Event Energy: "
           << etot << " MeV. --> Cut Failed";
      return false;
    }

    else {
      klog << log4cpp::Priority::DEBUG << "SmearedEnergyFilter::Event Energy: "
            << etot << " MeV. --> Cut Passed";
      fSmearedEnergyFilter_EdepAfter_H1->Fill(etot);
    } 

  fNumOutputEvents += 1;

  return true;
  }

  
  //--------------------------------------------------------------------
  bool SmearedEnergyFilter::End()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "SmearedEnergyFilter::End()";
    klog << log4cpp::Priority::INFO << "SmearedEnergyFilter::fNumInputEvents:  " << fNumInputEvents;
    klog << log4cpp::Priority::INFO << "SmearedEnergyFilter::fNumOutputEvents: " << fNumOutputEvents;

    return true;
  }

}
