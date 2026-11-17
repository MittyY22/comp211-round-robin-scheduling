# Round-Robin CPU Scheduling

COMP 211 Checkoff 3 topic: **Operating System Scheduling: Round-Robin Scheduling**.

This project uses a small C simulator to explore how a CPU scheduler shares time among ready processes. It compares round robin (RR) with first-come, first-served (FCFS) and examines the effect of the time quantum.

## Contents

| File | Purpose |
| --- | --- |
| [scheduler.c](scheduler.c) | Runnable C model with FCFS and RR examples |
| [sample_results.txt](sample_results.txt) | Actual output from compiling and running the default example |
| [AI_GENERATED_STUDY_DRAFT.pptx](AI_GENERATED_STUDY_DRAFT.pptx) | Editable study draft with English speaker notes and Chinese learning hints |
| [RESOURCES.md](RESOURCES.md) | Academic sources and suggestions for further exploration |

## Run the example

Requirements: a C compiler (`cc`, GCC, or Clang). No additional libraries are needed.

```sh
cc -std=c11 -Wall -Wextra -Werror scheduler.c -o scheduler
./scheduler
```

The default workload has three processes A, B, and C. Each arrives at time 0 and requires 4 ms of CPU work. The program prints the FCFS baseline and RR schedules for quanta of 1, 2, and 4 ms.

Use a specific quantum with the default workload:

```sh
./scheduler 2
```

Or choose a quantum followed by custom CPU bursts:

```sh
./scheduler 2 6 4 2
```

This runs RR with q = 2 ms for A = 6, B = 4, and C = 2 ms, alongside an FCFS baseline. All jobs still arrive at time 0 in alphabetical order. Inputs must be positive integers. The program allows up to 26 jobs and at most 10,000 ms of total CPU work.

## What the example demonstrates

The **quantum** is the maximum CPU time a process receives during one turn. If a process still has work when its turn ends, it waits for its next turn. A process that finishes early leaves the queue.

Two metrics describe different delays:

- **Response time:** first CPU run minus arrival time. This definition does not measure the time until visible output.
- **Turnaround time:** completion time minus arrival time.

For A = B = C = 4 ms:

| Policy | Average response (ms) | Average turnaround (ms) |
| --- | ---: | ---: |
| FCFS | 4 | 8 |
| RR, q = 1 ms | 1 | 11 |
| RR, q = 2 ms | 2 | 10 |
| RR, q = 4 ms | 4 | 8 |

With q = 2 ms, the schedule is:

```text
Time (ms):  0-2   2-4   4-6   6-8   8-10   10-12
Process:     A     B     C     A      B       C
```

First runs occur at 0, 2, and 4 ms. Completion occurs at 8, 10, and 12 ms. Their averages are 2 ms and 10 ms respectively. In this workload, earlier first turns come with a higher average turnaround time than FCFS. These are results for this example rather than a universal guarantee.

## Model assumptions and limits

This is a deterministic simulation, not an operating-system implementation or a benchmark of this computer. It assumes one CPU core, simultaneous arrivals, no I/O, and zero context-switch cost. Since all jobs are present from the start and never block, a cyclic scan of unfinished jobs produces the same order as a ready queue.

Actual context switches take time. A smaller quantum can increase switching frequency. For an illustrative steady-state model with one switch of cost c after each full quantum q, the switching share is c / (q + c). For q = 1 ms and an assumed c = 0.1 ms, that share is about 9.1%. This cost is **not included** in the program's results and is not a measured hardware value.

## Continue the exploration

Run a different workload, explain one result in your own words, and compare it with your prediction. A useful starting point is `./scheduler 2 6 4 2`: does a shorter CPU burst change the response-versus-turnaround comparison?

Before submitting the course project, add your own final slides and a truthful learning reflection with representative prompts and the AI conversation permalink. The presentation recording must be submitted separately according to the course instructions.

See [RESOURCES.md](RESOURCES.md) for the sources behind the scheduling concepts.
