.model small

data_in segment
    input db 4 dup(0) ; Массив для ввода данных
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

    input_loop:
        ; Ввод символа с клавиатуры
        mov ah, 01h
        int 21h
        sub al, '0' ; magic
        mov input[si], al

        inc si
        cmp si, 4 ; Check if all digits are entered
        jl input_loop

        mov si, 0 ; Reset the index for array traversal

        ; Convert two-digit numbers
        mov al, input[si] ; Load the first digit
        shl al, 4 ; Shift left to make room for the second digit
        add al, input[si + 1] ; Add the second digit

        mov res1, al ; Store the result in res1

        ; Move to the next two digits
        mov al, input[si + 2] ; Load the third digit
        shl al, 4 ; Shift left to make room for the fourth digit
        add al, input[si + 3] ; Add the fourth digit

        mov res2, al ; Store the result in res2

        push ax ; push 83, 99 to stack

        call far ptr far_conversion

        ret ; Return from subroutine

    near_conversion endp

start:
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