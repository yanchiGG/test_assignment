//
//	config.cpp
//

#include "../include/config.hpp"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

	config::config()

	{	
		std::ifstream f("config.json");
		conf_main = nlohmann::json::parse(f);
	}

	int config::get_config(const std::string conf_name)
	{
		std::string conf_str;
		conf_str = conf_main[conf_name];
		return std::stoi(conf_str);
	}
