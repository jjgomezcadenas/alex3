#include "RoadWidthStudy.hh"
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
  bool RoadWidthStudy::Init()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "RoadWidthStudy::Init()";
    klog << log4cpp::Priority::INFO << "RoadWidthStudy::Detector X Size = " << fMinDetX << " , " << fMaxDetX;
    klog << log4cpp::Priority::INFO << "RoadWidthStudy::Detector Y Size = " << fMinDetY << " , " << fMaxDetY;
    klog << log4cpp::Priority::INFO << "RoadWidthStudy::Detector Z Size = " << fMinDetZ << " , " << fMaxDetZ;
    klog << log4cpp::Priority::INFO << "RoadWidthStudy::Studying Widths from "
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
    fRoadWidthStudy_Evts1Road_H1->SetXTitle("Road Width [mm]");

    return true;
  }

  
  //--------------------------------------------------------------------
  bool RoadWidthStudy::Execute()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "RoadWidthStudy::Execute()";

    // If only one RTrack, No computing needed
    std::vector <ARTrack*> tracks = ASvc::Instance().GetRTracks();
    int numTracks = tracks.size();
    if (numTracks == 1) {
      for (int width=fMinWidth; width<fMaxWidth+1; width++)
        fRoadWidthStudy_Evts1Road_H1->AddBinContent(width+1);
      return true;
    }

/*
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
        if (tracks.size() == 1) fRoadWidthStudy_Evts1Road_H1->AddBinContent(width+1);
      }
    }
*/

    // METHOD BASED ON EUCLIDEAN DISTANCE OF RTracks
    // Generating the Distance Matrix
    TMatrix distMatrix = TMatrix(numTracks, numTracks);
    for (int i=0; i<numTracks-1; i++) {
      for (int j=i+1; j<numTracks; j++) {
        double trkDist = ASvc::Instance().GetTracksDist(tracks[i], tracks[j]);
        distMatrix(i,j) = distMatrix(j,i) = trkDist;
        //std::cout << "Dist (" << i << " , " << j << "): " << trkDist << std::endl;
      }
    }

    // Generating the Minimum Distance Vector
    TVector minDistVector(numTracks);
    for (int i=0; i<numTracks; i++) {
      double minDist = 1000.;
      for (int j=0; j<numTracks; j++) {
        if (i != j) 
          if (distMatrix(i,j) < minDist) minDist = distMatrix(i,j);
      }
      minDistVector(i) = minDist;
      //std::cout << "Min Dist " << i << ": " << minDist << std::endl;
    }

    // Starting the study for every Width
    for (int width=fMinWidth; width<fMaxWidth+1; width++) {
      //std::cout << "Study of Width: " << width << std::endl;

      // First Check: Some RTrack Too Far From the Rest ??
      bool firstCheck = true;
      for (int i=0; i<numTracks; i++) {
        if (minDistVector(i) > width) {
          firstCheck = false;
          //std::cout << "First Check False for RTrack: " << i << std::endl;
          break;
        }
      }

      // Second Check: All RTracks connected ??
      if (firstCheck == true) {
        // If there are only 2, they are connected
        if (numTracks == 2) fRoadWidthStudy_Evts1Road_H1->AddBinContent(width+1);

        else {
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
                if (dist < width) {
                  gotConnection = true;
                  //std::cout << "  Connection of " << notConnected[i] << std::endl;
                  connected.push_back(notConnected[i]);
                  notConnected.erase(notConnected.begin()+i);
                  break;
                }
              }
              if (gotConnection) break;
            }
            //std::cout << "Sizes: " << connected.size() << " " << notConnected.size() << std::endl;
          } while (gotConnection and (notConnected.size()>0));

          // If every RTrack is connected -> Evt OK
          int nons = notConnected.size();
          if (nons==0) {
            fRoadWidthStudy_Evts1Road_H1->AddBinContent(width+1);
            //std::cout << "All RTracks Connected Among Them" << std::endl;
          }
          //else {
          //  std::cout << "RTracks not Connected With The Others: ";
          //  for (int i=0; i<nons; i++) std::cout << notConnected[i] << ", ";
          //  std::cout << std::endl;
          //}

        }
      }
    } // Widths
    
   
    return true;
  }

  
  //--------------------------------------------------------------------
  bool RoadWidthStudy::End()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "RoadWidthStudy::End()";
    klog << log4cpp::Priority::INFO << "RoadWidthStudy::Number of events with just One Road:";
    for (int width=fMinWidth; width<fMaxWidth+1; width++)
      klog << log4cpp::Priority::INFO << "           Width: "
           << width << " -> " << fRoadWidthStudy_Evts1Road_H1->GetBinContent(width+1);

    return true;
  }

}
