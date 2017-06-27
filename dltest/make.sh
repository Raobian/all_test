
gcc main.c -ldl -rdynamic
gcc -shared -fPIC -nostartfiles -o mylib.so mylib.c
