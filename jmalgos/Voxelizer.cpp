#include "Voxelizer.hh"
#include <alex/ISvc.h>
#include <alex/PSvc.h>
#include <alex/ASvc.h>
#include <alex/ARTrack.h>


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
    SetDebugLevel("INFO");

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

      // Adding Ordered hits
      //std::cout << pTrk->NVoxels() << " " << pTrk->NMainPathVoxels() << std::endl;

      // As origin True Tracks are unknown, set to -1
      arTrk->AddTTrackID(-1);

      // Setting Extremes
      //arTrk->SetExtreme1();
      //arTrk->SetExtreme2();

      //arTrk->DisplayInfo(std::cout);
      ASvc::Instance().AddRTrack(arTrk);
    }

    SetDebugLevel("INFO");

    return true;
  }

  
  //--------------------------------------------------------------------
  bool Voxelizer::End()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "Voxelizer::End()";
    klog << log4cpp::Priority::INFO << "Voxelizer::Number of events with 1 Track: " 
      << fVoxelizer_NumTracks_H1->GetBinContent(2);

    return true;
  }
}
