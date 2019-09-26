SparkFun Edge 2
========================================

![SparkFun Edge 2](https://cdn.sparkfun.com//assets/parts/1/3/9/7/5/15420-SparkFun_Edge_2_Development_Board_-_Artemis-01.jpg)

[*SparkFun Edge 2 (DEV-15420)*](https://www.sparkfun.com/products/15420)

Edge computing is here! You've probably heard of this latest entry to the long lineage of tech buzzwords like "IoT," "LoRa," and "cloud" before it, but what is “the edge” and why does it matter? The cloud is impressively powerful but all-the-time connection requires power and connectivity that may not be available. Edge computing handles discrete tasks such as determining if someone said "yes" and responds accordingly. The audio analysis is done at the edge rather than on the web. This dramatically reduces costs and complexity while limiting potential data privacy leaks.

In collaboration with Google and Ambiq, SparkFun's Edge 2 Development Board is based around the newest edge technology and is perfect for getting your feet wet with voice and even gesture recognition without relying on the distant services of other companies. The truly special feature is in the utilization of SparkFun's open-source and FCC Certified Artemis module, whose ultra-efficient ARM Cortex-M4F 48MHz (with 96MHz burst mode) processor, is spec’d to run TensorFlow Lite using only 6uA/MHz. The SparkFun Edge 2 board currently measures ~1.6mA@3V and 48MHz and can run solely on a CR2032 coin cell battery for up to 10 days. Artemis sports all the cutting edge features expected of modern microcontrollers including six configurable I2C/SPI masters, two UARTs, one I2C/SPI slave, a 15-channel 14-bit ADC, and a dedicated Bluetooth processor that supports BLE5. On top of all that the Artemis has 1MB of flash and 384KB of SRAM memory - plenty for the vast majority of applications.

On the Edge 2 you'll have built-in access to sensors, Bluetooth, I2C expansion, and GPIO inputs/outputs. To support edge computing cases like voice recognition the Edge 2 board features two MEMS microphones, an ST LIS2DH12 3-axis accelerometer on its own I2C bus, and a connector to interface to an OV7670 camera (sold separately & functionality coming soon). As TensorFlow updates their algorithms more and more features will open up for the SparkFun Edge 2. An onboard Bluetooth antenna gives the Edge 2 out-of-the-box connectivity. Also available on the board is a Qwiic connector to add I2C sensors/devices, four LEDs, and four GPIO pins. To boast the low-power capabilities of the board we've outfitted it with battery operation from the CR2032 coin cell holder. Programming the board is taken care of with an external USB-serial adapter like the Serial Basic Breakout via a serial bootloader, but for more advanced users we've also made available the JTAG programming and debugger port.

As a brave explorer of this new technology, you'll have to use some advanced concepts but don't worry. Between Ambiq Micro's Software Development Kit and our SDK Setup Guide you'll have access to plenty of examples to begin working with your hardware.

Now get out there and make something amazing with the latest machine learning technology at your very own fingertips!

Repository Contents
-------------------

* **/Documentation** - Data sheets, additional product information
* **/Firmware** - Arduino test firmware sketch
* **/Hardware** - Eagle design files (.brd, .sch)
* **/Production** - Production panel files (.brd)

Documentation
--------------
* **[Board Support Package (BSP)](https://github.com/sparkfun/SparkFun_Edge_BSP)** - Ambiq SDK Board Support Package for the SparkFun Edge.
* **[Edge Board Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-edge-hookup-guide)** - Basic hookup guide for the SparkFun Edge.
* **[Software Development Kit (SDK) Setup Guide](https://learn.sparkfun.com/tutorials/using-sparkfun-edge-board-with-ambiq-apollo3-sdk)** - Software Development Kit for working with the SparkFun Edge.

Product Versions
----------------
* [DEV-15420](https://www.sparkfun.com/products/15420)- SparkFun Edge 2 w/ Artemis Module
* [DEV-15170](https://www.sparkfun.com/products/15170)- SparkFun Edge

Version History
---------------
* [v20](https://github.com/sparkfun/SparkFun_Edge/tree/v2.0.0) - Edge with the Artemis
* [v10](https://github.com/sparkfun/SparkFun_Edge/tree/v10) - Initial HW release


License Information
-------------------

This product is _**open source**_! 

Please review the LICENSE.md file for license information. 

If you have any questions or concerns on licensing, please contact techsupport@sparkfun.com.

Distributed as-is; no warranty is given.

- Your friends at SparkFun.

_<COLLABORATION CREDIT>_
