#pragma once
#include <vector>
#include "../telemetry.h"

void click_event_manager(std::vector<Telemetry>& telemetries, std::atomic<bool> *noexit) {
	std::string click;
	while (noexit) {
		while (click.find("}") == std::string::npos) {
			std::string line;
			std::getline(std::cin, line);
			click += line;
		}
		
		std::string button_str = click.substr(click.find("\"button\":") + 9);
		button_str = button_str.substr(0, button_str.find(","));
		int button = std::stoi(button_str);

		click = click.substr(click.find("\"name\":\"") + 8);
		click = click.substr(0, click.find("\","));

		for (auto& telemetry : telemetries) {
			if (click == telemetry.name()) {
				telemetry.click_event(button);
			}
		}
	}
}

/* 
[
	{
		"name":"ip", // we only care about this
		"button":1, // and maybe this?
		"modifiers":[],
		"x":3351,
		"y":1073,
		"relative_x":52,
		"relative_y":10,
		"output_x":1431,
		"output_y":1073,
		"width":83,
		"height":17
	}
...
*/