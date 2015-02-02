#!/usr/bin/python2

# this script parses a rusEfi console log, extract analog_chart line and
# calculates average trigger angles
# author spags  

import numpy

rpm_max_change = 20

AC_HEADER = 'analog_chart,'

fp = open("target.csv")
data = {}

last_time = 0
rpm = 10000
last_rpm = 0

for line in fp:
    # Chuck the date
    line = line[30:]
    
    if line.startswith('analog_chart,'):
        line = line.strip(AC_HEADER)
        numbers = [float(n) for n in line.split('|')[:24]]
                
        if abs(rpm-last_rpm) < 20:
            data[last_time] = numbers
        else:
            print "RPM Variance to great", last_rpm, rpm
        last_rpm = rpm
        
    elif line.startswith('time'):
        last_time = float(line.split(',')[1])
        last_rpm = rpm
        rpm = float(line.split(',')[3])
        
    else:
        pass

print "Got %d data points"%len(data)

a = {}
for i in range(0, len(numbers)+1,2):
    a[i] = numpy.zeros(len(data))
    
count = 0


for time,numbers in data.iteritems():
    for i in range(0, len(numbers),2):
        a[i][count] = numbers[i]
        
    count+=1
print "Trigger\t\tStdDeviation"
print "-"*40
for i in a.values():
    
    
    print "%f\t\t%f"%(numpy.average(i), i.std())
