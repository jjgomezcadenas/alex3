#ifndef ASVC_
#define ASVC_
/*
 Alex service: persistency
 
 JJGC, January, 2015.
*/


#include <alex/GDefs.h>
#include <alex/SingletonTemplate.h>
#include <alex/LogUtil.h>
#include <alex/AEvent.h>
#include <alex/AlexRootWriter.h>
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

		AEvent* GetEvent() {return fEvent;}
    AlexRootWriter& GetAlexRootWriter() {return fWriter;}


	private:
	  std::string fDebugLevel;

	  double fTrueEventEnergy;
	  double fRecEventEnergy;

		std::vector <alex::AParticle*> fParticles;
		std::vector <alex::ATTrack*> fTTracks;
		std::vector <alex::ARTrack*> fRTracks;


		AEvent* fEvent; ///< event to be accessed
    AlexRootWriter fWriter; ///< instance of the class that writes the ROOT file

	};

	typedef SingletonTemplate<AlexService> ASvc;   // Global declaration

}
#endif