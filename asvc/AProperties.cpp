
// ----------------------------------------------------------------------------
//  $Id: AProperties.cpp  2015-01-05 1
//
//  Author:  <gomez@mail.cern.ch>
//  Created: 5 Jan 2015
//  
//  Copyright (c) 2015 NEXT Collaboration
// ---------------------------------------------------------------------------- 

#include <alex/AProperties.h>


namespace alex {
	void AProperties::DisplayInfo(std::ostream& s) const
  	{
    	s << std::endl; 
    	for (std::map<std::string,std::string>::const_iterator 
           it=fProperties.begin(); 
    			 it!=fProperties.end(); ++it)
    	{
    		s << "Property["<<it->first <<"]="<< it->second << std::endl;
    	}
  	}

  std::string AProperties::DisplayProperties() const
  	{
    	std::stringstream s;   
    	for (std::map<std::string,std::string>::const_iterator 
           it=fProperties.begin(); 
    			 it!=fProperties.end(); ++it)
    	{
    		s << "    Property["<<it->first <<"] = "<< it->second << std::endl;
    	}
    	return s.str();
  	}
}

std::ostream& operator << (std::ostream& s, const alex::AProperties& ap) 
{
  ap.DisplayInfo(s);
  return s; 
}