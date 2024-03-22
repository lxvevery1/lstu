section .data
  binaryNumber db 10101010b  ; Здесь задайте свое 8-битное двоичное число

section .bss
  packedDecimalNumber resb 1  ; Результат в упакованном BCD формате

section .text
  global _start

_start:
  mov esi, binaryNumber     ; Загружаем адрес бинарного числа в регистр esi
  mov edi, packedDecimalNumber  ; Загружаем адрес результата в регистр edi

  mov al, [esi]             ; Загружаем байт бинарного числа в AL
  mov ah, 0                 ; Обнуляем AH

  mov cl, 4                 ; Устанавливаем счетчик битов
  xor dl, dl                ; Обнуляем DL, где будем хранить упакованный результат

convertLoop:
  shl al, 1                 ; Сдвигаем AL влево
  rcl dl, 1                 ; Сдвигаем CF в DL (результат)

  dec cl                    ; Уменьшаем счетчик
  jnz convertLoop           ; Повторяем цикл, пока не обработаем 4 бита

  mov [edi], dl             ; Сохраняем упакованный результат по адресу edi

  ; Для завершения программы:
  mov eax, 1                ; Системный вызов для выхода (1 - номер вызова для выхода)
  int 0x80                  ; Вызываем системный вызов
