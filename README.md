# Temperature-Displayer
A project written quickly for a work exam that demonstrates my C++ ability.

This project takes in some file named "data.txt", formatted "floor,room,temp". 
Then, using the data, it prints the warmest room, the average temperature 
per each floor, and the temperature of each floor.

Data in this project is stored in multiple ways. A linkedlist, flist, stores
a list of floors, with a vector of each room's temperature on that floor.
Another linkedlist, tlist, stores a list of temperatures with their corresponding
floors.

Linkedlists are viable for one building. They are not viable for a company who
potentially wishes to use one program to monitor the temperatures of multiple
buildings across the United States. In this case, a hashtable would be better for
fast temperature lookups.

But, for this simple project, it's enough.
