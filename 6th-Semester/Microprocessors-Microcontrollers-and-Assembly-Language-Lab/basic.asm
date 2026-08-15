.model small
.stack 100h
.code       

.data 
msg db 4                       ;store single value in variable
msg1 db 'My name is omar: $'   ;store string in variable

main proc          
    
    ;1 -> single key input
    ;2 -> single character output
    ;9 -> character string output
    
    mov ax, @data    ;initialize data
    mov ds,ax   
    
    mov ah,9         ;show string
    lea dx,msg1
    int 21h         
    
    mov ah,2         ;new line
    mov dl,10
    int 21h
    mov dl,13
    int 21h        
    
    mov ah,2         ;beep sound
    mov dl,07
    int 21h
    
    mov ah,2  
    add msg,48       ;add 48 for ASCII value
    mov dl,msg
    int 21h
    
    mov ah,1         ;user input 
    int 21h
    mov bl,al
    
    mov ah,1
    int 21h
    mov bh,al       
    
    mov ah,2
    mov dl,7
    int 21h
                     
    mov ah,2         ;new line
    mov dl,10
    int 21h
    mov dl,13
    int 21h
    
    mov ah,2         ;output
    mov dl,bl
    int 21h    
    
    mov ah,2
    mov dl,10
    int 21h
    mov dl,13
    int 21h
    
    mov ah,2
    mov dl,bh
    int 21h
    
    mov ah,4ch       ;exit
    int 21h
    main endp
end main
    