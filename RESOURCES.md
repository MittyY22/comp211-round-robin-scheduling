# Resources

## Academic references

1. Remzi H. Arpaci-Dusseau and Andrea C. Arpaci-Dusseau, *Operating Systems: Three Easy Pieces*, Chapter 7, especially sections 7.6 and 7.7: response time, round robin, quantum size, and scheduling trade-offs. [Chapter PDF](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-sched.pdf).
2. James Aspnes, Yale University, *Processor Scheduling*, especially sections 1 through 3: CPU scheduling, FCFS, preemption, and round robin. These are archived teaching notes; this project uses the general concepts rather than their historical descriptions of specific operating systems. [Teaching notes](https://www.cs.yale.edu/homes/aspnes/pinewiki/ProcessorScheduling.html).

## Ideas to investigate yourself

- Predict the schedule before running the simulator for a workload with unequal bursts.
- Explain the difference between first CPU service and completion.
- Consider how later arrivals or I/O blocking would change the simulator.
- Consider how adding context-switch cost would change the elapsed time.

The simulator and numeric examples in this repository are newly constructed educational material. The PPT cover uses an AI-generated conceptual illustration.
