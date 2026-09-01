.model small
.stack 100h

.data

num1 db 018h
num2 db 02Ah
num3 db 0C4h
num4 db 06Bh
num5 db 0FFh
num6 db 07Ah

msg1 db 'AND = $'
msg2 db 13,10,'OR  = $'
msg3 db 13,10,'SHL = $'
msg4 db 13,10,'SHR = $'
msg5 db 13,10,'ROL = $'
msg6 db 13,10,'ROR = $'

.code

main proc

    mov ax, @data
    mov ds, ax

    ; AND

    mov ah, 09h
    lea dx, msg1
    int 21h

    mov al, num1
    and al, 0Fh
    call print_hex

    ; OR

    mov ah, 09h
    lea dx, msg2
    int 21h

    mov al, num2
    or  al, 0D1h
    call print_hex

    ; SHL

    mov ah, 09h
    lea dx, msg3
    int 21h

    mov al, num3
    shl al, 3
    call print_hex


    ; SHR

    mov ah, 09h
    lea dx, msg4
    int 21h

    mov al, num4
    shr al, 6
    call print_hex

    ; ROL

    mov ah, 09h
    lea dx, msg5
    int 21h

    mov al, num5
    rol al, 2
    call print_hex


    ; ROR

    mov ah, 09h
    lea dx, msg6
    int 21h

    mov al, num6
    ror al, 7
    call print_hex

    mov ah, 4Ch
    int 21h

main endp


print_hex proc

    push ax
    push bx

    mov bl, al

    ; Print high nibble
    mov al, bl
    mov cl, 4
    shr al, cl
    call print_digit

    ; Print low nibble
    mov al, bl
    and al, 0Fh
    call print_digit

    pop bx
    pop ax

    ret

print_hex endp


print_digit proc

    cmp al, 09h
    jbe number

    add al, 07h

number:
    add al, 30h

    mov dl, al
    mov ah, 02h
    int 21h

    ret

print_digit endp

end main