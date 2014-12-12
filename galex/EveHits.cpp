#include <TColor.h>
#include <TEvePointSet.h>
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
#include <CLHEP/Units/SystemOfUnits.h>
#include "EveHits.h"

EveHits::EveHits() : 
                    fMarker_color(3),
                    fMarker_style(4),fMarker_size(1),
                    fNebin(10),fEmin(0),fEmax(500)
                                                        
{
  fStatus=false;  
  TColor::SetPalette(1, 0); // Spectrum palette
  fCol = TColor::GetNumberOfColors();
  //InitLogger();  Commented for now, but one could have an independent logger (not root)
}

void EveHits::InitLogger()
{
  log4cpp::Appender *appender1 = new log4cpp::OstreamAppender("console", &std::cout);
  appender1->setLayout(new log4cpp::BasicLayout());

  log4cpp::Category& klog = log4cpp::Category::getRoot();
  klog.setPriority(log4cpp::Priority::DEBUG);
  klog.addAppender(appender1);
}

void EveHits::SetMarkers(int marker_color, int marker_style, double marker_size)
{
  fMarker_color= marker_color;
  fMarker_style=marker_style;
  fMarker_size=marker_size;

  log4cpp::Category& klog = log4cpp::Category::getRoot();
  klog.info("In EveHits::SetMarkers: fMarker_color =%d fMarker_style =%d fMarker_size =%7.1f  \n",
    fMarker_color,fMarker_style,fMarker_size);

}

void EveHits::SetEnergyBins(int n_ebin, double emin, double emax)
{
  fNebin=n_ebin;
  fEmin=emin;
  fEmax=emax;

  log4cpp::Category& klog = log4cpp::Category::getRoot();

  klog.info("In EveHits::SetEnergyBins (weights): fNebin =%d fEmin =%7.1f fEmax =%7.1f  \n",
    fNebin,fEmin,fEmax);
}


TEvePointSet* EveHits::TrackHits(std::vector<TLorentzVector> track)
{
  fStatus=true;

  log4cpp::Category& klog = log4cpp::Category::getRoot();
  TEvePointSet* ps = new TEvePointSet(); 
  ps->SetOwnIds(kTRUE);

  ps->SetMarkerColor(fMarker_color);
  ps->SetMarkerStyle(fMarker_style);
  ps->SetMarkerSize(fMarker_size);

  klog.debug("number of hits in track  is %lu\n", track.size());

  for(size_t j=0; j < track.size(); j++)
  {
    TLorentzVector pos = track.at(j);
    ps->SetNextPoint(pos.X(), pos.Y(), pos.Z());
    ps->SetPointId(new TNamed(Form("Point %lu", j), ""));
    klog.debug(" hit number %lu in track: x= %7.3f y= %7.3f z=%7.3f (mm) \n", j,
            pos.X()/CLHEP::mm, pos.Y()/CLHEP::mm, pos.Z()/CLHEP::mm);

  }
  
  return ps;
}

TEvePointSetArray* EveHits::Hits(std::vector<std::pair<TLorentzVector,double> > hits)
{
  
  fStatus=true;

  log4cpp::Category& klog = log4cpp::Category::getRoot();
  klog.debug("In EveHits::Hits(): fStatus =%d type =%s\n",fStatus, fType.c_str());
  
  TEvePointSetArray* gtpcHits = new TEvePointSetArray(fType.c_str());

  gtpcHits->SetSourceCS(TEvePointSelectorConsumer::kTVT_XYZ);
  gtpcHits->SetMarkerColor(fMarker_color);
  gtpcHits->SetMarkerStyle(fMarker_style);
  gtpcHits->SetMarkerSize(fMarker_size);

 
  klog.debug("EveHits::Hits(): Setting the number of bins in gtpcHits\n");
  
  gtpcHits->InitBins("Energy", fNebin, fEmin, fEmax); //These are weights rather than energy
  double binWidth = (fEmax-fEmin)/fNebin;

  klog.info("In EveHits::HITS (weights): fNebin =%d fEmin =%7.1f fEmax =%7.1f  binWidth =%7.1f\n",
    fNebin,fEmin,fEmax,binWidth);

  klog.debug("EveHits::Hits(): Setting colors for the bins in gtpcHits\n");
   
  for (Int_t i = 1; i < fNebin; ++i)
  {
    int icol = i * fCol /fNebin;
    gtpcHits->GetBin(i)->SetMainColor(TColor::GetColorPalette(icol));
    klog.debug("EveHits::Hits(): assigning color %d to bin %d\n",icol,i);
  }

  gtpcHits->GetBin(0) ->SetMainColor(kBlue);
  gtpcHits->GetBin(fNebin)->SetMainColor(kRed);


  size_t n_hits = hits.size();
  

  for (size_t i = 0; i < n_hits; ++i)
  { 
    std::pair<TLorentzVector,double> hit = hits.at(i);
    TLorentzVector xyzt = hit.first; 
    double weight = hit.second; 
   
    gtpcHits->Fill(xyzt.X(), xyzt.Y(),xyzt.Z(),weight);  
    int bin = weight/binWidth;

    klog.debug("EveHits::Hits():FILLING hit number %lu: x= %7.3f y= %7.3f  z=%7.3f weight = %7.3f, bin =%d \n", 
      i,xyzt.X(), xyzt.Y(),xyzt.Z(),weight,bin);       
  } 
  gtpcHits->CloseBins();     
  
  return gtpcHits;
}

