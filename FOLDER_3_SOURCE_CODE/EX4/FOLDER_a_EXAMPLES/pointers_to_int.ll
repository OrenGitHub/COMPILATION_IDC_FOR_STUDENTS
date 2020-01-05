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

@PTR_FORMAT = constant [4 x i8] c"%p\0A\00", align 1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                              ;
; LIBRARY FUNCTION :: PrintPtr ;
;                              ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
define void @PrintPtr(i8** %ptr) {
entry:
  %ptr.addr = alloca i8**, align 8
  store i8** %ptr, i8*** %ptr.addr, align 8
  %0 = load i8**, i8*** %ptr.addr, align 8
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @PTR_FORMAT, i32 0, i32 0), i8** %0)
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
@STR.AAA.VAR = global i32 0, align 4
@STR.BBB.VAR = global i32 0, align 4
@STR.AB.VAR  = global i32 0, align 4

;;;;;;;;;;;;;;;;;;;;
;                  ;
; global variables ;
;                  ;
;;;;;;;;;;;;;;;;;;;;
@s = global i8* null, align 4
@array_of_strings = global i8** null, align 4

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
  %call = call i8* @malloc(i32 9)
  %call2 = call i8* @malloc(i32 12)
  %Temp_40 = bitcast i8* %call2 to i8**
  store i8** %Temp_40, i8*** @array_of_strings, align 4
  %Temp_00 = load i8**, i8*** @array_of_strings, align 4
  call void @PrintPtr(i8** %Temp_00)
  store i8* %call, i8** @s, align 8
  %Temp_90 = load i32, i32* @STR.AAA.VAR, align 4
  %Temp_22 = inttoptr i32 %Temp_90 to i8*
  %Temp_91 = load i32, i32* @STR.BBB.VAR, align 4
  %Temp_17 = inttoptr i32 %Temp_91 to i8*
  %Temp_34 = call i32 @strcmp(i8* %Temp_17, i8* %Temp_22)
  %Temp_55 = icmp ne i32 %Temp_34, 0
  br i1 %Temp_55, label %Label_4_if.body, label %Label_7_if.end

Label_4_if.body:

  %Temp_60 = load i32, i32* @STR.AB.VAR, align 8
  %Temp_88 = inttoptr i32 %Temp_60 to i8*
  call void @PrintString(i8* %Temp_88)
  br label %Label_7_if.end

Label_7_if.end:

  ret i32 0
}

