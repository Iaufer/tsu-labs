section .data
   A dd 1223
   B dd 113

   msg db "А меньше B"
   lenMsg equ $ - msg

   newLineMsg db 0xA, 0xD
   newLineLen equ $-newLineMsg

section .bss
   s resb 1024
   len resd 1

section	.text
   global _start        ; должно быть объявлено для использования gcc

_start:
   mov eax, [A]
   mov ebx, [B]

   cmp eax, ebx ; если А меньше В то не выполняю действия
   ja tau
      mov     ecx, msg
      mov     edx, lenMsg
      mov     ebx, 1
      mov     eax, 4
      int     0x80
      jmp pol
   tau:

   div ebx ;нахожу остаток
   mov eax, edx

    lea edi, [s]  ; т.к нельзя вывести число больше 9, я формирую результат в строку и вывоже строку
    xor ecx, ecx
    mov ebx, 10
    div:
        xor edx, edx
        inc ecx
        div ebx
        add edx, '0'
        push edx
        test eax, eax
    jnz div

    mov[len], ecx
    store:
        pop eax
        stosb
    loop store


    mov eax, 4 ; вывожу строку
    mov ebx, 1
    mov ecx, s
    mov edx, [len]

   int 80h

   pol:

   mov edx, newLineLen
   mov ecx, newLineMsg
   mov ebx, 1
   mov eax, 4
   int 0x80

   mov eax, 1
   
   int 0x80
   ;FINISH
  
