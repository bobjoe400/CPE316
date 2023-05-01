import math
import os

f = open("LUT.txt","w")
NUM_BITS = 12
P2P_VOLTS = 3.0
MAX_VOLTS = 3.3
BIAS_VOLTS = 1.5
TICKS_PERIOD = 3000

f.write("uint32_t SIN_LUT = {\n")
a = ((1<<(NUM_BITS-1))-1)*(P2P_VOLTS/MAX_VOLTS)
b = 1.0/(TICKS_PERIOD)
v_offset = (BIAS_VOLTS/MAX_VOLTS) * ((1<<NUM_BITS)-1)

counter = 0
for w in range(TICKS_PERIOD):
	y = int(a*math.sin(2*b*math.pi*w)+v_offset)
	write_str = str(y) + ","
	counter+=1
	if(counter == 15):
		write_str += "\n"
		counter = 0
	f.write(write_str)
f.write("};\n")

f.write("unit32_t TRI_LUT = {\n")
counter = 0
m = 2047.0/750 * (P2P_VOLTS/MAX_VOLTS)
for x in range(TICKS_PERIOD):
	if(x < 750):
		dir = 1
		y_offset = v_offset
	elif(750 <= x < 2250):
		dir = -1
		y_offset = m * 1500 + v_offset
	else:
		dir = 1
		y_offset = -1 * m * 3000 + v_offset
	y = int(dir * m * x + y_offset)
	write_str = str(y) + ","
	counter+=1
	if(counter == 15):
		write_str+="\n"
		counter = 0
	f.write(write_str)
f.write("};\n")

f.write("uint32_t SAW_LUT = {\n")
m = 4096.0/3000 * (P2P_VOLTS/MAX_VOLTS)
counter = 0
for x in range(TICKS_PERIOD):
	y = int(m*x)
	write_str = str(y) + ","
	counter+=1
	if(counter == 15):
		write_str+="\n"
		counter=0
	f.write(write_str)
f.write("};\n")
