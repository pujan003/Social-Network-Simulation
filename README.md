The goal of this product is to answer simple english language queries about a social network. 

In particular, I will simulate an academic social network, spread potentially across multiple universities. 
In PART A, I have implemented a discrete event simulator to create such a network. 
PART B will be able to answer user queries, posed in Engligh language, to answer queries about the network


**The Network**.

The network has two categories of people: students and faculty. A (residential) university comprises
departments, hostels, and faculty housing. All faculty join at the beginning before all students. The
students join once a year. The faculty join a department and are allocated a house each. The students
join a department and are allocated a hostel room each. In addition, each person has a set of
interests/hobbies. The year is divided onto two (six month) semesters, and a list of courses are floated
each semester. Each course is taught by one faculty member and a taken by a set of students. Each
member is likely to make friends with people they come in contact with either by being neighbors, or
being in the same class, or by having a common interest. Friends can also introduce other friends.
You will begin by reading an input file with parameters about courses, students, faculty etc. Based on
these parameters and a randomization, you will “generate” individual members who join the university
and continue simulating their befriending activities for a certain length of simulated time. This will
produce the social network graph.

**PART A**:
***NetworkGen***
This module creates agents and simulates their behavior to produce a graph with nodes and edges. It
consists of two processes.
1.
One is
TimeKeeper
.
It keeps time in terms of the number of simulated seconds since its start. It
advances the seconds at simulation speed as follows. It takes “alarm” requests by other “client”
processes for a future time. If the request is for a past time, the request is denied (and the
requester informed). Otherwise, the requester is woken up at the appropriate time. It can also be
queried for the current time. Timekeeper advances time to the next alarmed event's time in
sequence unless a client has requested a “time pause.” Initially, the time is paused. You are free
to choose the communication method – sockets and signals are candidates. It's clients are the
threads of the
Generator
process described next.
2.
The second process,
Generator
, first runs submodule
setEnvironment
and then forks four co-
operating generator threads.
Generator
executable takes a command-line parameter for the
number of days the generator simulates as “-d num_days”.
Module
Network
owns the graph
data structure and exposes function calls to generator threads. Submodule
setEnvironment
reads
and parses an input file that contains information about each participating university.

**PART B**:
***GraphGyani***
This module is made of a perl script,Gyani, and and a C executable,Analyzer. Analyzer is started from within Gyani.
Gyani reads query lines from stdin and parses each line. It makes the best guess about the query being made and packs the query to Analyzer and relays the answer back to stdout. Analyzer begins by reading the graph from the GraphML provided on the command line and performs computations to answer queries. It supports the following queries (you should implement
Dijkstra's shortest path and Floyd–Warshall all-pair shortest path algorithms):

1. Size of Clique of a given person (identified by university name and ID)
2. The length of the shortest path between two given people
3. The list of people on the shortest path between two given people
4. The shortest path in the graph (between any pair of people)
5. The importance of the given person (the importance is the number of the all-pair shortest paths that include that person)
6. Is any of the friends of a given person more important that him/her
