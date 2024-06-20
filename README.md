# CPU Scheduler 

## Project Description

This project is a CPU scheduler simulation implemented using C++, Flask, HTML, CSS, and JavaScript. It provides a web interface to simulate different CPU scheduling algorithms such as First Come First Serve (FCFS), Shortest Job Next (SJN), Priority Scheduling, Round Robin, and Shortest Remaining Time First (SRTF). Users can input process details and select an algorithm to visualize the scheduling process and view performance metrics.

## How to Run the Project

1. Clone the project repository from GitHub:

   ```bash
   git clone https://github.com/busybrowsensei1/CPU-Scheduler

2. Navigate to the project directory:

   ```bash
   cd CPU-Scheduler

3. Install the required dependencies using pip:

   ```bash
   pip install -r requirements.txt
   
4. Run the Flask web application:

   ```bash
   python app.py

5. Access the project in your web browser at http://localhost:5000


## Internal Working

Internally, the scheduling is performed using C++ programs that implement various scheduling algorithms. The application follows these steps:

1. **Input Collection**: User inputs such as the number of processes, arrival times, serve(burst) times, and algorithm choice are collected via a GUI.
2. **Data Processing**: The input data is formatted and sent to the server using Flask.
3. **Algorithm Execution**: The corresponding C++ program for the chosen algorithm is executed with the provided input.
4. **Display**: The output, along with calculated metrics, is displayed in the result section of the web application.

## Output

The application will display:

- Scheduling information for each process, including Arrival Time, Serve(Burst) Time, Finish Time, Response Time, and Waiting Time.
- Average Waiting Time: The average time a process spends waiting in the ready queue before its execution.
- Throughput: The rate of completion of processes per unit time.
- **Gantt Chart**: A visual representation of the scheduling of processes over time.

## Learning Takeaways

- **Understanding CPU scheduling algorithms and their implementations.**
- **Working with Flask for web development and backend processing.**
- **Integrating frontend technologies like HTML, CSS, and JavaScript for user interaction and visualization.**
- **Using Chart.js library for creating dynamic charts and graphs in web applications.**
- **Handling HTTP requests, form submissions, and rendering dynamic content in a web application.**


## References

- [CPU Scheduling in Operating Systems - GeeksforGeeks](https://www.geeksforgeeks.org/cpu-scheduling-in-operating-systems/)
