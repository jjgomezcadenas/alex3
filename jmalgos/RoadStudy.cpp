#include "RoadStudy.hh"
#include <alex/ISvc.h>
#include <alex/PSvc.h>
#include <alex/ASvc.h>
#include <alex/ARTrack.h>


namespace alex {

  //--------------------------------------------------------------------
  bool RoadStudy::Init()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel("INFO");
    
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "RoadStudy::Init()";
    klog << log4cpp::Priority::INFO << "RoadStudy::Detector X Size = " << fMinDetX << " , " << fMaxDetX;
    klog << log4cpp::Priority::INFO << "RoadStudy::Detector Y Size = " << fMinDetY << " , " << fMaxDetY;
    klog << log4cpp::Priority::INFO << "RoadStudy::Detector Z Size = " << fMinDetZ << " , " << fMaxDetZ;
    klog << log4cpp::Priority::INFO << "RoadStudy::Studying Widths from "
         << fMinWidth << " to " << fMaxWidth << " mm";

    std::pair<double,double> xRange;
    std::pair<double,double> yRange;
    std::pair<double,double> zRange;
    xRange.first  = fMinDetX;
    xRange.second = fMaxDetX;
    yRange.first  = fMinDetY;
    yRange.second = fMaxDetY;
    zRange.first  = fMinDetZ;
    zRange.second = fMaxDetZ;

    std::vector< std::pair<double,double> > detSize;
    detSize.push_back(xRange);
    detSize.push_back(yRange);
    detSize.push_back(zRange);

    // Init Paolina Stuff
    PSvc::Instance().Init("INFO", detSize);

    // Setting Titles to Histogram Axis
    fRoadStudy_Evts1Road_H1->SetXTitle("Road Width [mm]");

    return true;
  }

  
  //--------------------------------------------------------------------
  bool RoadStudy::Execute()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "RoadStudy::Execute()";

    // METHOD BASED ON PAOLINA
    for (int width=fMinWidth; width<fMaxWidth+1; width++) {
      std::vector<double> fVoxelSize;
      fVoxelSize.push_back(width);
      fVoxelSize.push_back(width);
      fVoxelSize.push_back(width);

      std::vector<std::pair<TVector3,double> >  voxels;
      voxels = PSvc::Instance().ComputePaolinaVoxels(ISvc::Instance().GetTrueHits(), fVoxelSize);
      if (voxels.size() > 0) {
        std::vector<paolina::Track*> tracks = PSvc::Instance().ComputePaolinaTracks();
        if (tracks.size() == 1) fRoadStudy_Evts1Road_H1->AddBinContent(width+1);
      }
    }


/*
    // METHOD BASED ON EUCLIDEAN DISTANCE OF RTracks
    std::vector <ARTrack*> tracks = ASvc::Instance().GetRTracks();
    int numTracks = tracks.size();
    double evtMaxDist = 0.;
    for (int i=0; i<numTracks-1; i++) {
      for (int j=i+1; j<numTracks; j++) {
        double trkDist = GetMinDistance(tracks[i], tracks[j]);
        klog << log4cpp::Priority::DEBUG << "RoadStudy::Distance from RTrk " << i
             << " to RTrk " << j << ": " << trkDist;
        if (trkDist > evtMaxDist) evtMaxDist = trkDist;
      }
    }

    for (int width=fMinWidth; width<fMaxWidth+1; width++) {
      if (evtMaxDist <= width) fRoadStudy_Evts1Road_H1->AddBinContent(width+1);
    }
*/
    
    return true;
  }

  
  //--------------------------------------------------------------------
  bool RoadStudy::End()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "RoadStudy::End()";
    klog << log4cpp::Priority::INFO << "RoadStudy::Number of events with just One Road:";
    for (int width=fMinWidth; width<fMaxWidth+1; width++)
      klog << log4cpp::Priority::INFO << "           Width: "
           << width << " -> " << fRoadStudy_Evts1Road_H1->GetBinContent(width+1);

    return true;
  }


  //--------------------------------------------------------------------
  double PRoadStudy::GetMinDistance(ARTrack* trk1, ARTrack* trk2)
  //--------------------------------------------------------------------
  {
    double trksDist = 1000.;

    for (auto hit1 : trk1->GetHits()) {
      TVector3 pos1 = hit1->GetPosition();
      for (auto hit2 : trk2->GetHits()) {
        TVector3 pos2 = hit2->GetPosition();
        TVector3 distV = pos1 - pos2;
        double hitsDist = distV.Mag();
        if (hitsDist < trksDist) trksDist = hitsDist;
      }
    }
    return trksDist;
  }

}
