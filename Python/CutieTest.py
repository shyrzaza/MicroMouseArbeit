# Import libraries
from numpy import *
import csv
from PyQt5.Qt import Qt as QT
from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
import serial
import random;

# Create object serial port

applicationRunning = True

portName = "COM13"                      # replace this port name by yours!
portName = input("Input COM Port")

fileName = "test"
fileName = input("Input fileName")
fileName = fileName + ".csv"


#csvfile = open(fileName, newline = '')

#reader = csv.reader(csvfile, delimiter = ' ', quotechar = '|')

#for row in reader:
#    print(', '.join(row))





baudrate = 57600
#ser = serial.Serial(portName,baudrate)

### START QtApp #####



app = QtGui.QApplication([])            # you MUST do this once (initialize things)
####################


class MyGraphicsWindow(pg.GraphicsWindow):
    def __init__(self, title):
        super(MyGraphicsWindow, self).__init__(title=title)

    def keyPressEvent(self, ev):
        global applicationRunning
        print('Key Press Event fired')
        if ev.key() == QT.Key_Space:
            print('Space was pressed')
            applicationRunning = False

    def closeEvent(self, ev):
        global applicationRunning
        print('Window was closed')
        applicationRunning = False


win = MyGraphicsWindow("Mouse") # creates a window
position_p = win.addPlot(title="Position", row=0, col=0)  # creates empty space for the plot in the window
position_p.setYRange(0,100, padding = 0)

position_curve = position_p.plot()                        # create an empty "plot" (a curve to plot)






#velocity_win = pg.GraphicsWindow(title="Mouse") # creates a window
velocity_p = win.addPlot(title="Velocity", row=0, col=1)  # creates empty space for the plot in the window
velocity_curve = velocity_p.plot()




sensor_p = win.addPlot(title="Sensor", row=1, col=0)  # creates empty space for the plot in the window
sensor_curve = sensor_p.plot()                        # create an empty "plot" (a curve to plot)




controller_p = win.addPlot(title="Controller", row=1, col=1)  # creates empty space for the plot in the window
controller_curve = controller_p.plot()                        # create an empty "plot" (a curve to plot)




windowWidth = 500                      # width of the window displaying the curve
position_Xm = linspace(0,0,windowWidth)          # create array that will contain the relevant time series
position_ptr = -windowWidth                      # set first x position



velocity_Xm = linspace(0,0,windowWidth)          # create array that will contain the relevant time series
velocity_ptr = -windowWidth                      # set first x position



sensor_Xm = linspace(0,0,windowWidth)          # create array that will contain the relevant time series
sensor_ptr = -windowWidth                      # set first x position



controller_Xm = linspace(0,0,windowWidth)          # create array that will contain the relevant time series
controller_ptr = -windowWidth                      # set first x position


f = open("Debug.txt", "r")






# Realtime data plot. Each time this function is called, the data display is updated
def update(thewriter):
    #print("update")
    global position_curve, position_ptr, position_Xm
    global velocity_curve, velocity_ptr, velocity_Xm
    global sensor_curve, sensor_ptr, sensor_Xm
    global controller_curve, controller_ptr, controller_Xm
    global f
    position_Xm[:-1] = position_Xm[1:]                      # shift data in the temporal mean 1 sample left
    velocity_Xm[:-1] = velocity_Xm[1:]                      # shift data in the temporal mean 1 sample left
    sensor_Xm[:-1] = sensor_Xm[1:]                      # shift data in the temporal mean 1 sample left
    controller_Xm[:-1] = controller_Xm[1:]                      # shift data in the temporal mean 1 sample left

    #value = ser.readline()                  # read line (single value) from the serial port
    value = f.readline()
    if(value == ""):
        print("end")
        f = open("Debug.txt", "r")
        value = f.readline()


    #print("update2")

    #split string
    splits = value.split(':')
    #print(splits)
    #Pos:XXX:Vel:XXX:Sensor:XXX
    #Position index 1
    #Velocity index 3
    #Sensor index 5

    #value = random.random() * 200;
    position_Xm[-1] = float(splits[1])  # vector containing the instantaneous values
    position_ptr += 1  # update x position for displaying the curve
    position_curve.setData(position_Xm)  # set the curve with this data
    position_curve.setPos(position_ptr, 0)  # set x position in the graph to 0

    velocity_Xm[-1] = float(splits[3])  # vector containing the instantaneous values
    velocity_ptr += 1  # update x position for displaying the curve
    velocity_curve.setData(velocity_Xm)  # set the curve with this data
    velocity_curve.setPos(velocity_ptr, 0)  # set x position in the graph to 0

    sensor_Xm[-1] = float(splits[5])  # vector containing the instantaneous values
    sensor_ptr += 1  # update x position for displaying the curve
    sensor_curve.setData(sensor_Xm)  # set the curve with this data
    sensor_curve.setPos(sensor_ptr, 0)  # set x position in the graph to 0

    controller_Xm[-1] = float(splits[7])  # vector containing the instantaneous values
    controller_ptr += 1  # update x position for displaying the curve
    controller_curve.setData(controller_Xm)  # set the curve with this data
    controller_curve.setPos(controller_ptr, 0)  # set x position in the graph to 0

    QtGui.QApplication.processEvents()    # you MUST process the plot now


    thewriter.writerow([splits[1],splits[3],splits[5],splits[7].replace('\r', '').replace('\n', '')])

### MAIN PROGRAM #####
# this is a brutal infinite loop calling your realtime data plot
with open(fileName, 'w', newline = '') as csvfile:
    writer = csv.writer(csvfile)
    while applicationRunning:
        update(writer)


### END QtApp ####
pg.QtGui.QApplication.exec_() # you MUST put this at the end
win.close()