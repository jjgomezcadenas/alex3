#ifndef ASVC_
#define ASVC_
/*
 Alex service: persistency
 

 JJGC, January, 2015.
*/

#include <alex/GDefs.h>
#include <alex/SingletonTemplate.h>
#include <alex/LogUtil.h>

#include <TFile.h>



namespace alex {

class AlexService {
	public:
		AlexServie(){};
		virtual ~AlexService(){};
		void Init(std::string debugLevel);

		

	private:
		
	};

	typedef SingletonTemplate<AlexService> ASvc;   // Global declaration

}
#endif