#ifndef Global_HPP
#define Global_HPP

// STDLIB

#include <cassert>
#include <cmath>

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

// SDL

#include <SDL2/SDL.h>

// Logging

#define LOG_DATETIME  "|" << __DATE__ << "|" << __TIME__ << "|"
#define LOG_PREFIX  LOG_DATETIME << " " << __PRETTY_FUNCTION__ << " from file " << __FILE__ << " at line " << __LINE__ 
#define console(MESSAGE) std::cout << LOG_DATETIME << " " << MESSAGE << std::endl;
#define trclog(MESSAGE) std::cout << LOG_PREFIX << ": " << MESSAGE << std::endl;
#define errlog(MESSAGE) std::cerr << "ERROR! " << LOG_PREFIX << ": ERROR! " << MESSAGE << std::endl;

#endif
