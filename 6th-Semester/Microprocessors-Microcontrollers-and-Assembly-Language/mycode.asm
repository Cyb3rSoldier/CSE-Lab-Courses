.model small
.stack 100h

.data

.code

main proc
    
    mov ax, 5h
    mov bx, 8h
    
    add ax,bx
    xchg ax,bx
    
    mov ah,4ch
    int 21h
    
    main endp
end main


