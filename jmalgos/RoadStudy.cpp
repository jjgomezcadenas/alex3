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

    for (int width=fMinWidth; width<fMaxWidth+1; width++) {
      std::vector<double> fVoxelSize;
      fVoxelSize.push_back(width);
      fVoxelSize.push_back(width);
      fVoxelSize.push_back(width);

      std::vector<std::pair<TVector3,double> >  voxels;
      voxels = PSvc::Instance().ComputePaolinaVoxels(ISvc::Instance().GetTrueHits(), fVoxelSize);
      if (voxels.size() > 0) {
        std::vector<paolina::Track*> tracks = PSvc::Instance().ComputePaolinaTracks();
        //std::cout << "Width " << width << " -> Roads: " << tracks.size() << std::endl;
        if (tracks.size() == 1) fRoadStudy_Evts1Road_H1->AddBinContent(width+1);
      }
    }

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
}
