/**
 * @file filebackup.h
 * @author HUANG He (he.hu4ng@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-25
 * 
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <filesystem>

/**
 * @brief demande user to change directory in case of the path is invalide
 * 
 * @param p file path
 */
void input_modification(std::filesystem::path& p);

/**
 * @brief print current time and the time interval of autosave.
 * 
 * @param delay time interval of autosave.
 */
void print_time(unsigned delay);

/**
 * @brief system using check
 * 
 */
#ifdef __unix__ 

//Linux system headers
#include "signal.h"
#include "unistd.h"
void signal_handler(int);
extern volatile bool flag;

#endif//Linux check

