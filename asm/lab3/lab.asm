section .data
    k dd 7
    j dd 9
    s dw ''


%macro print 1
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, 1
    
    int 0x80
%endmacro

section .text
    global _start

_start:


    ; mov eax, [k]
    ; mov ebx, 10


    ; L:
    ;     cmp eax, 0
    ;     je kek

    ;     div ebx
    ;     push edx
    ;     loop L

    ;     kek:

    mov eax, [k]
    mov ebx, 2

    div ebx
    ; add eax, 7

    ; add eax, 48
    ; mov [k], eax

    ; mov eax, 4
    ; mov ebx, 1
    ; mov ecx, k
    ; mov edx, 1
    
    ; int 0x80

    mov eax, [k]
    mov ebx, 2

    ;sub eax, 48
    div ebx

    ;add eax, 48
    ;add edx, 48

    mov [k], eax

    ; mov eax, 4
    ; mov ebx, 1
    ; mov ecx, k
    ; mov edx, 1
    
    ; int 0x80

    ; mov ebx, 2
    ; mov eax, [k]
    ; div ebx
    ; add eax, 48
    ; mov [s], eax
    ; print s


    ; add edx, 48
    ; mov [s], edx
    ; print s

    ; push 5
    ; pop edx
    ; add edx, 48
    ; mov [s], edx
    ; print s

    ; mov eax, [k]
    ; mov ebx, 10
    ; mov ecx, 4
    ; L:
    ;     print s
    ;     cmp eax, 0
    ;     je kek
    ;                                                 ; mov eax, [j]
    ;                                                 ; add eax, 48
    ;                                                 ; mov [j], eax
    ;                                                 ; print j
    ;     div ebx
    ;     ;push edx
    ;     ; pop edx
    ;     ; add edx, 48
    ;     ; mov [s], edx
    ;     ; print s
    ;     loop L

    ; kek:

    ; pop eax
    ; add eax, 48
    ; mov [s], eax
    ; print s
    ; pop eax
    ; add eax, 48
    ; mov [s], eax
    ; print s
    ; pop eax
    ; add eax, 48
    ; mov [s], eax
    ; print s
    ; pop eax
    ; add eax, 48
    ; mov [s], eax
    ; print s

    ; AO:
    ;     pop edx
    ;     add edx, 48
        
    ;     mov eax, 4
    ;     mov ebx, 1
    ;     mov ecx, edx
    ;     mov edx, 1
        
    ;     loop AO
    ; mov eax, [k]
    ; add eax, 48
    ; mov [k], eax

    ; mov eax, 4
    ; mov ebx, 1
    ; mov ecx, k
    ; mov edx, 1
    
    ; int 0x80

    mov eax, 1
    int 0x80