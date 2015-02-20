#include "TestAlex.hh"#include <alex/ISvc.h>#include <alex/PSvc.h>#include <alex/ASvc.h>#include <alex/ATTrack.h>#include <alex/AParticle.h>#include <alex/AHit.h>namespace alex {  void CheckATTrack(ATTrack* track, const irene::Track* iTrack);  void CheckAParticle(AParticle* aPart, const irene::Particle* iPart);  void CheckAHit(AHit* aHit, const std::pair<TLorentzVector,double> iHit);  //--------------------------------------------------------------------  bool TestAlex::Init()  //--------------------------------------------------------------------  {    // Setting the Debug Level    SetDebugLevel("DEBUG");    log4cpp::Category& klog = log4cpp::Category::getRoot();    klog << log4cpp::Priority::INFO << "TestAlex::Init()" ;    klog << log4cpp::Priority::INFO << "TestAlex::Test Alex TTracks = " << fTestATTrack;    klog << log4cpp::Priority::INFO << "TestAlex::Test Alex Particles = " << fTestAParticle;    klog << log4cpp::Priority::INFO << "TestAlex::Test Alex Hits = " << fTestAHit;    return true;  }    //--------------------------------------------------------------------  bool TestAlex::Execute()  //--------------------------------------------------------------------  {    log4cpp::Category& klog = log4cpp::Category::getRoot();    klog << log4cpp::Priority::DEBUG << "TestAlex::Execute()";    std::vector<const irene::Track*> iTracks;    iTracks = ISvc::Instance().GetEvent().Tracks();    // ATTrack    for (int t=0; t<iTracks.size(); t++) {      const irene::Track* iTrack = iTracks.at(t);      const irene::Particle* iPart = iTrack->GetParticle();      ATTrack* track = new ATTrack();      int id = iPart->GetParticleID();      track->SetID(id);      track->SetParticleID(id);      // AHits      const std::vector<std::pair<TLorentzVector,double> >& iHits = iTrack->GetHits();      for (int h=0; h<iHits.size(); h++) {      	const std::pair<TLorentzVector,double> iHit = iHits[h];      	AHit* aHit = new AHit();      	aHit->SetID(h);      	aHit->SetPosition(iHit.first.Vect());      	aHit->SetEdep(iHit.second);      	track->AddHit(aHit);        if (h==0) track->SetExtreme1(aHit);        if (h==iHits.size()-1) track->SetExtreme2(aHit);              	//aHit->DisplayInfo(std::cout);      	if (fTestAHit) CheckAHit(aHit, iHit);      }      // AParticle	    AParticle* aPart = new AParticle();      aPart->SetID(iPart->GetParticleID());      aPart->SetParticleName(iPart->Name());      aPart->SetCharge(iPart->GetCharge());      aPart->SetVertex(iPart->GetInitialVertex().Vect());      aPart->SetP4(iPart->GetInitialMomentum());      aPart->SetIsPrimary(iPart->IsPrimary());      aPart->SetMotherID(0);      if (!aPart->GetIsPrimary())        aPart->SetMotherID(iPart->GetMother()->GetParticleID());      aPart->SetProperty("Using_Setters", "Yes");      aPart->SetProperty("Using_Constructor", "No");      aPart->SetProperty("Creator_Process", iPart->GetCreatorProcess());      //aPart->DisplayInfo(std::cout);      if (fTestAParticle) CheckAParticle(aPart, iPart);      //track->DisplayInfo(std::cout);      if (fTestATTrack) CheckATTrack(track, iTrack);    }    return true;  }    //--------------------------------------------------------------------  bool TestAlex::End()  //--------------------------------------------------------------------  {    log4cpp::Category& klog = log4cpp::Category::getRoot();    klog << log4cpp::Priority::INFO << "TestAlex()::End()";    if (fTestATTrack)      klog << log4cpp::Priority::INFO << "TestAlex::TTracks TEST OK!!";    if (fTestAParticle)      klog << log4cpp::Priority::INFO << "TestAlex::Particles TEST OK!!";    if (fTestAHit)      klog << log4cpp::Priority::INFO << "TestAlex::Hits TEST OK!!";    return true;  }  //--------------------------------------------------------------------  void CheckATTrack(ATTrack* track, const irene::Track* iTrack)  //--------------------------------------------------------------------  {    assert (iTrack->GetParticle()->GetParticleID() == track->GetID());    assert (iTrack->GetParticle()->GetParticleID() == track->GetParticleID());    const std::vector<std::pair<TLorentzVector,double> >& iHits = iTrack->GetHits();    assert (iHits[0].first.Vect() == track->GetExtreme1()->GetPosition());    assert (iHits[0].second == track->GetExtreme1()->GetEdep());    assert (iHits[iHits.size()-1].first.Vect() == track->GetExtreme2()->GetPosition());    assert (iHits[iHits.size()-1].second == track->GetExtreme2()->GetEdep());    double iEdep = 0.;    for (auto iHit : iHits) iEdep += iHit.second;    assert (iEdep == track->GetEdep());  }  //--------------------------------------------------------------------  void CheckAParticle(AParticle* aPart, const irene::Particle* iPart)  //--------------------------------------------------------------------  {    assert (iPart->GetParticleID() == aPart->GetID());    assert (iPart->Name() == aPart->GetParticleName());    assert (iPart->GetCharge() == aPart->GetCharge());    assert (iPart->GetInitialVertex().Vect() == aPart->GetVertex());    assert (iPart->GetInitialMomentum() == aPart->GetP4());    assert (iPart->IsPrimary() == aPart->GetIsPrimary());    if (!aPart->GetIsPrimary())      assert(iPart->GetMother()->GetParticleID() == aPart->GetMotherId());  }  //--------------------------------------------------------------------  void CheckAHit(AHit* aHit, const std::pair<TLorentzVector,double> iHit)  //--------------------------------------------------------------------  {    assert (iHit.first.Vect() == aHit->GetPosition());    assert (iHit.second == aHit->GetEdep());  }}