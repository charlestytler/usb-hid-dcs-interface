// Copyright 2021 Charles Tytler

#include "usb_sender.hh"

#include "../external/hidapi/hidapi/hidapi.h"
#include "config_reader.hh"

#include <stdexcept>

namespace usb_sender
{
HidSubscriber::HidSubscriber(const json &device)
    : dcs_id_(device["Subscribe"]["DCS_ID"]), scale_(device["Subscribe"]["Scale"]), bias_(device["Subscribe"]["Bias"]),
      last_command_(0)
{
}

void HidSubscriber::update(const dcs_interface::DcsInterface &sim_monitor, hid_device *device_handle)
{
    const unsigned int command = static_cast<int>(scale_ * sim_monitor.get_decimal_of_dcs_id(dcs_id_)) + bias_;
    if (command != last_command_) {
        command_buffer_[3] = static_cast<unsigned char>(max(command, 255));
        hid_write(device_handle, command_buffer_, BUFFER_SIZE_);
        last_command_ = command;
    }
}

HidDevice::HidDevice(const json &device) { device_handle_ = hid_open(device["VID"], device["PID"], NULL); }

HidDevice::~HidDevice() { hid_close(device_handle_); }

void HidDevice::update_subscribers(const dcs_interface::DcsInterface &sim_monitor)
{
    for (auto subscriber : subscribers_) {
        subscriber.update(sim_monitor, device_handle_);
    }
}

UsbManager::UsbManager(const json &device_list);
{
    const int result = hid_init();
    if (result != 0) {
        throw std::runtime_error("Unable to initialize USB HID library");
    }

    for (const json &device : device_list) {
        devices_.emplace(HidDevice(device));
    }
};

UsbManager::~UsbManager() { hid_exit(); }

void UsbManager::update_all(const dcs_interface::DcsInterface &sim_monitor)
{
    for (auto &device : devices_) {
        device.update_subscribers(sim_monitor);
    }
}

} // namespace usb_sender
