<!-- Please do not change this logo with link -->

[![MCHP](images/microchip.png)](https://www.microchip.com)

# USB CDC Virtual Serial Port Using AVR® DU Microcontroller
This example shows how to communicate between the AVR DU microcontroller and a host computer using the USB Communication Device Class (CDC). In addition to an application that will work with standard terminal applications, a python script is included showing how to easily interface with the AVR DU over CDC.

## Related Documentation
- [AVR® DU Family Product Page](https://www.microchip.com/en-us/products/microcontrollers-and-microprocessors/8-bit-mcus/avr-mcus/avr-du?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_AVR-DU&utm_content=avr64du32-cnano-usb-cdc-virtual-serial-port-mplab-mcc-github&utm_bu=MCU08)
- [USB CDC to USART Bridge using AVR DU Microcontroller](https://github.com/microchip-pic-avr-examples/avr64du32-cnano-usb-cdc-to-usart-bridge-mplab-mcc.git)
- [USB CDC Specification](https://www.usb.org/document-library/class-definitions-communication-devices-12)

## Software Used
- [MPLAB® X IDE 6.20.0](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_AVR-DU&utm_content=avr64du32-cnano-usb-cdc-virtual-serial-port-mplab-mcc-github&utm_bu=MCU08) or newer
- [MPLAB® XC8 2.46.0](https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_AVR-DU&utm_content=avr64du32-cnano-usb-cdc-virtual-serial-port-mplab-mcc-github&utm_bu=MCU08) or newer compiler
- [MPLAB® Code Configurator(MCC) v5.5.0](https://www.microchip.com/en-us/tools-resources/configure/mplab-code-configurator?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_AVR-DU&utm_content=avr64du32-cnano-usb-cdc-virtual-serial-port-mplab-mcc-github&utm_bu=MCU08) plug-in or newer
- [MPLAB Data Visualizer v1.3.1665](https://www.microchip.com/en-us/tools-resources/debug/mplab-data-visualizer) or newer 
- [Python 3.11.0](https://www.python.org/) or newer

## Hardware Used
- [AVR64DU32](https://www.microchip.com/en-us/product/AVR64DU32?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_AVR-DU&utm_content=avr64du32-cnano-usb-cdc-virtual-serial-port-mplab-mcc-github&utm_bu=MCU08)
- [AVR64DU32 Curiosity Nano](https://www.microchip.com/en-us/development-tool/EV59F82A?utm_source=GitHub&utm_medium=TextLink&utm_campaign=MCU8_AVR-DU&utm_content=avr64du32-cnano-usb-cdc-virtual-serial-port-mplab-mcc-github&utm_bu=MCU08)

## Setup

### Physical Setup
The AVR DU Curiosity Nano Development Board has two USB-C® ports. One for programming the device via the on-board debugger and one connected directly to the AVR DU. While programming the device over the AVR DU's port is possible using bootloaders, this example uses the debugger port so both ports needs to be connected to the host computer. After programming, only the AVR DU side needs to continue being connected.

The Curiosity Nano has an Adjustable Target Regulator that regulates voltage to 3.3V by default. Since the USB peripheral in the AVR64DU32 needs to run at 3.3V, it either needs a 3.3V supply connected on the VUSB pin or a 5.0V supply on VDD with the internal USB Voltage Regulator active. With the Curiosity Nano default settings, the VBUS pinheader on the board must be connected with the included jumper to supply 3.3V directly to VUSB.

### MCC Project Setup
This section shows how the example is set up in MPLAB using MCC. An overview of the complete MCC setup is shown in the image below:
<p><img src="images/mcc_overview.jpg" width="600"/></p>

1. Start a new Microchip Embedded Application Project in MPLAB, selecting the AVR DU as your device.
2. Open MCC to start setting up the USB Device Stack:
    * If the USB library doesn’t show up in Libraries under Device Resources (By default on the left in MPLAB) it needs to be added in the Content Manager menu. The button is in the Device Resources section or under Tools in the menu.
3. Add the USB Device Stack library to the project.
4. Add the AC0, RTC and VREF drivers to the project.
5. Follow the setup below to configure the library and drivers.

#### USB General Settings
The configurator is set so that the AVR DU will identify as a CDC device on the highest level. The toggle switch for adding the Virtual Serial example code is also enabled.
<p><img src="images/mcc_usb_general_settings.jpg" width="500"/></p>

#### USB Device Descriptors
For this example, the Device Descriptors section is left as default. For other applications, information on the product can be added here.
<p><img src="images/mcc_usb_device_descriptors.jpg" width="500"/></p>

#### USB Interfaces
For this example, both a communication and data interface are required.
<p><img src="images/mcc_usb_interfaces.jpg" width="500"/></p>

#### USB CDC Communication Interface
The communication interface determines how the communication flow between the host and device. The Abstract Control Model (ACM) is used as a subclass but few of the supported commands are needed. Three Functional Descriptors are also required:
* Header - Required for Functional Descriptors
* ACM - Tells the host what commands the device supports (D1 indicates that device supports basic Line Coding and Control Line State commands needed for terminal applications)
* Union - Tells the host the relationship between two or more interfaces
<p><img src="images/mcc_usb_interface_comm.jpg" width="500"/></p>

### USB CDC Data Interface
All communication is sent over the data interface for this basic Virtual Serial Port application. The Packet Size field determines how much data can be transmitted in one USB packet. The data sent can be bigger or smaller and the stack will transmit a less amount or split it up in smaller packages.
<p><img src="images/mcc_usb_interface_data.jpg" width="500"/></p>

### Device Clock Setup
This example is configured to run on 24 MHz. The minimum oscillator frequency for USB on the AVR DU is 12 MHz.
<p><img src="images/mcc_clock_control.jpg" width="500"/></p>

The application uses a delay function to blink an LED if the USB connection fails. This delay function is dependent on knowing the main clock speed through the F_CPU define. Here, this has been set up as a preprocessed define macro in the project settings, as seen in the image below.

<p><img src="images/mplab_macros.jpg" width="500"/></p>

Alternatively, it could have been added in the main file as `#define F_CPU 24000000UL` above the `#include <util/delay.h>` line.

### USB Voltage Detection Setup
To ensure that the USB peripheral only tries to attach to the bus when the Curiosity Nano is connected to the PC, the Analog Comparator will periodically check if the voltage is within the acceptable range for V<sub>BUS</sub>.

#### Voltage Reference Setup
In the V<sub>REF</sub> peripheral, the Voltage Reference is set to 2.048V.
<p><img src="images/mcc_vref_hardware_settings.jpg" width="600"/></p>

#### Analog Comparator Setup (AC)
The Analog Comparator must be enabled by toggling Enable under Hardware Settings.

The positive input is set to the USB DETECT pin on the Curiosity Nano which is connected to Positive Pin 4 on the AC by default. The detection threshold is set using the internal reference voltage generator (DACREF) which is selected as the negative input to the AC.

To calculate the DACREF, use the formula from the data sheet:

*V_DACREF = (DACREF / 256) * V_REF*

Due to the voltage divider present on the Curiosity Nano, a threshold of 0.32V is needed for this project. Inputting this value into the Requested Voltage field in MCC can calculate the DACREF value automatically.

Refer to the [AVR64DU32 Curiosity Nano User Guide](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/UserGuides/AVR64DU32-Curiosity-Nano-UserGuide-DS50003671.pdf) for more information on how the *USB DETECT* is implemented on the Curiosity Nano.

<p><img src="images/mcc_ac_hardware_settings.jpg" width="500"/></p>

### RTC Setup
The RTC Periodic Interrupt Timer (PIT) is used to trigger the voltage detection described above. 

#### RTC Hardware Settings
The RTC is configured to run on a 1 kHz clock with no prescaler.
<p><img src="images/mcc_rtc_hardware_settings.jpg" width="500"/></p>

#### RTC Interrupt Settings
The PIT is then set to trigger at every 32 clock cycles of the RTC clock. this gives an update rate of ~31 Hz.
<p><img src="images/mcc_rtc_interrupt_settings.jpg" width="500"/></p>

The application is set up to need five stable voltage readings before initiating the USB communication. This means that, with no voltage fluctuations and the settings above, the start-up time will be in the 0.16s range.

### LED Setup
The on-board LED of the Curiosity Nano is used to indicate if the USB communications has failed. The LED is connected to the PF1 pin and can be selected as an output in the Pin Grid View below.

<p><img src="images/mcc_pin_grid.jpg" width="600"/></p>

The pin is given a custom name in the Pins menu, as seen below. This makes the code easier to read with function generated using this name.

<p><img src="images/mcc_pin_naming.jpg" width="600"/></p>

### Global Interrupts
Since this example uses interrupts for voltage monitoring, global interrupt must be enabled in the Interrupt Manager.

<p><img src="images/mcc_interrupt.jpg" width="500"/></p>

### Application
The included application is set up to echo back any data received over CDC.

The application checks if there is data in the received buffer and adds the data to the transmit buffer as long as the peripheral is ready and the buffer isn't full. The full flow of the main application can be seen in the diagram below.

<p><img src="images/application_flow.jpg" width="500"/></p>

The USB part of the application is set up in polling mode and therefore needs to handle the USB peripheral inside the main loop. Interrupt mode is also selectable in MCC and it simplifies the application by removing the need for USB handler.

### Identify Virtual Serial Port Number
When the device is programmed, it will show up as a Virtual Serial Port on the host. The method varies between operating systems and the most common cases are listed below. As MPLAB Data Visualizer is used in this example, the appropriate serial ports will show up directly in the program.

#### Windows®
In Windows, the easiest way to identify the port number is to go to *Device Manager>Ports (COM and LPT)* to easily identify the port number.. The device shows up as USB Serial Device (COM##), where ## is the number assigned by the host.

Alternatively, the following commands will also list the devices in terminal.

Command Prompt:
```
reg query HKLM\HARDWARE\DEVICEMAP\SERIALCOMM
```

PowerShell:
```
Get-WMIObject Win32_SerialPort | Select-Object Name,DeviceID,Description
```

#### macOS®  and Linux®
Using the terminal, add the command below to generate a list of connected devices.

```
ls /dev/tty.*
```

## Operation
This section assumes that the setup has been followed and that the device is programmed and connected to the host.

### MPLAB Data Visualizer
Step-by-step guide to open communication:
1. Open MPLAB Data Visualizer:
    * The Curiosity Nano will show up in the connection pane to the left side of the window
2. Send the COM port to the terminal window:
    * While hovering over the Curiosity Nano COM port, an option to "Display as text in the terminal" will appear
    * Serial connection will now have started
<p><img src="images/data_visualizer_capturing_serial.jpg" width="300"/></p>

3. Write any input in the terminal window and it will echo back when enter is pressed.
<p><img src="images/data_visualizer_terminal_window.jpg" width="700"/></p>

### Python® Script
Reading the USB CDC Virtual Serial Port data in a terminal isn't always the most useful way to access it. This section will demonstrate how to transmit and receive data using a Python script.

In addition to basic packages included by the standard Python installation, the script also uses [pyserial](https://pypi.org/project/pyserial/) that needs to be installed separately.

```
pip install pyserial
```

The included script is quite sparse and is only meant to show the basic functionality. While both Curiosity Nanos USB ports are connected and the device is programmed as described in the previous example, running the script is done using the following command:

```
python usb_cdc_virtual_serial_port.py
```

The python prefix depends on the installed Python version and setup. 

Running the script will print a status message for trying to open the serial communication:

```
Opening serial communication...
```

When communication is established, it will transmit a preset array of values to the AVR DU and print the following:

```
Transmitting Data:
<data transmitted as hex values>
```

The script will then attempt to read the echo from the AVR DU using the number of transmitted bytes as a limit on how many bytes to read. It will then print the received bytes in ASCII form:

```
Received Data:
b'<data received as ASCII characters>'
```

Python's `serial.read()` interprets the returned values as ASCII text, resulting in an array of chars instead of numbers. In the example script, this has been used directly, but if the values are to be used in another format, the read data must be converted.

Finally, the script will close the serial communication as not to hold up the device for other use.

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