#include "RoadWidthFilter.hh"
#include <alex/ISvc.h>
#include <alex/PSvc.h>
#include <alex/ASvc.h>
#include <alex/ARTrack.h>
#include <alex/VectorOperations.h>

#include <TVector.h>
#include <TMatrix.h>

namespace alex {

  //--------------------------------------------------------------------
  bool RoadWidthFilter::Init()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);
    
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "RoadWidthFilter::Init()";
    klog << log4cpp::Priority::INFO << "RoadWidthFilter::Road Width = " << fRoadWidth;

    fNumInputEvents = fNumOutputEvents = 0;

    // Setting Histogram Bin Names
    fRoadWidthFilter_NumRoads_H1->GetXaxis()->SetBinLabel(2, "One");
    fRoadWidthFilter_NumRoads_H1->GetXaxis()->SetBinLabel(3, "More than One");

    return true;
  }

  
  //--------------------------------------------------------------------
  bool RoadWidthFilter::Execute()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "RoadWidthFilter::Execute()";

    fNumInputEvents += 1;

    /// If only one RTrack, No computing needed
    std::vector <ARTrack*> tracks = ASvc::Instance().GetRTracks();
    int numTracks = tracks.size();
    if (numTracks == 1) {
      klog << log4cpp::Priority::DEBUG << "RoadWidthFilter::Passed -> Just One RTrack";
      fNumOutputEvents += 1;
      fRoadWidthFilter_NumRoads_H1->Fill(1);
      return true;
    }

    /// Generating the Distance Matrix
    TMatrix distMatrix = TMatrix(numTracks, numTracks);
    for (int i=0; i<numTracks-1; i++) {
      for (int j=i+1; j<numTracks; j++) {
        double trkDist = ASvc::Instance().GetTracksDist(tracks[i], tracks[j]);
        distMatrix(i,j) = distMatrix(j,i) = trkDist;
        klog << log4cpp::Priority::DEBUG << "Dist (" << i << " , " << j << "): "
                                         << trkDist;
      }
    }

    /// Generating the Minimum Distance Vector
    TVector minDistVector(numTracks);
    for (int i=0; i<numTracks; i++) {
      double minDist = 1000.;
      for (int j=0; j<numTracks; j++) {
        if (i != j) 
          if (distMatrix(i,j) < minDist) minDist = distMatrix(i,j);
      }
      minDistVector(i) = minDist;
      klog << log4cpp::Priority::DEBUG << "Min Dist " << i << ": " << minDist;
    }

    /// First Check: Some RTrack Too Far From the Rest ??
    for (int i=0; i<numTracks; i++) {
      if (minDistVector(i) > fRoadWidth) {
        klog << log4cpp::Priority::DEBUG << "RoadWidthFilter::Failed -> RTrack: " << i
             << " too far from the rest";
        fRoadWidthFilter_NumRoads_H1->Fill(2);
        return false;
      }
    }

    /// At this point, If there are only 2 RTracks, they are connected
    if (numTracks == 2) {
      klog << log4cpp::Priority::DEBUG << "RoadWidthFilter::Passed -> 2 RTracks connected";
      fNumOutputEvents += 1;
      fRoadWidthFilter_NumRoads_H1->Fill(1);
      return true;
    }

    /// Second Check: All RTracks connected ??
    // Initializing vectors
    std::vector<int> connected;
    connected.push_back(0);
    std::vector<int> notConnected;
    for (int i=1; i<numTracks; i++) notConnected.push_back(i);

    // Checking connections
    bool gotConnection;
    do {
      gotConnection = false;
      for (int i=0; i<notConnected.size(); i++) {
        for (int j=0; j<connected.size(); j++) {
          double dist = distMatrix(notConnected[i], connected[j]);
          if (dist < fRoadWidth) {
            gotConnection = true;
            klog << log4cpp::Priority::DEBUG << "  Connection of "
                 << notConnected[i];
            connected.push_back(notConnected[i]);
            notConnected.erase(notConnected.begin()+i);
            break;
          }
        }
        if (gotConnection) break;
      }
    } while (gotConnection and (notConnected.size()>0));

    // If every RTrack is connected -> Evt OK
    int ncSize = notConnected.size();
    if (ncSize==0) {
      klog << log4cpp::Priority::DEBUG << "RoadWidthFilter::Passed -> All RTracks Connected Among Them";
      fNumOutputEvents += 1;
      fRoadWidthFilter_NumRoads_H1->Fill(1);
      return true;
    }
    else {
      klog << log4cpp::Priority::DEBUG << "RoadWidthFilter::Failed -> RTracks not Connected With The Others: "
           << VPrint(notConnected);
      fRoadWidthFilter_NumRoads_H1->Fill(2);
      return false;
    }

    fRoadWidthFilter_NumRoads_H1->Fill(2);
    return false;
  }

  
  //--------------------------------------------------------------------
  bool RoadWidthFilter::End()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "RoadWidthFilter::End()";
    klog << log4cpp::Priority::INFO << "RoadWidthFilter::fNumInputEvents:  " << fNumInputEvents;
    klog << log4cpp::Priority::INFO << "RoadWidthFilter::fNumOutputEvents: " << fNumOutputEvents;

    return true;
  }
}
