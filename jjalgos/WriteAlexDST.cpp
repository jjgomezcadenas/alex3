#include "WriteAlexDST.hh"
#include <alex/ASvc.h>
#include <alex/TEvent.h>

namespace alex {

  //--------------------------------------------------------------------
  bool WriteAlexDST::Init()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot(); 
    klog << log4cpp::Priority::DEBUG << " WriteAlexDST::Init";
    SetDebugLevel(fDebug);

    klog << log4cpp::Priority::DEBUG << " Inst. TEvent";

    fAevent = new TEvent();
    std::stringstream s;

    s << fDstPath << "/" << fDstName;
    std::string filename = s.str();

    klog << log4cpp::Priority::INFO << " Alex DST file " 
    << filename;

    klog << log4cpp::Priority::DEBUG << " new TFile " ;

    fFile = new TFile(filename.c_str(), "RECREATE");

    klog << log4cpp::Priority::DEBUG << " Create Tree " ;

    fAevtTree = new TTree("AEVENT","Alex event tree");
    TTree::SetBranchStyle(1);

    klog << log4cpp::Priority::DEBUG << " Set Branch to event " ;

    fAevtTree->Branch("AEventBranch","alex::AEvent",&fAevent);
    
    return true;
  }
  //--------------------------------------------------------------------
  bool WriteAlexDST::Execute()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    SetDebugLevel(fDebug);

    klog << log4cpp::Priority::DEBUG << " WriteAlexDST::Execute";
    klog << log4cpp::Priority::DEBUG 
    << " Instantiate TEvent for event number " 
    << ASvc::Instance().GetEvtNum();

    fAevent->SetID(ASvc::Instance().GetEvtNum());

    klog << log4cpp::Priority::DEBUG 
    << " Set Event true energy to = " 
    << ASvc::Instance().GetTrueEventEnergy();

    fAevent->SetTrueEventEnergy(
      ASvc::Instance().GetTrueEventEnergy());

    klog << log4cpp::Priority::DEBUG 
    << " Set Event rec energy to = " 
    << ASvc::Instance().GetRecEventEnergy();

    fAevent->SetRecEventEnergy(
      ASvc::Instance().GetRecEventEnergy());


    // AParticles
    klog << log4cpp::Priority::DEBUG 
    << " Particles ";

    const std::vector <alex::AParticle*> aparticles = 
    ASvc::Instance().GetParticles();

    for (auto apart : aparticles)
    {
      fAevent->AddParticle(apart);
    }
    // // ATTracks

    // klog << log4cpp::Priority::DEBUG 
    // << " TTracks ";

    // const std::vector <alex::ATTrack*> atts = 
    // ASvc::Instance().GetTTracks();

    // for (auto att : atts)
    // {
    //   fAevent->AddTTrack(att);
    // }


    // // ARTracks
    
    // klog << log4cpp::Priority::DEBUG 
    // << " RTracks ";

    // const std::vector <alex::ARTrack*> arts = 
    // ASvc::Instance().GetRTracks();

    // for (auto art : arts)
    // {
    //   fAevent->AddRTrack(art);
    // }


// Fill Tree
    
    klog << log4cpp::Priority::DEBUG 
    << " Fill Tree ";
    
    fAevtTree->Fill();

    klog << log4cpp::Priority::DEBUG << " Clear event " ;

    fAevent->ClearEvent();

    return true;
  }
  //--------------------------------------------------------------------
  bool WriteAlexDST::End()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    SetDebugLevel(fDebug);

    klog << log4cpp::Priority::DEBUG << " WriteDST::END";

    klog << log4cpp::Priority::DEBUG << " Write and close";

    fFile->Write();
    fFile->Close();

    klog << log4cpp::Priority::DEBUG << " delete TEvent";
    delete fAevent;

    return true;
  }
}
