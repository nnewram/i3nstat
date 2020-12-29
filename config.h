#pragma once
#include <chrono>
using namespace std::chrono_literals;

namespace config {

const std::string background = "#101935";
const std::string ok         = "#2FBF71";
const std::string fine        = "#2E86AB";
const std::string bad        = "#DB162F";
const std::string white      = "#F9F9F9";

const bool show_ip   = true;
const bool show_ram  = true;
const bool show_cpu  = true;
const bool show_hdd  = true;
const bool show_date = true;
const bool show_time = true;

const auto ip_delay        = 1260s;
const auto connected_delay = 1s;
const auto ram_delay       = 3s;
const auto cpu_delay       = 1s;
const auto hdd_delay       = 10s;
const auto date_delay      = 60s;
const auto time_delay      = 1s;

const bool have_separator = true;
const std::string separator_color = "#6883BA";
const std::string separator = "➤";

const char* const dateformat          = "%Y-%m-%d";
const char* const timeformat          = "%H:%M";
const char* const expanded_timeformat = "%H:%M:%S";

const char* const root = "/";

}
