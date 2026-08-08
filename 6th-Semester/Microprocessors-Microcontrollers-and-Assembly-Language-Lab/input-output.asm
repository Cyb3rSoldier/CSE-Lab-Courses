.model small
.stack 100h

.data
    msg1 db 'Enter first number: $'
    msg2 db 0Dh, 0Ah, 'Enter second number: $'
    out1 db 0Dh, 0Ah, 'First number: $'
    out2 db 0Dh, 0Ah, 'Second number: $'

.code

main proc

    mov ax, @data
    mov ds, ax

    mov ah, 09h
    lea dx, msg1
    int 21h

    mov ah, 01h
    int 21h
    mov bl, al

    mov ah, 09h
    lea dx, msg2
    int 21h

    mov ah, 01h
    int 21h
    mov bh, al

    mov ah, 09h
    lea dx, out1
    int 21h

    mov ah, 02h
    mov dl, bl
    int 21h

    mov ah, 09h
    lea dx, out2
    int 21h

    mov ah, 02h
    mov dl, bh
    int 21h

    mov ah, 4Ch
    int 21h

main endp
end main