nasm -f elf64 output.asm -o run.o
ld run.o -o run
./run
