import serial
from serial.tools import list_ports
import csv
import datetime
import time

def tare_scales(uinput,ser):
    """
    If the user wants it, tare the scales
    """
    if uinput.lower() == "y":
        for i in range(0,10):
            ser.write(str(5).encode("utf-8"))

def get_serial_port():
    """
    Determine which serial port has the Arduino connected
    :return: [Serial object] Arduino Serial Port
    """
    comports_list = list(list_ports.comports())
    for port in comports_list:
        if port.manufacturer == "Arduino (www.arduino.cc)":
            ser = serial.Serial(port.device,115200)

    return ser

def get_file_pointer_csv():
    file_name=input("enter file name without extension\n")
    f= open(file_name+".csv","w")
    f_writer = csv.writer(f,csv.excel)
    return f,f_writer

def collect_data(csv_writer,ser):
    print()
    print("collecting data...")
    print()
    print("press CTRL-C to end")
    print()
    decoded_Data="l"    

    #start time to make time stamps
    time_start = time.time()
    while True:
        row = []

        try:
            time_point = time.time()-time_start
            row.append(str(time_point))

            for i in range(1,5):
                ser.write(str(i).encode("utf-8"))
                time.sleep(.1)
                serial_Data = ser.readline()                     #read one line from serial port (to /n)
                decoded_Data= serial_Data.decode("utf-8")       #decode serial data
                if decoded_Data.strip().strip() == "-0.0":
                    decoded_Data = decoded_Data[1:]
                #add decoded data to row
                row.append(decoded_Data.strip().strip())
            csv_writer.writerow(row)
        except KeyboardInterrupt:
            print("!! ...DONE... !!")
            break

def main():
    ser = get_serial_port()

    f,f_writer = get_file_pointer_csv()

                                              #initializes decoded_Data as a String

    header = ["Time_Stamp","Load_cell1","Load_cell2","Load_cell3","Load_cell4"]
    f_writer.writerow(header)

    uinput = input("Tare/Zero Scales? (Y/N): ")
    tare_scales(uinput,ser)

    collect_data(f_writer,ser)

    f.close()

if __name__ == "__main__":
    main()
