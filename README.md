# STUDY OF A CALL CENTER

This project is a class assignment that aims to simulate a call center and provide various stats relating to it's performance.

# Installation

## Linux and MacOS
```shell
git clone https://github.com/derruau/call_center

cd call_center

make
```
Additionnaly, use ``make clean`` to make a clean build of the project in case something's broken

## Installing on Windows
1. Install [MSYS2](https://www.msys2.org/) (it should be the default but make sure to install the UCRT environment) 
2. Open a MSYS2 terminal and type ``pacman -S --needed base-devel git mingw-w64-ucrt-x86_64-github-cli mingw-w64-ucrt-x86_64-toolchain``
    - MSYS2 will prompt you to choose things but just press ``ENTER`` everytime to choose the default options
    - You can remove ``mingw-w64-ucrt-x86_64-github-cli`` and skip to step 4 if you don't want to sign in to Github using MSYS2
3. type ``gh auth login`` and follow the instructions to link your Github account to MSYS2
4. In the Windows search bar, type & execute ``Edit environment variables for your account`` 
5. Double click the PATH environment variable and add these entries to it at the end:
    - ``C:\msys64\usr\bin``
    - ``C:\msys64\ucrt64\bin``
6. Restart any terminal you might have open
7. You can now compile the project using
    - ``make -w`` to compile the project
    - ``make clean -w`` to clean the build directory

## Debug using VSCODE:
To debug the program using VSCODE, use the built-in debugger:
1. Go to the 'Run and Debug' section
2. Select and run the 'Debug Mode' task (or 'Debug Mode (Windows)' if you're on Windows)

If you want to debug the program using ``gdb``, just build it with ``make debug`` (or ``make debug -w`` on Windows)

# Usage

```
Simulation of a call center. (School project)

Usage:
  - queue_project [options] <output-path>
  - queue_project --help
  - queue_project -l 2.6 -d 0s:30m -o 6 output.txt

Options:
  -h --help            Show this screen.
  -v --version         Show version.
  -q --quiet           Doesn't print anything to the screen
  -l --lambda          Lambda parameter of a Poisson Law. [default: TODO]
  -s --shift           The call centers shift opening and closing hours in 
                       duration format (see bellow).
  -d --duration        Minimum and Maximum call duration for a client in 
                       duration format (see bellow).
  -n --number-of-days  The number of days in the simulation [default: 1]
  -o --operators       Number of operators in the call center.

Duration Format:
  The duration format encodes a start and end time like so:
                [START_TIME]:[END_TIME]
  Each TIME parameter is written like so: [NUMBER][UNIT]
  Where:
    - NUMBER is a whole number
    - UNIT is a unit of time (s: seconds, m: minutes, h:hours, d: days,
     w: week, M: month, y: year)
  Example: The Duration Format 2s:4d means that the minimum duration is 2
           seconds and the maximum duration is 4 days.
```


# Conventions

- Each function is prefixed with the name of the file/struct it's operating on. For example if I want to make the function that dequeues a value for a queue data structure, I name the function 'queue_dequeue'.
- Each file has ONE and only ONE purpose. If I need two different 'components', I put them in different files.

## Important
It is **extremely important** that you only **seed once per execution of the program**!

If you do not **seed once per execution of the program** I will personnally hunt you down and make you write a personnal letter of apology to the person who had to debug the abomination that **YOU** created!

More seriously: when generating an array of random values, seeding more than one time by doing ``srand(time(NULL));`` will make the same data over and over again because the ``time`` function returns the time in seconds and the program obiously takes a lot less than one second to execute!! SO BY SEEDING MORE THAN ONCE YOU EFFECTIVELY RESET THE RANDOM NUMBER GENERATOR EVERY TIME YOU GENERATE DATA AHHHHHH WHY DID I MAKE THIS MISTAKE AND WASTE SO MUCH TIME AAAAHAHHH!!!!!!

# Error Codes

If the program is well made, you shouldn't encounter them, however in case you do here's what they mean:

An error code is a three letter number XYZ. the X number identifies which source file the error comes from and the YZ identifies the type of error in this file.

Here's a table of all the file identifiers:
|    0XX    |     1XX    |     2XX    |    3XX   |        4XX       | 5XX | 6XX | 7XX | 8XX | 9XX |
|:---------:|:----------:|:----------:|:--------:|:----------------:|:---:|:---:|:---:|:---:|:---:|
|   main.c  |   queue.c  |   stack.c  | helper.c | argument parsing |     |     |     |     |     | 
