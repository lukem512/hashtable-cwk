hashtable-cwk
=============

COMS11600 CW2 - Hash table to read A Christmas Carol and analyse word frequency

The aim of this coursework was to create a Hash Table, with an effective hash algorithm that would store the frequency of words appearing in A Christmas Carol. A Linked List would also be used to do the same. Queries were given to be run against these data structures, to find the frequency of certain words, and the times were to be reported.

The hash algorithm I implemented is a rotated XOR hash.

The times were as follows:

looking
  occurred 20 times
	list took 3046 comparisons
	table took 1 comparison

me
	occurred 111 times
	list took 4336 comparisons
	table took 3

attractive
	occurred 1 time
	list took 3 comparisons
	table took 1 comparison

please
	occurred 4 times
	list took 46 comparisons
	table took 1 comparison

where
	occurred 35 times
	list took 4056 comparisons
	table took 2 comparisons
	
knock
	occurred 3 times
	list took 341 comparisons
	table took 1 comparison

computer
	occurred 0 times
	list took 4371 comparisons
	table took 0 comparisons
