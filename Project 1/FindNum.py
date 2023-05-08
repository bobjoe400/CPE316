MIN_CLOCKS = 115
PERCENT_RANGE = 0.6
CLOCK_SPD = 32_000_0#00

MAX_CLOCKS = MIN_CLOCKS * (1+PERCENT_RANGE)

for i in range(int(CLOCK_SPD/MAX_CLOCKS), int(CLOCK_SPD/MIN_CLOCKS)):
    print_str = ''
    if(CLOCK_SPD%i == 0):
        print_str+= "num: "+str(i)+" CLOCK_SPD Match | "
        if(i%3==0):
            print_str+= "3 Match | "
        else:
            clk_i = i//3
            clk_f = i/3.0
            x = i*clk_i
            y = i*clk_f
            print_str+= "3's remain "+str(i%3)+", off by "+str(float(y-x))+" clocks after "+str(i)+" clock cycles | "
        if(i%4==0):
            print_str+= "4 Match | "
        if(i%5==0):
            print_str+= "5 Match | "
        print(print_str,"Clocks ",CLOCK_SPD/i)
            