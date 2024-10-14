global quicksort
section .text
; Función que realiza un algoritmo Quicksort no aleatorizado en una tabla de caracteres
; Argumentos:
;   - dirección de una tabla de caracteres en ebp+8
;   - entero que indica un punto de inicio en ebp+12 pasado por valor
;   - entero que indica un punto final en ebp+16 pasado por valor
; Valor de retorno:
;   - dirección de un array ordenado en eax
quicksort:
    push ebp
    mov ebp, esp
    sub esp, 16 ; Reserva espacio para valor de retorno, valor del pivote, valor j y valor i
    pusha       ; Guarda todos los registros de propósito general

    mov esi, [ebp+8]   ; esi almacena la dirección de la tabla
    mov eax, [ebp+16]  ; eax = índice final
    movzx edx, byte [esi+eax] ; Carga el último elemento como pivote
    mov [ebp-8], edx   ; Guarda el valor del pivote en la pila
    mov ebx, [ebp+12]  ; ebx = índice inicial
    sub eax, ebx
    mov ecx, eax       ; ecx = número de elementos en la tabla menos 1
    cmp ecx, 1
    je QS_primitive_case ; Si solo hay dos elementos, salta al caso primitivo

    mov eax, [ebp+12]
    dec eax            ; eax = i = índice inicial - 1
    mov ebx, [ebp+12]  ; ebx = j = índice inicial

QS_init_loop:
    ; Este loop inicializa la partición, moviendo elementos menores que el pivote al principio
    movzx edx, byte [esi+ebx] ; Carga el elemento actual
    mov [ebp-12], ebx  ; Guarda j temporalmente
    mov ebx, [ebp-8]   ; Carga el valor del pivote
    cmp dl, bl         ; Compara el elemento actual con el pivote
    mov ebx, [ebp-12]  ; Restaura j
    jge QS_init_loop_exit ; Si el elemento es >= pivote, sal del loop
    inc ebx            ; j++
    inc eax            ; i++
    dec ecx            ; Decrementa el contador de elementos
    jmp QS_init_loop

QS_init_loop_exit:
    cmp ecx, 0
    je QS_recurent_calls ; Si no quedan elementos, pasa a las llamadas recursivas

QS_sorting_loop:
    ; Este loop continúa la partición
    movzx edx, byte [esi+ebx] ; Carga el elemento actual
    mov [ebp-12], ebx  ; Guarda j temporalmente
    mov ebx, [ebp-8]   ; Carga el valor del pivote
    cmp dl, bl         ; Compara el elemento actual con el pivote
    mov ebx, [ebp-12]  ; Restaura j
    jl QS_element_less ; Si el elemento es < pivote, intercambia
    jmp QS_element_exit

QS_element_less:
    ; Intercambia elementos si el actual es menor que el pivote
    push ecx
    push edx
    movzx edx, byte [esi+eax+1] ; Carga el elemento en i+1
    movzx ecx, byte [esi+ebx]   ; Carga el elemento en j
    mov [esi+eax+1], cl         ; Mueve el elemento j a i+1
    mov [esi+ebx], dl           ; Mueve el elemento i+1 a j
    pop edx
    pop ecx
    inc eax                     ; i++

QS_element_exit:
    inc ebx            ; j++
    loop QS_sorting_loop

    ; Coloca el pivote en su posición final
    push ecx
    push edx
    movzx edx, byte [esi+eax+1] ; Carga el elemento en i+1
    movzx ecx, byte [esi+ebx]   ; Carga el elemento en j (pivote)
    mov [esi+eax+1], cl         ; Coloca el pivote en i+1
    mov [esi+ebx], dl           ; Mueve el elemento i+1 a la posición final
    pop edx
    pop ecx

QS_recurent_calls:
    ; Llamadas recursivas a Quicksort para las subparticiones

    ; Ordenación de la subpartición inferior
    cmp eax, [ebp+12]
    jle QS_lower_table_jump ; Si i <= índice inicial, salta
    mov [ebp-16], eax   ; Guarda i
    push eax            ; Fin de la subpartición inferior
    push dword [ebp+12] ; Inicio de la subpartición inferior
    push dword [ebp+8]  ; Dirección de la tabla
    call quicksort
    add esp, 12
    mov eax, [ebp-16]   ; Restaura i

QS_lower_table_jump:
    add eax, 2          ; i + 2 (inicio de la subpartición superior)
    cmp eax, [ebp+16]
    jge QS_upper_table_jump ; Si i+2 >= índice final, salta

    ; Ordenación de la subpartición superior
    mov [ebp-16], eax
    push dword [ebp+16] ; Fin de la subpartición superior
    push eax            ; Inicio de la subpartición superior
    push dword [ebp+8]  ; Dirección de la tabla
    call quicksort
    add esp, 12
    mov eax, [ebp-16]

QS_upper_table_jump:
    jmp QS_exit

QS_primitive_case:
    ; Maneja el caso de dos elementos
    mov eax, [ebp+12]         ; Índice inicial
    mov ebx, [ebp+16]         ; Índice final
    movzx edx, byte [esi+eax] ; Carga el primer elemento
    movzx ecx, byte [esi+ebx] ; Carga el segundo elemento
    cmp cl, dl                ; Compara los dos elementos
    jg QS_exit                ; Si están en orden, termina
    mov [esi+eax], cl         ; Si no, intercambia los elementos
    mov [esi+ebx], dl

QS_exit:
    mov [ebp-4], esi  ; Guarda la dirección de la tabla ordenada
    popa               ; Restaura todos los registros
    mov eax, [ebp-4]   ; Coloca la dirección de la tabla en eax (valor de retorno)
    mov ebp, [ebp]     ; Restaura el frame pointer
    add esp, 20        ; Limpia el stack
    ret                ; Retorna
