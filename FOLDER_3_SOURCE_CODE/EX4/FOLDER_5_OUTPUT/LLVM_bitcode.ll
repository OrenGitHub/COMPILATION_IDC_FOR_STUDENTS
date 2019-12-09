;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                         ;
; GLOBAL VARIABLE :: zero ;
;                         ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;
@my_zero = global i32 0, align 4

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

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                            ;
; STDANDRD LIBRARY :: printf ;
;                            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
@.str = private unnamed_addr constant [4 x i8] c"%d \00", align 1
declare dso_local i32 @printf(i8*, ...)

;;;;;;;;;;;;;;;;;;;
;                 ;
; GLOBAL VARIABLE ;
;                 ;
;;;;;;;;;;;;;;;;;;;
@i = global i32 0, align 4

;;;;;;;;;;;;;;;;;;;
;                 ;
; GLOBAL VARIABLE ;
;                 ;
;;;;;;;;;;;;;;;;;;;
@j = global i32 0, align 4

;;;;;;;;;;;;;;;;;;;
;                 ;
; GLOBAL VARIABLE ;
;                 ;
;;;;;;;;;;;;;;;;;;;
@p = global i32 0, align 4

;;;;;;;;;;;;;;;;;;;
;                 ;
; GLOBAL VARIABLE ;
;                 ;
;;;;;;;;;;;;;;;;;;;
@start = global i32 0, align 4

;;;;;;;;;;;;;;;;;;;
;                 ;
; GLOBAL VARIABLE ;
;                 ;
;;;;;;;;;;;;;;;;;;;
@end = global i32 0, align 4

;;;;;;;;;;;;;;;;;;;
;                 ;
; GLOBAL VARIABLE ;
;                 ;
;;;;;;;;;;;;;;;;;;;
@isPrime = global i32 0, align 4

;;;;;;;;;;;;;;;;;;;
;                 ;
; GLOBAL VARIABLE ;
;                 ;
;;;;;;;;;;;;;;;;;;;
@copyp = global i32 0, align 4

;;;;;;;;;;;;;;;;;;;
;                 ;
; GLOBAL VARIABLE ;
;                 ;
;;;;;;;;;;;;;;;;;;;
@copyisPrime = global i32 0, align 4

;;;;;;;;;;;;;;;;;;;;;;;
;                     ;
; ENTRY POINT :: main ;
;                     ;
;;;;;;;;;;;;;;;;;;;;;;;
define dso_local i32 @main(i32 %argc, i8** %argv) {
entry:
  %retval = alloca i32, align 4
  %argc.addr = alloca i32, align 4
  %argv.addr = alloca i8**, align 8
  store i32 0, i32* %retval, align 4
  store i32 %argc, i32* %argc.addr, align 4
  store i8** %argv, i8*** %argv.addr, align 8
  br label %main_body

main_body:

  %dave_0 = load i32, i32* @my_zero, align 4
  %Temp_0 = add nsw i32 %dave_0, 2
  store i32 %Temp_0, i32* @p, align 4
  %dave_1 = load i32, i32* @my_zero, align 4
  %Temp_1 = add nsw i32 %dave_1, 2
  store i32 %Temp_1, i32* @start, align 4
  %dave_2 = load i32, i32* @my_zero, align 4
  %Temp_2 = add nsw i32 %dave_2, 100
  store i32 %Temp_2, i32* @end, align 4
  br label %Label_1_while.cond

Label_1_while.cond:

  %Temp_4 = load i32, i32* @p, align 4
  %Temp_6 = load i32, i32* @end, align 4
  %dave_3 = load i32, i32* @my_zero, align 4
  %Temp_7 = add nsw i32 %dave_3, 1
  %Temp_5 = add nsw i32 %Temp_6, %Temp_7
  %Temp_3 = icmp slt i32 %Temp_4, %Temp_5
  %oren_4 = icmp eq i1 %Temp_3, 0
  br i1 %oren_4, label %Label_0_while.end, label %any.label_4
  
any.label_4:

  %dave_5 = load i32, i32* @my_zero, align 4
  %Temp_8 = add nsw i32 %dave_5, 2
  store i32 %Temp_8, i32* @i, align 4
  %dave_6 = load i32, i32* @my_zero, align 4
  %Temp_9 = add nsw i32 %dave_6, 2
  store i32 %Temp_9, i32* @j, align 4
  %dave_7 = load i32, i32* @my_zero, align 4
  %Temp_10 = add nsw i32 %dave_7, 1
  store i32 %Temp_10, i32* @isPrime, align 4
  br label %Label_3_while.cond

Label_3_while.cond:

  %Temp_12 = load i32, i32* @i, align 4
  %Temp_13 = load i32, i32* @p, align 4
  %Temp_11 = icmp slt i32 %Temp_12, %Temp_13
  %oren_8 = icmp eq i1 %Temp_11, 0
  br i1 %oren_8, label %Label_2_while.end, label %any.label_8
  
any.label_8:

  %dave_9 = load i32, i32* @my_zero, align 4
  %Temp_14 = add nsw i32 %dave_9, 2
  store i32 %Temp_14, i32* @j, align 4
  br label %Label_5_while.cond

Label_5_while.cond:

  %Temp_16 = load i32, i32* @j, align 4
  %Temp_17 = load i32, i32* @p, align 4
  %Temp_15 = icmp slt i32 %Temp_16, %Temp_17
  %oren_10 = icmp eq i1 %Temp_15, 0
  br i1 %oren_10, label %Label_4_while.end, label %any.label_10
  
any.label_10:

  %Temp_18 = load i32, i32* @p, align 4
  store i32 %Temp_18, i32* @copyp, align 4
  br label %Label_7_while.cond

Label_7_while.cond:

  %Temp_21 = load i32, i32* @i, align 4
  %Temp_22 = load i32, i32* @j, align 4
  %Temp_20 = mul nsw i32 %Temp_21, %Temp_22
  %Temp_23 = load i32, i32* @copyp, align 4
  %Temp_19 = icmp eq i32 %Temp_20, %Temp_23
  %oren_11 = icmp eq i1 %Temp_19, 0
  br i1 %oren_11, label %Label_6_while.end, label %any.label_11
  
any.label_11:

  %dave_12 = load i32, i32* @my_zero, align 4
  %Temp_24 = add nsw i32 %dave_12, 0
  store i32 %Temp_24, i32* @isPrime, align 4
  %dave_13 = load i32, i32* @my_zero, align 4
  %Temp_25 = add nsw i32 %dave_13, 0
  store i32 %Temp_25, i32* @copyp, align 4
  br label %Label_7_while.cond

Label_6_while.end:

  %Temp_27 = load i32, i32* @j, align 4
  %dave_14 = load i32, i32* @my_zero, align 4
  %Temp_28 = add nsw i32 %dave_14, 1
  %Temp_26 = add nsw i32 %Temp_27, %Temp_28
  store i32 %Temp_26, i32* @j, align 4
  br label %Label_5_while.cond

Label_4_while.end:

  %Temp_30 = load i32, i32* @i, align 4
  %dave_15 = load i32, i32* @my_zero, align 4
  %Temp_31 = add nsw i32 %dave_15, 1
  %Temp_29 = add nsw i32 %Temp_30, %Temp_31
  store i32 %Temp_29, i32* @i, align 4
  br label %Label_3_while.cond

Label_2_while.end:

  %Temp_32 = load i32, i32* @isPrime, align 4
  store i32 %Temp_32, i32* @copyisPrime, align 4
  br label %Label_9_while.cond

Label_9_while.cond:

  %Temp_34 = load i32, i32* @copyisPrime, align 4
  %dave_16 = load i32, i32* @my_zero, align 4
  %Temp_35 = add nsw i32 %dave_16, 1
  %Temp_33 = icmp eq i32 %Temp_34, %Temp_35
  %oren_17 = icmp eq i1 %Temp_33, 0
  br i1 %oren_17, label %Label_8_while.end, label %any.label_17
  
any.label_17:

  %Temp_36 = load i32, i32* @p, align 4
  call void @PrintInt(i32 %Temp_36)
  %dave_18 = load i32, i32* @my_zero, align 4
  %Temp_37 = add nsw i32 %dave_18, 0
  store i32 %Temp_37, i32* @copyisPrime, align 4
  br label %Label_9_while.cond

Label_8_while.end:

  %Temp_39 = load i32, i32* @p, align 4
  %dave_19 = load i32, i32* @my_zero, align 4
  %Temp_40 = add nsw i32 %dave_19, 1
  %Temp_38 = add nsw i32 %Temp_39, %Temp_40
  store i32 %Temp_38, i32* @p, align 4
  br label %Label_1_while.cond

Label_0_while.end:

  ret i32 0
}
