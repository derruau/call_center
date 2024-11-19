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

TO BE DEFINED

# Conventions

- Each function is prefixed with the name of the file/struct it's operating on. For example if I want to make the function that dequeues a value for a queue data structure, I name the function 'queue_dequeue'.
- Each file has ONE and only ONE purpose. If I need two different 'components', I put them in different files.

# Error Codes

If the program is well made, you shouldn't encounter them, however in case you do here's what they mean:

An error code is a three letter number XYZ. the X number identifies which source file the error comes from and the YZ identifies the type of error in this file.

Here's a table of all the file identifiers:
|    0XX    |     1XX    |     2XX    | 3XX | 4XX | 5XX | 6XX | 7XX | 8XX | 9XX |
|:---------:|:----------:|:----------:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|   main.c  |   queue.c  |   stack.c  |     |     |     |     |     |     |     | 
