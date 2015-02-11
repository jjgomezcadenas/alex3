#include "EnergySmearer.hh"
#include <alex/ASvc.h>
#include <alex/ARTrack.h>


namespace alex {

  //--------------------------------------------------------------------
  bool EnergySmearer::Init()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel("INFO");
    
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
    const std::vector <ARTrack*> rtracks = ASvc::Instance().GetRTracks();
    for (auto track : rtracks) {
      for (auto hit : track->GetHits()) {
        hit->SetEdep(hit->GetEdep() * voxelFactor);
      }
    }
*/

    double smE = 0.;
    for (auto track : ASvc::Instance().GetRTracks()) {
      double trueTrkE = track->GetEdep();
      // Scaling FWHM at Qbb to Sigma at True Energy
      double sigmaE = ((fFWHM/100.) * sqrt(fQbb) * sqrt(trueTrkE)) / fFWHM2Sigma;
      double smTrkE = trueTrkE + fRand->Gaus(0., 1.) * sigmaE;
      smE += smTrkE;
      //std::cout << "RTrack Smered Energy: " << smTrkE << std::endl;

      // Updating Energy of Voxels from Reconstructed Tracks
      double voxelFactor = smTrkE / trueTrkE;
      for (auto hit : track->GetHits()) hit->SetEdep(hit->GetEdep() * voxelFactor);
    }

    ASvc::Instance().SetRecEventEnergy(smE);
    fEnergySmearer_SmEdep_H1->Fill(smE);
    klog << log4cpp::Priority::DEBUG << "EnergySmearer::Smeared Energy: " << smE;

    return true;
  }

  
  //--------------------------------------------------------------------
  bool EnergySmearer::End()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "EnergySmearer::End()";

    delete fRand;

    return true;
  }

}
