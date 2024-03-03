//
//	config.hpp
//

#pragma once

#include <nlohmann/json.hpp>
#include <string>


class config
	{
		private:

		nlohmann::json conf_main;

		public:

		config();

		int get_config(const std::string conf_name);

	};

