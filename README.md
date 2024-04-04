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


