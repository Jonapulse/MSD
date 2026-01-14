import matplotlib.pyplot as plt

def is_float(num):
    try:
        float(num)
        return True
    except ValueError:
        return False

def parse_trace_info(filename):
    f = open(filename)
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

#hop_info_1 and hop_info_2 have the same x values. Re-ordered some of the IPs to guarantee that.
def graph_hop_info(hop_info_1, hop_info_2):
    x_values = []
    y_values_1 = []
    y_values_2 = []
    for i in range(len(hop_info_1)):
        if i % 2 == 1:
            hop_info_1[i][2] = "\n" + hop_info_1[i][2] #newline every other x label for display
        x_values.append(hop_info_1[i][2])
        y_values_1.append(sum(hop_info_1[i][3])/len(hop_info_1[i][3]))
        y_values_2.append(sum(hop_info_2[i][3])/len(hop_info_2[i][3]))

    plt.plot(x_values, y_values_1, label="1-12-26")
    plt.plot(x_values, y_values_2, "-.", label="1-13-26")
    plt.xlabel("IP addresses")
    plt.ylabel("Average latency (ms)")
    plt.legend()
    plt.title("Traceroute to hempuli.com")

    plt.show()

def parse_ping_info(filename):
    f = open(filename)
    ping_times = []
    for line in f:
        if "time=" in line:
            ping_times.append(float(line[line.find("time=") + 5: line.find("ms") - 1]))
    f.close()
    return ping_times

def process_ping_info(ping_data):
    baseline = min(ping_data)
    sum = 0
    for datum in ping_data:
        sum += datum - baseline
    average = sum / len(ping_data)
    print(f"Average round drip queueing delay is {average:.3f}")

#graph_hop_info(parse_trace_info("tracerouteoutput.txt"), parse_trace_info("traceroutoutput2.txt"))
process_ping_info(parse_ping_info("ping_output.txt"))


