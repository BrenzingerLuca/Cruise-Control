# Cruise Control — Sprint 1

## Overview
This project implements a simple cruise control simulation using a PID controller and a linearized vehicle dynamics model.
The controller computes an engine force to drive the vehicle’s velocity toward a user-defined target.
The simulation runs in discrete time using an explicit Euler integration step and exports a CSV file containing the velocity over time.

---

## Features
- Linearized car dynamics (velocity-proportional drag)
- Discrete PID controller (P, I, D terms in difference form)
- Explicit Euler integration for state updates
- Integrated terminal plot of the current simulation
- CSV output for plotting or data analysis
- User input for initial speed, target speed, and PID gains with valid check

---

## How It Works

### Vehicle Model
Acceleration is computed using a linearized drag model:

**a = (engine_force − friction_coefficient * v) / m**

### PID Controller
The control signal is computed from:
- **P**: proportional to the current error  
- **I**: accumulated error over time  
- **D**: rate of change of the error

### Numerical Integration
Velocity is updated per timestep using the explicit Euler method:

**v_next = v + a * dt**

### Output
The program records velocity at each timestep and writes a CSV file formatted like:

time,velocity  
0.0,0.0  
0.2,0.85

---

## Build Instructions
Compile using Cmake  
Inside the cruise_control folder execute the following code :

```sh
mkdir build
cd build
cmake ..
cmake --build .
```
Execute the programm after building with:
```sh
./cruise_control
```

### Saving the data
The resulting data will be saved to: data/my_cruise.csv


### Plotting the data
If you have Python with Pandas and Matplotlib installed you can execute the plot_csv.py script by running:
```sh
python plot_csv.py
```
Optionally if you use python3 run:
```sh
python3 plot_csv.py
```

In the folder "data" we provide some example files and plots, the filenames contain of starting velocity, goal velocity and the P, I and D gain.
