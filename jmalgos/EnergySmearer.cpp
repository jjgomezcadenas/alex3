#include "EnergySmearer.hh"
#include <alex/ASvc.h>
#include <alex/ARTrack.h>
#include <alex/AHit.h>


namespace alex {

  //--------------------------------------------------------------------
  bool EnergySmearer::Init()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);
    
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "EnergySmearer::Init()";
    klog << log4cpp::Priority::INFO << "EnergySmearer::FWHM at Qbb: " << fFWHM << " \%";

    fRand = new TRandom3();

    return true;
  }

  
  //--------------------------------------------------------------------
  bool EnergySmearer::Execute()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "EnergySmearer::Execute()";

    double trueE = ASvc::Instance().GetTrueEventEnergy();
    fEnergySmearer_TrueEdep_H1->Fill(trueE);
    klog << log4cpp::Priority::DEBUG << "EnergySmearer::True Energy: " << trueE;

/*    // Scaling FWHM at Qbb to Sigma at True Energy
    double sigmaE = ((fFWHM/100.) * sqrt(fQbb) * sqrt(trueE)) / fFWHM2Sigma;

    double smE = trueE + fRand->Gaus(0., 1.) * sigmaE;
    fEnergySmearer_SmEdep_H1->Fill(smE);
    klog << log4cpp::Priority::DEBUG << "EnergySmearer::Smeared Energy: " << smE;

    // Updating Energy of Voxels from Reconstructed Tracks
    double voxelFactor = smE / trueE;
    const std::vector <ARTrack*> rTracks = ASvc::Instance().GetRTracks();
    for (auto rTrack : rTracks) {
      for (auto hit : rTrack->GetHits()) {
        hit->SetEdep(hit->GetEdep() * voxelFactor);
      }
    }
*/

    double smE = 0.;
    for (auto rTrack : ASvc::Instance().GetRTracks()) {
      rTrack->SetEnergyRes(fFWHM);
      double trueTrkE = rTrack->GetEdep();
      // Scaling FWHM at Qbb to Sigma at True Energy
      double sigmaE = ((fFWHM/100.) * sqrt(fQbb) * sqrt(trueTrkE)) / fFWHM2Sigma;
      double smTrkE = trueTrkE + fRand->Gaus(0., 1.) * sigmaE;
      smE += smTrkE;
      //std::cout << "RTrack Smered Energy: " << smTrkE << std::endl;
      klog << log4cpp::Priority::DEBUG << "EnergySmearer::RTrack "
           << rTrack->GetID() << " Smeared Energy: " << smTrkE;

      // Updating Energy of Voxels from Reconstructed Tracks
      double voxelFactor = smTrkE / trueTrkE;
      for (auto hit : rTrack->GetHits()) hit->SetEdep(hit->GetEdep() * voxelFactor);

      //rTrack->DisplayInfo(std::cout);
    }

    ASvc::Instance().SetRecEventEnergy(smE);
    fEnergySmearer_SmEdep_H1->Fill(smE);
    klog << log4cpp::Priority::DEBUG << "EnergySmearer:: Event Smeared Energy: " << smE;

    return true;
  }

  
  //--------------------------------------------------------------------
  bool EnergySmearer::End()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "EnergySmearer::End()";

    delete fRand;

    return true;
  }

}
