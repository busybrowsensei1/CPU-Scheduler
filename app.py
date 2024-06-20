from flask import Flask, render_template, request
import subprocess

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/schedule', methods=['POST'])
def schedule():
    algorithm = request.form['algorithm']
    n = int(request.form['n'])
    quantum = request.form.get('quantum', '')

    arrival_times = request.form.getlist('arrival_time')
    serve_times = request.form.getlist('serve_time')
    priorities = request.form.getlist('priority')

    input_data = f"{n}\n"
    for i in range(n):
        if algorithm == "priority":
            input_data += f"{arrival_times[i]} {serve_times[i]} {priorities[i]}\n"
        else:
            input_data += f"{arrival_times[i]} {serve_times[i]}\n"
    if algorithm == "round_robin":
        input_data += f"{quantum}\n"

    try:
        process = subprocess.Popen(['./scheduler', algorithm], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        output, error = process.communicate(input=input_data)
        if error:
            return f"Error: {error}"
        
        # Parse the output from scheduler.cpp
        output_lines = output.strip().split('\n')
        processes = []
        average_waiting_time = 0.0
        average_turnaround_time = 0.0  # New variable for average turnaround time
        throughput = 0.0
        gantt_chart = []

        for line in output_lines:
            if line.startswith("P") and len(line.split()) == 7:  # Adjusted for the added turnaround time
                parts = line.split()
                process = {
                    'arrival_time': int(parts[1]),
                    'serve_time': int(parts[2]),
                    'finish_time': int(parts[3]),
                    'response_time': int(parts[4]),
                    'waiting_time': int(parts[5]),
                    'turnaround_time': int(parts[6])  # Added turnaround time
                }
                average_waiting_time += process['waiting_time']
                average_turnaround_time += process['turnaround_time']  # Update average turnaround time
                processes.append(process)
            elif line.startswith("Throughput:"):
                throughput = float(line.split()[1])
            elif line.startswith("P") and len(line.split()) == 3:
                parts = line.split()
                gantt_chart.append({
                    'id': int(parts[0][1:]),
                    'start_time': int(parts[1]),
                    'finish_time': int(parts[2])
                })

        average_waiting_time /= n
        average_turnaround_time /= n  # Calculate average turnaround time

        return render_template('result.html', output=processes, average_waiting_time=average_waiting_time, average_turnaround_time=average_turnaround_time, gantt_chart=gantt_chart, throughput=throughput)

    except Exception as e:
        return f"Execution failed: {str(e)}"

if __name__ == '__main__':
    app.run(debug=True)
