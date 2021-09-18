// Copyright 2021 Charles Tytler

#include "config_reader.hh"
#include "dcs_subscriber.hh"
#include "usb_sender.hh"

namespace usb_sender
{
int main()
{
    constexpr char USB_DEVICES_CONFIG[] = "usb_devices_config.json";

    const json config = load_config(USB_DEVICES_CONFIG);
    UsbManager usb_manager(config["Devices"]);

    const dcs_interface::DcsConnectionSettings settings = {.rx_port = config["ConnectionSettings"]["listener_port"],
                                                           .tx_port = config["ConnectionSettings"]["send_port"],
                                                           .ip_address = config["ConnectionSettings"]["ip_address"]};
    dcs_interface::DcsInterface sim_monitor(settings);

    for (;;) {
        sim_monitor.update_dcs_state();
        usb_manager.update_all(sim_monitor);
        // Add a timer wait.
    }

    return 0;
}
} // namespace usb_sender
