#pragma once
#include "config.h"
#include "telemetry_functions.h"

std::string ip_color(std::string ip) {
	if (ip == "no connection")
		return config::bad;
	else if (ip == "unreachable")
		return config::fine;
	return config::ok;
}

std::string ram_color(std::string ram) {
	auto pos = ram.find(" ");
	int p = std::stoi(ram.substr(pos, ram.find("%") - pos));
	
	switch (p) {
		case 0 ... 50:
			return config::ok;
		case 51 ... 80:
			return config::fine;
	}

	return config::bad;
}

std::string cpu_color(std::string cpu) {
	/*switch on the average of the cpus to get the color.*/
	return config::ok;
}

std::string hdd_color(std::string hdd) {
	if (hdd == "ERR")
		return config::bad;
	
	if (hdd.find("GB") != std::string::npos) {
		hdd = get_hddusage();
	}

	auto pos = hdd.find(" ");
	int p = std::stoi(hdd.substr(pos, hdd.find("%") - pos));
	
	switch (p) {
		case 0 ... 70:
			return config::ok;
		case 71 ... 95:
			return config::ok;
	}

	return config::bad;
}

std::string connected_color(std::string status) {
	if (status == "✔️")
		return config::ok;
	return config::bad;
}

std::string separator_color(std::string sep) {
	return config::separator_color;
}