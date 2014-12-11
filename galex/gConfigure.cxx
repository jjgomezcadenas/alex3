// exConfigure
// Configures the setup to run the algos in folder example
// August, 2014


#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <map>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <fstream>

#include <alex/AlexConfigure.h>
#include <alex/StringOperations.h>
#include <alex/LogUtil.h>
using std::stringstream;

using namespace alex;
using std::string; 
using std::cout; 
using std::endl; 
using std::ostream;
using std::ifstream;
using std::vector;


int main(int argc, char **argv)
{
	
	InitLogger();
	log4cpp::Category& klog = log4cpp::Category::getRoot();
	AlexConfigure::Instance().Init("DEBUG","GAlexConfig");

  cout << "argc = " << argc << endl;
  //cout << "argv[0] = " << argv[1] << endl;

  if( argc != 3)   
  { 
    cout <<" Usage: xConfigure <pathToGalex> <nameGalexConfigFile>" << endl;
    return -1;
  }


  string pathToGalex;
  string galexConf;

  {
    stringstream ss;
    ss << argv[1];
    ss>>pathToGalex;
  }
  {
    stringstream ss;
    ss << argv[2];
    ss>>galexConf;
  }

	//string galexConf="GalexConfig.xml";
	string galexConfHeader="GalexInit.hh";
  
  klog << log4cpp::Priority::INFO 
        << " path to Galex=" << pathToGalex;

  klog << log4cpp::Priority::INFO 
        << " name of Galex configure file =" << galexConf;
  
	
  string pathGalexConf = PathFromStrings(pathToGalex,galexConf);
  klog << log4cpp::Priority::INFO 
        << " Parse gAlexConfig file located at=" << pathGalexConf;

	AlexConfigure::Instance().ParseGalexConfiguration(pathGalexConf);
	
  string pathAConfHeader = PathFromStrings(pathToGalex,galexConfHeader);
  klog << log4cpp::Priority::INFO 
    << " Write galex init header file at=" << galexConfHeader;
		std::ofstream out(pathAConfHeader.c_str());
  	out << AlexConfigure::Instance().WriteGalexHeader();
  	out.close();
	
  return 0;
 }