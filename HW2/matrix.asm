
extern calloc
extern free

global matrixNew ;done
global matrixDelete 
global matrixSet ;done
global matrixGet ;done
global matrixGetRows ;done
global matrixGetCols ;done
global matrixAdd
global matrixScale
global matrixMu

%define ROWS 0
%define COLS 8
%define REALCOLS 16
%define DATA 24 
%define FLOAT_SIZE 4
%define HELP_FIELD 6

%macro roundTo4 1
    add %1, 3
    shr %1, 2
    shl %1, 2 
%endmacro


section .text

    ; Matrix matrixNew(unsigned int rows, unsigned int cols);
    ;                               edi                esi
    matrixNew: 
        mov rcx, rsi
        roundTo4 rcx 
        mov rax, rcx

        mul rdi
        add rax, HELP_FIELD
         
        push rsi 
        push rdi

        mov rdi, rax
        mov rsi, FLOAT_SIZE

        call calloc 

        pop rdi
        pop rsi

        mov rcx, rsi 
        roundTo4 rcx
        mov [rax + ROWS], rdi
        mov [rax + COLS], rsi
        mov [rax + REALCOLS], rcx


; TODO if matrix very large

        ret
    ;void matrixDelete(Matrix matrix);
    matrixDelete:
        call free 
        ret  


    ;unsigned int matrixGetRows(Matrix matrix);
    matrixGetRows:
        mov rax, [rdi + ROWS]

        ret

    ;unsigned int matrixGetCols(Matrix matrix);
    matrixGetCols:
        mov rax, [rdi + COLS]

        ret

    ;void matrixSet(Matrix matrix, unsigned int row, unsigned int col, float value);
    ;                      rdi                  rsi               rdx
    matrixSet
        mov rax, rsi
        imul rax, [rdi + REALCOLS]
        add rax, rdx
        movss [rdi + rax * 4 + DATA], xmm0
        ret

    ;float matrixGet(Matrix matrix, unsigned int row, unsigned int col);
    ;                       rdi                  rsi               rdx

    matrixGet
        mov rax, rsi
        imul rax, [rdi + REALCOLS]
        add rax, rdx
        movss xmm0, [rdi + rax * 4 + DATA]
        
        ret

    ;Matrix matrixAdd(Matrix a, Matrix b);
    ;                        rdi       rsi

    matrixAdd: 
        push r12
        push r13
        push r14
        mov rax, [rdi + ROWS]
        mov rcx, [rsi + ROWS] 
        cmp rax, rcx
        jne .fail

        mov rax, [rdi + COLS]
        mov rcx, [rsi + COLS]
        cmp rax, rcx
        jne .fail

        mov r12, rdi ; a
        mov r13, rsi ; b
    
        mov rdi, 0
        mov rsi, 0

        mov rdi, [r12 + ROWS]
        mov rsi, [r12 + COLS]
        
        call matrixNew
        mov r14, rax ; c
    
        mov rcx, 0
        mov rdx, [r12 + REALCOLS]  
        imul rdx, [r12 + ROWS]
        .loop 
            movups xmm0, [r12 + rcx * 4 + DATA]
            movups xmm1, [r13 + rcx * 4 + DATA]
            addps  xmm0, xmm1
            movups [r14 + rcx * 4 + DATA], xmm0

            add rcx, 4
            cmp rdx, rcx
            jg .loop

        mov rax, r14
        jmp .end

    .fail
        pop r14
        pop r13
        pop r12
        mov rax, 0
        ret

    .end
        pop r14
        pop r13
        pop r12
        ret

; g++-multilib

section .data
    ;FLOAT_SIZE dd 4
    ZERO dd 0


