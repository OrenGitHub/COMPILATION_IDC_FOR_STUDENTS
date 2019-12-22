;;;;;;;;;;;;;;;;;;;;;;;;;;
;                        ;
; EXTERNAL LIBRARY FUNCS ;
;                        ;
;;;;;;;;;;;;;;;;;;;;;;;;;;
declare i8* @malloc(i32)
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
@STR.AAA = constant [4 x i8] c"AAA\00", align 1
@STR.BBB = constant [4 x i8] c"BBB\00", align 1
@STR.AB  = constant [3 x i8] c"AB\00", align 1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                 ;
; i8* wrappers for actual stringa ;
;                                 ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
@STR.AAA.VAR = global i8* null, align 8
@STR.BBB.VAR = global i8* null, align 8
@STR.AB.VAR  = global i8* null, align 8

;;;;;;;;;;;;;;;;;;;;
;                  ;
; global variables ;
;                  ;
;;;;;;;;;;;;;;;;;;;;
@s = global i8* null, align 8

;;;;;;;;;;;;;;;;
;              ;
; init strings ;
;              ;
;;;;;;;;;;;;;;;;
define i32 @init_strings() {
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @STR.AAA, i32 0, i32 0), i8** @STR.AAA.VAR, align 8
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @STR.BBB, i32 0, i32 0), i8** @STR.BBB.VAR, align 8
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @STR.AB,  i32 0, i32 0), i8** @STR.AB.VAR,  align 8
  ret i32 0
}

;;;;;;;;
;      ; 
; main ;
;      ; 
;;;;;;;;
define i32 @main(i32 %argc, i8** %argv) {
entry:
  %Temp_13 = call i32 @init_strings()
  %call = call i8* @malloc(i32 9)
  store i8* %call, i8** @s, align 8
  %Temp_17 = load i8*, i8** @s, align 8
  %Temp_22 = load i8*, i8** @STR.AAA.VAR, align 8
  %Temp_25 = load i8*, i8** @STR.BBB.VAR, align 8
  %Temp_34 = call i32 @strcmp(i8* %Temp_17, i8* %Temp_22)
  %Temp_55 = icmp ne i32 %Temp_34, 0
  br i1 %Temp_55, label %Label_4_if.body, label %Label_7_if.end

Label_4_if.body:

  %Temp_60 = load i8*, i8** @STR.AB.VAR, align 8
  call void @PrintString(i8* %Temp_60)
  br label %Label_7_if.end

Label_7_if.end:

  ret i32 0
}

