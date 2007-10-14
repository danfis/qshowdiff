/**
 * In this file are placed all macros and stuff for debuging,
 */
#ifndef _DEBUG_H_
#define _DEBUG_H_

/**
 * header files
 */
#ifndef NDEBUG
    #include <iostream>
#endif

/**
 * TODO: Colored output
 * DBG("error" << "message");
 * ERROR("error" << "message");
 */
#ifndef NDEBUG
/*
    #define DEBUG_HELPER(msg, type) \
        std::cerr << __FILE__ << ": " << __LINE__ << ": " << type << ": " \
                  << msg << std::endl; \
        std::cerr.flush()
        */
    #define DEBUG_HELPER(msg, type) \
        std::cerr << msg << std::endl; \
        std::cerr.flush()
    #define DBG(msg) DEBUG_HELPER(msg, "Debug")
    #define ERROR(msg) DEBUG_HELPER(msg, "Error")
    #define WARNING(msg) DEBUG_HELPER(msg, "Warning")
    #define MILESTONE(msg) DEBUG_HELPER(msg, "Milestone")
#else
    #define DEBUG_HELPER(msg, type)
    #define DB(msg, type)
    #define ERROR(msg, type)
    #define WARNING(msg, type)
#endif

#endif
