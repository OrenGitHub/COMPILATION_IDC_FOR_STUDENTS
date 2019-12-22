;;;;;;;;;;;;;;;;;;;;;;;;;;
;                        ;
; EXTERNAL LIBRARY FUNCS ;
;                        ;
;;;;;;;;;;;;;;;;;;;;;;;;;;
declare i32* @malloc(i32)
declare i32 @strcmp(i8*, i8*)
declare i32 @printf(i8*, ...)

;;;;;;;;;;;;;;;;;;;;;
;                   ;
; printf parameters ;
;                   ;
;;;;;;;;;;;;;;;;;;;;;
@.str = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                 ;
; LIBRARY FUNCTION :: PrintString ;
;                                 ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
define void @PrintString(i8* %s) {
entry:
  %s.addr = alloca i8*, align 4
  store i8* %s, i8** %s.addr, align 4
  %Temp_55 = load i8*, i8** %s.addr, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i8* %Temp_55)
  ret void
}

;;;;;;;;;;;;;;;;;;
;                ;
; ACTUAL STRINGS ;
;                ;
;;;;;;;;;;;;;;;;;;
@STR.ACCESS.VIOLATION = constant [17 x i8] c"access violation\00", align 1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                 ;
; i8* wrappers for actual stringa ;
;                                 ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
@STR.ACCESS.VIOLATION.VAR = global i8* null, align 8

;;;;;;;;;;;;;;;;;;;;
;                  ;
; global variables ;
;                  ;
;;;;;;;;;;;;;;;;;;;;
@s = global i8* null, align 8
@i = global i32 0, align 4
@myArray = global i32* null, align 8

;;;;;;;;;;;;;;;;
;              ;
; init strings ;
;              ;
;;;;;;;;;;;;;;;;
define i32 @init_strings() {
  store i8* getelementptr inbounds ([17 x i8], [17 x i8]* @STR.ACCESS.VIOLATION, i32 0, i32 0), i8** @STR.ACCESS.VIOLATION.VAR, align 8
  ret i32 0
}

;;;;;;;;
;      ; 
; main ;
;      ; 
;;;;;;;;
define i32 @main(i32 %argc, i8** %argv) {
entry:

  ;;;;;;;;;;;;;;;;;;;;
  ;                  ;
  ; [1] init strings ;
  ;                  ;
  ;;;;;;;;;;;;;;;;;;;;
  %Temp_11 = call i32 @init_strings()

  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  ;                             ;
  ; [2] Compute allocation size ;
  ;                             ;
  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  %Temp_7 = load i32, i32* @i, align 4
  %Temp_13 = call i32 @foo(i32 %Temp_7)
  %Temp_14 = add nsw i32 %Temp_13, 17
  %Temp_22 = add nsw i32 %Temp_14, 1
  %Temp_30 = call i32* @malloc(i32 %Temp_22)

  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  ;                                                   ;
  ; [3] Write allocation size in entry 0 of the array ;
  ;                                                   ;
  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  %Temp_40 = getelementptr inbounds i32, i32* %Temp_30, i32 0
  store i32 %Temp_14, i32* %Temp_40, align 4

  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  ;                                     ;
  ; [4] Should we initialize the array? ;
  ;                                     ;
  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  %Temp_50 = load i32, i32* @i, align 4
  %Temp_51 = icmp slt i32 %Temp_50, 0
  br i1 %Temp_51, label %Label_2_Negative_Idx, label %Label_3_Non_Negative_Idx

  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  ;                                                            ;
  ; [5] Finally, assign the allocation address to the variable ;
  ;                                                            ;
  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  store i32* %Temp_30, i32** @myArray, align 8

  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  ;                                    ;
  ; [6] Check if subscript is negative ;
  ;                                    ;
  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  %Temp_50 = load i32, i32* @i, align 4
  %Temp_51 = icmp slt i32 %Temp_50, 0
  br i1 %Temp_51, label %Label_2_Negative_Idx, label %Label_3_Non_Negative_Idx

Label_2_Negative_Idx:

  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  ;                                     ;
  ; [7] subscript *is* negative -> exit ;
  ;                                     ;
  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  call void @access_violation()
  br label %Label_4_end

Label_3_Non_Negative_Idx:

  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  ;                                      ;
  ; [8] subscript is *not* negative      ;
  ;     check if subscript >= array size ;
  ;                                      ;
  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  %Temp_60 = load i32, i32* @i, align 4
  %Temp_70 = load i32*, i32** @myArray, align 8
  %Temp_71 = getelementptr inbounds i32* %Temp_70, i32 0, i32 0
  %Temp_72 = load i32, i32* Temp_71, align 8
  %Temp_73 = icmp sge i32 %Temp_50, %Temp_72
  br i1 %Temp_73, label %Label_4_Out_Of_Bounds_Idx, label %Label_5_Inbounds_Idx

  store i8* %call, i8** @s, align 8
  %Temp_17 = load i8*, i8** @s, align 8

Label_4_end:

  ret i32 0
}

