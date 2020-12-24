#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <sstream>

#include <fstream>
#include <string_view>

#include <ctime>

#include "config.h"

std::string get_ip() {
	curlpp::Cleanup myCleanup;
	std::ostringstream ipos;
	
	try {
		ipos << curlpp::options::Url("https://wtfismyip.com/text");
	} catch (...) {

		try {
			curlpp::options::Url("https://www.google.com/");
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

std::string get_hddusage() {
	return "hdd";
}

std::string get_date() {
	std::time_t now = std::time(nullptr);
	std::tm *localtime = std::localtime(&now);
	char strtime[5 + 1 + 2 + 1 + 2 + 1] = {0};
	std::strftime(strtime, sizeof(strtime), config::timeformat, localtime);
	return std::string(strtime);
}

std::string get_time() {
	return "13:37";
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