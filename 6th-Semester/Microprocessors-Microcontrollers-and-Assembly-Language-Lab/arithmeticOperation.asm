.model small
.stack 100h    

.data 
msg1 db 'Enter first number: $'
msg2 db 10,13,'Enter second number: $'
out1 db 10,13,'Sum: $'     
out2 db 10,13,'Sub: $' 

.code

main proc    
    mov ax, @data
    mov ds,ax
    
    mov ah,9
    lea dx,msg1
    int 21h
    
    mov ah,1    
    int 21h   
    mov bl,al 
    
    mov ah,9
    lea dx, msg2
    int 21h
    
    mov ah,1 
    int 21h    
    mov bh,al 
    
    mov ah,9 
    lea dx,out1
    int 21h
    
    add bl,bh 
    sub bl,48
    
    mov ah,2
    mov dl,bl
    int 21h  
    
    
    
    
    mov ah,4ch
    int 21h   
    
main endp    
end main
    