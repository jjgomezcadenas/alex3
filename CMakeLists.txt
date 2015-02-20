# -*- cmake -*-
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(ALEX3)

MESSAGE("CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
#Set compilier flags
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
   # Mac OS X specific code
   SET(CMAKE_CXX_FLAGS "-Wall -g -O2 -std=c++11" )
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # Linux specific code
    SET(CMAKE_CXX_FLAGS "-Wall -g -O2 -std=c++0x" )
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")


SET(CMAKE_VERBOSE_MAKEFILE ON)
#SET(CMAKE_BUILD_TYPE ${CMAKE_CXX_FLAGS})

MESSAGE("CMAKE source dir: ${CMAKE_SOURCE_DIR}")
MESSAGE("CMAKE binary dir: ${CMAKE_BINARY_DIR}")

MESSAGE("CMAKE compiler: ${CMAKE_CXX_COMPILER}")
MESSAGE("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
MESSAGE("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# Set where to look for external packages 
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/") 

MESSAGE("CMAKE_MODULE_PATH source dir: ${CMAKE_MODULE_PATH}")


# Look for the needed libraries
find_package(Irene REQUIRED)
find_package(Paolina REQUIRED)
find_package(Log4CPP REQUIRED)
find_package(RecPack REQUIRED)
find_package(CLHEP REQUIRED)
find_package(TinyXML2 REQUIRED)
find_package(ROOT REQUIRED)


MESSAGE("Irene include directories: ${IRENE_INCLUDE_DIR}")
MESSAGE("Paolina include directories: ${PAOLINA_INCLUDE_DIR}")
MESSAGE("Log4CPP include directories: ${LOG4CPP_INCLUDE_DIR}")
MESSAGE("RecPack include directories: ${RECPACK_INCLUDE_DIR}")
MESSAGE("CLHEP include directories: ${CLHEP_INCLUDE_DIR}")
MESSAGE("TinyXML2 include directories: ${TINYXML2_INCLUDE_DIR}")
MESSAGE("ROOT include directories: ${ROOT_INCLUDE_DIR}")


MESSAGE("Irene libraries: ${IRENE_LIBRARIES}")
MESSAGE("Paolina libraries: ${PAOLINA_LIBRARIES}")
MESSAGE("LOG4CPP libraries: ${LOG4CPP_LIBRARIES}")
MESSAGE("RecPack libraries: ${RECPACK_LIBRARIES}")
MESSAGE("CLHEP libraries: ${CLHEP_LIBRARIES}")
MESSAGE("TinyXML2 libraries: ${TINYXML2_LIBRARIES}")
MESSAGE("ROOT libraries: ${ROOT_LIBRARIES}")


SET(ALEX_WDIR 
  $ENV{AWDIR}
) 

SET(GALEX galex) # Define the galex directory

#Make symbolic links in alex/ to all header files
EXECUTE_PROCESS(
  COMMAND mkdir -p alex)


FILE(GLOB alex_headers . util/*.h config/*.h base/*.h isvc/*.h psvc/*.h 
  asvc/*.h)

FOREACH(file ${alex_headers})
  EXECUTE_PROCESS(
    COMMAND ln -s -f ${file} alex)
ENDFOREACH(file)


# Directories that will be searched for headers during compilation
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/asvc
          ${ALEX_WDIR} ${GALEX}
					${IRENE_INCLUDE_DIR} ${PAOLINA_INCLUDE_DIR} 
					${ROOT_INCLUDE_DIR} ${TINYXML2_INCLUDE_DIR} 
					${LOG4CPP_INCLUDE_DIR} ${RECPACK_INCLUDES_DIR} ${CLHEP_INCLUDE_DIR})

#set everything needed for the root dictonary and create the dictionary

# set(ASVC_DICTIONARY ${CMAKE_BINARY_DIR}/AsvcDict.cxx)  # set dictionary path

# MESSAGE("Generate dictionary")

# SET(ASVC_HEADERS ${CMAKE_SOURCE_DIR}/asvc/AHit.h ${CMAKE_SOURCE_DIR}/asvc/ATTrack.h
#   ${CMAKE_SOURCE_DIR}/asvc/ARTrack.h ${CMAKE_SOURCE_DIR}/asvc/AParticle.h
#   ${CMAKE_SOURCE_DIR}/asvc/AEvent.h)

# ROOT_GENERATE_DICTIONARY(
#            "${ASVC_DICTIONARY}"            # path to dictionary to generate
#            "${CMAKE_SOURCE_DIR}/asvc"  # list of includes
#            "${ASVC_HEADERS}" 
#            "${CMAKE_SOURCE_DIR}/asvc/LinkDef.h"   # ROOT linkDef file
#          )

 FILE(GLOB alex_src . util/*.cpp config/*.cpp base/*.cpp isvc/*.cpp psvc/*.cpp
 asvc/*.cpp )


# # # # Finally, create it!

MESSAGE("Creating Alex library")

#ADD_LIBRARY(alex SHARED ${alex_src} ${ASVC_DICTIONARY})

ADD_LIBRARY(alex SHARED ${alex_src})
SET_TARGET_PROPERTIES(alex PROPERTIES VERSION 1.1.0 SOVERSION 1)
TARGET_LINK_LIBRARIES(alex ${LOG4CPP_LIBRARIES} ${IRENE_LIBRARIES} ${PAOLINA_LIBRARIES} 
	${RECPACK_LIBRARIES} ${ROOT_LIBRARIES} ${CLHEP_LIBRARIES} ${TINYXML2_LIBRARIES})


MESSAGE("Creating xConfigure")
add_executable (xConfigure config/xConfigure.cxx)
target_link_libraries (xConfigure alex)

MESSAGE("Creating gConfigure")
add_executable (gConfigure galex/gConfigure.cxx)
target_link_libraries (gConfigure alex)


# MESSAGE("Executing xConfigure")
# EXEC_PROGRAM(${CMAKE_BINARY_DIR}/xConfigure
#         ARGS ${ALEX_WDIR})
#         #OUTPUT_VARIABLE CLHEP_PREFIX)

  
ADD_SUBDIRECTORY(${ALEX_WDIR})
ADD_SUBDIRECTORY(alexMain)
#ADD_SUBDIRECTORY(galex)
#ADD_SUBDIRECTORY(asvc)
#ADD_SUBDIRECTORY(test)
#ADD_SUBDIRECTORY(exampleConf)
#ADD_SUBDIRECTORY(example)
#ADD_SUBDIRECTORY(exampleMain)


# # Installation destinations (just for the lib, not the python module)
# INSTALL(TARGETS alex LIBRARY DESTINATION lib)
# INSTALL(FILES ${alex_headers} DESTINATION include/alex)

# # Get ready for creating a package
# INCLUDE(CPack)
