#pragma once
#include <chrono>
using namespace std::chrono_literals;

namespace config {

std::string background = "#101935";
std::string ok         = "#2FBF71";
std::string fine       = "#2E86AB";
std::string bad        = "#DB162F";
std::string white      = "#F9F9F9";

bool show_ip   = true;
bool show_ram  = true;
bool show_cpu  = true;
bool show_hdd  = true;
bool show_date = true;
bool show_time = true;

auto ip_delay        = 1260s;
auto connected_delay = 1s;
auto ram_delay       = 3s;
auto cpu_delay       = 1s;
auto hdd_delay       = 10s;
auto date_delay      = 60s;
auto time_delay      = 1s;


bool have_separator = true;
std::string separator_color = "#6883BA";
std::string separator = "➤";

const char *dateformat          = "%Y-%m-%d";
const char *timeformat          = "%H:%M";
const char *expanded_timeformat = "%H:%M:%S";

const char *root = "/";

}
