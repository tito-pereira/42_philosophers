-----| Timetables |-----

-----|  Actions and Timers  |-----

"Eating" action:
The slightly most complex action of this program because it manages the most mutexes,
but still nothing too complex for 42 students doing this project to understand.
It simply creates a condition where the "eating status" is only active once the philosopher
holds the locks for both the [philosopher - 1] && [philosopher - 2] forks, and an initial
conditional where, if there was only 1 philosopher created, it simply skips the eating phase
until that philosopher dies.

"Thinking" action:
Since there are no defined rules or specified time for the "thinking" phase of the
philosophers, in order to maximize time efficiency and death avoidance, i simply chose to
not create any usleep() function for this phase, instead just print the status message
inside the corresponding mutex and quickly move on to the next action.

"Sleeping" action:
A very straightforward action, simply prints out the "sleeping" status message and then
uses usleep() the corresponding the <time_to_sleep> argument passed indicates 