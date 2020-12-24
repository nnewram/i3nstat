#pragma once

namespace config {

std::string background = "#101935";

bool show_ip = true;
bool show_ram = true;
bool show_hdd = true;
bool show_date = true;
bool show_time = true;

bool have_separator = true;
std::string separator_color = "#564787";
std::string separator = "➤";

const char *dateformat = "%Y-%m-%d";
const char *timeformat = "%H:%M:%S";
}