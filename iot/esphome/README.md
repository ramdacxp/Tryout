# ESPHome

[ESPHome](https://esphome.io/) is the IoT counterpart for Home Assistant. It provides a proven platform to connect any kind of IoT device to HA using a simple YAML markup describing the board and attached hardware like sensors or displays. Under the hood Platform-IO is used to build the firmware. It can even be used from a web browser to make the startup easy.

## Web.ESPHome

Most ESP8266 and ESP32 development boards cen be connected via USB zu a host computer. If no USB connector is available, a TTL Serial Adapter is needed.

The firmware is transferred via a serial protocol to the board. This is even possible from a normal modern web browser (Chrome or Edge). Later on, if the device is connected to WLAN, updates can also transferred over the air (OTA).

[web.ESPHome.io](https://web.esphome.io/) provides a website to flash an initial software to an ESP, upload a firmware (which was built locally) or to check the logs of the device.

This is a done locally in the browser. Data is not sent to the site owner. If you trust this, you can even flash your Wifi credentials to a device.

**Hint:** A website can access the serial port only, if it was loaded vis HTTPS. Locally hosted copies of this site need to have a valid certificate.

**Hint 2:** Windows 10 and 11 already ship with the required serial drivers to connect devices via USB. If the connection fails. ESPHome offers the driver downloads. The CH340 driver is not available for Windows on ARM, but the others work.

## Home Assistant Integration

The ESPHome dashboard can be integrated into Home Assistant using the related extension.

This works even on Home Assistant OS on a Raspberry Pi 4.

## Standalone usage in Docker

Complete host network was not available.
But then it works when mounting the dashboard port in brigde mode.

Performance of sdk installation and build via the ESPHome dashboard is very slow. Even, if the number ob builds is restricted or the container gets more amount of CPU.

## Installation on Copilot PC (Windows 11 on ARM)

Python3 is now available for Arm. But the installation via "pip3 esphome" causes errors while resolving the dependencies.

The dependencies contain the VC++ build tools, which is a larger download.

## Installation in WSL on Copilot PC (Windows 11 on ARM)

**Hint:** As of 2024-10, the WSL USB connection is supported on x64 only, not on ARM. See [usbipd-win](https://github.com/dorssel/usbipd-win) and the [Microsoft Learn](https://learn.microsoft.com/en-us/windows/wsl/connect-usb) article. OTA updates work fine. Initial upload can be done via Web.ESPHome.

This description was tested with a Copilot PC wunnind Windows on ARM with WSL2 using `Ubuntu 22.04.5 LTS`.

Python3 is already installed in Ubuntu:

```bash
wsl

mischa@Armstrong:/mnt/c/Users/micha$ python3 --version
Python 3.10.12
```

Create a python virtual environment with the venv module (`-m venv`) and call it `esphome-env`. Load it and install ESPHome in it (`pip3`):

```bash
cd Tryout/iot/esphome
python3 -m venv esphome-env
source esphome-env/bin/activate
pip3 install esphome
```

From now on the `esphome` CLI can be used within the venv (which needs to be loaded via the `source` command). If a venv is used, its name is shown at the beginning of the prompt.

```bash
(esphome-env) mischa@Armstrong:/mnt/c/Users/micha/Source/Repos/Tryout/iot/esphome$ esphome -h
usage: esphome [-h] [-v] [-q] [-s key value] [--version] command ...

ESPHome 2024.10.2

positional arguments:
  command               Command to run:
    config              Validate the configuration and spit it out.
    compile             Read the configuration and compile a program.
    upload              Validate the configuration and upload the latest binary.
    logs (log)          Validate the configuration and show all logs.
    discover            Validate the configuration and show all discovered devices.
    run                 Validate the configuration, create a binary, upload it, and start logs.
    clean-mqtt          Helper to clear retained messages from an MQTT topic.
    wizard              A helpful setup wizard that will guide you through setting up ESPHome.
    mqtt-fingerprint    Get the SSL fingerprint from a MQTT broker.
    version             Print the ESPHome version and exit.
    clean               Delete all temporary build files.
    dashboard           Create a simple web server for a dashboard.
    rename              Rename a device in YAML, compile the binary and upload it.

options:
  -h, --help            show this help message and exit
  -v, --verbose         Enable verbose ESPHome logs.
  -q, --quiet           Disable all ESPHome logs.
  -s key value, --substitution key value
                        Add a substitution
  --version             Print the ESPHome version and exit.
```

Start the dashboard webserver with `esphome dashboard .` and open the dashboard at <http://localhost:6052>
