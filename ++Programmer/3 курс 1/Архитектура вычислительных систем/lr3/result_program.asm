.model small

data_in segment
    input db 4 dup(0) ; Массив для ввода данных
    output db 8 dup(0) ; Массив, содержащий отдельные символы для каждого числа
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
    ;--------------------------------------------------------
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
        sub al, '0' ; Convert ASCII to integer

        ; Store the modified value in the input array
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

        ; Print the input array for verification
        mov si, 0
        print_input:
            mov dl, input[si]
            add dl, '0' ; Convert back to ASCII
            mov ah, 02h ; DOS function to print character
            int 21h

            inc si
            cmp si, 4
            jl print_input

        ; Push the modified values (83, 99) to the stack
        push ax

        ; Call the far subroutine for further processing
        call far ptr far_conversion

        ret ; Return from subroutine

    near_conversion endp
    ;--------------------------------------------------------

start:
    call near_conversion

    ;--------------------------------------------------------
    play_audio:
        ; загрузка счетчика канала 2 значением 0E24h (нота "Ми")
        mov al, 24h ; сначала выводится младший байт
        out 42h, al
        mov al, 0Eh ; затем выводится старший байт
        out 42h, al
        ; включение сигнала и динамика
        in al, 61h
        or al, 00000011b
        out 61h, al

        ; формирование короткой задержки (примерно 0.5 секунды)
        mov cx, 3277 ; Adjust this value for the desired delay
        mov dx, 8
        mov ah, 86h
        int 15h

        ; выключение сигнала и динамика
        in al, 61h
        and al, 11111100b
        out 61h, al
        
    ;--------------------------------------------------------

    mov ax, 4C00h
    int 21h

code ends

;--------------------------------------------------------
far_code segment
    res3 db 0
    assume CS:far_code
    far_conversion proc far
        mov res3, al
        retf 2
    far_conversion endp
far_code ends
;--------------------------------------------------------

end start