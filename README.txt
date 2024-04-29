This project was made while studying in 42 Porto as part of the Computer Science
Common Core curriculum.
This project is 42's version of the classical "Dining Philosophers" problem, regularly
used in CS to teach about multithreading and concurrency problems.
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

My way of keeping track of the current hunger level of each philosopher was to create, for each
philosopher, an additional thread that would simply keep refreshing the current hunger level for each
philosopher, to which we can call the "Death Cycle".

The calculations for the "hunger" value are very simple:
hunger = (current time in ms) - (the time it was since the start of last meal)
which basically translates to how much time has passed since each philosopher last ate.

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
(update)

-----|  3.0: Actions             |-----

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

-----|  4.0: Timers              |-----

One of the most importants aspects to learn how to handle with multi-threading programming, as well
as data concurrency with mechanisms such as mutexes, it's program execution "timers", especially
if our program directly uses time as a component of it's execution, just like this one does.
If time is a factor, then every program heavily focused on a lot of in/out operations, OS
schedulers and overall on a lot of function calls or recursion, is at risk, because these heavily
affect execution speed and therefore affect "timers" and execution times.

For example, after finally getting this "philosophers" program to work, i had a hard time using
Valgrind to debug and check for memory leaks, because Valgrind slowed down my program so much,
that all the timers slowed down and all the philosophers would starve simply by waiting for
Valgrind to allow to program to continue it's execution.

This part isn't really explaining my code itself, but more as a warning for any 42 student currently
doing this project. With multi-threading programming, not only are you fighting against
bad syntax that used to cause normal segfaults and memory leaks, but you are now also
fighting against your own ability to write stack-efficient code and keeping in mind good
programming practics and philosophies.

Another thing to consider is the scenarios where philosophers are actually supposed to die.
During my initial testing, my program was working "too well": what i mean by that is it had no
memory leaks, correct outputs, every philosopher was staying alive when they were supposed to, but
they were also staying alive when they were NOT supposed to.
Now, what do i mean, were "not supposed" to stay alive?
Between deadlock situations and ensuring you are properly checking for every possible data race
and shared memory space between threads, it is to be expected that some philosophers may
starve to death for a good cause: ensuring proper programming techniques and safety measures.
This project also teaches that there may be times where a tradeoff between execution speed
for more safety is necessary and/or preferable, even if it results in the death of some philosophers
here and there.