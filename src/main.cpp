#include "filebackup.h"

#include <csignal>
#include <iostream>
#include <print>
#include <thread>

namespace fs = std::filesystem;

inline void sleepSeconds(unsigned sec) 
{
    std::this_thread::sleep_for(std::chrono::seconds(sec));
}

int main()
{
    signal(SIGINT, signal_handler);

    std::string source;
    unsigned delay;

    std::println("Please enter the source path:");
    std::cin >> source;

    fs::path sourcePath(source);
    while(!fs::exists(sourcePath))
        input_modification(sourcePath);

    std::println("Please enter autosave time interval (in seconds):");
    std::cin >> delay;

    unsigned counter = 0;
    while(flag)
    {
        fs::create_directories(sourcePath / "Backups");
        std::string newPath = "Save" + std::to_string(counter++);
        fs::rename(sourcePath / "world", sourcePath / "Backups" / newPath);

        print_time(delay);
        sleepSeconds(delay);
    }

    std::println("Backup process terminated.");
    return 0;
}