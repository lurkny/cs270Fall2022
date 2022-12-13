Tower of Hanoi Plan


1. Shift N-1 Disks from A to B using C
2. Shift last disk from A to C
3. Shift N-1 disks from B to C using A



Create a function towerOfHanoi where pass the N (current number of disk), from_rod, to_rod, aux_rod.
Make a function call for N – 1 th disk.
Then print the current the disk along with from_rod and to_rod
Again make a function call for N – 1 th disk.
