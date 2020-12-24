#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include "telemetry.h"
#include "i3json.h"
#include "telemetry_functions.h"
#include "telemetry_color.h"
#include "config.h"
using namespace std::chrono_literals;

std::vector<Telemetry> telemetries {
	Telemetry {"ip",        config::show_ip,   ip_color,        get_ip,        160s, false /* we dont want a separator between the next element */},
	Telemetry {"connected", config::show_ip,   connected_color, get_connected, 1s   },
	Telemetry {"ram",       config::show_ram,  ram_color,       get_ramusage,  3s   },
	Telemetry {"hdd",       config::show_hdd,                   get_hddusage,  10s  },
	Telemetry {"date",      config::show_date, config::fine,    get_date,      60s  },
	Telemetry {"time",      config::show_time,                  get_time,      1s   }
};

Telemetry separator {"sep", config::have_separator, config::separator_color, get_separator, 31536000s /* lol should probably make a "dont update" */ };

int main() {
	bool noexit = true;

	initialize();

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

		std::cout << json.get() << std::endl;
		std::flush(std::cout);
		std::this_thread::sleep_for(1s);
		std::cout << ",";
	}
}