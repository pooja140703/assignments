# finding non crossing path  of flights in python
# Path Crossing - Leetcode 1496 - Python
#find intersecting points of two lines in python and how to avoid them

#approach: I tried to implement the logic that ones finding intersection ,suppose
# for flight2 it crossing flight1 ,we try to find next point in x-axis and y-axis 
# where they don't intersect and then create one new point there and connect it with 
# the point of flight2 which were crossing.

import matplotlib.pyplot as plt
import matplotlib.lines as mlines

def do_intersect(p1, q1, p2, q2):
    # Function to check if two line segments (p1, q1) and (p2, q2) intersect
    if(p1[0]==p2[0] and q1[0]==q2[1]):
      return False

    def on_segment(p, q, r):
        if min(p[0], q[0]) <= r[0] <= max(p[0], q[0]) and min(p[1], q[1]) <= r[1] <= max(p[1], q[1]):
            return True
        return False

    def orientation(p, q, r):
        val = (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1])
        if val == 0:
            return 0
        return 1 if val > 0 else 2

    o1 = orientation(p1, q1, p2)
    o2 = orientation(p1, q1, q2)
    o3 = orientation(p2, q2, p1)
    o4 = orientation(p2, q2, q1)

    if o1 != o2 and o3 != o4:
        return True

    if o1 == 0 and on_segment(p1, q1, p2): return True
    if o2 == 0 and on_segment(p1, q1, q2): return True
    if o3 == 0 and on_segment(p2, q2, p1): return True
    if o4 == 0 and on_segment(p2, q2, q1): return True

    return False

def plot_flights(flights):
    fig, ax = plt.subplots()

    for idx, flight in enumerate(flights):
        x, y = zip(*flight)
        ax.plot(x, y, marker='o', label=f'Flight {idx+1}')
    
    # Check for intersections
    for i in range(len(flights)):
        for j in range(i+1, len(flights)):
            for k in range(len(flights[i])-1):
                for l in range(len(flights[j])-1):
                    if do_intersect(flights[i][k], flights[i][k+1], flights[j][l], flights[j][l+1]):
                        print(f'Intersection detected between Flight {i+1} and Flight {j+1}')

    ax.legend()
    plt.xlabel('X Coordinate')
    plt.ylabel('Y Coordinate')
    plt.title('Flight Paths')
    plt.grid()
    plt.show()

# Example input
flights = [
    [(1,1), (2,2), (3,3)],
    [(1,1), (2,4), (3,2)],
    [(1,1), (4,2), (3,4)]
]

plot_flights(flights)
