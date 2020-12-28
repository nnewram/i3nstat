#pragma once
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <sstream>

#include <fstream>
#include <string_view>

#include <ctime>

#include <sys/statvfs.h>

#include "config.h"

std::string get_ip() {
	curlpp::Cleanup myCleanup;
	std::ostringstream ipos;
	
	try {
		ipos << curlpp::options::Url("https://wtfismyip.com/text");
	} catch (...) {

		try {
			curlpp::options::Url("https://www.google.com/"); // FIXME: do we assume google is the standard for being connected to internet?
		} catch (...) {
			return "no connection";
		}

		return "unreachable";
	}

	std::string ip = "IP: " + ipos.str();
	ip.erase(ip.find("\n"));
	return ip;
}

std::string get_ramusage() {
	std::ifstream memusageFile;
	std::string bloat;
	std::string unit;
	int total;
	int available;
	float precentage;
	memusageFile.open("/proc/meminfo");
	if (!memusageFile.is_open())
		return "ERR /proc/meminfo";
	
	memusageFile >> bloat >> total >> unit;
	
	std::getline(memusageFile, bloat);
	std::getline(memusageFile, bloat);

	memusageFile >> bloat >> available >> unit;
	precentage = (float)(total - available) / (float)total;

	memusageFile.close();
	
	return "RAM: " + std::to_string((int)(100 * precentage)) + "%";
}

std::string get_cpu() {
	std::ifstream procstat;
	procstat.open("/proc/stat");
	std::vector<int> usages;
	std::string cpu_name;
	int sumtime = 0;
	int idle = 0;
	int collect = 0;
	
	while ((procstat >> cpu_name) && cpu_name != "intr") {
		sumtime = 0;
		for (int i = 0; i < 3; i++) {
			procstat >> collect;
			sumtime += collect;
		}

		procstat >> idle;
		sumtime += idle;

		for (int i = 0; i < 6; i++) {
			procstat >> collect;
			sumtime += collect;
		}

		usages.push_back((int)(100 * (1 - ((float)idle/(float)sumtime))));
	}

	procstat.close();

	int avgusage = 0;

	for (auto& usage : usages) {
		avgusage += usage;	
	}

	avgusage /= usages.size();

	return "CPU: " + std::to_string(avgusage) + "%";
}

std::string get_hddusage() {
	struct statvfs stat;

	if (statvfs(config::root, &stat) != 0) {
		return "ERR";
	}

	return "HDD: " + std::to_string((int)(100 * (float)(stat.f_blocks - stat.f_bfree) / (float)(stat.f_blocks - stat.f_bfree + stat.f_bavail))) + " %";
}

std::string get_date() {
	std::time_t now = std::time(nullptr);
	std::tm *localtime = std::localtime(&now);
	char strtime[100] = {0};
	std::strftime(strtime, sizeof(strtime), config::dateformat, localtime);
	return std::string(strtime);
}

std::string get_time() {
	std::time_t now = std::time(nullptr);
	std::tm *localtime = std::localtime(&now);
	char strtime[100] = {0};
	std::strftime(strtime, sizeof(strtime), config::timeformat, localtime);
	return std::string(strtime);
}

std::string get_connected() {
	curlpp::Cleanup myCleanup;
	
	try {
		curlpp::options::Url("https://www.google.com/");
	} catch (...) {
		return "❌";
	}

	return "✔️";
}

std::string get_separator() {
	return config::separator;
}