// Copyright 2021 Charles Tytler

#include "../external/hidapi/hidapi/hidapi.h"
#include "../external/cpp-dcs-interface/dcs_interface/DcsInterface.h"
#include "../external/json/src/nlohmann/json.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

json load_config(const char *path)
{
    json config;
    std::ifstream config_input(path);
    if (config_input.is_open())
    {
        config_input >> config;
        config_input.close();
    }
    else
    {
        throw std::runtime_error("Unable to open config file.");
    }
    return config;
}

int main()
{
    constexpr char USB_DEVICES_CONFIG[] = "usb_devices_config.json";

    const json config = load_config(USB_DEVICES_CONFIG);
    std::cout << "Config loaded: " << config["Device_1"]["VID"] << std::endl;

    const int result = hid_init();
    return result;
}
