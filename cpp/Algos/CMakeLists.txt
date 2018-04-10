PROJECT(myAlgos)
include_directories(./)
add_library(myAlgos STATIC
        algos.cpp
        utility.cpp
        intzip.cpp
        algos.h
        utility.h
        intzip.h
        types.h)
