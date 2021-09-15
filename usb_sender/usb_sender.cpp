// Copyright 2021 Charles Tytler

#include "../external/hidapi/hidapi/hidapi.h"
#include "../external/cpp-dcs-interface/dcs_interface/DcsInterface.h"
#include "../external/json/src/nlohmann/json.hpp"

#include <string>
#include <iostream>
#include <fstream>

using json = nlohmann::json;

json load_config(const std::string &path)
{
    std::ifstream config_input(path);
    json config;
    config_input >> config;
    return config;
}

int main()
{
    const json config = load_config("usb_devices_config.json");
    std::cout << "Config loaded: " << config["Device_1"]["VID"] << std::endl;

    const int result = hid_init();
    return result;
}