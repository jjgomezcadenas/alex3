CMAKE_MINIMUM_REQUIRED(VERSION 2.6)


# Make sure the linker can find the  library once it is built. 
link_directories (${ALEX_SOURCE_DIR}) 

set(ASVC_DICTIONARY ASVCDict.cxx)  # set dictionary path
root_generate_dictionary(
           "${ASVC_DICTIONARY}"            # path to dictionary to generate
           "${ALEX_SOURCE_DIR}"  # list of includes
           "AHit.h"       # list of classes to process
           "LinkDef.h"                    # ROOT linkDef file
         )

