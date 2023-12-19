## Assignment - 3

Consider float arrays X and Y with N elements. Implement the following three functions to complete the forward pass function for the handwritten digit recognition neural network:
1. [relu](https://en.wikipedia.org/wiki/Rectifier_(neural_networks%29): `relu(X, N) = [max(0, x) for each x in X]`
2. [argmax](https://en.wikipedia.org/wiki/Arg_max): `X[argmax(N, X)] = max(X)`
3. [vector_sum](https://www.youtube.com/watch?v=CLMzrIlUf_c): `vector_sum(N, X,Y,N) = [x+y for each x,y in X and Y]`

Compile with curses (-lcurses) and optimizations. Use a terminal that supports mouse input (alacritty, Windows Terminal with WSL, kitty, gnome terminal). Run the output binary from this directory.

The application is rather simple. Press f to begin drawing, and press g when you're done. The prediction should be displayed below the drawing area. Press c to clear and start over, and q to quit.

For bonus points, implement relu and vector_sum with simd intrinsics. Note that input array sizes may not necessarily be multiples of 4. For bonus bonus points, implement argmax with simd intrinsics too. 

## Submission
To submit your assignments, create a directory with name as your github username, and place your code inside that directory.
