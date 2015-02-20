#include "Voxelizer.hh"
#include <alex/ISvc.h>
#include <alex/PSvc.h>
#include <alex/ASvc.h>
#include <alex/ARTrack.h>
#include <alex/AHit.h>


namespace alex {

  //--------------------------------------------------------------------
  bool Voxelizer::Init()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel("INFO");
    
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "Voxelizer::Init()";
    klog << log4cpp::Priority::INFO << "Voxelizer::Detector X Size = " << fMinDetX << " , " << fMaxDetX;
    klog << log4cpp::Priority::INFO << "Voxelizer::Detector Y Size = " << fMinDetY << " , " << fMaxDetY;
    klog << log4cpp::Priority::INFO << "Voxelizer::Detector Z Size = " << fMinDetZ << " , " << fMaxDetZ;
    klog << log4cpp::Priority::INFO << "Voxelizer::Voxel Size  = " << fVoxelX << " , " << fVoxelY << " , " << fVoxelZ;
    klog << log4cpp::Priority::INFO << "Voxelizer::Mimimum Energy  = " << fEmin;

    fVoxelSize.push_back(fVoxelX);
    fVoxelSize.push_back(fVoxelY);
    fVoxelSize.push_back(fVoxelZ);

    std::pair<double,double> xRange;
    std::pair<double,double> yRange;
    std::pair<double,double> zRange;
    std::vector< std::pair<double,double> > detSize;

    xRange.first  = fMinDetX;
    xRange.second = fMaxDetX;
    yRange.first  = fMinDetY;
    yRange.second = fMaxDetY;
    zRange.first  = fMinDetZ;
    zRange.second = fMaxDetZ;

    detSize.push_back(xRange);
    detSize.push_back(yRange);
    detSize.push_back(zRange);

    // Init Paolina Stuff
    PSvc::Instance().Init("INFO", detSize);

    return true;
  }

  
  //--------------------------------------------------------------------
  bool Voxelizer::Execute()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "Voxelizer::Execute()";

    std::vector<std::pair<TVector3,double> >  voxels;
    voxels = PSvc::Instance().ComputePaolinaVoxels(ISvc::Instance().GetTrueHits(), fVoxelSize);
    int numVoxels = voxels.size();
    fVoxelizer_NumVoxels_H1->Fill(numVoxels);
    klog << log4cpp::Priority::DEBUG << "Voxelizer::Num Voxels: " << numVoxels;

    std::vector<paolina::Track*> tracks;
    if (numVoxels > 0) {
      tracks = PSvc::Instance().ComputePaolinaTracks();
      int numTracks = tracks.size();
      fVoxelizer_NumTracks_H1->Fill(numTracks);
      klog << log4cpp::Priority::DEBUG << "Voxelizer::Num Tracks: " << numTracks;
    }

    // Convertion from Paolina Tracks to ARTracks
    for (int t=0; t<tracks.size(); t++) {
      ARTrack* arTrk = new ARTrack(t);
      paolina::Track* pTrk = tracks[t];

      std::cout << "True Energy from Paolina Track: " << pTrk->GetEDep() << std::endl;

      // Converting from Paolina Voxels to AHits
      for (int v=0; v<pTrk->NVoxels(); v++) {
        AHit* ahit = new AHit();
        const paolina::Voxel* pVxl = pTrk->GetVoxel(v);
        ahit->SetID(v);
        TVector3 pos;
        pos.SetXYZ(pVxl->GetPosition().x(),
                   pVxl->GetPosition().y(),
                   pVxl->GetPosition().z());
        ahit->SetPosition(pos);
        ahit->SetEdep(pVxl->GetEDep());
        arTrk->AddHit(ahit);
      }

      // As origin True Tracks are unknown, set to -1
      arTrk->AddTTrackID(-1);

      // Setting Spatial Energy
      arTrk->SetSpatialRes(TVector3(fVoxelX, fVoxelY, fVoxelZ));

      // Setting Extremes
      std::pair <int, int> pExtremes = pTrk->GetExtremes();
      AHit* hit1 = arTrk->GetHit(pExtremes.first);
      AHit* hit2 = arTrk->GetHit(pExtremes.second);
      arTrk->SetExtreme1(new AHit(*hit1));
      arTrk->SetExtreme2(new AHit(*hit2));

      // Adding Ordered hits
      for (int v=0; v<pTrk->NMainPathVoxels(); v++) {
        const paolina::Voxel* pVxl = pTrk->GetMainPathVoxel(v);
        for (auto hit: arTrk->GetHits()) {
          if ( (hit->GetEdep() == pVxl->GetEDep()) and
               (hit->GetPosition().x() == pVxl->GetPosition().x()) and
               (hit->GetPosition().y() == pVxl->GetPosition().y()) and
               (hit->GetPosition().z() == pVxl->GetPosition().z()) ) {
            arTrk->AddOrdHit(hit);
            break;
          }
        } 
      }

      //arTrk->DisplayInfo(std::cout);
      ASvc::Instance().AddRTrack(arTrk);
    }

    return true;
  }

  
  //--------------------------------------------------------------------
  bool Voxelizer::End()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "Voxelizer::End()";

    return true;
  }
}
