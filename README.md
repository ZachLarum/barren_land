## Barren Land
A case study problem administered by Target.

# Problem
You have a farm of 400m by 600m where coordinates of the field are from (0, 0) to (399, 599). A portion of the farm is barren, and all the barren land is in the form of rectangles. Due to these rectangles of barren land, the remaining area of fertile land is in no particular shape. An area of fertile land is defined as the largest area of land that is not covered by any of the rectangles of barren land. 
Read input from STDIN. Print output to STDOUT 
Input 
You are given a set of rectangles that contain the barren land. These rectangles are defined in a string, which consists of four integers separated by single spaces, with no additional spaces in the string. The first two integers are the coordinates of the bottom left corner in the given rectangle, and the last two integers are the coordinates of the top right corner. 
Output 
Output all the fertile land area in square meters, sorted from smallest area to greatest, separated by a space. 

# Breakdown
There are two main challenges to the this problem. The first is adding the barren land. The second is adding up of the fertile area(s).

Peripheral problems include parsing the input and delivering the output.

# Approach 1
Create a 2 dimensional vector initialized with fertile land (indicated by 1).
First step
As barren rectangles are recieved, mark the corresponding areas with 0, indicating the land is barren.

Second step
Walk throught the array. As fertile land is encountered, use BFS to find its area, marking each spot with a -1 indicating the land has been visted.

# Questions
If I am given a rectangle that is partially out of bounds, do I throw or accept the input and apply the area within the boundary?

Do I have to follow the sample input format or can I choose my own?

Do I have to follow the sample output format or can I choose my own?

How many plots can I recieve as input?

Would we ever want to change the size of the farm?



----- Under construction -----
I will accept
  Any numeric digit.
  Any sequence of numeric digits smaller than the interger max value.
  I will accept exactly four sequences of numeric digits less than or equal to the "integer max values"?. These four numeric sequences must be wrapped in double quotes ("). If there are multiple, they must be seperated by a comma.
  

