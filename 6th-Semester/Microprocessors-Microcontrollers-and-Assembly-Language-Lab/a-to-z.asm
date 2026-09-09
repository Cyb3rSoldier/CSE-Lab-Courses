.model small
.stack 100h
.code
.data   
msg db 10,13,'$'

main proc    
    mov ax,@data
    mov ds,ax
       
    mov cx, 26
    mov dl, 'A'
    
    level:    
    cmp dl, 'S'
    je skip     
    
    mov ah, 2
    int 21h    
    
    push dx          
    mov ah,09h
    lea dx, msg
    int 21h   
    pop dx 
                  
    skip:   
    inc dl
    loop level
    
    exit: 
    mov ah, 4ch
    int 21h
    
    main endp
end main