## Assignment - 4

For this assignment, you will be implementing merge sort algorithm (as you did for assignment 2.2) but multithreaded. Use the following steps as a guideline for this assignment:

```
1. Generate an array of random intergers (rand() function from the standard library)
2. Use merge sort algorithm to sort the generated array.
3. Implement a thread pool and perform the merge sort in a multithreaded environment.
4. Perform the same task using different number of threads (2, 3, 4, ...), and measure the performance of the program in each case.
5. Generate a CSV file documenting the performance with reference to the number of threads used. 
```

Note: Measuring the temporal performance of your program is a platform dependent problem. Use [platform macros](https://dev.to/tenry/predefined-c-c-macros-43id) to make your code platfrom independent.

Your final output should look something like this:

`output.csv`
```
# of threads, time (ms)
2, ...
3, ...
4, ...
...
```