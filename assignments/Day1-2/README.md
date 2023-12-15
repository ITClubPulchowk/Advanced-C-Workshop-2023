## Assignment 2.1
You are provided a file (`input.txt`) containing a number of expressions in [postfix notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation#Explanation) as follows:

`input.txt:`
```
5 6 * 4 + 8 -
9 4 / 5 - 7 +
```

You are required to generate a file named `output.txt` containing the results of each of the given expressions. For the above input, the output should look something like this:

`output.txt:`
```
26.000000
4.250000
```

<details>
	<summary>Hint:</summary>
	Use Stack data structure
</details>


## Assignment 2.2
You are provided a file (`input.txt`) containing a list of entries. Each entry is a pair of a key and a value as follows:

`input.txt`
```
key : value
bada : bing
tick : tock
bada : boom
```

You are required to generate a file named `sorted.txt` containing all the entries in the input sorted based on their keys in ascending order. *Use merge sort for sorting the entries*. If two entries have the same key, they should be sorted based on their values. The output for the above input should be:

`sorted.txt:`
```
bada : bing
bada : boom
key : value
tick : tock
```



## Assignment 2.3
You are provided a file (`input.txt`) containing some arbitrary text. The text will not contain any punctuations, and the words may be separated by either a space or a newline.

`input.txt:`
```
You cannot end a sentence with because because because is a conjunction
```

Use a hash table to generate a file named `frequency.txt` containing each word with its corresponding frequency in the given text. The output for the given input should be:

`frequency.txt:`
```
because : 3
a : 2
you : 1
with : 1
sentence : 1
is : 1
end : 1
conjunction : 1
cannot : 1
```

*Note: The ordering of the output does not matter. Your program should be case-insensitive i.e. "The" and "the" should count as the same word.* 