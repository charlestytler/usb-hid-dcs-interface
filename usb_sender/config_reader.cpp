// Copyright 2021 Charles Tytler

#include "config_reader.hh"

#include <fstream>
#include <stdexcept>

namespace usb_sender
{

json load_config(const char *path)
{
    json config;
    std::ifstream config_input(path);
    if (config_input.is_open()) {
        config_input >> config;
        config_input.close();
    } else {
        throw std::runtime_error("Unable to open config file.");
    }
    return config;
}
} // namespace usb_sender
