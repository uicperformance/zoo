# zoo

In this assignment, we experiment with malloc, valgrind, massif and gdb in diagnosing some problems with 
a small existing program. 

*do not read secret_defs.h*

Reading this file will ruin one of your very healthy exercises. 

## Setting up

Clone the repo, and type `make`.

## Memory leaks

The provided zoo management software maintains a list of zoo animals using a generic linked list data structure. Unfortunately, the client has noticed that the program leaks memory. A lot of memory. 

They've included some prints of total heap memory usage. Even after removing every animal from the zoo, a lot of memory is held up in active allocations. Of course, this memory returns to the OS when the process exits, but the clients envision a long-running application and don't want to see memory leaks.

*Your assignment:* Use valgrind --leak-check=full to find, then fix the memory leaks. You will find more than one. Make sure you use valgrind to track down the problems, rather than carefully read the code. The latter only works on small programs. 

## Excessive memory allocation

After eliminating the leaks, you'll find that the program allocates quite a lot of memory for a relatively small number of animals. This is also not making the clients happy.

*Your assignment:* without reading secret_defs.h, use massif (valgrind --tool=massif and ms_print), to learn how and where a lot of memory is being allocated. Then use gdb to dig into the details, and try to figure out what might be hiding in secret_defs.h to make the program behave this way. :-)

