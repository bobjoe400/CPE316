import math
import os

f = open("LUT.txt","w")
NUM_BITS = 12
P2P_VOLTS = 3.0
MAX_VOLTS = 3.3
BIAS_VOLTS = 1.5
TICKS_PERIOD = 2500
LINE_SPLIT = 15
MAX_VALUE = 0xFFF
v_offset = (BIAS_VOLTS/MAX_VOLTS) * (MAX_VALUE)

f.write("#define NUM_SAMPLES "+str(TICKS_PERIOD)+"\n\n")

f.write("uint32_t SIN_LUT[NUM_SAMPLES] = {\n")
a = (MAX_VALUE>>1)*(P2P_VOLTS/MAX_VOLTS)
b = 1.0/(TICKS_PERIOD)

counter = 0
for w in range(TICKS_PERIOD):
	y = int(a*math.sin(2*b*math.pi*w)+v_offset)
	write_str = str(y) + ","
	counter+=1
	if(counter == LINE_SPLIT):
		write_str += "\n"
		counter = 0
	f.write(write_str)
f.write("};\n")

f.write("\nuint32_t TRI_LUT[NUM_SAMPLES] = {\n")
counter = 0
one_fourth_period = TICKS_PERIOD/4
m = v_offset/one_fourth_period
print("v_offset: ",v_offset,"\nm: ",m,"\n1/4 period: ",one_fourth_period)
for x in range(TICKS_PERIOD):
	if(x < one_fourth_period):
		dir = 1
		y_offset = v_offset
	elif(one_fourth_period <= x < 3*one_fourth_period):
		dir = -1
		y_offset = 3 * v_offset
	else:
		dir = 1
		y_offset = -1 * 3 * v_offset
	y = int(dir * m * x + y_offset)
	write_str = str(y) + ","
	counter+=1
	if(y==1813):
		print(x)
	if(counter == LINE_SPLIT):
		write_str+="\n"
		counter = 0
	f.write(write_str)
f.write("};\n")

f.write("\nuint32_t SAW_LUT[NUM_SAMPLES] = {\n")
m = ((P2P_VOLTS/MAX_VOLTS) * MAX_VALUE) / TICKS_PERIOD
print("m: ",m)
counter = 0
for x in range(TICKS_PERIOD):
	y = int(m*x)
	write_str = str(y) + ","
	counter+=1
	if(counter == LINE_SPLIT):
		write_str+="\n"
		counter=0
	f.write(write_str)
f.write("};")
