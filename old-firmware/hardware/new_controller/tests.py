import serial
import argparse
import numpy as np 

#Max Float Value 
MAX_FLOAT = 3.402823466e38 #Maximum 4 byte float value
MIN_FLOAT = 1.175494351e-38 #Minimum 4 byte float value
#Packet Data 
flight_state = ['@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J']
binary_state = ['0', '1']

#Setup serial interface
ser = serial.Serial()
ser.baudrate = 115200

parser = argparse.ArgumentParser()
parser.add_argument("run test", help="'run-test' --Runs all tests\n")
args = parser.parse_args()

if ('run test' in args):
    #TODO ADD TESTS
    print("test ran")


#Generate Random Packets
def generate_random_data():
    smallest_float_range = np.linspace(-MIN_FLOAT, MIN_FLOAT, 0.000000001)
    largest_float_range = np.linspace(-MAX_FLOAT, MAX_FLOAT, 0.000000001)
    float_range = np.append(smallest_float_range, largest_float_range) 
