#pragma once
#include "config.h"

#include <sys/statvfs.h>

std::string cpu_expanded() {
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

	std::string res {"CPU:"};
	for (auto& usage : usages) {
		res += " " + std::to_string(usage);
	}

	return res;
}

std::string time_expanded() {
	std::time_t now = std::time(nullptr);
	std::tm *localtime = std::localtime(&now);
	char strtime[100] = {0};
	std::strftime(strtime, sizeof(strtime), config::expanded_timeformat, localtime);
	return std::string(strtime);
}

std::string hdd_expanded() {
	struct statvfs stat;
	
	if (statvfs(config::root, &stat) != 0) {
		return "ERR";
	}

	return "HDD: " + std::to_string((int)((float)(stat.f_bsize * stat.f_bavail) / (float)(1024 * 1024 * 1024))) + " GB";
}