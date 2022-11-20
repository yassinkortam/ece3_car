import serial
import json
import numpy as np

def readChar(PORT, BAUD):
    with serial.Serial(
        PORT,
        BAUD,
        timeout=1,
    ) as s:
        return s.read().decode("ASCII")

def getData(PORT, BAUD):

    dataRead = ""
    char = readChar(PORT, BAUD)

    #keep reading until start marker is reached
    while char != 'S':
       char = readChar(PORT, BAUD)

    #read everything between start and end markers
    if char == 'S':
        while char != '{':
            char = readChar(PORT, BAUD)
        while char != 'E':
            dataRead += char
            char = readChar(PORT, BAUD)

    data = json.loads(dataRead)
    sensorData = np.array(data["sensor"])
    print(sensorData)
    return sensorData
