section .data
    k dd 8
    a dd -3
    minus db '-'
    _a dd 0
    tmp dd 0
section .bss
   s resb 1024
   len resd 1
section .text
    global _start
_start:
    xor eax, eax
    mov eax, [k]
    cmp eax, 0
    jne kzero ;проверка степени на равенство нулю
        mov eax, [k]
        add eax, 1
        add eax, 48
        mov [k], eax
        mov eax, 4
        mov ebx, 1
        mov ecx, k
        mov edx, 1
        int 0x80
        jmp exit
    kzero:

    xor eax, eax
    mov eax, [a]
    cmp eax, 0 ; если а равно нулю 
    jne azero
        mov eax, [a]
        add eax, 48
        mov [a], eax
        mov eax, 4
        mov ebx, 1
        mov ecx, a
        mov edx, 1
        int 0x80
        jmp exit
    azero:


    xor eax, eax
    mov eax, [a]
    cmp eax, 1
    jne aone ; если а равно 1
        mov eax, [a]
        add eax, 48
        mov [a], eax
        mov eax, 4
        mov ebx, 1
        mov ecx, a
        mov edx, 1
        int 0x80
        jmp exit
    aone:

    mov ebx, [a]
    cmp ebx, 0
    jg ot
        mov eax, [k]
        mov ecx, 2
        div ecx
        cmp edx, 0
        je ost
            mov eax, 4
            mov ebx, 1
            mov ecx, minus
            mov edx, 1
            int 0x80
            mov eax, [a]
            mov ebx, -1
            mul ebx
            mov [a], eax
            jmp vixod
        ost:
            mov eax, [a]
            mov ebx, -1
            mul ebx
            mov [a], eax
    ot:
    vixod:
    
    mov eax, [a]
    mov ebx, [a]
    mov edx, 1
    mov edi, 1

    

    L:
        mov edi, 1
        cmp edx, [k]
        jl __kek
        jmp exit
        __kek:
        _L:
            cmp edi, [a]
            jl _kek
                jmp _exit
            _kek:
            add eax, ebx
            inc edi
            loop _L
            _exit:
            mov ebx, eax
            inc edx

        loop L

    exit:

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

    ; _pr:
    ;     pop eax
    ;     add eax, 48
    ;     mov [tmp], eax
    ;     mov eax, 4
    ;     mov ebx, 1
    ;     mov ecx, tmp
    ;     mov edx, 1
    ;     int 0x80
    ;     loop _pr

    ; L:
    ;     cmp edx, [k]
    ;     jl __kek
    ;         jmp exit
    ;     __kek:
    ;     _L:
    ;         cmp edi, [a]
    ;         jl _kek
    ;             jmp _exit
    ;         _kek:
    ;         add eax, ebx
    ;         inc edi
    ;         loop _L
    ;     _exit:
    ;     mov ebx, eax   
    ;     inc edx 
    ;     loop L



    ; add eax, 48
    ; mov [k], eax
    ; mov eax, 4
    ; mov ebx, 1
    ; mov ecx, k
    ; mov edx, 1
    ; int 0x80

    mov eax, 1
    int 0x80
