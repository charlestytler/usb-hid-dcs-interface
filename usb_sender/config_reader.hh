// Copyright 2021 Charles Tytler

#pragma once

#include "../external/json/src/nlohmann/json.hpp"

namespace usb_sender
{
using json = nlohmann::json;

// Reads in a .json config file.
// Throws: exception if unable to open file.
json load_config(const char *path);

} // namespace usb_sender
