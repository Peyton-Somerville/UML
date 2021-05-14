Project 2:
Peyton Somerville (worked alone)


Experiments:

1. Make writer threads starve
./ReaderWriters 100 5 100 5 1000000 500000 1000000 500000 1000 5
Results:
Total number of reads: 467452
Total number of writes: 5


2. Make reader threads starve
./ReaderWriters 1000000 500000 1000000 500000 100 5 100 5 5 1000
Results:
Total number of reads: 1145
Total number of writes: 46656

./ReaderWriters 1000000 1000000 1000000 1000000 100 5 100 5 5 1000
Results:
Total number of reads: 489
Total number of writes: 37239

./ReaderWriters 1000000 500000 1000000 500000 50 5 50 5 1 2000
Results:
Total number of reads: 21
Total number of writes: 41822

I cannot figure out how to make the readers starve.
