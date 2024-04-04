# NB-IoT measurement
In this comprehensive guide will walk you through the process of setting up and launching an Arduino NB-IoT application using an Arduino MKR 1500 board. Whether you're a beginner or an experienced developer, this guide will provide you with step-by-step instructions to get your NB-IoT project up and running smoothly.
In this guide, we'll cover the following sections:

In this guide, we'll cover the following sections:

1. **Configuration Documentation:** Understand how to configure the Arduino MKR 1500 board for NB-IoT connectivity.
2. **NB-IoT MQTT Documentation:** Learn how to implement an MQTT application on the Arduino MKR 1500 board.
3. **Setup Guide:** Follow detailed steps to set up your Arduino NB-IoT application from start to finish.

Feel free to navigate directly to the section you need using the quick links below:

- [Configuration Documentation](#documentation-configuration-sketch)
- [NB-IoT MQTT Documentation](#documentation-arduino-nb-iot-mqtt-application)
- [Setup Guide](#arduino-nb-iot-application-setup-guide)

Let's dive in and explore the world of Arduino NB-IoT applications!


# Documentation: Configuration Sketch

This documentation provides an overview and explanation of the Arduino sketch used to configure the preferred Radio Access Technology (RAT) and extended Discontinuous Reception (eDRX) settings for an Arduino MKR NB 1500 board.

## Overview

The provided sketch allows users to select their preferred 4G Narrowband Radio Access Technology (RAT) and eDRX configuration. These configurations are crucial for establishing and maintaining network connectivity for NB-IoT applications.

## Usage

1. **Setup:**
   - Connect your Arduino MKR NB 1500 board to your computer via USB.
   - Open the Arduino IDE and upload the provided sketch to the board.

2. **Configuration:**
   - Upon uploading the sketch, the Serial Monitor will prompt you to choose your preferred RAT and eDRX configuration.
   - RAT options:
     - CAT M1 only (0)
     - NB IoT only (1)
     - CAT M1 preferred, NB IoT as failover (2)
     - NB IoT preferred, CAT M1 as failover (3)
   - eDRX options:
     - Disable eDRX (0)
     - Enable eDRX with TAU of 10.24s (1)
     - Enable eDRX with TAU of 20.48s (2)
     - Enable eDRX with TAU of 40.96s (3)
     - Enable eDRX with TAU of 61.44s (4)

3. **Selection:**
   - Enter the corresponding number for your preferred RAT and eDRX configuration in the Serial Monitor.
   - The sketch will set the chosen configuration and apply the changes.

4. **Apply Changes:**
   - The selected RAT and eDRX configuration will be saved to the modem's internal memory.
   - The changes will be applied, and the configuration will be preserved through subsequent uploads of MKR NB 1500 sketches.

## Functions

### `setRAT(String choice, String edrx)`

- **Description:** Sets the RAT and eDRX configuration based on user input.
- **Parameters:**
  - `choice`: String representing the chosen RAT configuration.
  - `edrx`: String representing the chosen eDRX configuration.
- **Returns:** `true` if the configuration is successfully set.

### `apply()`

- **Description:** Applies the changes and saves the configuration to the modem's internal memory.
- **Returns:** `true` if the changes are successfully applied.

## Additional Notes

- Ensure that the SIM card inserted into the Arduino MKR NB 1500 board supports NB-IoT network.
- Refer to the documentation provided by Arduino for more information on configuring and using the MKR NB 1500 board.

# Documentation: Arduino NB-IoT MQTT Application

This documentation provides an overview and explanation of the Arduino sketch used to implement an MQTT (Message Queuing Telemetry Transport) application on an Arduino MKR NB 1500 board.

## Overview

The provided sketch establishes communication with an MQTT broker over the NB-IoT network and facilitates the exchange of messages between the Arduino board and the broker. It utilizes the ArduinoMqttClient library for MQTT functionality and the MKRNB library for NB-IoT connectivity.

## Usage

1. **Setup:**
   - Connect your Arduino MKR NB 1500 board to your computer via USB.
   - Open the Arduino IDE and upload the provided sketch to the board.
   - Ensure that the necessary libraries (`MKRNB` and `ArduinoMqttClient`) are installed in your Arduino IDE.

2. **Configuration:**
   - Modify the MQTT configurations section in the sketch to specify the broker address, port, and topic details according to your MQTT setup.
   - Optionally, set the PIN number for the NB-IoT module in the `PINNUMBER` constant.

3. **Operation:**
   - Upon setup, the sketch connects to the NB-IoT network and establishes a connection with the MQTT broker.
   - It subscribes to the specified MQTT topic to receive messages.
   - In the loop, it sends messages at regular intervals to the MQTT broker.
   - Received messages are printed to the Serial Monitor, and reception delay is calculated and sent back to the broker.

4. **Functionality:**
   - The sketch generates a unique message ID for each message sent and maintains a list of sent IDs.
   - It handles the sending of message IDs and reception delay information to separate MQTT topics.

## Functions

### `setup()`

- **Description:** Initializes the NB-IoT and MQTT connections, subscribes to the MQTT topic, and allocates memory for storing message IDs.

### `loop()`

- **Description:** Continuously polls for MQTT messages, sends messages at regular intervals, and calculates reception delay.

### `onMqttMessage(int messageSize)`

- **Description:** Callback function executed when a message is received from the MQTT broker. Prints the message topic and contents to the Serial Monitor and sends reception delay information back to the broker.

### `generateUniqueId(char *buffer, int length)`

- **Description:** Generates a unique ID for each message using a random character set.

### `sendIdList()`

- **Description:** Sends the list of message IDs to a separate MQTT topic and clears the message IDs list.

## Additional Notes

- Ensure that the NB-IoT network is available and properly configured for the Arduino MKR NB 1500 board.
- Verify that the MQTT broker address, port, and topics are correctly configured to match your MQTT setup.
- Use the Serial Monitor for debugging and monitoring MQTT message exchange.

# Arduino NB-IoT Application Setup Guide

This guide will walk you through the process of setting up and launching an Arduino NB-IoT application using an Arduino MKR 1500 board, a SIM card that supports NB-IoT network, a USB connection, and the Arduino IDE.

## Requirements:

- Arduino MKR 1500 board
- SIM card compatible with NB-IoT network
- USB cable
- Arduino IDE installed on your laptop

## Steps:

1. **Insert SIM Card:**
   - Insert the SIM card into the SIM card slot on your Arduino MKR 1500 board.

2. **Connect Arduino to Laptop:**
   - Connect the Arduino MKR 1500 to your laptop using the USB cable.

3. **Upload Initial Sketch:**
   - Open the Arduino IDE on your laptop.
   - Upload the first sketch named "parametrage" to your Arduino MKR 1500 board.
   - Once uploaded, navigate to `Tools -> Serial Monitor` in the Arduino IDE.

4. **Select RAT and eDrx:**
   - In the serial monitor, select your choice of Radio Access Technology (RAT) and extended Discontinuous Reception (eDrx) according to your requirements.

5. **Open Second Sketch:**
   - Now, open the second sketch named "Measurement" in the Arduino IDE.

6. **Configure Parameters:**
   - Within the "Measurement" sketch, adjust the parameters based on your preferences:
     ```cpp
     // Mission parameters
     const int idLength = 6; // Adjust the length as needed
     unsigned long messageInterval = 1000; // Interval between messages in milliseconds
     unsigned long duration = 60000; // Duration in milliseconds
     ```
   
7. **Upload Measurement Sketch:**
   - Upload the modified "Measurement" sketch to your Arduino MKR 1500 board.

8. **Monitor Data Transmission:**
   - After uploading the sketch, you should see data transmission in the serial monitor. This indicates that your Arduino is successfully sending data.

9. **Utilize Services:**
   - To visualize and interact with the data, you can use our services provided in the second repository. This includes integration with platforms like Node-RED.

## Note:
- Make sure your SIM card subscription supports NB-IoT network.
- Ensure that you have a stable internet connection during the setup process.
- Refer to the documentation provided with your Arduino MKR 1500 for additional assistance.

Follow these steps carefully to successfully launch your Arduino NB-IoT application. If you encounter any issues, refer to troubleshooting guides or seek assistance from relevant forums and communities.




