import matplotlib.pyplot as plt

def main():
    graph_total_time()
    graph_average_time()
    graph_cpu_usage()

def graph_cpu_usage():
    fifo_cpu_usage = "../cliente/fifo_statistics/fifo_cpu_usage.txt"
    hp_cpu_usage = "../cliente/hp_statistics/hp_cpu_usage.txt"
    php_cpu_usage = "../cliente/php_statistics/php_cpu_usage.txt"
    # add other server path here...

    list_cpu_usage_fifo = build_x_y_list(fifo_cpu_usage)
    list_cpu_usage_hp = build_x_y_list(hp_cpu_usage)
    list_cpu_usage_php = build_x_y_list(php_cpu_usage)
    # build the x y list here...

    if len(list_cpu_usage_fifo[0]) == 0 or len(list_cpu_usage_fifo[1]) == 0 or \
       len(list_cpu_usage_hp[0]) == 0 or len(list_cpu_usage_hp[1]) == 0 or\
        len(list_cpu_usage_php[0]) == 0 or len(list_cpu_usage_php[1]) == 0  :
        print("It can not plot inexisting points.")
    else:
        plt.figure()
        # FIFO
        plt.subplot(311)  # 311 means: 3 rows 1 column 1st element:
        plt.title("Fifo server % CPU usage graph")
        plt.ylabel("Elements")
        plt.xlabel("% CPU usage")
        plt.plot(list_cpu_usage_fifo[1], list_cpu_usage_fifo[0])
        
        #Heavy Process
        plt.subplot(312)  # 312 means: 3 rows 1 column 2nd element
        plt.title("Heavy process server % CPU usage graph")
        plt.ylabel("Elements")
        plt.xlabel("% CPU usage")
        plt.plot(list_cpu_usage_hp[1], list_cpu_usage_hp[0])
       
        # Pre heavy process
        plt.subplot(313)  # 312 means: 3 rows 1 column 2nd element
        plt.title("Pre-heavy process server % CPU usage graph")
        plt.ylabel("Elements")
        plt.xlabel("% CPU usage")
        plt.plot(list_cpu_usage_php[1], list_cpu_usage_php[0])
        plt.subplots_adjust(top=0.92, bottom=0.08, left=0.145, right=0.95, hspace=0.65,
                            wspace=0.35)

        plt.show()


def graph_average_time():
    fifo_average_time = "../cliente/fifo_statistics/fifo_average_time.txt"
    hp_average_time = "../cliente/hp_statistics/hp_average_time.txt"
    php_average_time = "../cliente/php_statistics/php_average_time.txt"
    # add other server path here...

    list_average_time_fifo = build_x_y_list(fifo_average_time)
    list_average_time_hp = build_x_y_list(hp_average_time)
    list_average_time_php = build_x_y_list(php_average_time)
    # build the x y list here...


    if len(list_average_time_fifo[0]) == 0 or len(list_average_time_fifo[1]) == 0 or \
       len(list_average_time_hp[0]) == 0 or len(list_average_time_hp[1]) == 0 or \
        len(list_average_time_php[0]) == 0 or len(list_average_time_php[1]) == 0:
        print("It can not plot inexisting points.")
    else:
        plt.figure()
        #FIFO
        plt.subplot(311)  # 311 means: 3 rows 1 column 1st element:
        plt.title("Fifo server average time graph")
        plt.ylabel("Average time (s)")
        plt.xlabel("Elements")
        plt.plot(list_average_time_fifo[1], list_average_time_fifo[0])

        #Heavy process
        plt.subplot(312)  # 311 means: 3 rows 1 column 1st element:
        plt.title("Heavy process server average time graph")
        plt.ylabel("Average time (s)")
        plt.xlabel("Elements")
        plt.plot(list_average_time_hp[1], list_average_time_hp[0])
        
        #Pre heavy process
        plt.subplot(313)  # 311 means: 3 rows 1 column 1st element:
        plt.title("Pre-heavy process server average time graph")
        plt.ylabel("Average time (s)")
        plt.xlabel("Elements")
        plt.plot(list_average_time_php[1], list_average_time_php[0])

        plt.subplots_adjust(top=0.92, bottom=0.08, left=0.10, right=0.95, hspace=0.65,
                            wspace=0.35)
        plt.show()


def graph_total_time():
    fifo_total_time = "../cliente/fifo_statistics/fifo_total_time.txt"
    hp_total_time = "../cliente/hp_statistics/hp_total_time.txt"
    php_total_time = "../cliente/php_statistics/php_total_time.txt"
    # add pre hp server path here...


    list_total_time_fifo = build_x_y_list(fifo_total_time)
    list_total_time_hp = build_x_y_list(hp_total_time)
    list_total_time_php = build_x_y_list(php_total_time)
    # build the x y list here...

    if len(list_total_time_fifo[0]) == 0 or len(list_total_time_fifo[1]) == 0 or \
       len(list_total_time_hp[0]) == 0 or len(list_total_time_hp[1]) == 0 or \
        len(list_total_time_php[0]) == 0 or len(list_total_time_php[1]) == 0:
        print("It can not plot inexisting points.")
    else:
        plt.figure()
        #FIFO
        plt.subplot(311)  # 311 means: 3 rows 1 column 1st element:
        plt.title("Fifo server total time graph")
        plt.ylabel("Total time (s)")
        plt.xlabel("Elements")
        plt.plot(list_total_time_fifo[1], list_total_time_fifo[0])

        #Heavy process
        plt.subplot(312)  # 311 means: 3 rows 1 column 1st element:
        plt.title("Heavy process server total time graph")
        plt.ylabel("Total time (s)")
        plt.xlabel("Elements")
        plt.plot(list_total_time_hp[1], list_total_time_hp[0])
        
        #Pre heavy process
        plt.subplot(313)  # 311 means: 3 rows 1 column 1st element:
        plt.title("Pre-heavy process server total time graph")
        plt.ylabel("Total time (s)")
        plt.xlabel("Elements")
        plt.plot(list_total_time_php[1], list_total_time_php[0])
 
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
            x_list.append(float(number_x))
            while buffer[i] != "]":
                number_y += buffer[i]
                i += 1
            i += 1
            y_list.append(float(number_y))
            number_x = ""
            number_y = ""
        else:
            i += 1
    return [x_list, y_list]


main()
