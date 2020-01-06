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
@INT_FORMAT = constant [4 x i8] c"%d\0A\00", align 1
@STR_FORMAT = constant [4 x i8] c"%s\0A\00", align 1
@PTR_FORMAT = constant [4 x i8] c"%p\0A\00", align 1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                              ;
; LIBRARY FUNCTION :: PrintInt ;
;                              ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
define void @PrintInt(i32 %i) {
entry:
  %i.addr = alloca i32, align 4
  store i32 %i, i32* %i.addr, align 4
  %0 = load i32, i32* %i.addr, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @INT_FORMAT, i32 0, i32 0), i32 %0)
  ret void
}

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                 ;
; LIBRARY FUNCTION :: PrintString ;
;                                 ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
define void @PrintString(i8* %s) {
entry:
  %s.addr = alloca i8*, align 4
  store i8* %s, i8** %s.addr, align 4
  %0 = load i8*, i8** %s.addr, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @STR_FORMAT, i32 0, i32 0), i8* %0)
  ret void
}

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                              ;
; LIBRARY FUNCTION :: PrintPtr ;
;                              ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
define void @PrintPtr(i8* %ptr) {
entry:
  %ptr.addr = alloca i8*, align 4
  store i8* %ptr, i8** %ptr.addr, align 4
  %0 = load i8*, i8** %ptr.addr, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @PTR_FORMAT, i32 0, i32 0), i8* %0)
  ret void
}

;;;;;;;;;;;;;;;;;;
;                ;
; ACTUAL STRINGS ;
;                ;
;;;;;;;;;;;;;;;;;;
@STR.AAA = constant [4 x i8] c"AAA\00", align 1
@STR.BBB = constant [4 x i8] c"AAA\00", align 1
@STR.AB  = constant [3 x i8] c"AB\00", align 1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                 ;
; i32 wrappers for actual strings ;
;                                 ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
@STR.AAA.VAR = global i32 0, align 4
@STR.BBB.VAR = global i32 0, align 4
@STR.AB.VAR  = global i32 0, align 4

;;;;;;;;;;;;;;;;;;;;
;                  ;
; global variables ;
;                  ;
;;;;;;;;;;;;;;;;;;;;
@str = global i32 0, align 4
@array_of_strings = global i32 0, align 4

;;;;;;;;;;;;;;;;
;              ;
; init strings ;
;              ;
;;;;;;;;;;;;;;;;
define void @init_strings() {
  %Temp_999 = ptrtoint [4 x i8]* @STR.AAA to i32
  store i32 %Temp_999, i32* @STR.AAA.VAR, align 4
  %Temp_997 = ptrtoint [4 x i8]* @STR.BBB to i32
  store i32 %Temp_997, i32* @STR.BBB.VAR, align 4
  %Temp_996 = ptrtoint [3 x i8]* @STR.AB to i32
  store i32 %Temp_996, i32* @STR.AB.VAR, align 4
  ret void
}

;;;;;;;;
;      ; 
; main ;
;      ; 
;;;;;;;;
define i32 @main(i32 %argc, i8** %argv) {
entry:
  call void @init_strings()
  %Temp_01 = load i32, i32* @STR.AAA.VAR, align 4
  %Temp_02 = load i32, i32* @STR.BBB.VAR, align 4
  %Temp_03 = inttoptr i32 %Temp_01 to i8*
  %Temp_04 = inttoptr i32 %Temp_02 to i8*
  %Temp_05 = call i32 @strcmp(i8* %Temp_03, i8* %Temp_04)
  %Temp_06 = call i8* @malloc(i32 16)
  %Temp_07 = ptrtoint i8* %Temp_06 to i32
  call void @PrintInt(i32 %Temp_07)
  store i32 %Temp_07, i32* @array_of_strings, align 4
  %Temp_08 = load i32, i32* @array_of_strings, align 4
  %Temp_09 = add nsw i32 %Temp_08, 12
  call void @PrintInt(i32 %Temp_09)
  %Temp_10 = inttoptr i32 %Temp_09 to i32*
  store i32 %Temp_01, i32* %Temp_10
  %Temp_11 = icmp eq i32 %Temp_05, 0
  br i1 %Temp_11, label %Label_4_if.body, label %Label_7_if.end

Label_4_if.body:

  %Temp_12 = load i32, i32* @array_of_strings, align 4
  %Temp_13 = add nsw i32 %Temp_12, 12
  call void @PrintInt(i32 %Temp_13)
  %Temp_14 = inttoptr i32 %Temp_13 to i32*
  %Temp_15 = load i32, i32* %Temp_14, align 4
  %Temp_16 = inttoptr i32 %Temp_15 to i8*
  call void @PrintString(i8* %Temp_16)
  br label %Label_7_if.end

Label_7_if.end:

  ret i32 0
}

