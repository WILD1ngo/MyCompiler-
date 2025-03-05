nasm -f elf64 test.asm -o run.o
ld run.o -o run
./run
