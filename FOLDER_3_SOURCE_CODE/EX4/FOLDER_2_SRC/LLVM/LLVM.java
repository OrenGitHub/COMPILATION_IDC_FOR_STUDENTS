/***********/
/* PACKAGE */
/***********/
package LLVM;

/*******************/
/* GENERAL IMPORTS */
/*******************/
import java.io.*;
import java.io.PrintWriter;

/*******************/
/* PROJECT IMPORTS */
/*******************/
import TEMP.*;

/********/
/* LLVM */
/********/
public class LLVM
{
	private int WORD_SIZE=4;

	/***********************/
	/* The file writer ... */
	/***********************/
	private PrintWriter fileWriter;

	/***********************/
	/* The file writer ... */
	/***********************/
	public void finalizeFile()
	{
		fileWriter.format("  ret i32 0\n");
		fileWriter.format("}\n");
		fileWriter.close();
	}
	public void print_int(TEMP t)
	{
		int idx=t.getSerialNumber();
		fileWriter.format("  call void @PrintInt(i32 %%Temp_%d)\n",idx);
	}

	public void allocate(String var_name)
	{
		fileWriter.format(";;;;;;;;;;;;;;;;;;;\n");
		fileWriter.format(";                 ;\n");
		fileWriter.format("; GLOBAL VARIABLE ;\n");
		fileWriter.format(";                 ;\n");
		fileWriter.format(";;;;;;;;;;;;;;;;;;;\n");
		fileWriter.format("@%s = global i32 0, align 4\n\n",var_name);
	}
	public void load(TEMP dst,String var_name)
	{
		int idxdst=dst.getSerialNumber();
		fileWriter.format("  %%Temp_%d = load i32, i32* @%s, align 4\n",idxdst,var_name);
	}
	public void store(String var_name,TEMP src)
	{
		int idxsrc=src.getSerialNumber();
		fileWriter.format("  store i32 %%Temp_%d, i32* @%s, align 4\n",idxsrc,var_name);		
	}
	static int x=0;
	public void li(TEMP t,int value)
	{	
		int idx=t.getSerialNumber();

		fileWriter.format("  %%zero_%d = load i32, i32* @my_zero, align 4\n",x);
		fileWriter.format("  %%Temp_%d = add nsw i32 %%zero_%d, %d\n",idx,x++,value);
	}
	public void add(TEMP dst,TEMP oprnd1,TEMP oprnd2)
	{
		int i1 =oprnd1.getSerialNumber();
		int i2 =oprnd2.getSerialNumber();
		int dstidx=dst.getSerialNumber();

		fileWriter.format(
			"  %%Temp_%d = add nsw i32 %%Temp_%d, %%Temp_%d\n",
			dstidx,
			i1,
			i2);
	}
	public void mul(TEMP dst,TEMP oprnd1,TEMP oprnd2)
	{
		int i1 =oprnd1.getSerialNumber();
		int i2 =oprnd2.getSerialNumber();
		int dstidx=dst.getSerialNumber();

		fileWriter.format(
			"  %%Temp_%d = mul nsw i32 %%Temp_%d, %%Temp_%d\n",
			dstidx,
			i1,
			i2);
	}
	public void icmp_lt(TEMP dst,TEMP oprnd1,TEMP oprnd2)
	{
		int i1 =oprnd1.getSerialNumber();
		int i2 =oprnd2.getSerialNumber();
		int dstidx=dst.getSerialNumber();

		fileWriter.format(
			"  %%Temp_%d = icmp slt i32 %%Temp_%d, %%Temp_%d\n",
			dstidx,
			i1,
			i2);
	}
	public void icmp_eq(TEMP dst,TEMP oprnd1,TEMP oprnd2)
	{
		int i1 =oprnd1.getSerialNumber();
		int i2 =oprnd2.getSerialNumber();
		int dstidx=dst.getSerialNumber();

		fileWriter.format(
			"  %%Temp_%d = icmp eq i32 %%Temp_%d, %%Temp_%d\n",
			dstidx,
			i1,
			i2);
	}
	public void label(String inlabel)
	{
		if (inlabel.equals("main"))
		{
			fileWriter.format(";;;;;;;;;;;;;;;;;;;;;;;\n");
			fileWriter.format(";                     ;\n");
			fileWriter.format("; ENTRY POINT :: main ;\n");
			fileWriter.format(";                     ;\n");
			fileWriter.format(";;;;;;;;;;;;;;;;;;;;;;;\n");
			fileWriter.format("define dso_local i32 @main(i32 %%argc, i8** %%argv) {\n");
			fileWriter.format("entry:\n");
			fileWriter.format("  %%retval = alloca i32, align 4\n");
			fileWriter.format("  %%argc.addr = alloca i32, align 4\n");
			fileWriter.format("  %%argv.addr = alloca i8**, align 8\n");
			fileWriter.format("  store i32 0, i32* %%retval, align 4\n");
			fileWriter.format("  store i32 %%argc, i32* %%argc.addr, align 4\n");
			fileWriter.format("  store i8** %%argv, i8*** %%argv.addr, align 8\n");
			fileWriter.format("  br label %%main_body\n");
			fileWriter.format("\nmain_body:\n\n");
		}
		else
		{
			fileWriter.format("\n%s:\n\n",inlabel);
		}
	}	
	public void jump(String inlabel)
	{
		fileWriter.format("  br label %%%s\n",inlabel);
	}	
	public void blt(TEMP oprnd1,TEMP oprnd2,String label)
	{
		int i1 =oprnd1.getSerialNumber();
		int i2 =oprnd2.getSerialNumber();
		
		fileWriter.format("  %%oren = icmp slt i32 %%Temp_%d, 0\n",i1);
		fileWriter.format("  br i1 %%oren, label %%%s, label %%any.label_%d\n",label,x);
		fileWriter.format("  \nany.label_%d:\n\n",x++);
	}
	public void bge(TEMP oprnd1,TEMP oprnd2,String label)
	{
		int i1 =oprnd1.getSerialNumber();
		int i2 =oprnd2.getSerialNumber();
		
		fileWriter.format("  %%oren = icmp sge i32 %%Temp_%d, 0\n",i1);
		fileWriter.format("  br i1 %%oren, label %%%s, label %%any.label_%d\n",label,x);
		fileWriter.format("  \nany.label_%d:\n\n",x++);
	}
	public void bne(TEMP oprnd1,TEMP oprnd2,String label)
	{
		int i1 =oprnd1.getSerialNumber();
		int i2 =oprnd2.getSerialNumber();
		
		fileWriter.format("  %%oren = icmp ne i32 %%Temp_%d, 0\n",i1);
		fileWriter.format("  br i1 %%oren, label %%%s, label %%any.label_%d\n",label,x);
		fileWriter.format("  \nany.label_%d:\n\n",x++);
	}
	public void beq(TEMP oprnd1,TEMP oprnd2,String label)
	{
		int i1 =oprnd1.getSerialNumber();
		int i2 =oprnd2.getSerialNumber();
		
		fileWriter.format("  %%oren = icmp eq i32 %%Temp_%d, 0\n",i1);
		fileWriter.format("  br i1 %%oren, label %%%s, label %%any.label_%d\n",label,x);
		fileWriter.format("  \nany.label_%d:\n\n",x++);
	}
	public void beqz(TEMP oprnd1,String label1,String label2)
	{
		int i1 =oprnd1.getSerialNumber();

		fileWriter.format("  %%equal_zero_%d = icmp eq i1 %%Temp_%d, 0\n",x,i1);
		fileWriter.format("  br i1 %%equal_zero_%d, label %%%s, label %%%s\n",x,label1,label2);
		fileWriter.format("  \n%s:\n\n",label2);
		x++;
	}
	
	/**************************************/
	/* USUAL SINGLETON IMPLEMENTATION ... */
	/**************************************/
	private static LLVM instance = null;

	/*****************************/
	/* PREVENT INSTANTIATION ... */
	/*****************************/
	private LLVM() {}

	/******************************/
	/* GET SINGLETON INSTANCE ... */
	/******************************/
	public static LLVM getInstance()
	{
		if (instance == null)
		{
			instance = new LLVM();
			
			/****************************/
			/* Initialize a file writer */
			/****************************/
			try
			{
				String dirname="./FOLDER_5_OUTPUT/";
				String filename="LLVM_bitcode.ll";
				assert(false);
				instance.fileWriter = new PrintWriter(dirname+filename);
			}
			catch (Exception e)
			{
				e.printStackTrace();
			}
			instance.fileWriter.format(";;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
			instance.fileWriter.format(";                         ;\n");
			instance.fileWriter.format("; GLOBAL VARIABLE :: zero ;\n");
			instance.fileWriter.format(";                         ;\n");
			instance.fileWriter.format(";;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
			instance.fileWriter.format("@my_zero = global i32 0, align 4\n\n");

			instance.fileWriter.format(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
			instance.fileWriter.format(";                              ;\n");
			instance.fileWriter.format("; LIBRARY FUNCTION :: PrintInt ;\n");
			instance.fileWriter.format(";                              ;\n");
			instance.fileWriter.format(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
			instance.fileWriter.format("define dso_local void @PrintInt(i32 %%i) {\n");
			instance.fileWriter.format("entry:\n");
			instance.fileWriter.format("  %%i.addr = alloca i32, align 4\n");
			instance.fileWriter.format("  store i32 %%i, i32* %%i.addr, align 4\n");
			instance.fileWriter.format("  %%0 = load i32, i32* %%i.addr, align 4\n");
			instance.fileWriter.format("  %%call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %%0)\n");
			instance.fileWriter.format("  ret void\n");
			instance.fileWriter.format("}\n");
			instance.fileWriter.format("\n");
			instance.fileWriter.format(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
			instance.fileWriter.format(";                            ;\n");
			instance.fileWriter.format("; STDANDRD LIBRARY :: printf ;\n");
			instance.fileWriter.format(";                            ;\n");
			instance.fileWriter.format(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
			//instance.fileWriter.format("@.str = private unnamed_addr constant [4 x i8] c\"%d \00\", align 1\n");
			instance.fileWriter.format("@.str = private unnamed_addr constant [4 x i8] c\"%%d \\00\", align 1\n");
			instance.fileWriter.format("declare dso_local i32 @printf(i8*, ...)\n\n");
		}
		return instance;
	}
}
