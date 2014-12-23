CMAKE_MINIMUM_REQUIRED(VERSION 2.6)


# Make sure the compiler can find include files from our  library. 
include_directories (${ALEX_SOURCE_DIR}) 

MESSAGE("In alexMain: IRENE_INSTALL_DIR = ${IRENE_INSTALL_DIR}")
# Make sure the linker can find the  library once it is built. 
link_directories (${ALEX_SOURCE_DIR} ${ALEX_WDIR}) 

add_executable (alexMain alexMain.cpp)
target_link_libraries (alexMain alexAlgos alex)
EXECUTE_PROCESS(
    COMMAND ln -s -f 
    ${IRENE_INSTALL_DIR}/ireneDict_rdict.pcm alexMain/.)
EXECUTE_PROCESS(
    COMMAND ln -s -f 
    ${PAOLINA_INSTALL_DIR}/paolinaDict_rdict.pcm alexMain/.)


