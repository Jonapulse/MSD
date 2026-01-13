import matplotlib.pyplot as plt

def is_float(num):
    try:
        float(num)
        return True
    except ValueError:
        return False

def parse_trace_info():
    f = open("tracerouteoutput.txt")
    tracerout_hops = []
    hop_info = [] #[[#, name, ip, delay list], ...]
    for line in f:
        split_line = line.split()
        start_here_for_delays = 2
        #Check if this is a number, if it is, start a new hop_info
        if split_line[0].isdigit():
            hop_info.append([split_line[0], split_line[1], split_line[2][1:-1],[]])
            start_here_for_delays = 3

        #Add delay times until they run out to whichever hop_info's at the end
        for val in split_line[start_here_for_delays:]:
            if is_float(val):
                hop_info[-1][3].append(float(val))
    f.close()
    return hop_info

def graph_hop_info(hop_info):
    x_values = []
    y_values = []
    for i in range(len(hop_info)):
        x_values.append(hop_info[i][2])
        y_values.append(sum(hop_info[i][3])/len(hop_info[i][3]))
    plt.plot(x_values, y_values)
    plt.xlabel("IP addresses")
    plt.ylabel("Average latency (ms)")
    plt.title("Traceroute to hempuli.com")

    plt.tight_layout()
    plt.show()

hop_info = parse_trace_info()
graph_hop_info(hop_info)


