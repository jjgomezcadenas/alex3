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
#endif