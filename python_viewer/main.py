import matplotlib.pyplot as plt

def main():
    graph_total_time()
    graph_average_time()
    graph_cpu_usage()

def graph_cpu_usage():
    fifo_cpu_usage = "../cliente/fifo_statistics/fifo_cpu_usage.txt"
    hp_cpu_usage = "../cliente/hp_statistics/hp_cpu_usage.txt"
    # add other server path here...

    list_cpu_usage_fifo = build_x_y_list(fifo_cpu_usage)
    list_cpu_usage_hp = build_x_y_list(hp_cpu_usage)
    # build the x y list here...

    if len(list_cpu_usage_fifo[0]) == 0 or len(list_cpu_usage_fifo[1]) == 0 or \
       len(list_cpu_usage_hp[0]) == 0 or len(list_cpu_usage_hp[1]) == 0:
        print("It can not plot inexisting points.")
    else:
        plt.figure()
        # FIFO
        plt.subplot(3, 1, 1)  # 311 means: 3 rows 1 column 1st element:
        plt.title("Fifo server % CPU usage graph")
        plt.xlabel("Elements")
        plt.ylabel("% CPU usage")
        plt.plot(list_cpu_usage_fifo[0], list_cpu_usage_fifo[1])
        
        #Heavy Process
        plt.subplot(3, 1, 2)  # 312 means: 3 rows 1 column 2nd element
        plt.title("Heavy process server % CPU usage graph")
        plt.xlabel("Elements")
        plt.ylabel("% CPU usage")
        plt.plot(list_cpu_usage_hp[0], list_cpu_usage_hp[1])
       
        # Pre heavy process
        # *

        plt.subplots_adjust(top=0.92, bottom=0.08, left=0.145, right=0.95, hspace=0.65,
                            wspace=0.35)

        plt.show()


def graph_average_time():
    fifo_average_time = "../cliente/fifo_statistics/fifo_average_time.txt"
    hp_average_time = "../cliente/hp_statistics/hp_average_time.txt"
    # add other server path here...

    list_average_time_fifo = build_x_y_list(fifo_average_time)
    list_average_time_hp = build_x_y_list(hp_average_time)
    # build the x y list here...


    if len(list_average_time_fifo[0]) == 0 or len(list_average_time_fifo[1]) == 0 or \
       len(list_average_time_hp[0]) == 0 or len(list_average_time_hp[1]) == 0:
        print("It can not plot inexisting points.")
    else:
        plt.figure()
        #FIFO
        plt.subplot(311)  # 311 means: 3 rows 1 column 1st element:
        plt.title("Fifo server average time graph")
        plt.xlabel("Average time (s)")
        plt.ylabel("Elements")
        plt.plot(list_average_time_fifo[0], list_average_time_fifo[1])

        #Heavy process
        plt.subplot(312)  # 311 means: 3 rows 1 column 1st element:
        plt.title("Heavy process server average time graph")
        plt.xlabel("Average time (s)")
        plt.ylabel("Elements")
        plt.plot(list_average_time_hp[0], list_average_time_hp[1])
        
        #Pre heavy process
        # * 
        plt.subplots_adjust(top=0.92, bottom=0.08, left=0.10, right=0.95, hspace=0.65,
                            wspace=0.35)
        plt.show()


def graph_total_time():
    fifo_total_time = "../cliente/fifo_statistics/fifo_total_time.txt"
    hp_total_time = "../cliente/hp_statistics/hp_total_time.txt"
    # add pre hp server path here...


    list_total_time_fifo = build_x_y_list(fifo_total_time)
    list_total_time_hp = build_x_y_list(hp_total_time)
    # build the x y list here...

    if len(list_total_time_fifo[0]) == 0 or len(list_total_time_fifo[1]) == 0 or \
       len(list_total_time_hp[0]) == 0 or len(list_total_time_hp[1]) == 0:
        print("It can not plot inexisting points.")
    else:
        plt.figure()
        #FIFO
        plt.subplot(311)  # 311 means: 3 rows 1 column 1st element:
        plt.title("Fifo server total time graph")
        plt.xlabel("Total time (s)")
        plt.ylabel("Elements")
        plt.plot(list_total_time_fifo[0], list_total_time_fifo[1])

        #Heavy process
        plt.subplot(312)  # 311 means: 3 rows 1 column 1st element:
        plt.title("Heavy process server total time graph")
        plt.xlabel("Total time (s)")
        plt.ylabel("Elements")
        plt.plot(list_total_time_hp[0], list_total_time_hp[1])
        
        #Pre heavy process
        # *
 
        plt.subplots_adjust(top=0.92, bottom=0.08, left=0.10, right=0.95, hspace=0.65,
                            wspace=0.35)
        plt.show()


def build_x_y_list(fifo_total_time):
    f = open(fifo_total_time)
    buffer = f.read()
    buffer_len = len(buffer)
    x_list = []
    y_list = []
    number_x = ""
    number_y = ""
    i = 0
    while i < buffer_len:
        if buffer[i] == "[":
            i += 1
            while buffer[i] != ",":
                number_x += buffer[i]
                i += 1
            i += 1
            print("Number x: " + number_x)
            x_list.append(float(number_x))
            while buffer[i] != "]":
                number_y += buffer[i]
                i += 1
            i += 1
            print("Number y: " + number_y)
            y_list.append(float(number_y))
            number_x = ""
            number_y = ""
        else:
            i += 1
    return [x_list, y_list]


main()
