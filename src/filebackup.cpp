/**
 * @file filebackup.cpp
 * @author HUANG He (he.hu4ng@outlook.com)
 * @brief 
 * @version 0.2
 * @date 2025-10-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <csignal>
#include <filesystem>
#include <iostream>
#include <print>
#include <thread>

namespace fs = std::filesystem;

/**
 * @brief Read path and verify if it is valid.
 */
auto read_path(const std::string& msg) -> fs::path
{
	fs::path target_path;
	do
	{
		std::println("{}", msg);
		std::cin >> target_path;
		if (!fs::exists(target_path))
			std::println("Path not found. Try again.");

	} while (!fs::exists(target_path));
	return target_path;
}

/**
 * @brief Create time stamp
 */
auto timestamp_string() -> std::string
{
	auto time		= std::time(nullptr);
	auto local_time = *std::localtime(&time);
	return std::format(
		"{:04}{:02}{:02}_{:02}{:02}{:02}",
		local_time.tm_year + 1900,
		local_time.tm_mon  + 1,
		local_time.tm_mday,
		local_time.tm_hour,
		local_time.tm_min,
		local_time.tm_sec);
}

/**
 * @brief Call this to backup file.
 */
void file_backup_agent()
{
	static volatile bool flag = true; 
	std::signal(SIGINT, [](int) { flag = false; });

	fs::path file_path	 = read_path("Please enter the file path to backup: ");
	fs::path backup_root = read_path("Please enter the backup destination directory: ");

	std::println("Enter autosave interval (seconds): ");
	size_t delay{60};
	std::cin >> delay;

	std::println("Starting backup agent. Press Ctrl + C to stop.");
	fs::create_directories(backup_root / "backups");
	size_t counter{0};

	while (flag)
	{
		try
		{
			// Backup file name with time stamp
			auto backup_name = file_path.filename().string() 
				+ "_" + timestamp_string() 
				+ "_Save" 
				+ std::to_string(counter++);

			fs::copy_file(
				file_path,
				backup_root / "backups" / backup_name,
				fs::copy_options::overwrite_existing);
		}
		catch (const fs::filesystem_error& e)
		{
			std::cerr << "Backup failed: " << e.what() << '\n';
		}

		for (unsigned i = 0; i < delay && flag; ++i)
			std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	std::println("Backup process terminated.");
}