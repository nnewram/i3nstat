#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include "telemetry.h"
#include "i3json.h"
#include "telemetry_functions.h"
#include "telemetry_color.h"
#include "config.h"
#include "clickevents/clickmanager.h"
#include "clickevents/click_functions.h"

using namespace std::chrono_literals;

std::vector<Telemetry> telemetries {
	Telemetry {"ip",        config::show_ip,   ip_color,        get_ip,        config::ip_delay,        false              },
	Telemetry {"connected", config::show_ip,   connected_color, get_connected, config::connected_delay,                    },
	Telemetry {"ram",       config::show_ram,  ram_color,       get_ramusage,  config::ram_delay                           },
	Telemetry {"cpu",       config::show_cpu,  cpu_color,       get_cpu,       config::cpu_delay,       true, cpu_expanded }, /* we might wanna get some named arguments. idk */
	Telemetry {"hdd",       config::show_hdd,  hdd_color,       get_hddusage,  config::hdd_delay,       true, hdd_expanded },
	Telemetry {"date",      config::show_date, config::fine,    get_date,      config::date_delay                          },
	Telemetry {"time",      config::show_time,                  get_time,      config::time_delay,      true, time_expanded}
};

Telemetry separator {"sep", config::have_separator, config::separator_color, get_separator, 31536000s /* lol should probably make a "dont update" */ };

int main() {
	std::atomic<bool> noexit = true;
	std::string previous {""};

	initialize();
	std::thread click_thread(click_event_manager, std::ref(telemetries), &noexit);

	while (noexit) {
		i3json json;
		
		for (int i = 0; i < telemetries.size(); i++) {
			auto& telemetry = telemetries[i];

			if (telemetry.should_show()) {
				json.add(telemetry.name(), telemetry.color(), telemetry.value(), telemetry.wants_sep());
			}

			if (separator.should_show() && (i != telemetries.size() - 1) && telemetry.wants_sep()) {
				json.add(separator.name(), separator.color(), separator.value(), true);
			}
		}

		std::string current = json.get();
		
		if (current != previous) {
			std::cout << current << std::endl;

			previous = current;
			std::cout << ",";
		}

		std::this_thread::sleep_for(0.1s);
	}

	std::cout << "]" << std::endl;
	click_thread.join();
}
