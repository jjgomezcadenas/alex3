
// ----------------------------------------------------------------------------
//  $Id: PSvc.cpp 
//
//  Author:  <gomez@mail.cern.ch>
//  Created: July 2014
//  
//  Copyright (c) 2014 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include <TStopwatch.h>
#include <alex/PSvc.h>
#include <alex/LogUtil.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>

using std::string; 
using std::cout; 
using std::endl; 
using std::ostream;
using std::vector;

namespace alex {

// //--------------------------------------------------------------------
//   void PaolinaManager::Init(std::string debugLevel, 
//     std::vector<double> voxel_size,
//     std::vector<double> left_range,std::vector<double> right_range, 
//     double rblob)
// //--------------------------------------------------------------------
//   {
//     fDebugLevel = debugLevel;
//     SetDebugLevel(debugLevel);
//     log4cpp::Category& klog = log4cpp::Category::getRoot();
//     klog << log4cpp::Priority::DEBUG 
 // << " PaolinaManager::Init() left/right range " ;

//     klog << log4cpp::Priority::DEBUG << " init Voxel Builder" ;
//     klog << log4cpp::Priority::DEBUG 
//       << " voxel_size[0] =" << voxel_size[0]
//       << " voxel_size[1] =" << voxel_size[1]
//       << " voxel_size[2] =" << voxel_size[2]
//       << " left_range[0] =" << left_range[0]
//       << " left_range[1] =" << left_range[1]
//       << " left_range[2] =" << left_range[2]
//       << " right_range[0] =" << right_range[0]
//       << " right_range[1] =" << right_range[1]
//       << " right_range[2] =" << right_range[2]
//       << " rblob  =" << rblob;
      

//     fPVB =new paolina::VoxelBuilder(voxel_size, left_range, right_range);
//     fPTB = new paolina::TrackBuilder();
//     fPBB = new paolina::BlobBuilder(rblob);
//     //ComputePaolinaVoxels();
//   }


//--------------------------------------------------------------------
  void PaolinaManager::Init(std::string debugLevel,
                            std::vector<double> voxelSize,
                            std::vector<std::pair<double,double> > detSize,
                            double blobRadius)
//--------------------------------------------------------------------
  {
    fPVB = new paolina::VoxelBuilder(voxelSize, detSize);
    fPTB = new paolina::TrackBuilder();
    fPBB = new paolina::BlobBuilder(blobRadius);
    fPaolina = false;
    //ComputePaolinaVoxels();
  }

//--------------------------------------------------------------------
  double PaolinaManager::ComputePaolinaObjects(
        std::vector<std::pair<TLorentzVector,double> > hits)
//--------------------------------------------------------------------  
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG 
    << " PaolinaManager::ComputePaolinaVoxels()" ;
  
    if(fPvoxels.size() > 0)
    {
      klog << log4cpp::Priority::DEBUG 
      << "Deleting previous voxel vector";
      
      for (size_t i=0; i < fPvoxels.size(); i++)
      delete fPvoxels.at(i); 
      fPvoxels.clear();
    }
    
  
    TStopwatch*  timer = new TStopwatch();
    timer->Start();

    klog << log4cpp::Priority::DEBUG << " Fill Voxel vector";

    fPvoxels = fPVB->FillVoxels(hits);

    klog << log4cpp::Priority::DEBUG << " IdentifyTracks";
    fPtracks = fPTB->IdentifyTracks(fPvoxels);

    klog << log4cpp::Priority::DEBUG << " MakeBlobs";
    fPblobs = fPBB->MakeBlobs(fPtracks.at(0));
    timer->Stop(); 

    double rtime = timer->RealTime();
    double cctime = timer->CpuTime();

    delete timer;

    klog << log4cpp::Priority::INFO << "Fill Voxels finds" 
         << fPvoxels.size()
         << "voxels" << " and  " << fPtracks.size() << " paolina tracks";

    klog << log4cpp::Priority::INFO << "RealTime =" << rtime << " seconds"
         << " CpuTime = " << cctime << "seconds";

    fPaolina = true;
    return cctime;
   
  }
//--------------------------------------------------------------------
  std::vector<std::pair<TVector3,double> > PaolinaManager::GetVoxels()
//--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG 
    << " PaolinaManager::GetVoxels()" ;

    if (not fPaolina)
    {
      klog << log4cpp::Priority::FATAL << "Paolina objects not computed";
      exit(-1);
    }

    std::vector<std::pair<TVector3,double> > theVoxels;
    for (auto vox : fPvoxels)
    { 
      std::pair<TVector3,double> theVox;
      const paolina::vector3<double> vpos = vox->GetPosition();
      
      //TVector3 theVector = vox->posvector();

      TVector3 theVector;
      
      theVector[0]= vpos.x();
      theVector[1]= vpos.y();
      theVector[2]= vpos.z();
      theVox.first = theVector;
      theVox.second =   vox->GetEDep(); 
      //theVox.second =   vox->EDep(); 
      theVoxels.push_back(theVox);   
    }   

    return theVoxels;
  }
//--------------------------------------------------------------------
  std::vector<paolina::Voxel*> PaolinaManager::GetPaolinaVoxels() 
//--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG 
    << " PaolinaManager::GetPaolinaVoxels()" ;
    if (not fPaolina)
    {
      klog << log4cpp::Priority::FATAL << "Paolina objects not computed";
      exit(-1);
    }

    return fPvoxels;
  }
//--------------------------------------------------------------------
  std::vector<paolina::Track*> PaolinaManager::GetPaolinaTracks()
//--------------------------------------------------------------------  
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << 
    " PaolinaManager::GetPaolinaTracks()" ;
  
    if (not fPaolina)
    {
      klog << log4cpp::Priority::FATAL << "Paolina objects not computed";
      exit(-1);
    }

    return fPtracks;
  }

//--------------------------------------------------------------------
  std::pair<paolina::Blob*, paolina::Blob*> PaolinaManager::GetPaolinaBlobs()
//--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG 
    << " PaolinaManager::GetPaolinaBlobs()" ;

    if (not fPaolina)
    {
      klog << log4cpp::Priority::FATAL << "Paolina objects not computed";
      exit(-1);
    }
  
    return fPblobs;
  }
//--------------------------------------------------------------------
  std::string PaolinaManager::PrintVoxels()
//--------------------------------------------------------------------
  {
    std::ostringstream s;
    s << std::endl;

    s << " Paolina Voxels: " << std::endl;

    std::vector<std::pair<TVector3,double> > theVoxels;
    for (auto vox : fPvoxels)
    { 
      std::pair<TVector3,double> theVox;
      const paolina::vector3<double> vpos = vox->GetPosition();
      double edep =   vox->GetEDep();

      s 
           << " x (mm) = " << vpos.x()
           << " y (mm) = " << vpos.y()
           << " z (mm) = " << vpos.z()
           << " edep (MeV) = " << edep << std::endl;    
    }
    return s.str();   
  }
}
