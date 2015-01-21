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

#include <TFile.h>

namespace alex {

class AlexService {
	public:

		AlexService(){};

		virtual ~AlexService(){};
		
		void Init(std::string debugLevel);

		// AParticles
		void AddParticle(const alex::AParticle* part);
		const alex::AParticle* GetParticle(int id) const;
		const std::vector <alex::AParticle*> GetParticles() const {return fParticles;}

		// ATTracks
		void AddTTrack(const alex::ATTrack* ttrack);
		const alex::ATTrack* GetTTrack(int id) const;
		const std::vector <alex::ATTrack*> GetTTracks() const {return fTTracks;}

		// ARTracks
		void AddRTrack(const alex::ARTrack* rtrack);
		const alex::ARTrack* GetRTrack(int id) const;
		const std::vector <alex::ARTrack*> GetRTracks() const {return fRTracks;}


	private:
	  std::string fDebugLevel;

		std::vector <alex::AParticle*> fParticles;
		std::vector <alex::ATTrack*> fTTracks;
		std::vector <alex::ARTrack*> fRTracks;

	};

	typedef SingletonTemplate<AlexService> ASvc;   // Global declaration

}
#endif