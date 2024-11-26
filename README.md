# STUDY OF A CALL CENTER

This project is a class assignment that aims to simulate a call center and provide various stats relating to it's performance.

# Installation

```shell
git clone https://github.com/derruau/call_center

cd call_center

make
```

Additionnaly, use ``make clean`` to make a clean build of the project in case something's broken

# Usage

```
Simulation of a call center. (School project)

Usage:
  - queue_project [options] <output-path>
  - queue_project --help
  - queue_project -l 2.6 -d 0s:30m -o 6 output.txt

Options:
  -h --help        Show this screen.
  -v --version     Show version.
  -l --lambda      Lambda parameter of a Poisson Law. [default: TODO]
  -s --shift       The call centers shift opening and closing hours in 
                   duration format (see bellow).
  -d --duration    Minimum and Maximum call duration for a client in 
                   duration format (see bellow).
  -o --operators   Number of operators in the call center.

Duration Format:
  The duration format encodes a start and end time like so:
                [START_TIME]:[END_TIME]
  Each TIME parameter is written like so: [NUMBER][UNIT]
  Where:
    - NUMBER is a whole number
    - UNIT is a unit of time (s: seconds, m: minutes, d: days)
  Example: The Duration Format 2s:4d means that the minimum 
           duration is 2 seconds and the maximum duration is 4 days.
```


# Conventions

- Each function is prefixed with the name of the file/struct it's operating on. For example if I want to make the function that dequeues a value for a queue data structure, I name the function 'queue_dequeue'.
- Each file has ONE and only ONE purpose. If I need two different 'components', I put them in different files.

# Error Codes

If the program is well made, you shouldn't encounter them, however in case you do here's what they mean:

An error code is a three letter number XYZ. the X number identifies which source file the error comes from and the YZ identifies the type of error in this file.

Here's a table of all the file identifiers:
|    0XX    |     1XX    |     2XX    |    3XX   | 4XX | 5XX | 6XX | 7XX | 8XX | 9XX |
|:---------:|:----------:|:----------:|:--------:|:---:|:---:|:---:|:---:|:---:|:---:|
|   main.c  |   queue.c  |   stack.c  | helper.c |     |     |     |     |     |     | 
