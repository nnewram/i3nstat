#pragma once
#include <string_view>
#include <functional>
#include <chrono>
using namespace std::chrono_literals;

class Telemetry {
private:
	const std::string teleName;
	const std::string teleColor;
	const std::function<std::string(std::string)> teleColorFunction;
	const std::function<std::string(void)> teleFunc;
	std::chrono::duration<double> teleInterval;
	std::chrono::time_point<std::chrono::system_clock> lastUsed;
	std::string cache;

	const bool shouldShow;
	const bool teleWantsSep;
public:
	Telemetry(const std::string& name, const bool show, const std::function<std::string(void)> func, std::chrono::duration<double> interval, const bool wantsSep = true)
	: teleName(std::string(name)), shouldShow(show), teleColor("#FFFFFF"), teleColorFunction(nullptr), teleFunc(func), teleInterval(interval), cache(func()), teleWantsSep(wantsSep) {}
	
	Telemetry(const std::string& name, const bool show, const std::string& color, const std::function<std::string(void)> func, std::chrono::duration<double> interval, const bool wantsSep = true)
	: teleName(name), shouldShow(show), teleColor(color), teleFunc(func), teleColorFunction(nullptr), teleInterval(interval), cache(func()), teleWantsSep(wantsSep) {}

	Telemetry(const std::string& name, const bool show, const std::function<std::string(std::string)> colorfunc, const std::function<std::string(void)> func, std::chrono::duration<double> interval, const bool wantsSep = true)
	: teleName(name), shouldShow(show), teleColor(""), teleFunc(func), teleColorFunction(colorfunc), teleInterval(interval), cache(func()), teleWantsSep(wantsSep) {}

	const std::string& name() {
		return teleName;
	}

	const bool should_show() {
		return shouldShow;
	}

	std::string color() {
		if (teleColor == "")
			return teleColorFunction(value());
		return teleColor;
	}

	std::string value() {
		if (std::chrono::system_clock::now() - lastUsed >= teleInterval) {
			cache = teleFunc();
			lastUsed = std::chrono::system_clock::now();
		}

		return cache;
	}

	const bool wants_sep() {
		return teleWantsSep;
	}
};

