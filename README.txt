This project was made while studying in 42 Porto as part of the Computer Science
Common Core curriculum.
It was an introduction to multi-threading programming, with several goals in mind:
- practice of basic syntax, logic, data types and structs;
- familiarity with C language;
- practice the manipulation of threads;
- practice the use of mutexes;
- solving race conditions problems;

For anyone looking to learn something from my code or simply browsing github for some answers,
i created a short object oriented explanation of what i did, in order to help any reader
to quickly understand the code:

-----|  0.0: Description         |-----

(to be written)

-----|  1.0: Philosophers        |-----

(to be written)

-----|  1.1: Life Cycle          |-----

(to be written)

-----|  1.2: Death Cycle         |-----

(to be written)

-----| 2.0: Timestamps           |-----

An essential part of this project was to display the current timestamp, in milisseconds,
on all of the status messages regarding the philosophers's actions. However, our only allowed
function to achieve this was the gettimeofday() function, which gives us two values:
the current SECOND, and the current MICROSSECOND.
I decided that i wanted to have a "real time" timestamp, in milisseconds, starting from 0 at the
start of the program's execution, and keep counting the time until the end of the execution.
To achieve this, i would need to craft my own time-counting system using the available tools:
- creating a thread (&timetable) with the sole purpose of infinitely keep updating the time in
order to count how many minutes have passed since the beginning of the execution;
- a get_time() function that would use the updated "real" time calculated in the &timetable thread,
as well as the beginning timestamps captured at the beginning of the execution (seconds &&
microsseconds), to dinamically calculate and return the value, in milisseconds, of the
current timestamp;

(to be written)

-----|  3.0: Actions and Timers  |-----

"Eating" action:
The slightly more complex action of this program because it manages the most mutexes,
but still nothing too complex for 42 students doing this project to understand.
It simply creates a condition where the "eating status" is only active once the philosopher
holds the locks for both the [philosopher - 1] && [philosopher - 2] forks, and an initial
conditional where, if there was only 1 philosopher created, it simply skips the eating phase
until that philosopher dies.
In my first version on this project, i ran into a stalemate condition where each philosopher
would pick up only one fork and eternally be waiting for the next one to be available, which
would never be and they would all starve holding one fork.
I thought about creating a dinamic micro use of the usleep() function where, in ascending order,
each philosopher would wait a little bit of time before attempting to eat, in order to give the
other philosophers time to eat, but i thought this would go against project guidelines of
"philosophers are not allowed to communicate" and settled for the simpler solution:
creating a conditional where, after a philosopher picks up a fork, if the next fork is not
available to be picked up, instead of waiting, they would drop the current fork and try the
entire eating process again, in hopes of creating enought time, but also running into the risk
of every philosopher executing the exact same "pick up / drop" actions at the same time in
a comical mirror fashion until they all starve to death.

"Thinking" action:
Since there are no defined rules or specified time for the "thinking" phase of the
philosophers, in order to maximize time efficiency and death avoidance, i simply chose to
not create any usleep() function for this phase, instead just print the status message
inside the corresponding mutex and quickly move on to the next action.

"Sleeping" action:
A very straightforward action, simply prints out the "sleeping" status message and then
uses usleep() the corresponding the <time_to_sleep> argument passed indicates 