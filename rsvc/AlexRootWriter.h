// ----------------------------------------------------------------------------
///  \file   AlexRootWriter.h
///  \brief  Class to write Alex events to a ROOT file, inside a Tree .
///
///  \author   <paola.ferrario@ific.uv.es> // modified by JJ
///  \date     14 Feb 2013 // Feb 2015
///  \version  $Id: RootWriter.h 9286 2013-10-04 12:43:34Z paola $
///
///  Copyright (c) 2013 NEXT Collaboration
// ----------------------------------------------------------------------------

#ifndef AROOTWRITER_
#define AROOTWRITER_

#include <TFile.h>
#include <TTree.h>
#include <alex/AEvent.h>

//namespace irene {class ParameterInfo;}

namespace alex {

  class AlexRootWriter {

  public:
    /// Constructor
    AlexRootWriter();
    /// Destructor
    ~AlexRootWriter() {}

  private:
    TFile* fFile; ///< ROOT file where the output is written
    TTree* fAevtTree; ///< ROOT tree where the events are stored
    AEvent* fAevent; ///< event to be stored
    bool fIsopen; ///< true is the file is already open
    

  public:

    bool Open(const std::string filename, std::string option);
    void Write(AEvent& event);
    void Close();
    bool IsOpen();
    //void WriteMetadata(ParameterInfo* mdata);

  };

} // end namespace irene

#endif
