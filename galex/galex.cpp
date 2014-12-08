// GALEX: Graphics Alex
//J.J. Gomez-Cadenas, December 2014


#include "RootGlobals.h"
#include "RootEve.h"
#include "RootGUI.h"
#include "RootUtil.h"

#include <alex/LogUtil.h>
#include <alex/IDefs.h>
#include <alex/ISvc.h>

#include "GalexMF.h"
#include "EveHits.h"
#include "MultiView.h"

#include <CLHEP/Units/SystemOfUnits.h>


using namespace std;
using namespace CLHEP;
using namespace alex;

const char *filetypes[] = { "All files",     "*",
                            "ROOT files",    "*.root",
                            "NEXT files",    "*.next",
                            "ROOT macros",   "*.C",
                            0,               0 };


GalexMF::GalexMF(const TGWindow *p, UInt_t w, UInt_t h)
{

  fGalex= new TGMainFrame(p, w, h);
  fGalex -> SetWindowName("Galex GUI");
  
  //InitLogger();
  InitData();
  InitGui();  
  //InitGeometry();

}

GalexMF::~GalexMF()
{
  fGalex->SetCleanup(kDeepCleanup);
  delete fEveTH;
  delete fEveTV;
  delete fEveTT;
  //delete fIrene;
}

void GalexMF::InitLogger()
{
  log4cpp::Appender *appender1 = new log4cpp::OstreamAppender("console", &std::cout);
  appender1->setLayout(new log4cpp::BasicLayout());

  log4cpp::Category& klog = log4cpp::Category::getRoot();
  klog.addAppender(appender1);
  klog.setPriority(log4cpp::Priority::DEBUG);

  klog.debug("In GalexMF::InitLogger(): \n");
  
}

void GalexMF::InitData()
{
  log4cpp::Category& klog = log4cpp::Category::getRoot();
  klog.debug("In GalexMF::InitData(): \n");
    
  fTimer = new TStopwatch();
  fEvent=0;
  fFSet = false;
  fClose = true;

  // file info data

  sEvtTree = "EVENT";
  sEvtBranch = "EventBranch";
  
  
  fEveTH = new EveHits(); //TH or TrueHits Eve Object
  fEveTV = new EveHits(); //TV or TrueVertex Eve Object
  fEveTT = new EveHits(); //TT or TrueTracks Eve Object
  

  fEveTH->SetType("True hits");
  fEveTV->SetType("True vertex");
  fEveTT->SetType("True tracks");

  int marker_color=3;
  int marker_style=4;
  double marker_size=0.5;
  
  fEveTH->SetMarkers(marker_color, marker_style, marker_size);
  fEveTH->SetStatus(false);
  fEveTV->SetStatus(false);
  fEveTT->SetStatus(false);
}

void GalexMF::SetLogger()
{
  log4cpp::Category& klog = log4cpp::Category::getRoot();
  klog.debug("In GalexMF::SetLogger to %s: \n", fDebug);

  if(strncmp (fDebug,"FATAL",4)  ==0) 
    klog.setPriority(log4cpp::Priority::FATAL);
  else if (strncmp (fDebug,"ERROR",4)  ==0) 
    klog.setPriority(log4cpp::Priority::ERROR);
  else if (strncmp (fDebug,"WARN",4)  ==0) 
    klog.setPriority(log4cpp::Priority::WARN);
  else if (strncmp (fDebug,"NOTICE",4)  ==0) 
    klog.setPriority(log4cpp::Priority::NOTICE);
  else if (strncmp (fDebug,"INFO",4)  ==0) 
    klog.setPriority(log4cpp::Priority::INFO);
  else if (strncmp (fDebug,"DEBUG",4)  ==0) 
    klog.setPriority(log4cpp::Priority::DEBUG);
}



void GalexMF::CleanGraphics()
{
  log4cpp::Category& klog = log4cpp::Category::getRoot();
  klog.debug("In GalexMF::CleanGraphics\n");
    
  if (fEveTH->Status())
  {
    klog.debug("Destroy gTrueHits from previous event\n");

    gTrueHits->DestroyElements();
    delete gTrueHits;
    fEveTH->SetStatus(false);
  }

  if (fEveTV->Status())
  {
    klog.debug("Destroy gTrueVertex from previous event\n");

    gTrueVertex->DestroyElements();
    delete gTrueVertex;
    fEveTV->SetStatus(false);
  }

  klog.debug("Destroy gTrueTracks from previous event\n");

  if (fEveTT->Status())
  {
    for(size_t i=0; i < gTrueTracks.size(); i++ )
    {
      klog.debug("Destroy track number %lu\n",i );
      gTrueTracks.at(i)->DestroyElements();
      delete gTrueTracks.at(i);
    }
    gTrueTracks.clear();
  }
}

 void GalexMF::CloseFile()
{
  log4cpp::Category& klog = log4cpp::Category::getRoot();
  klog.debug("In GalexMF::CloseFile(): cleaning previous graphics objects\n");

  if (fClose)
  {

    CleanGraphics();
    //delete gEve->GetCurrentEvent();
    gEve->AddEvent(new TEveEventManager("Event", "NEXT Event")) ; 
  
    //reset event number
    fEvent=0;
    fFile->Close();
    delete fIevt;

    fBOpenFile-> SetEnabled(kTRUE);
    fBLoadEvent-> SetEnabled(kFALSE);
    fBTrueTracks-> SetEnabled(kFALSE);
    fBTrueHits-> SetEnabled(kFALSE);
    fBTrueVertex-> SetEnabled(kFALSE);
    fClose = false;
  }
}

void GalexMF::OpenFile()
{
  log4cpp::Category& klog = log4cpp::Category::getRoot();
  klog.debug("In GalexMF::OpenFile(): cleaning previous graphics objects\n");

  fClose = true; 
  fEvent=0;

  //enable/disable buttoms
  fBLoadEvent-> SetEnabled(kTRUE);
  fBCloseFile-> SetEnabled(kTRUE);
  fBTrueTracks-> SetEnabled(kFALSE);
  fBTrueHits-> SetEnabled(kFALSE);
  fBTrueVertex-> SetEnabled(kFALSE);
  fBOpenFile-> SetEnabled(kFALSE);
  
  
  //TG file dialog object to grab file and directory
  TGFileInfo fi;
  fi.fFileTypes = filetypes;
  fi.fIniDir    = StrDup(*fDirName);
  //strcpy (fi.fIniDir,"/Users/jjgomezcadenas/Development/NEXT/DATA");
  
  new TGFileDialog(gClient->GetRoot(), this->fGalex, kFDOpen, &fi);

  klog.debug("TGFileInfo: file = %s (dir = %s)\n", fi.fFilename,fi.fIniDir);
  klog.debug("file: %s (dir: %s)\n", fi.fFilename,fi.fIniDir);

  *fDirName = fi.fIniDir;
  *fFileName = fi.fFilename;

  //Opening file, accessing tree, recreating Irene event

  klog.debug("Opening DST file =%s\n",fFileName->Data());
  fFile = TFile::Open(fFileName->Data());

  klog.debug("Opening Tree\n");
  fEvtTree = dynamic_cast<TTree*>(fFile->Get(sEvtTree));

  klog.info("number of entries in Irene Tree = %lld\n",fEvtTree->GetEntries());

  klog.debug("Recreating Irene event\n");
  fIevt = new irene::Event();
  fEvtTree->SetBranchAddress(sEvtBranch, &fIevt);

  klog.debug("Irene DST opened successfuly and Irene event loaded from branch\n");

}

void GalexMF::LoadEvent()
{
  log4cpp::Category& klog = log4cpp::Category::getRoot();
  klog.debug("In GalexMF::LoadEvent(): cleaning previous graphics objects\n");

  CleanGraphics();

  fBTrueTracks-> SetEnabled(kTRUE);
  fBTrueHits-> SetEnabled(kTRUE);
  fBTrueVertex-> SetEnabled(kTRUE);
  
  klog.debug("reading topo event = %d \n",fEvent);
  klog.debug("Adding event = %d \to graphics manager\n",fEvent);

  gEve->AddEvent(new TEveEventManager("Event", "NEXT Event")) ; 

  int nb = fEvtTree->GetEntry(fEvent);
  klog.debug("Mapping irene event: read %d bytes from tree\n",nb);
  alex::ISvc::Instance().LoadEvent(fIevt);
  alex::ISvc::Instance().SetEvtNum(fEvent);

  fEvent++;
}

void GalexMF::TrueHits()
{
  log4cpp::Category& klog = log4cpp::Category::getRoot();
  klog.debug("In GalexMF::TrueHits():: event = %d\n",fEvent-1);

  IHits trueHits = alex::ISvc::Instance().GetTrueHits();
  klog << log4cpp::Priority::DEBUG << " true hits = " << trueHits.size();

  
  klog.debug("cleaning previous graphics objects\n");
  CleanGraphics();  

  klog.debug("--Create graphic object (gTrueHits) for true hits \n");

  int n_ebin = 15;
  double emin = 0; // in keV
  double emax = fDeDx; // in keV

  klog.debug("In GalexMF::TrueHits():: n_ebin = %d emin = %7.1f (keV) emax = %7.1f (keV)\n",
    fEvent-1,emin/keV, emax/keV);

  fEveTH->SetEnergyBins(n_ebin, emin, emax);

  gTrueHits = fEveTH->Hits(trueHits);

  klog.debug("Adding gtpcHists to the manager and drawing scene\n");

  gEve->AddElement(gTrueHits);
  DrawScene(); 
  fEveTH->SetStatus(true);
        
}

void GalexMF::TrueTracks()
{
  log4cpp::Category& klog = log4cpp::Category::getRoot();
  klog.debug("In GalexMF::TrueTracks():: event = %d\n",fEvent-1);

  // if (strncmp (fDebug,"DEBUG",4)  ==0) 
  //   fIrene->PrintTrueTracks();
  
  // klog.debug("cleaning previous graphics objects\n");
  // CleanGraphics();

  // int marker_color=2;
  // int marker_style=4;
  // double marker_size=0.5;

  // klog.debug("--Loop over tracks and get the hits of each track  \n");

  // std::vector<const irene::Track*> trueTracks = fIrene->TrueTracks();
  // for (size_t i=0; i < trueTracks.size(); i++)
  // {
  //   const irene::Track* itrk = trueTracks.at(i);
  //   const std::vector<std::pair<TLorentzVector,double> > ihits = itrk->GetHits();
  //   std::vector<TLorentzVector> trkPoints;

  //   for(size_t i=0; i<ihits.size(); i++)
  //   {
  //     trkPoints.push_back(ihits.at(i).first);
  //   }

  //   klog.debug("--Create a graphic object per each track and store into vector  \n");
    
  //   marker_color++;
    
  //   fEveTT->SetMarkers(marker_color, marker_style, marker_size);

  //   //allocate a new graphic object of type gtpcHits
  //   TEvePointSet* trkHits = fEveTT->TrackHits(trkPoints);

  //   gTrueTracks.push_back(trkHits);

  //   klog.debug("Adding trkHits from track %d to the manager and drawing scene\n",i);

  //   gEve->AddElement(trkHits);

  // }
  // DrawScene();
}

void GalexMF::TrueVertex()
{
  log4cpp::Category& klog = log4cpp::Category::getRoot();
  klog.debug("In GalexMF::TrueVertex():: event = %d\n",fEvent-1);

  // if (strncmp (fDebug,"DEBUG",4)  ==0) 
  //   fIrene->PrintTrueVertex();
  
  // klog.debug("--Clear previous true vertex \n");

  // if (fEveTV->Status())
  // {
  //   klog.debug("Destroy gTrueVertex from previous event\n");

  //   gTrueVertex->DestroyElements();
  //   delete gTrueVertex;
  //   fEveTV->SetStatus(false);
  // }

  // klog.debug("--Create graphic object (gTrueHits) for true hits \n");

  // int marker_color=46;
  // int marker_style=20;
  // double marker_size=2.0;
  
  // fEveTV->SetMarkers(marker_color, marker_style, marker_size);

  // std::vector<TLorentzVector> vertex;
  // vertex.push_back(fIrene->TrueVertex());

  // gTrueVertex = fEveTV->TrackHits(vertex);

  // klog.debug("Adding gTrueVertex to the manager and drawing scene\n");

  // gEve->AddElement(gTrueVertex);
  // DrawScene(); 
        
}



void GalexMF::DrawScene()
{
  log4cpp::Category& klog = log4cpp::Category::getRoot();
  klog.debug("In GalexMF::DrawScene():: event = %d\n",fEvent-1);
  
  gEve->GetViewers()->DeleteAnnotations();
  TEveElement* top = gEve->GetCurrentEvent();

  klog.debug("Destroy EventRphi \n");
  gMultiView->DestroyEventRPhi();

  klog.debug("Import EventRphi \n");
  gMultiView->ImportEventRPhi(top);

  klog.debug("Destroy EventRhoz \n");  
  gMultiView->DestroyEventRhoZ();

  klog.debug("Import EventRhoz \n");
  gMultiView->ImportEventRhoZ(top);

  klog.debug("ReDraw() \n");
  gEve->Redraw3D();
}

void GalexMF::InitGalex()
{
 log4cpp::Category& klog = log4cpp::Category::getRoot();
  klog.debug("in GalexMF::InitGalex(): Instantiate GalexParam\n");

  fDebug="DEBUG";
  fDeDx = 20.*keV;

  fDirName = new TString("/Users/jjgomezcadenas/Development/NEXT/DATA");
  fFileName= new TString();

  fRmin = 150*mm;
  fRmax = 151*mm;
  fZl = 150*mm;

}


void GalexMF::InitGui()
{
  log4cpp::Category& klog = log4cpp::Category::getRoot();
  klog.debug("in GalexMF::InitGui(): define cframe\n");

  fGalex -> SetWindowName("Galex GUI");

  TGCompositeFrame *cframe = new TGCompositeFrame(fGalex, 170, 20, 
                                             kHorizontalFrame | kFixedWidth);

  // fBSetParam = new TGTextButton(cframe, "&Init");
  // cframe->AddFrame(fBSetParam, new TGLayoutHints(kLHintsTop | kLHintsExpandX,
  //                                            3, 2, 2, 2));
  // fBSetParam-> Associate(fGalex);
  // fBSetParam-> Connect("Clicked()", "GalexMF", this, "InitGalex()");

  fBOpenFile = new TGTextButton(cframe, "&OpenFile");
  cframe->AddFrame(fBOpenFile, new TGLayoutHints(kLHintsTop | kLHintsExpandX,
                                             3, 2, 2, 2));
  fBOpenFile-> Associate(fGalex);
  fBOpenFile-> Connect("Clicked()", "GalexMF", this, "OpenFile()");
  fBOpenFile-> SetEnabled(kTRUE);

  fBLoadEvent = new TGTextButton(cframe, "&LoadEvent");
  cframe->AddFrame(fBLoadEvent, new TGLayoutHints(kLHintsTop | kLHintsExpandX,
                                                  3, 2, 2, 2));

  fBLoadEvent-> Associate(fGalex);
  fBLoadEvent-> Connect("Clicked()", "GalexMF", this, "LoadEvent()");
  fBLoadEvent-> SetEnabled(kFALSE);

  
  klog.debug("in GalexMF::GalexGui(): define iframe\n");

  TGCompositeFrame *iframe = new TGCompositeFrame(fGalex, 170, 20, 
                                                  kHorizontalFrame | kFixedWidth);
  
  
  fBTrueTracks = new TGTextButton(iframe, "&TTracks");
  iframe->AddFrame(fBTrueTracks, new TGLayoutHints(kLHintsTop | kLHintsExpandX,
                                              3, 2, 2, 2));

  fBTrueTracks-> SetEnabled(kFALSE); 
  fBTrueTracks-> Associate(fGalex);
  fBTrueTracks-> Connect("Clicked()", "GalexMF", this, "TrueTracks()");

   
  fBTrueHits = new TGTextButton(iframe, "&THits");
  iframe->AddFrame(fBTrueHits, new TGLayoutHints(kLHintsTop | kLHintsExpandX,
                                             3, 2, 2, 2));
  fBTrueHits-> SetEnabled(kFALSE);
  fBTrueHits-> Associate(fGalex);
  fBTrueHits-> Connect("Clicked()", "GalexMF", this, "TrueHits()");

  fBTrueVertex = new TGTextButton(iframe, "&TVertex");
  iframe->AddFrame(fBTrueVertex, new TGLayoutHints(kLHintsTop | kLHintsExpandX,
                                             3, 2, 2, 2));
  fBTrueVertex-> SetEnabled(kFALSE);
  fBTrueVertex-> Associate(fGalex);
  fBTrueVertex-> Connect("Clicked()", "GalexMF", this, "TrueVertex()");

  TGCompositeFrame *kframe = new TGCompositeFrame(fGalex, 170, 20, 
                                                  kHorizontalFrame | kFixedWidth);
  
  TGCompositeFrame *cframe1 = new TGCompositeFrame(fGalex, 170, 20, 
                                                  kHorizontalFrame | kFixedWidth);
   
  fBExit = new TGTextButton(cframe1, "&Exit");
  cframe1->AddFrame(fBExit, new TGLayoutHints(kLHintsTop | kLHintsExpandX,
                                             2, 2, 2, 2));

  fBExit -> SetCommand("gApplication -> Terminate()");

  fBCloseFile = new TGTextButton(cframe1, "&CloseFile");
  cframe1->AddFrame(fBCloseFile, new TGLayoutHints(kLHintsTop | kLHintsExpandX,
                                             2, 2, 2, 2));
  fBCloseFile-> Associate(fGalex);
  fBCloseFile-> Connect("Clicked()", "GalexMF", this, "CloseFile()");

  fBCloseFile-> SetEnabled(kFALSE); 
  
  fGalex -> AddFrame(cframe, new TGLayoutHints(kLHintsCenterX, 2, 2, 5, 1));
  fGalex -> AddFrame(iframe, new TGLayoutHints(kLHintsCenterX, 2, 2, 5, 1));
  fGalex -> AddFrame(kframe, new TGLayoutHints(kLHintsCenterX, 2, 2, 5, 1));
  //fGalex -> AddFrame(cframe2, new TGLayoutHints(kLHintsCenterX, 2, 2, 5, 1));
  fGalex -> AddFrame(cframe1, new TGLayoutHints(kLHintsCenterX, 2, 2, 5, 1));
  fGalex -> MapSubwindows();
  fGalex -> Resize(fGalex -> GetDefaultSize());
  fGalex -> MapWindow();

}


void GalexMF::InitGeometry()
{
  log4cpp::Category& klog = log4cpp::Category::getRoot();
  klog.debug("in GalexMF::InitGeometry(): init Geometry\n");

  fNextGeom = new TEveElementList("Geometry");

  klog.debug("Creating a tube\n");  
  

  klog.info("SetParam: Toy detector dimensions:: fRmin =%7.1f mm fRmax =%7.1f mm fzl =%7.1f mm  \n",
    fRmin/mm,fRmax/mm,fZl/mm);

  fToyGeometry = new TEveGeoShape("ToyTPC");

  fToyGeometry->SetShape(new TGeoTube(fRmin, fRmax, fZl));
  fToyGeometry->SetMainColor(kCyan);
  fToyGeometry->SetMainTransparency(90);

  klog.debug("Adding tube element to geometry\n"); 
  fNextGeom->AddElement(fToyGeometry);

  klog.debug("Adding geometry to Eve\n"); 
  gEve->AddGlobalElement(fNextGeom);


  //Multiview
  klog.debug("Creating multiview\n");    
  
  gMultiView = new MultiView();

  klog.debug("Importing views\n");
  gMultiView->ImportGeomRPhi(fNextGeom);
  gMultiView->ImportGeomRhoZ(fNextGeom);
  gEve->Redraw3D(kTRUE);
}

int main(int argc, char **argv)
{

  //  TROOT root("root","Panel");
  TApplication app("GalexMF",&argc, argv);

  TEveManager::Create();
  TEveBrowser* browser = gEve->GetBrowser();
  browser->StartEmbedding(TRootBrowser::kLeft);

  GalexMF* gmf = new GalexMF(gClient -> GetRoot(), 1000, 600);
  gmf->InitLogger();
  gmf->InitGalex();
  gmf->InitGeometry();
  app.Run();
  return 0;

}