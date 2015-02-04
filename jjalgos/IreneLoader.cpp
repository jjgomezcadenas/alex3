/////////////////////////////////////////////////////////////////// Algorithm reading the Irene Events and filling Alex Classes:// AHits, AParticles and ATTracks.// Persistency is made by ASvc./////////////////////////////////////////////////////////////////#include "IreneLoader.hh"#include <alex/ISvc.h>#include <alex/PSvc.h>#include <alex/ASvc.h>#include <alex/ATTrack.h>#include <alex/AParticle.h>#include <alex/AHit.h>namespace alex {  //--------------------------------------------------------------------  bool IreneLoader::Init()  //--------------------------------------------------------------------  {    // Set the Debug Level    SetDebugLevel("DEBUG");    log4cpp::Category& klog = log4cpp::Category::getRoot();    klog << log4cpp::Priority::INFO << "IreneLoader::Init()" ;    fTracks = 0;    fParticles =0;    return true;  }    //--------------------------------------------------------------------  bool IreneLoader::Execute()  //--------------------------------------------------------------------  {    log4cpp::Category& klog = log4cpp::Category::getRoot();    klog << log4cpp::Priority::DEBUG << "IreneLoader::Execute()";    // Getting Irene Tracks    klog << log4cpp::Priority::DEBUG << "+++Get tracks from ISvc";    // ITracks =std::vector<const irene::Track*>     ITracks iTracks = ISvc::Instance().GetTracks();    IParticles iParticles = ISvc::Instance().GetParticles();    klog << log4cpp::Priority::DEBUG << "Clear vectors in ASvc";    // Clear Alex Service    ASvc::Instance().Clear();    // ATTrack    for (int t=0; t<iTracks.size(); t++)     {      fTracks++;      klog << log4cpp::Priority::DEBUG << "Adding track " << t ;      const irene::Track* iTrack = iTracks.at(t);      const irene::Particle* iPart = iTrack->GetParticle();      ATTrack* track = new ATTrack();      int id = iPart->GetParticleID();      track->SetID(id);      track->SetParticleID(id);      // AHits      IHits iHits = iTrack->GetHits();      for (int h=0; h<iHits.size(); h++)       {      	const std::pair<TLorentzVector,double> iHit = iHits[h];      	AHit* aHit = new AHit();      	aHit->SetID(h);      	aHit->SetPosition(iHit.first.Vect());      	aHit->SetEdep(iHit.second);      	track->AddHit(aHit);        if (h==0) track->SetExtreme1(aHit);        if (h==iHits.size()-1) track->SetExtreme2(aHit);              	delete aHit;      }      ASvc::Instance().AddTTrack(track);      delete track;    }      // AParticles    for (int t=0; t<iParticles.size(); t++)     {      fParticles++;      klog << log4cpp::Priority::DEBUG << "Adding particle " << t ;      const irene::Particle* iPart = iParticles.at(t);	    AParticle* aPart = new AParticle();      aPart->SetID(iPart->GetParticleID());      aPart->SetName(iPart->Name());      aPart->SetCharge(iPart->GetCharge());      aPart->SetVertex(iPart->GetInitialVertex().Vect());      aPart->SetP4(iPart->GetInitialMomentum());      aPart->SetIsPrimary(iPart->IsPrimary());      aPart->SetMotherID(0);      if (!aPart->GetIsPrimary())        aPart->SetMotherID(iPart->GetMother()->GetParticleID());      aPart->SetProperty("CreatorProcess", iPart->GetCreatorProcess());      aPart->SetProperty("TrackLength", std::to_string(iPart->GetTrackLength()));      // Persistency      ASvc::Instance().AddParticle(aPart);            //klog << log4cpp::Priority::DEBUG << track->PrintInfo();      //klog << log4cpp::Priority::DEBUG << aPart->PrintInfo();      delete aPart;                }    const std::vector <AParticle*> ps = ASvc::Instance().GetParticles();    std::cout << std::endl << "*********************" << std::endl;    std::cout << "Num particles in ASvc: " << ps.size();    std::cout << std::endl << "*********************" << std::endl;    return true;  }    //--------------------------------------------------------------------  bool IreneLoader::End()  //--------------------------------------------------------------------  {    log4cpp::Category& klog = log4cpp::Category::getRoot();    klog << log4cpp::Priority::INFO << "IreneLoader::End()";    klog << log4cpp::Priority::INFO << "Number of tracks loadded" << fTracks;    klog << log4cpp::Priority::INFO << "Number of particles loaded" << fParticles;    return true;  }}