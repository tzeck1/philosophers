# Philosophers
I’ve never thought philosophy would be so deadly.<br>
In this project, I learned the basics of threading a process and mutexes. <br>
<br>
Here you can read more about the problem https://en.wikipedia.org/wiki/Dining_philosophers_problem <br>
<br>
<img width="197" alt="Screenshot 2022-03-27 at 20 34 58" src="https://user-images.githubusercontent.com/65648486/160295607-ee927cd5-197c-4664-b986-2a92c75b6202.png">
<br>

## Introduction

**- philo number:** how many philosophers are sitting at the table <br>
**- time to die:** time in milliseconds until a philo dies after his last meal <br>
**- time to eat:** time in milliseconds it takes a philo to eat <br>
**- time to die:** time in milliseconds it takes a philo to sleep <br>
**- number must eat:** how many times a philo must at least have eaten to end the simulation <br>
<br>

A philosopher has to announce its current status in the STDOUT, which can be: <br>
- philo n has taken a fork <br>
- philo n is eating <br>
- philo n is sleeping <br>
- philo n is thinking <br>
- philo n died <br>

## Usage

``make`` to compile all source files <br>
``./philo <philo number> <time to die> <time to eat> <time to sleep> <number must eat>`` to start the simulation
