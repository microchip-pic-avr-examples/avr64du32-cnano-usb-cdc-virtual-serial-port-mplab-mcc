<!-- Please do not change this logo with link -->

[![MCHP](images/microchip.png)](https://www.microchip.com)

# USB CDC Virtual Serial Port using AVR® DU Microcontroller
This example shows how to communicate between the AVR DU microcontroller and a host computer using the USB Communication Device Class (CDC). In addition to an application that will work with standard terminal applications, a python script is included showing how to easily interface with the AVR DU over CDC.

## Related Documentation
- [AVR® DU Family Product Page](https://www.microchip.com/en-us/products/microcontrollers-and-microprocessors/8-bit-mcus/avr-mcus/avr-du)
- [USB CDC to USART Bridge using AVR DU Microcontroller](https://github.com/microchip-pic-avr-examples/avr64du32-cnano-usb-cdc-to-usart-bridge-mplab-mcc.git)
- [USB CDC Specification](https://www.usb.org/document-library/class-definitions-communication-devices-12)

## Software Used
- MPLAB® X IDE 6.20.0 or newer [(MPLAB® X IDE 6.20)](https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-x-ide?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_MMTCha_MPAE_Examples&utm_content=avr64du32-cnano-usb-cdc-virtual-serial-port-mplab-mcc-github)
- MPLAB® XC8 2.46.0 or newer compiler [(MPLAB® XC8 2.46)](https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-xc-compilers?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_MMTCha_MPAE_Examples&utm_content=avr64du32-cnano-usb-cdc-virtual-serial-port-mplab-mcc-github)
- MPLAB® Code Configurator (MCC) plugin 5.5.0 or newer [(MPLAB® Code Configurator 5.5.0)](https://www.microchip.com/en-us/tools-resources/configure/mplab-code-configurator)
- MPLAB® Data Visualizer 1.3.1335 or newer [(MPLAB Data Visualizer v1.3.1665)](https://www.microchip.com/en-us/tools-resources/debug/mplab-data-visualizer)
- Python 3.11.0 or newer [Python](https://www.python.org/)

## Hardware Used
- [AVR64DU32 Curiosity Nano](https://www.microchip.com/en-us/development-tool/EV59F82A)

## Setup

### Physical Setup
The AVR DU Curiosity Nano Development Board has two USB-C ports. One for programming the device via the onboard debugger and one connected directly to the AVR DU. While programming the device over the AVR DU's port is possible using bootloaders, this example uses the debugger port so both ports needs to be connected to the host computer. After programming only the AVR DU side needs to continue being connected.

### MCC Setup
This section shows how the example is set up in MCC.

#### USB General Settings
The configurator is set so that the AVR DU will identify as a CDC device on the highest level. The toggle switch for adding the Virtual Serial example code is also enabled.
<p><img src="images/mcc_usb_general_settings.jpg" width="500"/></p>

#### USB Device Descriptors
For this example the Device Descriptors section is left as default. For other applications, information on the product can be added here.
<p><img src="images/mcc_usb_device_descriptors.jpg" width="500"/></p>

#### USB Interfaces
For this example, both a communication and data interface are required.
<p><img src="images/mcc_usb_interfaces.jpg" width="500"/></p>

#### USB CDC Communication Interface
The communication interface is the one that sets up how the communication flows in the setup. The Abstract Control Model (ACM) is used as a subclass but few of the supported commands are needed. Three Functional Descriptors are also required:
* Header - Required for Functional Descriptors
* ACM - Tells the host what commands the device supports (D1 indicates that device supports basic *Line Coding* and *Control Line State* commands)
* Union - Tells the host the relationship between two or more interface
<p><img src="images/mcc_usb_interface_comm.jpg" width="500"/></p>

### USB CDC Data Interface
All communication is sent over the data interface for this basic Virtual Serial Port application. The Packet Size field determines how much data can be transmitted in one USB packet. The data sent can be bigger or smaller and the stack will transmit less or split it up in smaller packages.
<p><img src="images/mcc_usb_interface_data.jpg" width="500"/></p>

### Device Clock Setup
This example is configured to run on 24 MHz. The minimum oscillator frequency for USB on the AVR DU is 12 MHz.
<p><img src="images/mcc_clock_control.jpg" width="500"/></p>

### Application
The example application is set up to write back any data received over CDC.

The application checks if there is data in the received buffer and adds the data to the transmit buffer as long as the peripheral is ready and the buffer isn't full. The full flow of the main application can be seen in the diagram below.

<p><img src="images/application_flow.jpg" width="400"/></p>

The application is set up in polling mode and therefore needs to handle the USB peripheral inside the main loop. Interrupt mode can be selected in MCC which would simplify the application by removing the need for USB handler.

### Identify Virtual Serial Port Number
When the device is programmed it will show up as a Virtual Serial Port on the host. The method varies between operating systems and the most common methods are listed below. As MPLAB Data Visualizer is used in this example the appropriate serial ports will show up directly in the program.

#### Windows
In Windows, the easiest way to identify the port number is to go into *Device Manager* and look under *Ports (COM & LPT)*. The device would show up as *USB Serial Device (COM##)* where ## is the number assigned by the host.

Alternatively the following commands will also list the devices in terminal.

Command Prompt:
```
reg query HKLM\HARDWARE\DEVICEMAP\SERIALCOMM
```

PowerShell:
```
Get-WMIObject Win32_SerialPort | Select-Object Name,DeviceID,Description
```

#### Mac/Linux
Using the terminal, a list of connected devices will show if the command below is used.

```
ls /dev/tty.*
```

## Operation
This section assumes that the setup has been followed and that the device is programmed and connected to the host.

### MPLAB Data Visualizer
* Open MPLAB Data Visualizer
* Start serial communication
  * show the different methods of starting it
* Demonstrate writing to the terminal
* Possibly add section demonstrating live terminal in putty

#### Starting Serial Connection
<p><img src="images/data_visualizer_capturing_serial.jpg" width="300"/></p>

#### Using the Terminal
<p><img src="images/data_visualizer_terminal_window.jpg" width="700"/></p>


### Python Script
Reading the USB CDC Virtual Serial Port data in a terminal isn't always the most useful way to access it. This section will demonstrate how to transmit and receive data using a Python script.

In addition to basic packages included by the standard Python installation it also uses [pyserial](https://pypi.org/project/pyserial/) that needs to be installed separately.

```
pip install pyserial
```

The included script is quite sparse and is only meant to show the basic functionality. While the AVR DU's USB port is connected and the device is programmed for the previous example, running the script is done using the following command:

```
python usb_cdc_virtual_serial_port.py
```

The python prefix depends on the installed Python version and setup. 

Running the script will print a status message for trying to open the serial communication:

```
Opening serial communication...
```

When communication is established it will transmit a preset array of values to the AVR DU and print the following:

```
Transmitting Data:
<data transmitted as hex values>
```

The script will then attempt to read the echo from the AVR DU using the number of transmitted bytes as a limit on how many bytes to read. It will then print the received bytes in ASCII form:

```
Received Data:
b'<data received as ASCII characters>'
```

Python's `serial.read()` interprets the returned values as ASCII text, resulting in an array of chars instead of numbers. In the example script, this has been used directly but if the values are to be used in another format the read data must be converted.

Finally the script will close the serial communication as not to hold up the device for other use.

```
Closing the serial communication.
```

The script itself will try to identify the connected Virtual Serial Port number using the VID and PID used in the MCC setup. If it throws an error, or the VID or PID is changed, the script has an optional argument `-s` that can be used to input the number. This is exemplified below:

```
python usb_cdc_virtual_serial_port.py -s COM10
```

## Summary
By following this example, the user will:
1. Understand the basics of CDC communication on the AVR DU.
2. Be able to create simple applications where CDC is the communication protocol between host and device.