#ifndef Galex_H_
#define Galex_H_


#include <TQObject.h>
#include <RQ_OBJECT.h>
#include <TGButton.h>

#include <stdio.h>
#include <string.h>



class TGWindow;
class TGMainFrame;
class TString;
class TGNumberEntry;
class TGTextEntry;
class TGGroupFrame;
class TGLabel;
class TFile;
class TTree;
class TStopwatch; 
class TGLayoutHints;
class TGDockableFrame;
class TGMenuBar;

class TEveGeoShape;
class TEvePointSetArray;
class TEvePointSet;

class MultiView;
class TEveElementList;

class EveHits;

namespace irene
{
    class Event;
}

class GalexMF 
{
	RQ_OBJECT("GalexMF")
	
	public:

    TGMainFrame*    fGalex; //main frame object itself


    TFile*          fFile ;    ///< DST data file    
    TTree*          fEvtTree; ///< Tree containing the event data (irene)
    
    const char*     sEvtTree ;  //s = string: name of Tree and Branch
    const char*     sEvtBranch ;

    TString*        fDirName;  //name of directory and file
    TString*        fFileName;

    
	TGTextButton*      fBOpenFile;  // b for buttom
    TGTextButton*      fBCloseFile;  // b for buttom
    TGTextButton*      fBLoadEvent;
    TGTextButton*      fBTrueTracks;
    TGTextButton*      fBTrueHits;
    TGTextButton*      fBTrueVertex;
    TGTextButton*      fBSetParam;
    TGTextButton*      fBExit;

    TGLayoutHints      *fMenuBarLayout, *fMenuBarItemLayout;
    TGGroupFrame       *fGframe;
    TGNumberEntry      *fNumber;
    //TGLabel            *fLabel;
    

    TEveElementList* fNextGeom; 
    TEveGeoShape*    fToyGeometry;
    MultiView* gMultiView;  //g for graphics


    TGTransientFrame     *fMain;

    TStopwatch*                                     fTimer;
   
    irene::Event*                                   fIevt; //i for irene objects
    
    EveHits*                                        fEveTH;  //TH = TrueHits
    EveHits*                                        fEveTV;  //TV = TrueVertex
    EveHits*                                        fEveTT;  //TT = TrueTrack
    
    
    TEvePointSetArray*                              gTrueHits; 
    TEvePointSet*                                   gTrueVertex; 
    std::vector<TEvePointSet*>                      gTrueTracks; 


    const char* fDebug;     //level of debugging
    
    /*
    Enumeration values for logging
    EMERG   
    FATAL   
    ALERT   
    CRIT  
    ERROR   
    WARN  
    NOTICE  
    INFO  
    DEBUG   
    NOTSET  
    */

    bool fFSet; // set to true once you init Karen

    
    double fRmin, fRmax, fZl; //dimensions of Toy detector
    double fRTPC,fZTPC; // params for Toy Detector

    double fDeDx ; //dE/dx at chosen pressure
    
    int             fEvent; //event number

    bool fClose; 

	GalexMF(const TGWindow *p, UInt_t w, UInt_t h);
	virtual ~GalexMF();
    void InitLogger();
    void SetLogger();
    void InitData();
    void InitGalex();
    void CleanGraphics();
    
	void OpenFile();
    void CloseFile();
	void LoadEvent();

    void TrueHits();
    void TrueTracks();
    void TrueVertex();
    
    void DrawScene();
    void InitGui();
    void InitGeometry();

      
};

#endif
