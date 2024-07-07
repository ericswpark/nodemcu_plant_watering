# NodeMCU plant watering project

Quick and dirty Arduino sketch that uses a NodeMCU board to control four relays based on four capacitive moisture sensor inputs.

## Setup

- Create a `WiFiCredentials.h` file with the following contents:

```cpp
#ifndef WIFICRED_H
#define WIFICRED_H

// Enter your Wi-Fi credentials here
const char* ssid = "SSID_HERE";
const char* password = "PASSWORD_HERE";

// Enter OTA password if desired
const char* ota_pw = "OTA_PASSWORD_HERE";

#endif
```

- Compile and upload