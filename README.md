*This project has been created as part of the 42 curriculum by cycolonn.*

# 🍴 Philosophers - Technical Documentation

## 1. Description
**Philosophers** is an introduction to the basics of multi-threaded programming and shared memory management. The project illustrates Edsger Dijkstra's famous **Dining Philosophers problem**, highlighting the challenges of thread synchronization, mutexes, and the prevention of race conditions and deadlocks.

<p align="center">
  <img src="./assets/DEMO.gif" alt="PHILO Demo" height="100%" width="100%">
</p>

---

<br />

## 2. Technical Instructions & Features
The project was designed to meet the strict requirements of the 42 subject:

---

<br />

* **Multi-threading**: Each philosopher is represented by an independent thread running in parallel.
* **Mutex Management**: Use of `pthread_mutex_t` to protect access to forks and shared variables (simulation status, last meal time).
* **Real-Time Monitoring**: A dedicated monitoring thread tracks the state of each philosopher to detect death within a 10ms margin.
* **Starvation Avoidance**: Implementation of scheduling strategies (anti-queue) to ensure that every philosopher has a fair chance to eat.
* **CPU Optimization**: Use of "Smart Sleep" and calculated delays to minimize CPU usage without sacrificing timing precision.

---

<br />

## 3. Resources & Technical Choices
Our implementation follows specific technical decisions to optimize stability under heavy load:

---

<br />

### 🧠 Centralized Memory Management (The `t_data` Structure)
* **Unified Access**: All configurations (time to die, eat, sleep) and control mutexes are grouped into a central structure accessible by all threads.
* **Data Protection**: Every access to a shared variable is systematically encapsulated within a mutex lock (`stop_mutex`, `meal_mutex`, `print_mutex`).

---

<br />

### ⚖️ Anti-Deadlock Strategy
* **Fork Sorting**: To avoid Circular Wait (deadlock), philosophers pick up their forks according to the lowest memory address first.
* **Thread Staggering**: An `ft_anti_queue` system delays odd-ID philosophers at startup using a clean `usleep` to prevent immediate resource saturation at T=0.
* **Dynamic Thinking Time**: For odd numbers of philosophers, a thinking time is calculated as `((time_to_eat * 3) / 2) - time_to_sleep` to synchronize meal cycles and reduce fork contention.

---

<br />

### ⏱️ Time Management & Precision
* **Gettimeofday**: Use of millisecond precision for lifecycle tracking.
* **Passive Waiting**: The `ft_waiting` function fragments wait times into small intervals to remain responsive to simulation end signals while significantly reducing Context Switching.

---

<br />

### 🛠️ Authorized Functions
This project is built strictly using the authorized system functions: `memset`, `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`, `pthread_create`, `pthread_detach`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock`.

---

<br />

## 📈 How to Compile and Run
To compile and launch the simulation, use the following commands:

---

<br />

```bash
# Clone the repo
git clone [https://github.com/Cyril-glitch/philosophers.git](https://github.com/Cyril-glitch/philosophers.git)

# Compile the project
cd philosophers
make

# Run the simulation
# Format: ./philo [nb_philos] [time_to_die] [time_to_eat] [time_to_sleep] [optional: nb_meals]
./philo 199 610 200 200