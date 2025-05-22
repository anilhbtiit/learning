#include <iostream>
#include <array>
#include <algorithm>
#include <string>

struct Device {
    int deviceId;
    bool status;
    std::string location;
};

// Function to initialize devices
std::array<Device, 5> initializeDevices() {
    std::array<Device,5> temp{
        Device{1, true, "Living Room"},
        Device{2, false, "Kitchen"},
        Device{3, true, "Bedroom"},
        Device{4, false, "Office"},
        Device{5, true, "Garage"}
    };
    return temp;
}

// Function to search for a device by deviceId
std::array<Device, 5>::iterator findDeviceById(std::array<Device, 5>& devices, int searchDeviceId) {
    return std::find_if(devices.begin(), devices.end(),
        [searchDeviceId](Device dev) {
            return dev.deviceId == searchDeviceId;
        });
}

// Function to display device information
void displayDeviceInfo(const Device& dev) {
    std::cout << "Device ID: " << dev.deviceId << std::endl;
    std::cout << "Status: " << (dev.status ? "Active" : "Inactive") << std::endl;
    std::cout << "Location: " << dev.location << std::endl;
}

int main() {
    std::array<Device, 5> devices = initializeDevices();
    int searchDeviceId = 3;
    auto it = findDeviceById(devices, searchDeviceId);
    if (it != devices.end()) {
        displayDeviceInfo(*it);
    } else {
        std::cout << "Device with ID " << searchDeviceId << " not found." << std::endl;
    }

    return 0;
}
