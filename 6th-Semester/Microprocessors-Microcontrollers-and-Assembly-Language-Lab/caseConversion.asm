.model small
.stack 100h
.code
.data
msg1 db "Input: $"
msg2 db 10,13,"Output: $"

main proc
    mov ax,@data
    mov ds, ax
    
    mov ah, 09h
    lea dx, msg1
    int 21h
    
    mov ah, 01h
    int 21h  
    mov bl,al
    
    sub bl, 32
    
    mov ah, 09h
    lea dx, msg2
    int 21h
    
    mov ah, 02h
    mov dl, bl
    int 21h
    
    mov ah, 4ch
    int 21h
    
    main endp
end main