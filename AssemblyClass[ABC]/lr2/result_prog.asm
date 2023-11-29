model small

data_in segment
    input db 83, 99
data_in ends

data_out segment
    res1 db 0
    res2 db 0
data_out ends

stack segment
    dw 100 dup(0) ; Stack definition
stack ends

code segment
    assume DS:data_out, ES:data_in, CS:code, SS:stack

    near_conversion proc
        mov ax, data_in
        mov es, ax
        mov ax, data_out
        mov ds, ax 

        mov si, 0 ; Initialize index for array traversal

    convert_loop:
        mov al, input[si] ; Load the current element from the array
        xor ah, ah

        mov bl, 10
        div bl
        mov dl, al
        mov al, ah
        shl dl, 4
        
        or al, dl

        ; Check the index to determine which element is being processed
        cmp si, 0
        je store_res1 ; Jump to store_res1 if si is 0
        
        mov res2, al
        
        push ax ; push 99 to stack

        call far ptr far_conversion

        jmp next_iteration

    store_res1:
        mov res1, al

    next_iteration:
        ; Move to the next element in the array
        inc si
        cmp si, 2 ; Check if all elements are processed
        jl convert_loop

        ret ; Return from subroutine

    near_conversion endp

start:
    mov ax, stack
    mov ss, ax

    call near_conversion

    mov ah, 4Ch
    int 21h

code ends

far_code segment
    res3 db 0
    assume CS:far_code
    far_conversion proc far
        mov res3, al
        retf 2
    far_conversion endp
far_code ends

end start