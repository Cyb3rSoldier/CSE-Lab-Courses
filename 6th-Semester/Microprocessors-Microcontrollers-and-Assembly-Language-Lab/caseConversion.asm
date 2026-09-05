.model small
.stack 100h

.data
msg1 db "Input: $"
msg2 db 10,13,"Output: $"

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

    cmp bl, 'a'
    jb check_uppercase
    cmp bl, 'z'
    ja check_uppercase

    sub bl, 32
    jmp display_output

check_uppercase:
    cmp bl, 'A'
    jb display_output
    cmp bl, 'Z'
    ja display_output

    add bl, 32

display_output:
    mov ah, 09h
    lea dx, msg2
    int 21h

    mov ah, 02h
    mov dl, bl
    int 21h

    mov ah, 4Ch
    int 21h

main endp
end main
