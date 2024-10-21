import matplotlib.pyplot as plt


def analyze(file_path):
    cpu_total = 0
    overhead_total = 0
    total_duration = 0

    with open(file_path, "r") as file:
        lines = file.readlines()

    for line in lines:
        parts = line.split(", ")
        duration = int(parts[1])

        if "CPU execution" in parts[2]:
            cpu_total += duration
        elif duration < 4:
            overhead_total += duration

        # Update total_duration with the time from the last line
        total_duration = int(parts[0])

    total_io_time = total_duration - (cpu_total + overhead_total)

    total_io_p = round((total_io_time / total_duration) * 100, 1)
    total_cpu_p = round((cpu_total / total_duration) * 100, 1)
    total_overhead_p = round((overhead_total / total_duration) * 100, 1)

    p = (total_io_p, total_cpu_p, total_overhead_p)

    return (p, total_io_time, cpu_total, overhead_total, total_duration)


# Example usage
execution_one = "../execution1.txt"
execution_two = "../execution2.txt"

result_one = analyze(execution_one)

result_two = analyze(execution_two)

# Calculate the average result between two executions
average_result = (
    [(x + y) / 2 for x, y in zip(result_one[0], result_two[0])],
    (result_one[1] + result_two[1]) / 2,
    (result_one[2] + result_two[2]) / 2,
    (result_one[3] + result_two[3]) / 2,
    (result_one[4] + result_two[4]) / 2,
)

# Plotting the two pie charts for execution1 and execution2
labels = ["IO Time %", "CPU Time %", "Overhead %"]

# Pie chart for execution1
plt.figure(figsize=(14, 6))

plt.subplot(1, 2, 1)
plt.pie(result_one[0], labels=labels, autopct="%1.1f%%", startangle=140)
plt.title("Execution 1")

plt.subplot(1, 2, 2)
plt.pie(result_two[0], labels=labels, autopct="%1.1f%%", startangle=140)
plt.title("Execution 2")

# Save pie charts as an image
plt.savefig("execution_pie_charts.png")

# Clear the figure to prepare for the next plot
plt.clf()

# Bar graph showing average metrics for CPU Time, IO Time, Overhead, and Total Duration
metrics_labels = ["CPU Time", "IO Time", "Overhead", "Total Duration"]
average_metrics = average_result[1:]

plt.figure(figsize=(10, 6))
plt.bar(metrics_labels, average_metrics, color=["blue", "orange", "green", "red"])
plt.title("Average Metrics Across Executions")
plt.xlabel("Metrics")
plt.ylabel("Time (ms)")

# Save bar graph as an image
plt.savefig("average_metrics_bar_graph.png")

# Optionally, you can still use plt.show() if you want to display them while saving
# plt.show()
