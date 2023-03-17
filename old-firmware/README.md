# TIME II Code Base

# Overview 

### The code serves 3 main functions: <br />
1) Write each received packet from the nano lab to the SD card. <br />
2) Monitor and maintain a consistent temperature across all the heating pads. <br />
3) Keep track of each phase of flight to run the experiment at the correct time. <br />

## Functions
1. `String extract_data(int num)`: Extracts the i<sup>th</sup> field from a data packet.
2. `bool temp_reg(void)`: Regulates temperature to give spec. (See relevant docs)
3. `float read_temp(void)`: Reads current temperature as a single precision `float`.
4. `void read_packet(void)`: Reads the current packet senti via serial and stores in a `char` array.
5. `void setup_sd(void)`: Initializes SD card along with the creation of a `.csv` files.
6.  `void write_sd(char* packet)`: Writes to SD card with the `char*` array.
7.  `void motor_setup(int STEP, int DIR, int nSLEEP)`: Assumes a servo motor and initalizes pins. (See source for pins)
8.  `void setup(void)`: All setup functions are called here as per Arduino Spec.
9.  `void loop(void)`: Main looping body of TIMEII as per Arduino Spec.
    
## Data Structures
1. `typedef enum {
    PREFLIGHT,
    MICROG,
    POSTFLIGHT
} STATES`: Data types to hold each state of TIME II. `PREFLIGHT`: Regulate temperature and write packets to SD card. <br />
`MICROG`: This is where the experiment is run, namely, the actuate of the motors to inject the antibotic. Notice, this occurs at the warning stage of for MICROG. (See Nanolab spec) <br />
`POSTFLIGHT`: TBD, mainly maintain temperature and write to SD card. <br />
2. `char current_packet[200]`: Holds the 200 byte packet sent via Serial.
3. `File log_file`: File instance used for writing.
4. `const int STEP, DIR, nSLEEP`: Variables for the motor pins.

## Test Files
1. `tests.py`: Randomly Generates the 200 Byte packet and checks Serial output for correctness. Notice, Serial output will be ignored in the official launch.
