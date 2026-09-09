.model small
.stack 100h
.code
.data   
array db 1,2,3

main proc    
    mov ax,@data
    mov ds,ax       
    
    mov si, offset array
    mov cx,3
       
    my_loop:
    mov ah, 2
    mov dl, [si]    
    add bl, dl 
    inc si
    
    loop my_loop
    
    add bl, 48
    
    mov ah, 02h
    mov dl,bl
    int 21h
    
    
    exit: 
    mov ah, 4ch
    int 21h
    
    main endp
end main