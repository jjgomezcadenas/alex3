#ifndef ACONFIG_
#define ACONFIG_
/*
 ACONFIG: Alex Configuration
 

 JJGC, July, 2014.
*/

#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <map>
#include <alex/SingletonTemplate.h>
#include <alex/IAlgorithm.h>
#include <alex/IData.h>

#include <alex/LogUtil.h>

#include <TFile.h>



namespace alex {

class AlexManager {
	public:
		AlexManager(){};
		virtual ~AlexManager(){};
		void Init(std::string debugLevel);

		void RegisterAlgorithm(IAlgorithm* algo );
		void InitAlgorithms();
		bool ExecuteAlgorithms();
		void EndAlgorithms();
		void ClearAlgorithms();

		void RegisterData(std::string name, IData* data )
		{fIData[name]=data;}
		IData* RetrieveData(std::string name){return fIData[name]; }
		void ClearData();
		// const IData* RetrieveData(std::string name) const
		// {return fIData[name];} 

	

	private:
		std::vector<IAlgorithm*> fIAlgo;
		std::map<std::string,IData*> fIData;
			
	};

	typedef SingletonTemplate<AlexManager> Alex;   // Global declaration

}
#endif