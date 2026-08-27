# Philosophers

A 42 project that simulates the dining philosophers problem using threads and mutexes.

The goal is to synchronize multiple philosophers competing for shared forks while preventing race conditions, deadlocks, and starvation.

## How It Works

Each philosopher repeatedly:

1. Takes two forks
2. Eats
3. Sleeps
4. Thinks

Each philosopher runs in a separate thread. Forks are protected by mutexes, and a monitoring system detects whether a philosopher has died.

The simulation stops when:

- A philosopher dies from not eating in time
- Every philosopher has eaten the required number of meals

## Installation

```bash
git clone https://github.com/paula17d/philosophers.git
cd philosophers
make
```

## Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [required_meals]
```

All time values are provided in milliseconds.

Example:

```bash
./philo 5 800 200 200
```

Example with a required meal count:

```bash
./philo 5 800 200 200 7
```

## Arguments

| Argument | Description |
|----------|-------------|
| `number_of_philosophers` | Number of philosophers and forks |
| `time_to_die` | Maximum time a philosopher can go without eating |
| `time_to_eat` | Time required to eat |
| `time_to_sleep` | Time spent sleeping |
| `required_meals` | Optional number of meals each philosopher must eat |

## Output

The program displays timestamped status messages:

```text
0 1 has taken a fork
1 1 is eating
201 1 is sleeping
401 1 is thinking
```

## Makefile Commands

| Command | Description |
|---------|-------------|
| `make` | Compile the program |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and executable |
| `make re` | Recompile the program |

## Concepts

Threads · Mutexes · Synchronization · Race conditions · Deadlocks · Shared resources · Timing · Concurrent programming
