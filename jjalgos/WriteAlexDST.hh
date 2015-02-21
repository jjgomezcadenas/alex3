
#ifndef ALGOWriteAlexDST_
#define ALGOWriteAlexDST_
// Generated by AlexConf: do not edit
#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <map>
#include <TH1F.h>
#include <TH2F.h>
#include <alex/IAlgorithm.h>
#include "PWriteAlexDST.h"
namespace alex {
  class WriteAlexDST: public IAlgorithm,PWriteAlexDST{
  public:
    WriteAlexDST();
    ~WriteAlexDST(){}
    bool Init() ;
    bool Execute() ;
    bool End() ;
    std::string  Name() const {return fName;}
    void SetName(std::string name) {fName = name;}
  private:
    std::string fName;
    std::string fDstPath;
    std::string fDstName;
    std::string fDebug;
  };
}
#endif 