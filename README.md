# Vehicle Routing Problem Algorithms
This repository documents the collective efforts of our group to find an efficient solution to the Vehicle Routing Problem, which is based off of the Traveling Salesman Problem, and documentation of the process thereof.

# What is Contained Within This Repository
 - Our code
 - Our results
 - The tables and graphs cited within our reports
 - Out reports, presentations, etc.

# People Involved
Adam Campbell
Tyler Gill
Tristan Worthington

# Dataset
The following is a table of describing the dataset used:
    DEPOT:
    0
    
    VEHICLE INFO:
    Capacity: 15
    Number of Vehicles: 1
    
    NODE DATA (ID, X, Y, Demand):
    0 50 50 0
    1 10 20 4
    2 20 40 2
    3 30 10 7
    4 40 30 3
    5 60 20 5
    6 70 40 6
    7 80 10 4
    8 90 30 3
    9 20 80 8
    10 60 80 6

    DISTANCE MATRIX:
       0 1  2  3  4  5  6  7  8  9  10
    0  0 50 36 45 22 31 22 50 41 42 36
    1  50 0 22 22 31 50 61 70 80 63 78
    2  36 22 0 32 22 45 50 64 70 41 50
    3  45 22 32 0 22 31 50 50 61 72 76
    4  22 31 22 22 0 22 31 41 50 54 50
    5  31 50 45 31 22 0 22 22 31 67 60
    6  22 61 50 50 31 22 0 32 22 50 41
    7  50 70 64 50 41 22 32 0 22 92 72
    8  41 80 70 61 50 31 22 22 0 76 54
    9  42 63 41 72 54 67 50 92 76 0 41
    10 36 78 50 76 50 60 41 72 54 41 0

    Distance Formula: d(i,j) = sqrt((x_i-x_j)^2 + (y_i-y_j)^2)


# Generative AI Disclosure
Generative AI was used in the creation of the following:
    - Initial dataset used for testing