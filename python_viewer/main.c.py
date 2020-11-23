import matplotlib.pyplot as plt


def main():
    graph_total_time()
    graph_average_time()


def graph_average_time():
    fifo_average_time = "../cliente/fifo_statistics/fifo_average_time.txt"
    # add other server path here...
    # ·
    # ·
    # ·
    list_average_time = build_x_y_list(fifo_average_time)
    # build the x y list here...
    # ·
    # ·
    # ·
    plt.figure()
    plt.subplot(311)  # 311 means: 3 rows 1 column 1st element:
    plt.title("Fifo server average time graph")
    if len(list_average_time[0]) == 0 or len(list_average_time[1]) == 0:
        print("It can not plot inexisting points.")
    else:
        plt.plot(list_average_time[0], list_average_time[1])
        # add subplot for the other servers here
        # ·
        # ·
        # ·
        plt.show()


def graph_total_time():
    fifo_total_time = "../cliente/fifo_statistics/fifo_total_time.txt"
    # add other server path here...
    # ·
    # ·
    # ·

    list_total_time = build_x_y_list(fifo_total_time)
    # build the x y list here...
    # ·
    # ·
    # ·
    plt.figure()
    plt.subplot(311)  # 311 means: 3 rows 1 column 1st element:
    plt.title("Fifo server total time graph")
    if len(list_total_time[0]) == 0 or len(list_total_time[1]) == 0:
        print("It can not plot inexisting points.")
    else:
        plt.plot(list_total_time[0], list_total_time[1])
        # add subplot for the other servers here
        # ·
        # ·
        # ·
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
