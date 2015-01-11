#include "TestAlex.hh"
#include <alex/ISvc.h>
#include <alex/PSvc.h>
#include <alex/PSvc.h>
#include <alex/AParticle.h>

namespace alex {

  void FillAPart(const irene::Particle* iPart, AParticle* aPart);

  //--------------------------------------------------------------------
  bool TestAlex::Init()
  //--------------------------------------------------------------------
  {
    // Init the IreneManager
    ISvc::Instance().Init("DEBUG");

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "TestAlex::Test Alex Particles = " << fTestAParticle;

    return true;
  }

  
  //--------------------------------------------------------------------
  bool TestAlex::Execute()
  //--------------------------------------------------------------------
  {
    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "TestAlex::Execute()";

    // Testing Alex Particles
    bool partTest = true;
    if (fTestAParticle) {
      std::vector<const irene::Particle*> iParts;
      iParts = ISvc::Instance().GetEvent().Particles();

      for (int p=0; p<iParts.size(); p++) {
        AParticle* aPart = new AParticle();
        const irene::Particle* iPart = iParts[p];
        FillAPart(iPart, aPart);
        
        // Checking the setter process
        assert (iPart->GetParticleID() == aPart->GetID());
        assert (iPart->Name() == aPart->GetName());
        assert (iPart->GetCharge() == aPart->GetCharge());
        assert (iPart->GetInitialVertex().Vect() == aPart->GetVertex());
        assert (iPart->GetInitialMomentum() == aPart->GetP4());
        assert (iPart->IsPrimary() == aPart->GetIsPrimary());
        if (!aPart->GetIsPrimary())
          assert(iPart->GetMother()->GetParticleID() == aPart->GetMotherId());

        delete aPart;
      }

    }

    return true;
  }

  
  //--------------------------------------------------------------------
  bool TestAlex::End()
  //--------------------------------------------------------------------
  {
    return true;
  }


  //--------------------------------------------------------------------
  void FillAPart(const irene::Particle* iPart, AParticle* aPart)
  //--------------------------------------------------------------------
  {
    //std::cout << "***** Part ID: " << iPart->GetParticleID() << std::endl;

    // Filling the Alex Particle from Irene Particle
    aPart->SetID(iPart->GetParticleID());
    aPart->SetName(iPart->Name());
    aPart->SetCharge(iPart->GetCharge());
    aPart->SetVertex(iPart->GetInitialVertex().Vect());
    aPart->SetP4(iPart->GetInitialMomentum());
    aPart->SetIsPrimary(iPart->IsPrimary());
    aPart->SetMotherID(0);
    if (!aPart->GetIsPrimary())
      aPart->SetMotherID(iPart->GetMother()->GetParticleID());

    aPart->SetProperty("Using_Setters", "Yes");
    aPart->SetProperty("Using_Constructor", "No");

    //aPart->DisplayInfo(std::cout);
  }

}



