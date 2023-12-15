section .data
    arr dd -9, -1, -1, 1, 1, 1, 0, 0, 0
    arrlen dd 9
    otr dd 0
    pol dd 0
    zero dd 0
    max dd 0


    msg1 dd "otr bolshe"
    msg2 dd "zerobolshe"
    msg3 dd "pol bolshe"
    

section .text
    global _start
_start:
    mov esi, arr
    mov edi, 0
    mov ecx, [arrlen]
    xor ebp, ebp ; кол-во отриц
    xor esp, esp ; кол-во нулей
    xor ebx, ebx ; кол-во пол

    L:
        mov eax, [esi + 4 * edi]
        cmp eax, 0
        jge kek
            inc ebp  ; считает отриц
        kek:
            cmp eax, 0
            jne polet
                inc esp     ; считает нули
            polet:
                cmp eax, 0
                jle kung
                    inc ebx ; считает пол
                kung:
            inc edi
        loop L

    mov [otr], ebp
    mov[zero], esp
    mov [pol], ebx

    mov eax, [otr]  ; преположим что это макс
    mov edi, [zero]
    mov ecx, [pol]


    cmp eax, edi
    jl ed
        cmp eax, ecx
        jl ec
            mov eax, 4
            mov ebx, 1
            mov ecx, msg1
            mov edx, 10
            int 0x80
        ec:
    ed:

    mov eax, [otr]  ; преположим что это макс
    mov edi, [zero]
    mov ecx, [pol]

    cmp edi, eax
    jl ea
        cmp edi, ecx
        jl ex
            mov eax, 4
            mov ebx, 1
            mov ecx, msg2
            mov edx, 10
            int 0x80
        ex:
    ea:

    mov eax, [otr]  ; преположим что это макс
    mov edi, [zero]
    mov ecx, [pol]

    cmp ecx, eax
    jl be
        cmp ecx, edi
        jl eb
            mov eax, 4
            mov ebx, 1
            mov ecx, msg3
            mov edx, 10
            int 0x80
        eb:
    be:






    ; cmp edi, eax
    ; jl mx
    ;     mov eax, edi
    ; mx:
    
    ; cmp ecx, eax
    ; jl _mx
    ;     mov eax, ecx
    ; _mx:

    ; add eax, 48
    ; mov [max], eax

    ; mov eax, 4
    ; mov ebx, 1
    ; mov ecx, max
    ; mov edx, 1
    ; int 0x80


 



    ; add ebx, 48
    ; mov [zero], ebx

    ; add ebp, 48
    ; mov [pol], ebp    
    
    ; mov eax, 4
    ; mov ebx, 1
    ; mov ecx, pol
    ; mov edx, 1
    ; int 0x80

    ; add esp, 48
    ; mov [pol], esp    
    
    ; mov eax, 4
    ; mov ebx, 1
    ; mov ecx, pol
    ; mov edx, 1
    ; int 0x80

    ; mov eax, 4
    ; mov ebx, 1
    ; mov ecx, zero
    ; mov edx, 1
    ; int 0x80

    mov eax, 1
    int 0x80

