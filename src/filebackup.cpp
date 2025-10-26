#include "filebackup.h"

#include <iostream>
#include <print>

//Linux system headers
#include "signal.h"
#include "unistd.h"

/**
 * @brief try to accept a new input in case of the path is invalide.
 * 
 * @param p old path
 */
void input_modification(std::filesystem::path &p)
{
    p.clear();
    std::string newPath;
    std::println("This path is invalide ! Please enter a valide path.");
    std::cin>>newPath;
    p.assign(newPath);
}

/**
 * @brief Print Current time and remind user when next backup will be saved.
 * 
 * @param delay 
 */
void print_time(unsigned delay)
{
    auto t = time(NULL);
    auto tm = *localtime(&t);

    std::println("Save backuped at {}/{}/{} {}h{}.", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);   
    std::println("Next Backup will be in {} min.",delay);
}

volatile bool flag = true;
/**
 * @brief A signal handler, makes the program stop when recive Ctrl + C.
 * 
 * @param a 
 */
void signal_handler(int a)
{
    flag = false;
}
