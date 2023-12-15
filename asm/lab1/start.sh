#!/bin/bash
nasm -f elf lab_1.asm && \
ld -m elf_i386 -s -o lab_1 lab_1.o && \
./lab_1
