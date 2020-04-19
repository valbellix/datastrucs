# libdatastructs
The objective of this project is my own fun. I used to be a weirdo so I am having some fun writing some C code to implement data structures. I come from Java/C++ background, these languages come with a rich set of collections ready to be use. Sometimes I write C stuff for fun, but I always found frustrating the lack of support to collections offered by the *standard*. I know there are other approaches (*glib* is the first noticeable example that came into my mind without going too far), but I would like to stay closer to the *core* C without injecting any dependencies if I only need a *vector* on my 10 loc program.

With all that in mind, I would like a no frills, generic and easy to use library of C to implement basic data structures and collections, so I started to write one on my own... just for fun. I do not know how much of this can be really usable in the real world and I can get tired of it in the long run (or other commitmets will eat all my spare time), so, please be kind and take this as it is.

# Build Instructions
There is a CMakeLists.txt file you can use to generate your preferred way to build this library. I really like to do out-of-source builds and I encourage you to do the same. For example, you can generate makefiles (or VS projects) by:
```shell
$ mkdir build
$ cd build
$ cmake ..
$ make
```

# Disclaimer
This code is likely to be very buggy so use it at your own risk.

# License
This work is licensed under MIT License, if you wonder *why*, my answer is and it will always be *why not?*