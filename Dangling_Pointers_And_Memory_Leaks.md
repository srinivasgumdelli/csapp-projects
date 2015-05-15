# Dangling Pointers #



**What is a pointer?**

First, we must do a basic recap of what a pointer is. Memory is just a bunch of 'slots', to access them we need a way of keeping count of which slot is which.

A pointer refers to a memory address (the method of keeping count) without forcing the programmer to remember the specific and large number that is the memory address. (EG: Pointer 'Bag' refers to a Memory Address '100683')


**What is a Dangling Pointer?**

A dangling pointer is a pointer that refers to some value that no longer exists for the program to use.

This occurs when a memory block the pointer points to is freed from memory usage by the program. The memory block can then be used by other programs - in short, what you want the pointer to refer to no longer exists.

You can then use dangling pointers to access other programs' memory (a vital component of hacking). This violates memory safety and is **NOT** something you want to happen.

**How do I prevent Dangling Pointers?**

Typically dangling pointers occur after you delete what the pointer references to, eg:

char **ptr = (char**)malloc(sizeof(char));
/..../    do stuff with the memory being referred to by ptr
free(ptr);

ptr now doesn't refer to what you want it to since the memory at which ptr points to has been freed for other programs to use and may have changed in unpredictable ways. To correct this we do:

ptr = NULL;

This sets the dangling pointer back to the base value (Null) so that it will no longer refer to a freed memory.

# Memory Leaks #

**What is a Memory Leak?**

A memory leak is the opposite of a dangling pointer. The pointer is moves to another value without the memory it was originally referring to being freed. The end result is that the memory is still thought to be in use, but the program cannot access (it doesn't know where it is).

**How do I prevent Memory Leaks?**

Typically memory leaks will occur if you move the pointer without freeing the memory:

char **ptr = (char**)malloc(sizeof(char));
/..../    do stuff with the memory being referred to by ptr
ptr = 100;

There's no longer a way to get the memory address of what ptr was originally referring to. This means that memory becomes deadweight, taking up space for no good reason.

The solution? Never move a pointer in some arbitrary manner (you can do +/- where you can track the changes, but not ptr = some\_number)