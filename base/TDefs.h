#ifndef TDEFS_
#define TDEFS_
/*
 Root-dependend (T) includes and defs
*/

#include <alex/GDefs.h>

#include <TMath.h>
#include <TVector3.h>
#include <TLorentzVector.h>



namespace alex {
typedef std::pair<TLorentzVector,double> IHit;
typedef std::vector<std::pair<TLorentzVector,double> > IHits;
}

inline std::string PrintTVector3(TVector3 t)
{
	std::stringstream s;  
	s << " x = " << t.X() << " y = " << t.Y() 
	<< " z = " << t.Z() << std::endl;

	return s.str();
}

inline std::string PrintTLorentzVector(TLorentzVector t)
{
	std::stringstream s;  
	s << " Px = " << t.Px() << " Py = " << t.Py() 
	<< " Pz = " << t.Pz() <<  " E = " << t.E() << std::endl;

	return s.str();
}
#endif