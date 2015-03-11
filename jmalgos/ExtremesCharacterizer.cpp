#include "ExtremesCharacterizer.hh"
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
  bool ExtremesCharacterizer::Init()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "ExtremesCharacterizer::Init()";

    fExtremesCharacterizer_BlobRad_Blob2E_H2->SetOption("COLZ");

    return true;
  }

  
  //--------------------------------------------------------------------
  bool ExtremesCharacterizer::Execute()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "ExtremesCharacterizer::Execute()";

    // Getting Hottest RTrack
    std::vector <ARTrack*> rTracks = ASvc::Instance().GetRTracks();
    double maxEdep = 0.;
    ARTrack* hRTrack;
    for (auto rTrack: rTracks) {
      double eDep = rTrack->GetEdep();
      if (eDep > maxEdep) {
        maxEdep = eDep;
        hRTrack = rTrack;
      }
    }

    ///// Distance from Rec to True Extremes
    TVector3 rPos1, rPos2;
    TVector3 tPos1, tPos2;
    double dist1, dist2;

    // Getting the Reconstructed Extremes Positions
    const std::pair<AHit*, AHit*> rExtremes = hRTrack->GetExtremes();
    rPos1 = rExtremes.first->GetPosition();
    rPos2 = rExtremes.second->GetPosition();

    klog << log4cpp::Priority::DEBUG << "ExtremesCharacterizer::Hottest RTrack ID: " << hRTrack->GetID()
         << "  Extreme1: (" << rPos1.x() << " , " << rPos1.y() << " , " << rPos1.z()
         << ")  Extreme2: (" << rPos2.x() << " , " << rPos2.y() << " , " << rPos2.z() << ")";


    // Getting the True Extreme Positions
    std::vector <int> tTrackIDs = hRTrack->GetTTrackIDs();

    // Checking if event is signal or background
    // And if signal, getting the extremes
    bool isSignal = false;
    int numPrim = 0;
    for (auto tTrackID: tTrackIDs) {
      ATTrack* tTrack  = ASvc::Instance().GetTTrack(tTrackID);
      AParticle* tPart = ASvc::Instance().GetParticle(tTrack->GetParticleID());
      if (tPart->GetIsPrimary()) {
        isSignal = true;
        numPrim += 1;
        if (numPrim == 1) {
          tPos1 = tTrack->GetExtreme2()->GetPosition();
          klog << log4cpp::Priority::DEBUG << "ExtremesCharacterizer::Primary 1 TTrack ID: " << tTrack->GetID()
               << "  Final Extreme: (" << tPos1.x() << " , " << tPos1.y() << " , " << tPos1.z() << ")";
        }
        if (numPrim == 2) {
          tPos2 = tTrack->GetExtreme2()->GetPosition();
          klog << log4cpp::Priority::DEBUG << "ExtremesCharacterizer::Primary 2 TTrack ID: " << tTrack->GetID()
               << "  Final Extreme: (" << tPos2.x() << " , " << tPos2.y() << " , " << tPos2.z() << ")";
          break;
        }
      }
    }

    // It is background
    if (numPrim == 0) {
      // Getting Hottest TTrack from Hottest RTrack
      maxEdep = 0.;
      ATTrack* hTTrack;
      for (auto tTrackID: tTrackIDs){
        ATTrack* tTrack = ASvc::Instance().GetTTrack(tTrackID);
        double eDep = tTrack->GetEdep();
        if (eDep > maxEdep) {
          maxEdep = eDep;
          hTTrack = tTrack;
        }
      }

      // Getting the True Extremes Positions
      const std::pair<AHit*, AHit*> tExtremes = hTTrack->GetExtremes();
      tPos1 = tExtremes.first->GetPosition();
      tPos2 = tExtremes.second->GetPosition();

      klog << log4cpp::Priority::DEBUG << "ExtremesCharacterizer::Hottest TTrack ID: " << hTTrack->GetID()
           << "  Extreme1: (" << tPos1.x() << " , " << tPos1.y() << " , " << tPos1.z()
           << ")  Extreme2: (" << tPos2.x() << " , " << tPos2.y() << " , " << tPos2.z() << ")";
    }

    // Matching Rec & True extremes
    TVector3 dist = rPos1 - tPos1;
    double d11 = dist.Mag();
    dist = rPos1 - tPos2;
    double d12 = dist.Mag();
    if (d11 < d12) {
      dist1 = d11;
      dist = rPos2 - tPos2;
      dist2 = dist.Mag();
    }
    else {
      dist1 = d12;
      dist = rPos2 - tPos1;
      dist2 = dist.Mag();
    }

    klog << log4cpp::Priority::DEBUG << "ExtremesCharacterizer::Distance1: " << dist1 
         << "  Distance2: " << dist2;

    fExtremesCharacterizer_DistTrueRec_H1->Fill(dist1);
    fExtremesCharacterizer_DistTrueRec_H1->Fill(dist2);



    ///// Study of Blob Radius vs Blob2E
    int numRads = fExtremesCharacterizer_BlobRad_Blob2E_H2->GetXaxis()->GetNbins();
    std::vector <double> eBlob1;
    std::vector <double> eBlob2;
    for (int rad=0; rad<numRads; rad++) {
      eBlob1.push_back(0.);
      eBlob2.push_back(0.);
    }

    for (auto rHit: hRTrack->GetHits()) {
      TVector3 hPos = rHit->GetPosition();
      double hitE = rHit->GetEdep();
      dist1 = (rPos1 - hPos).Mag();
      dist2 = (rPos2 - hPos).Mag();
      for (int rad=0; rad<numRads; rad++) {
        if (dist1 < rad) eBlob1[rad] += hitE;
        if (dist2 < rad) eBlob2[rad] += hitE;
      }
    }

    for (int rad=0; rad<numRads; rad++) {
      double e1 = eBlob1[rad];
      double e2 = eBlob2[rad];
      if (e1 < e2) fExtremesCharacterizer_BlobRad_Blob2E_H2->Fill(rad+1, e1);
      else fExtremesCharacterizer_BlobRad_Blob2E_H2->Fill(rad+1, e2);
    }

    return true;
  }


  //--------------------------------------------------------------------
  bool ExtremesCharacterizer::End()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "ExtremesCharacterizer::End()";

    return true;
  }

}
