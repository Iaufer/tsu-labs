section .data
    X dd 1, 3, 4, 7,  9
    Y dd 0, 2, 6, 8, 11
    tmp dd 0
    _tmp dd 0
    ix dd 0
    lenXY dd 5
    _lenXY dd 4


section .text
    global _start
_start:
    mov esi, X
    mov esp, Y
    mov edi, 0

    xor ecx, ecx
    xor ebp, ebp 
    xor ebx, ebx
    
    L:
        cmp edi, [_lenXY]
            jne _AU
                jmp ___exit
            _AU:
        mov eax, [esi + 4 * edi]
        inc edi

        _L:
            mov ecx, [esp + 4 * ebp]
            
            cmp eax, ecx
            jg kek
                mov eax, [esi + 4 * edi]
                cmp eax, ecx
                jl poletel
                    jmp exit
                poletel:
            kek:

            exit:

            inc ebp

            cmp ebp, [lenXY]
            jne AU
                jmp __exit
            AU:

            loop _L

            __exit:
            xor ebp, ebp

        loop L
        
    ___exit:

    add ebx, 48
    mov [tmp], ebx

    mov eax, 4
    mov ebx, 1
    mov ecx, tmp
    mov edx, 1
    int 0x80

    mov eax, 1
    int 0x80