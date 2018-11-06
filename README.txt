This program determines whether or not it is possible to split a group of wrestlers into two teams where there are no rivalries within a team.
Data is read from a file chosen by you in the beginning of the program. The data should be in this format:

4     //The first line is the number of wrestlers
A     //the following lines have the wrestlers names
B     //
C     //
D     //
3     //after the names is the number of rivalries
A C   //the rivalries are formatted with the two participating parties separated by a space.
B D   //
A D   //

The program will output the results both to the command line, as well as to a file named wrestler.out

In order to use this program:
Compile the program with:   g++ -o wrestlers wrestler.cpp
Run the program with:       ./wrestler
