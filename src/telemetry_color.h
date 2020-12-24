#include "config.h"

std::string ip_color(std::string ip) {
	if (ip == "no connection")
		return "#FF0000";
	else if (ip == "unreachable")
		return "#0000FF";
	return "#00FF00";
}

std::string ram_color(std::string ram) {
	auto pos = ram.find(" ");
	int p = std::stoi(ram.substr(pos, ram.find("%") - pos));
	
	switch (p) {
		case 0 ... 50:
			return "#00FF00";
		case 51 ... 80:
			return "#0000FF";
	}

	return "#FF0000";
}

std::string connected_color(std::string status) {
	if (status == "✔️")
		return "#00FF00";
	return "#FF0000";
}

std::string separator_color(std::string sep) {
	return config::separator_color;
}