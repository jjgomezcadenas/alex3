#include "DrawHits.hh"
#include <alex/ISvc.h>
#include <alex/ASvc.h>
#include <TH2F.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TApplication.h>
namespace alex {

  //--------------------------------------------------------------------
  bool DrawHits::Init()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level for the algorithm
    SetDebugLevel(fDebug);

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "DrawHits::Init()" ;
    klog << log4cpp::Priority::INFO << "DrawHits::Type of Hits: " << fType;

    char * ch ;
    int argc = 0;
    TApplication * gApplication = new TApplication("DrawHits", &argc, &ch);
    gApplication->SetReturnFromRun(true);

    return true;
  }


  //--------------------------------------------------------------------
  bool DrawHits::Execute()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level for the algorithm
    SetDebugLevel(fDebug);

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::DEBUG << "DrawHits::Execute()";

    TCanvas * c1 = new TCanvas("c1", "Hits", 10, 10, 600, 600);

    // Area of interest
    double minX = +1000.;
    double minY = +1000.;
    double maxX = -1000.;
    double maxY = -1000.;
    double margin = 10.;


    // Dealing with True Hits
    if (fType == "True") {
      IHits allHits = ISvc::Instance().GetTrueHits();
      klog << log4cpp::Priority::DEBUG << "DrawHits::Num True hits = " << allHits.size();

      // Updating Focus limits
      for(auto hit : allHits) {
        double hitPosX = hit.first.X();
        double hitPosY = hit.first.Y();
        if (hitPosX > maxX) maxX = hitPosX;
        if (hitPosX < minX) minX = hitPosX;
        if (hitPosY > maxY) maxY = hitPosY;
        if (hitPosY < minY) minY = hitPosY;
      }

      // Create & Fill the Histogram
      TH2F* h2_xyAll = new TH2F("h2_xy", "xy hits",
                                (maxX-minX)+2*margin, minX-margin, maxX+margin,
                                (maxY-minY)+2*margin, minY-margin, maxY+margin);
      for(auto hit : allHits)
        h2_xyAll->Fill(hit.first.X(),hit.first.Y());

      // Draw the histogram.
      h2_xyAll->GetXaxis()->SetTitle("x");
      h2_xyAll->GetYaxis()->SetTitle("y");
      h2_xyAll->Draw("colz");
      c1->Update();

      // Await input from the user before continuing.
      char userInput;
      std::cin >> userInput;

      delete h2_xyAll;
    }

    // Dealing with Reconstructed Hits
    else if (fType == "Rec") {
      // Updating Focus limits
      for (auto rTrack: ASvc::Instance().GetRTracks()) {
        for (auto rHit: rTrack->GetHits()) {
          TVector3 hitPos = rHit->GetPosition();
          double hitPosX = hitPos.X();
          double hitPosY = hitPos.Y();
          if (hitPosX > maxX) maxX = hitPosX;
          if (hitPosX < minX) minX = hitPosX;
          if (hitPosY > maxY) maxY = hitPosY;
          if (hitPosY < minY) minY = hitPosY;
        }
      }

      // Create & Fill the Histogram
      TH2F* h2_xyAll = new TH2F("h2_xy", "xy hits",
                                (maxX-minX)+2*margin, minX-margin, maxX+margin,
                                (maxY-minY)+2*margin, minY-margin, maxY+margin);

      for (auto rTrack: ASvc::Instance().GetRTracks()) {
        for (auto rHit: rTrack->GetHits()) {
          TVector3 hitPos = rHit->GetPosition();
          h2_xyAll->Fill(hitPos.X(), hitPos.Y());
        }
      }

      // Draw the histogram.
      h2_xyAll->GetXaxis()->SetTitle("x");
      h2_xyAll->GetYaxis()->SetTitle("y");
      h2_xyAll->Draw("colz");
      c1->Update();

      // Await input from the user before continuing.
      char userInput;
      std::cin >> userInput;

      delete h2_xyAll;
    }

    else {
      klog << log4cpp::Priority::DEBUG << "DrawHits::Unknown Type of Hits";
      c1->Close();
      delete c1;
      return true;
    }
    

    // Close the plot and delete the histogram.
    c1->Close();
    delete c1;
  
    return true;
  }


  //--------------------------------------------------------------------
  bool DrawHits::End()
  //--------------------------------------------------------------------
  {
    // Set the Debug Level
    SetDebugLevel(fDebug);

    log4cpp::Category& klog = log4cpp::Category::getRoot();
    klog << log4cpp::Priority::INFO << "DrawHits::End()";

    return true;
  }
}
