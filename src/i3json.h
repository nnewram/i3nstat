#pragma once
#include <string_view>
#include "config.h"

std::string strfy(const std::string& str) {
	return "\"" + str + "\"";
}

std::string style() {
	return	  strfy("border") + ": " + strfy(config::background) + ", "
		+ strfy("background") + ": " + strfy(config::background) + ", "
		+ strfy("separator") + ": " + "true" + ", "
		+ strfy("separator_block_width") + ": " + "1" + ", "
		+ strfy("border_top") + ": " + "2" + ", "
		+ strfy("border_bottom") + ": " + "1" + ", "
		+ strfy("border_left") + ": " + "5" + ", "
		+ strfy("border_right") + ": " + "5";
}

class i3json {
private:
	std::string res;
	bool isfirst = true;
public:
	i3json() : res("") {}

	void add(const std::string& name, const std::string& color, const std::string& text) {
		if (res == "")
			res += "[";
		
		res += "{"	+ strfy("name")		+	": " + strfy(name)		+ ", "
				+ strfy("color")	+	": " + strfy(color)		+ ", "
				+ strfy("full_text")	+	": " + strfy(text)		+ ", "
				+ style()
			+ "}";
		
		res += ", ";

		isfirst = false;
	}

	std::string& get() {
		auto pos = res.find_last_of(",")-1;
		res[pos] = '}';
		res[pos + 1] = ']';
		return res;
	}
};

void initialize() {
	std::string bruh {""};
	
	std::cout << "{ " + strfy("version") + ": " << 1 <<  "}" << std::endl;
	std::cout << "[" << std::endl;
}