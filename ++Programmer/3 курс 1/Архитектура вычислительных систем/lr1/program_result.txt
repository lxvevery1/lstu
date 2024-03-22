model small 
data_in segment 
 input db 83 
data_in ends 
data_out segment 
 res1 db 0 
data_out ends 
code segment 
 res2 db 0 
 assume DS:data_out, ES:data_in, CS:code 
start: 
 mov ax, data_in 
 mov es, ax 
 mov ax, data_out 
 mov ds, ax 
 mov al, input 
 xor ah, ah 
 mov bl, 10 
 div bl 
 mov dl, al 
 mov al, ah 
 shl dl, 4 
 or al, dl 
 mov res1, al 
 mov res2, al 
 
 mov ah, 4Ch 
 int 21h 
end start