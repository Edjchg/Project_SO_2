import matplotlib.pyplot as plt


def main():
    fifo_average_time = "../cliente/fifo_statistics/fifo_average_time.txt"
    fifo_total_time = "../cliente/fifo_statistics/fifo_total_time.txt"
    list_total_time = build_total_time_list(fifo_total_time)
    print(list_total_time)
    plt.plot(list_total_time[0], list_total_time[1])
    plt.show()


def build_total_time_list(fifo_total_time):
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
    return [x_list, y_list]


main()
