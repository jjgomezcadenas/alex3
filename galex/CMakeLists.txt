CMAKE_MINIMUM_REQUIRED(VERSION 2.6)


# Make sure the compiler can find include files from our  library. 

# INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR} ${ALEX_SOURCE_DIR} ${GALEX}
# 					${IRENE_INCLUDE_DIR} ${PAOLINA_INCLUDE_DIR} 
# 					${ROOT_INCLUDE_DIR} ${TINYXML2_INCLUDE_DIR} 
# 					${LOG4CPP_INCLUDE_DIR} ${RECPACK_INCLUDES_DIR} ${CLHEP_INCLUDE_DIR})


# Make sure the linker can find the  library once it is built. 
link_directories (${ALEX_SOURCE_DIR}) 

FILE(GLOB galex_headers ./GalexMF.h ./MultiView.h ./EveHits.h ./LinkDef.h )

FOREACH(file ${galex_headers})
  EXECUTE_PROCESS(
    COMMAND ln -s -f ${file} galex)
ENDFOREACH(file)

set(GALEX_DICTIONARY GalexDict.cxx)  # set dictionary path
root_generate_dictionary(
           "${GALEX_DICTIONARY}"            # path to dictionary to generate
           "${ALEX_SOURCE_DIR}"  # list of includes
           "GalexMF.h;MultiView.h;EveHits.h"       # list of classes to process
           "LinkDef.h"                    # ROOT linkDef file
         )
#         set(SOURCES ${SOURCES} ${ROOTPWA_DICTIONARY})  # append dictionary to sources

add_executable (xgalex galex.cpp EveHits.cpp MultiView.cpp ${GALEX_DICTIONARY} )
target_link_libraries (xgalex alex)

EXECUTE_PROCESS(
    COMMAND ln -s -f galex/xgalex .)
EXECUTE_PROCESS(
    COMMAND ln -s -f galex/GalexDict_rdict.pcm .)

EXECUTE_PROCESS(
    COMMAND ln -s -f 
    ${IRENE_INSTALL_DIR}/ireneDict_rdict.pcm .)
EXECUTE_PROCESS(
    COMMAND ln -s -f 
    ${PAOLINA_INSTALL_DIR}/paolinaDict_rdict.pcm .)

