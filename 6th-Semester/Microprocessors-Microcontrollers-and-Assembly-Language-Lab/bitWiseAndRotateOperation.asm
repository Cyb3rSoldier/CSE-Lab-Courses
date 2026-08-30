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
msg2 db 10,13,'OR = $'       
msg3 db 10,13,'SHL = $'
msg4 db 10,13,'SHR = $'
msg5 db 10,13,'ROL = $'
msg6 db 10,13,'ROR = $'
.code

main proc
    mov ax, @data
    mov ds,ax
               
    ;AND
    mov ah,09h
    lea dx,msg1
    int 21h           
        
    mov al,num1
    and al,0Fh
    mov bl,al
    
    mov al,bl
    shr al,4
    call print_hex
    
    mov al,bl
    and al,0Fh
    call print_hex   
    
    ;OR
    mov ah,09h
    lea dx,msg2
    int 21h           
        
    mov al,num2
    and al,0D1h
    mov bl,al
    
    mov al,bl
    shr al,4
    call print_hex
    
    mov al,bl
    and al,0Fh
    call print_hex
    
    ;SHL
    mov ah,09h
    lea dx,msg3
    int 21h     
    
    mov al,num3
    mov bl,al      
        
    mov al,bl
    shl al,3
    call print_hex
    
    mov al,bl
    and al,0Fh
    call print_hex         
    
    ;SHR
    mov ah,09h
    lea dx,msg4
    int 21h     
    
    mov al,num4
    mov bl,al      
        
    mov al,bl
    shr al,6
    call print_hex      
    
    ;ROL
    mov ah,09h
    lea dx,msg5
    int 21h     
    
    mov al,num5
    mov bl,al      
        
    mov al,bl
    rol al,2
    call print_hex    
    
    ;ROR
    mov ah,09h
    lea dx,msg6
    int 21h     
    
    mov al,num6
    mov bl,al      
        
    mov al,bl
    ror al,7
    call print_hex
    
    mov al,bl
    and al,0Fh
    call print_hex
    
    
    mov ah, 4ch
    int 21h
    
main endp            

print_hex proc
    add al,48
    cmp al,57
    jbe out
    add al, 7
    
    out:
    mov ah, 02h   
    mov dl,al
    int 21h
    ret
   print_hex endp           

end main
    
    