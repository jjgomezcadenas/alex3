#ifndef ISVC_
#define ISVC_
/*
 Irene Svc to provide access to irene (eg DST) to algos
 JJGC, July, 2014.
 New version, December 2014
*/

#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <map>
#include <alex/SingletonTemplate.h>
#include <alex/LogUtil.h>
#include "IDefs.h"

#include <TFile.h>
#include <TTree.h>
#include <TRandom2.h>



namespace alex {

class IreneManager {
	public:
		IreneManager(){};
		virtual ~IreneManager(){};
		void Init(std::string debugLevel);
		void Init(std::string debugLevel,std::vector<double> voxel_size,
    std::vector<double> left_range,std::vector<double> right_range, double rblob);
		void InitDst(std::string fileName,const irene::Event* ievt);
		int DstEntries();
		int DstGetEntry(int ivt);
		void LoadEvent(const irene::Event* ievt);
		const irene::Event& GetEvent();

		TLorentzVector TrueVertex(){return fVertex;}
		
		IParticles GetElectrons() const {return fElectrons;}
		int GetNumberOfElectrons() const {return fElectrons.size();}
		IParticles GetPrimaryElectrons() const {return fBetas;}
		int GetNumberOfPrimaryElectrons() const {return fBetas.size();}
		std::pair<IParticle, IParticle> GetPMaxElectrons() const {return fBetasMax;}
		IHits GetTrueHits() const {return fTrueHits;}
		std::pair<IHits, IHits> GetPMaxElectronsHits() const {return fBetasMaxHits;}
		

    void SetStartEvent(int sevt) { startEvt = sevt; }
    int GetStartEvent() const { return startEvt; }

    void SetEvtNum(int sevt) { evtNum = sevt; }
    int GetEvtNum() const { return evtNum; }

	private:
		void FetchElectrons();
		void FetchPMaxElectrons();
		void GetTrueVertex();
		void GetPaolinaVoxels();
    
    int startEvt;
    int evtNum;

    //TRandom2* fRandom;
		TFile* fIfile;
  	TTree* fEvtTree;
        
  	const irene::Event* fIevt;
  	IParticles fElectrons;
  	IParticles fBetas; //beta = primary electron
  	IHits fTrueHits;
  	TLorentzVector fVertex;
  	
    std::vector<const irene::Track*> fIreneTracks ; 
  	std::pair<IParticle, IParticle> fBetasMax;
  	std::pair<IHits, IHits> fBetasMaxHits;

  	//paolina Voxels

		std::vector<paolina::Voxel*> fPvoxels;	
  	//Voxel builder
  	paolina::VoxelBuilder* fPVB;

  	//paolina tracks
  	std::vector<paolina::Track*> fPtracks;

  	//paolina track builder
  	paolina::TrackBuilder* fPTB;

  	//paolina blobs
  	std::pair<paolina::Blob*, paolina::Blob*> fPblobs;

  	//paolina Blob builder
  	paolina::BlobBuilder* fPBB;
			
	};

	typedef alex::SingletonTemplate<IreneManager> ISvc;   // Global declaration

}
#endif
