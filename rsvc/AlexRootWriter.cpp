
// ----------------------------------------------------------------------------
//  $Id: RootWriter.cc 9286 2013-10-04 12:43:34Z paola $
//
//  Author:  <paola.ferrario@ific.uv.es>
//  Created: 14 Feb 2013
//  
//  Copyright (c) 2013 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include <alex/AlexRootWriter.h>
//#include "ParameterInfo.h"

#include <sys/stat.h>

//#include <iostream>     
#include <sstream>

namespace alex {

  AlexRootWriter::AlexRootWriter()
  {
    fFile = 0;
    fAevtTree = 0;   
    fIsopen = false;
  }

  bool AlexRootWriter::Open(const std::string filename, std::string option)
  {
    if (fFile)
      delete fFile;

    // Check if the path exists
    std::istringstream iss(filename);
    std::vector<std::string> myline;
    std::string text;
    while (getline(iss, text, '/')) { 
      myline.push_back(text);
    }   

    std::string path;
    if (myline.size() == 1) {
      path = ".";
    }
    for (int i=0; i<myline.size()-1; ++i) {
      path.append(myline[i]);
      if (i != myline.size()-2)
	path.append("/");
    }
    
    struct stat st;
    if (stat(path.c_str(),&st) != 0)
      return false;

    fAevent = 0;
    fFile = new TFile(filename.c_str(), option.c_str());
    fAevtTree = new TTree("AEVENT","Alex event tree");
    TTree::SetBranchStyle(1);
    fAevtTree->Branch("AEventBranch","alex::AEvent",&fAevent);
    fIsopen = true;
  
    return true;
  }

  void AlexRootWriter::Close()
  {
    if (!fFile || !fFile->IsOpen())
      return;
    
    fFile->Write();
    fFile->Close();

    fIsopen = false;
  }

  void AlexRootWriter::Write(AEvent& event)
  {
    fAevent = &event;

    if (!fAevtTree)
      std::cout << "Event tree does not exist!" << std::endl;

    fAevtTree->Fill();
  }

  bool AlexRootWriter::IsOpen()
  {
    return fIsopen;
  }

  // void RootWriter::WriteMetadata(ParameterInfo* mdata)
  // {
  //   _evtTree->GetUserInfo()->Add(mdata);
  // }


}
