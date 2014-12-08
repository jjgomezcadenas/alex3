#ifndef EVEH_H_
#define EVEH_H_
/*
 EveHits = Hits suitable for EVE display
 EVE, the ROOT Event Visualization facility can display a TEvePointSetArray. This is
 a collection of (x,y,z,e) points, where "e" is the weight of xyz. 
 An EveHit takes as an input a vector of pairs ((x,y,z),e) and provides a method
 that returns a new pointer to TEvePointSetArray. In addition it provides methods to
 set the markers, size and colors use to display the TEvePointSetArray.

 JJGC, March, 2014.
*/
#include <vector>
#include <string>
#include <utility>
#include <TLorentzVector.h>

class TEvePointSetArray;
class TEvePointSet;



class EveHits {
public:
	
	bool fStatus;
	int fCol;
	int fMarker_color, fMarker_style;
	double fMarker_size; 
    int fNebin;
    double fEmin, fEmax;
    std::string fType;

	
public:
	EveHits();
	
	virtual ~EveHits(){};
	void InitLogger();
	void SetMarkers(int marker_color, int marker_style, double marker_size);
	void SetEnergyBins(int n_ebin, double emin, double emax);
	inline bool Status(){return fStatus;}
	inline void SetStatus(bool status){fStatus=status;}
	inline void SetType(std::string type){fType = type;}
	inline std::string GetType(){return fType;}

   TEvePointSetArray* Hits(std::vector<std::pair<TLorentzVector,double> > hits);
   TEvePointSet* TrackHits(std::vector<TLorentzVector> track);
 
   ClassDef(EveHits, 0)
};
#endif