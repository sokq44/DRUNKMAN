import json
import matplotlib.pyplot as plt

def draw_path(path_data, board_data):
    x_values = []
    y_values = []
    step_lengths = []

    for step in path_data:
        if step:
            x_values.append(step['beg_x'])
            y_values.append(step['beg_y'])
            x_values.append(step['end_x'])
            y_values.append(step['end_y'])
            step_lengths.append(step['length'])

    plt.plot(x_values, y_values, marker='o')

    # Create the square
    bottom_left_x = board_data[0]['bottom_left_x']
    bottom_left_y = board_data[0]['bottom_left_y']
    side_length = board_data[1]['bottom_right_x'] - bottom_left_x

    plt.plot([bottom_left_x, bottom_left_x + side_length, bottom_left_x + side_length, bottom_left_x, bottom_left_x], [bottom_left_y, bottom_left_y, bottom_left_y + side_length, bottom_left_y + side_length, bottom_left_y], color='black')

    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('Path')

    total_length = sum(step_lengths)
    average_step_length = total_length / len(step_lengths)

    plt.text(0.19, 1.02, f"Avg Step Length: {average_step_length:.4f}", ha='center', transform=plt.gca().transAxes, fontweight='bold', color='red')
    plt.text(0.83, 1.02, f"Total Length: {total_length:.4f}", ha='center', transform=plt.gca().transAxes, fontweight='bold', color='red')

    plt.grid(True)
    plt.show()

# Read JSON file
with open('source_files/path.json') as file:
    data = json.load(file)

path_data = data['steps']
board_data = data['board']

draw_path(path_data, board_data)
