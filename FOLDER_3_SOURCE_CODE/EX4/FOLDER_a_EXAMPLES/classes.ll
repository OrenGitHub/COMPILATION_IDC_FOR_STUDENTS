;;;;;;;;;;;;;;;;;;;;;;;
;                     ;
; STDLIB DECLARATIONS ;
;                     ;
;;;;;;;;;;;;;;;;;;;;;;;
declare i8* @malloc(i32)
declare i32 @printf(i8*, ...)

;;;;;;;;;;;;;;;;;;;;
;                  ;
; GLOBAL VARIABLES ;
;                  ;
;;;;;;;;;;;;;;;;;;;;
@oren = global i32* null, align 4

;;;;;;;;;;;;;;;;;;;;;
;                   ;
; printf parameters ;
;                   ;
;;;;;;;;;;;;;;;;;;;;;
@.str = constant [4 x i8] c"%d\0A\00", align 1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                              ;
; LIBRARY FUNCTION :: PrintInt ;
;                              ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
define dso_local void @PrintInt(i32 %i) {
entry:
  %i.addr = alloca i32, align 4
  store i32 %i, i32* %i.addr, align 4
  %0 = load i32, i32* %i.addr, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %0)
  ret void
}

;;;;;;;;;;;;;;;;;;;;;;;
;                     ;
; ENTRY POINT :: main ;
;                     ;
;;;;;;;;;;;;;;;;;;;;;;;
define i32 @main(i32 %argc, i8** %argv) {
entry:

  ;;;;;;;;;;;;;;;;;;;;;;;
  ;                     ;
  ; Temp_1 = new Person ;
  ;                     ;
  ;;;;;;;;;;;;;;;;;;;;;;;
  %Temp_1 = call i8* @malloc(i32 20)

  ;;;;;;;;;;;;;;;;;;;;;;;;;;;
  ;                         ;
  ; Temp_2 = (i32 *) Temp_1 ;
  ;                         ;
  ;;;;;;;;;;;;;;;;;;;;;;;;;;;
  %Temp_2 = bitcast i8* %Temp_1 to i32*

  ;;;;;;;;;;;;;;;;;
  ;               ;
  ; oren = Temp_2 ;
  ;               ;
  ;;;;;;;;;;;;;;;;;
  store i32* %Temp_2, i32** @oren, align 4

  ;;;;;;;;;;;;;;;;;;;;;;
  ;                    ;
  ; oren->salary = 244 ;
  ;                    ;
  ;;;;;;;;;;;;;;;;;;;;;;
  %Temp_3 = load i32*, i32** @oren, align 4
  %Temp_4 = getelementptr inbounds i32, i32* %Temp_3, i32 2
  store i32 244, i32* %Temp_4

  ;;;;;;;;;;;;;;;;;;;;;;;;;;
  ;                        ;
  ; PrintInt(oren->salary) ;
  ;                        ;
  ;;;;;;;;;;;;;;;;;;;;;;;;;;
  %Temp_5 = load i32*, i32** @oren, align 4
  %Temp_6 = getelementptr inbounds i32, i32* %Temp_5, i32 2
  %Temp_7 = load i32, i32* %Temp_6, align 4
  call void @PrintInt(i32 %Temp_7)

  ;;;;;;;;;;
  ;        ;
  ; return ;
  ;        ;
  ;;;;;;;;;;
  ret i32 0
}


