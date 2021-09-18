// Copyright 2021 Charles Tytler

#pragma once

#include "../external/cpp-dcs-interface/dcs_interface/DcsInterface.h"
#include "../external/hidapi/hidapi/hidapi.h"
#include "../external/json/src/nlohmann/json.hpp"

#include <set>

namespace usb_sender
{
using json = nlohmann::json;

class HidSubscriber
{
    HidSubscriber(const json &subscription_settings);

    void update(const dcs_interface::DcsInterface &sim_monitor, hid_device *device_handle);

  private:
    const int dcs_id_;
    const double scale_;
    const int bias_;
    int last_command_; // Last command sent to USB Device.

    static constexpr int BUFFER_SIZE_ = 14;
    unsigned char command_buffer_[BUFFER_SIZE_] = {
        0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
};

class HidDevice
{
    HidDevice(const json &device_settings);

    ~HidDevice();

    void update_subscribers(const dcs_interface::DcsInterface &sim_monitor);

  private:
    hid_device *device_handle_;
    std::set<HidSubscriber> subscribers_{};
};

class UsbManager
{
    UsbManager(const json &device_list);
    ~UsbManager();

    void update_all(const dcs_interface::DcsInterface &sim_monitor);

  private:
    std::set<HidDevice> devices_{};
}
} // namespace usb_sender
