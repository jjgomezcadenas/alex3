#ifndef ASVC_
#define ASVC_
/*
 Alex service: persistency
 
 JJGC, January, 2015.
*/


#include <alex/GDefs.h>
#include <alex/SingletonTemplate.h>
#include <alex/LogUtil.h>
#include <alex/AParticle.h>
#include <alex/ATTrack.h>
#include <alex/ARTrack.h>

namespace alex {

class AlexService {
	public:

		AlexService(){};

		virtual ~AlexService() {Clear();}
		
		void Init(std::string debugLevel);

		void Clear();

		void SetStartEvent(int sevt) { startEvt = sevt; }
    int GetStartEvent() const { return startEvt; }

    void SetEvtNum(int sevt) { evtNum = sevt; }	
    int GetEvtNum() const { return evtNum; }

		// Event Energy
		double GetTrueEventEnergy() const {return fTrueEventEnergy;}
		double GetRecEventEnergy() const {return fRecEventEnergy;}
		void SetRecEventEnergy(double e) {fRecEventEnergy=e;}

		// AParticles
		void AddParticle(alex::AParticle* part);
		alex::AParticle* GetParticle(int id) const;
		const std::vector <alex::AParticle*> GetParticles() const {return fParticles;}

		// ATTracks
		void AddTTrack(alex::ATTrack* ttrack);
		alex::ATTrack* GetTTrack(int id) const;
		const std::vector <alex::ATTrack*> GetTTracks() const {return fTTracks;}

		// ARTracks
		void AddRTrack(alex::ARTrack* rtrack);
		alex::ARTrack* GetRTrack(int id) const;
		const std::vector <alex::ARTrack*> GetRTracks() const {return fRTracks;}


	private:
	  std::string fDebugLevel;

	  int startEvt;
    int evtNum;

	  double fTrueEventEnergy;
	  double fRecEventEnergy;

		std::vector <alex::AParticle*> fParticles;
		std::vector <alex::ATTrack*> fTTracks;
		std::vector <alex::ARTrack*> fRTracks;


	
	};

	typedef SingletonTemplate<AlexService> ASvc;   // Global declaration

}
#endif