section .data
    A dd 2
    B dd 20
    C dd 20

    msg db "Треугольник можно построить!!!", 0xA
    lenMsg equ $ - msg

    msg1 db "Треугольник нельзя построить!!!", 0xA
    lenMsg1 equ $ - msg1

    msg2 db "Треугольник равносторонний!!!", 0xA
    lenMsg2 equ $ - msg2

    msg3 db "Треугольник равнобедренный!!!", 0xA
    lenMsg3 equ $ - msg3


section .text
    global _start

_start:
    mov eax, [A]
    mov ebx, [B]
    mov ecx, [C]

    add eax, ebx
    
    ;треугольник можно построить если выполняется след. условия: A + B > C и A + C > B и B + C > A
    
    cmp eax, ecx  ; здесь происходить сравненние А + B > C, если результат удовлетворяет условию то происходит след. проверка
    jbe kek
        sub eax, ebx
        add eax, ecx

        cmp eax, ebx ; здесь происходить сравненние А + С > B, если результат удовлетворяет условию то происходит след. проверка
        jbe kik
            sub eax, ecx
            add ebx, ecx

            cmp ebx, eax  ; здесь происходить сравненние B + C > A, если результат удовлетворяет условию => 
            ; => треугоульник можно посторить и нужно понять что это за треугольник(равнобедренный, обычный, равносторонний)
            jbe kak
                ;исправить
                ; mov ecx, msg
                ; mov edx, lenMsg
                ; mov ebx, 1
                ; mov eax, 4
                ; int 0x80

                mov eax, [A]
                mov ebx, [B]
                mov ecx, [C]

                ;проверка на равносторонний

                cmp eax, ebx
                jne gig
                    cmp ebx, ecx
                    jne gog
                        jmp ravnostor
                        ; mov ecx, msg2
                        ; mov edx, lenMsg2
                        ; mov ebx, 1
                        ; mov eax, 4
                        ; int 0x80
                    gog:
                gig:

                ;проверка на равнобедренный
                
                cmp eax, ebx
                jne tak
                    jmp ravnobedr
                tak:

                cmp eax, ecx
                jne tok
                    jmp ravnobedr
                tok:

                cmp ebx, ecx
                jne tik
                    jmp ravnobedr
                tik:

                ;если это не равнобедр., равносторонний => он обычный => будет выведена предложения, что треугольник посторить можно
                
                jmp poletel

    kek:
        kik:
            kak:

    mov ecx, msg1
    mov edx, lenMsg1
    mov ebx, 1
    mov eax, 4
    int 0x80

    jmp exit

    ravnostor:

    mov ecx, msg2
    mov edx, lenMsg2
    mov ebx, 1
    mov eax, 4
    int 0x80

    jmp poletel

    ravnobedr:

    mov ecx, msg3
    mov edx, lenMsg3
    mov ebx, 1
    mov eax, 4
    int 0x80   

    jmp poletel     

    poletel:

    mov ecx, msg
    mov edx, lenMsg
    mov ebx, 1
    mov eax, 4
    int 0x80
    
    exit:

    mov eax, 1
    int 0x80