#ifndef PSVC_
#define PSVC_
/*
 Paolina Svc to provide access to Paolina
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
#include "PDefs.h"


namespace alex {

class PaolinaManager {
	public:
		PaolinaManager(){};
		virtual ~PaolinaManager(){};
		// void Init(std::string debugLevel, std::vector<double> voxel_size,
  //   			  std::vector<double> left_range,std::vector<double> right_range, 
  //   			  double rblob);

    void Init(std::string debugLevel,std::vector<double> voxelSize,
              std::vector<std::pair<double,double> > detSize,
              double blobRadius);

    double ComputePaolinaObjects(
          std::vector<std::pair<TLorentzVector,double> > hits);

		std::vector<paolina::Voxel*> GetPaolinaVoxels(); 
    std::vector<paolina::Track*>  GetPaolinaTracks();
    std::pair<paolina::Blob*, paolina::Blob*> GetPaolinaBlobs();

		std::vector<std::pair<TVector3,double> > GetVoxels();
    std::string PrintVoxels();

	private:
		
    std::string fDebugLevel;
    bool fPaolina;

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

  // Global declaration
	typedef alex::SingletonTemplate<PaolinaManager> PSvc; 

}
#endif
