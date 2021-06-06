# Assignment 7: The Great Firewall of Santa Cruz

This program filters and reports bad words parsed from stdin.

## Build
```
make
```
or
```
make all
```

## Running
```
./banhammer [-h] [-t hash table size] [-f bloom filter size] [-m] [-s]
```
Use -h to get the help/usage message.
-t: specify hash table size
-f: specify bloom filter size
-m: enable move to print rule
-s: enable printing of statistics
