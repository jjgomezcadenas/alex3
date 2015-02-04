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
#include "PDefs.h"


namespace alex {

class PaolinaManager {
	public:
		PaolinaManager(){};
		virtual ~PaolinaManager(){};

    void Init(std::string debugLevel,
              std::vector<std::pair<double,double> > detSize);
  
    std::vector<std::pair<TVector3,double> > ComputePaolinaVoxels(IHits hits,
                                                                  std::vector<double> voxelSize);
    std::vector<paolina::Track*>  ComputePaolinaTracks();
    std::pair<paolina::Blob*, paolina::Blob*> ComputePaolinaBlobs(double blobRadius);

    std::string PrintVoxels();
    std::string PrintBlobs();
    std::string PrintTracks();

	private:
		
    std::string fDebugLevel;
    
    std::vector<std::pair<double,double> > fDetSize;
    //voxels
		std::vector<paolina::Voxel*> fPvoxels;	
  	//paolina tracks
  	std::vector<paolina::Track*> fPtracks;
  	//paolina blobs
  	std::pair<paolina::Blob*, paolina::Blob*> fPblobs;

	};

  // Global declaration
	typedef alex::SingletonTemplate<PaolinaManager> PSvc; 

}
#endif
