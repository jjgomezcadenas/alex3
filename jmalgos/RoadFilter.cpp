#include "RoadFilter.hh"
#include <alex/ISvc.h>
#include <alex/PSvc.h>
#include <alex/ASvc.h>
#include <alex/ARTrack.h>


namespace alex {

  //--------------------------------------------------------------------
  bool RoadFilter::Init()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel("INFO");
    
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "RoadFilter::Init()";
    klog << log4cpp::Priority::INFO << "RoadFilter::Detector X Size = " << fMinDetX << " , " << fMaxDetX;
    klog << log4cpp::Priority::INFO << "RoadFilter::Detector Y Size = " << fMinDetY << " , " << fMaxDetY;
    klog << log4cpp::Priority::INFO << "RoadFilter::Detector Z Size = " << fMinDetZ << " , " << fMaxDetZ;
    klog << log4cpp::Priority::INFO << "RoadFilter::Road Width = " << fRoadWidth;

    fNumInputEvents = fNumOutputEvents = 0;

    fVoxelSize.push_back(fRoadWidth);
    fVoxelSize.push_back(fRoadWidth);
    fVoxelSize.push_back(fRoadWidth);

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

    return true;
  }

  
  //--------------------------------------------------------------------
  bool RoadFilter::Execute()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "RoadFilter::Execute()";

    fNumInputEvents += 1;

    std::vector<std::pair<TVector3,double> >  voxels;
    voxels = PSvc::Instance().ComputePaolinaVoxels(ISvc::Instance().GetTrueHits(), fVoxelSize);
    std::vector<paolina::Track*> tracks;
    int numTracks = 0;
    if (voxels.size() > 0) {
      tracks = PSvc::Instance().ComputePaolinaTracks();
      numTracks = tracks.size();
      fRoadFilter_NumRoads_H1->Fill(numTracks);
      klog << log4cpp::Priority::DEBUG << "RoadFilter::Num Roads: " << numTracks;
    }


    if (numTracks == 1) {
      fNumOutputEvents += 1;
      return true;
    }

    return false;
  }

  
  //--------------------------------------------------------------------
  bool RoadFilter::End()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "RoadFilter::End()";
    klog << log4cpp::Priority::INFO << "RoadFilter::fNumInputEvents:  " << fNumInputEvents;
    klog << log4cpp::Priority::INFO << "RoadFilter::fNumOutputEvents: " << fNumOutputEvents;

    return true;
  }
}
