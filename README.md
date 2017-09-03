Robotic Motion Planning: A* Search



### Project Description
#### Part 1:

The first step is to implement A* to help a robot, getting from start to goal.

The environment for this problem is a simple 2D grid, in which the robot can move in 8 directions, the 4
cardinal directions, as well as diagonally. Moving diagonally is more expensive, it costs ```sqrt(2)``` units instead of 1 unit.
The robot can move to any cell that is open. You can store the map in a 2D array or any data structure that you prefer.

Given a start and goal position, write a program that computes and returns a minimum cost path from start
to goal, using A*. You can use any heuristic function you'd like.

Please use small maps to test your code.

#### Part 2:

For part 2, we've given to the robot a hummer that can use to brake a single cell. The robot can use the tool only once per query. 
This means, that in a single action, the robot can pass into a cell that is occupied (has an obstacle). There
is no additional cost to this action. 

Extend the previous algorithm to find the shortest path given that the robot can use the hummer. 
It is not required to use the hummer if it does not help. 
However, there should be cases that the robot has to use the hummer in order to get to its target.


Example of a map where 0: corresponds to open cells, and 1: corresponds to cells with obstacles
```
14 32
0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 1 0 1 0 0 0 0 1
1 1 1 1 1 1 1 0 1 0 0 0 1 0 0 0 0 0 0 0 1 0 1 0 1 0 1 0 0 0 0 1
0 0 0 0 0 0 0 0 1 0 0 0 1 0 0 0 0 0 0 0 1 0 1 0 1 0 1 0 0 0 0 1
0 0 0 0 0 0 0 0 1 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 1 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 1 0 0 0 1 0 0 0 0 1 0 0 1 0 0 0 1 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 1 0 0 0 1 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 1
0 0 0 0 1 1 1 1 1 0 0 0 1 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 1
0 1 1 1 1 0 0 0 0 0 0 0 1 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 1
0 1 0 0 1 0 0 0 0 0 0 1 0 0 0 0 0 1 1 1 1 0 1 1 1 1 1 0 0 0 0 1
0 1 0 0 1 0 0 0 0 0 1 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 0 0 0 0 1
0 1 1 1 1 0 0 0 0 1 0 0 0 0 0 0 0 1 1 1 1 0 1 1 1 1 1 0 0 0 0 1
0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 1 1
```
Example of a map that the hummer is helpful
```
10 4           10 4  
S 1 0 T        S * * T    
0 1 0 0        0 1 0 0    
0 1 0 0        0 1 0 0    
0 1 0 0  ->    0 1 0 0    
0 1 0 0        0 1 0 0    
0 1 0 0        0 1 0 0    
0 1 0 0        0 1 0 0    
0 1 0 0        0 1 0 0    
0 1 0 0        0 1 0 0    
0 0 0 0        0 0 0 0    
```


Example where the robot has to use the hummer to get to its target and 
should not use the hummer to optimize the path.
```
14 11
0 S 0 0 0 0 0 0 1 0 1
1 1 1 1 1 1 1 0 1 0 1
0 0 0 0 0 0 0 0 1 0 1
0 0 0 0 0 0 0 0 1 0 1
0 0 0 0 0 0 0 0 1 0 1
0 0 0 0 0 0 0 0 1 0 1
0 0 0 0 1 1 1 1 1 0 1
0 0 0 0 0 0 0 0 0 0 1
0 1 1 1 1 0 0 0 0 0 1
0 1 0 0 1 0 0 0 0 0 1
0 1 0 0 1 0 0 0 0 0 1
0 1 1 1 1 0 0 0 1 1 1
0 0 0 0 0 0 0 0 1 0 1
0 0 0 0 0 0 0 0 1 T 1
```

### How to run
```Make``` is used to build the code.

To build the code:  ```make```

To run the executable: ```./main```

### Thoughts

My understanding is that the challenge is to use Dijkstra's algorithm to build a trajectory planner for the robot. Each position in 2D grid is a node in Dijkstra's algorithm. Part one and part two are combine together. By passing enableHammer to true, the robot will use the hammer when it is necessary.

It's a 2D grid. I used ```z``` axis to indicator that whether the robot had used the hammer before. In Dijkstra's algorithm, we have double size of nodes compared to the number of positions in 2D grid.

In the 2D grid, we have eight directions. With ```z``` axis, we extended the number of directions to 16. A rule was added:
```(x, y, 0)``` can point two kind of neighbor nodes
```(next_x, next_y, 1)``` when the position ```grid[next_x][next_y]``` is an obstacle. 
```(next_x, next_y, 0)``` when the position ```grid[next_x][next_y]``` is not an obstacle. 
```(x, y, 1)``` can only point to ```(next_y, next_y, 1)``` when the position ```grid[next_x][next_y]``` is not an obstacle.

At one position, the robot uses the hammer. The ```z``` value will increase from 0 to 1. The maximum value of ```z``` axis is 1, which means the robot has used the hammer before.


### Result
#### Test case 1
#### Part 1:
2D Grid
```
0 1 0 0 
0 1 0 0 
0 1 0 0 
0 1 0 0 
0 1 0 0 
0 0 0 0 
```

Start -> Goal

(0, 0) -> (3, 3)

Found the end position. Min cost is 11.2426
```
(0,0) 
(1,0) 
(2,0) 
(3,0) 
(4,0) 
(5,1) 
(4,2) 
(3,2) 
(2,2) 
(1,2) 
(0,3)
```

#### Part 2:
2D Grid
```
0 1 0 0 
0 1 0 0 
0 1 0 0 
0 1 0 0 
0 1 0 0 
0 0 0 0 
```

Start -> Goal

(0, 0) -> (3, 3)

Enable the hammer

Found the end position. Min cost is 3
```
(0,0) 
(0,1) Use the hammer. 
(0,2) 
(0,3)
```

#### Test case 2
#### Part 1:
2D Grid
```
0 1 0 
0 0 0 
1 0 0 
```

Start -> Goal

(1, 0) -> (2, 2)

Found the end position. Min cost is 2.41421
```
(1,0) 
(1,1) 
(2,2)
```

#### Part 2:
2D Grid
```
0 1 0 
0 0 0 
1 0 0 
```

Start -> Goal

(1, 0) -> (2, 2)

Enable the hammer

Found the end position. Min cost is 2.41421
```
(1,0) 
(1,1) 
(2,2)
```

#### Test case 3
#### Part 1:
2D Grid
```
0 1 0 
1 1 0 
1 0 0 
```

Start -> Goal

(0, 0) -> (2, 2)

Failed to reach the end position


#### Part 2:
2D Grid
```
0 1 0 
1 1 0 
1 0 0 
```
Enable the hammer

Start -> Goal

(0, 0) -> (2, 2)

Found the end position. Min cost is 2.82843
```
(0,0) 
(1,1) Use the hammer. 
(2,2)
```
