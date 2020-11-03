# stm32-tflm-benchmarking

C Header-File intended to help benchmarking TFLM projects on STM32 Boards

## Disclaimer

The initial idea for the source code was found here: https://aishack.in/tutorials/timing-macros/

It was changed to work on STM32 Boards and a few features have been added. Also instead of floating point numbers only `uint32_t` is used to save resources on the embedded platform.

A previous version of my library used hardcoded event names and function calls which added overheads and was not easily extendable.

## Short Documentation

The documentation is completely based on preprocessor macros and should be intuitive to use.

If the variable `BENCHMARKING` is NOT defined, all the macros will be skipped, so make sure to pass `-DBENCHMARKING` to the compiler!

List of available "functions":

- `DECLARE_BENCHMARK(s)`: Creates set of (static) variables for the given task name `s` to be used internally
- `START_BENCHMARK(s)`: Starts the measurement for the given task name `s`
- `STOP_BENCHMARK(s)`: Saves the time delta/min/max/total for the given task name `s`
- `GET_BENCHMARK_CURRENT_MS(s)`/`GET_BENCHMARK_MIN_MS(s)`/`GET_BENCHMARK_MAX_MS(s)`/`GET_BENCHMARK_AVG_MS(s)`: Returns the current/min/max/avg results for the given task name `s` as `uint32_t`
- `RESET_BENCHMARK(s)`: Resets the min/max/average results for the given task name `s`
- `PRINT_BENCHMARK(s)`: Use `printf(stderr, ...)` to print a summary to the given task name `s` to the serial terminal.
- `PRINT_TIMESTAMP()`: Prints the current miliseconds via `printf(stderr, ...)` on the serial terminal.

As the variable scope of the declared tasks is local/static make sure to access the results in the same function.

## Example Usage

```

#define BENACHMARKING
void task() {
  DECLARE_BENCHMARK(my_task);

  ...

  START_BENCHMARK(my_task);

  // DO STUFF HERE

  STOP_BENCHMARK(my_task);

  ...

  PRINT_TIMESTAMP()
  PRINT_BENCHMARK(my_task);
}
```

## Example Ouput

The serial output for the previous example may look like this:

```
Time: 14437 ms
my_task_ms(cur/min/max/avg)=6/4/444/8
```
