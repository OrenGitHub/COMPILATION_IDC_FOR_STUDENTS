declare i8* @malloc(i32)
declare i8* @strcmp(i8*, i8*)

@STR.AAA = constant [4 x i8] c"AAA\00", align 1
@STR.BBB = constant [4 x i8] c"BBB\00", align 1

@STR.AAA.VAR = global i8* null, align 8
@STR.BBB.VAR = global i8* null, align 8
@s           = global i8* null, align 8

define i32 @main(i32 %argc, i8** %argv) {
entry:
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @STR.AAA, i32 0, i32 0), i8** @STR.AAA.VAR, align 8
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @STR.BBB, i32 0, i32 0), i8** @STR.BBB.VAR, align 8
  %call = call i8* @malloc(i32 9)
  store i8* %call, i8** @s, align 8
  %Temp_17 = load i8*, i8** @s, align 8
  %Temp_22 = load i8*, i8** @STR.AAA.VAR, align 8
  %Temp_34 = call i8* @strcmp(i8* %Temp_17, i8* %Temp_22)
  ret i32 0
}


