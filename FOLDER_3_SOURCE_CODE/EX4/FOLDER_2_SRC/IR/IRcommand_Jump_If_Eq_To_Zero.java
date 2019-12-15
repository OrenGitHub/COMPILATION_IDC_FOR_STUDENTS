/***********/
/* PACKAGE */
/***********/
package IR;

/*******************/
/* GENERAL IMPORTS */
/*******************/

/*******************/
/* PROJECT IMPORTS */
/*******************/
import TEMP.*;
import LLVM.*;
import MIPS.*;

public class IRcommand_Jump_If_Eq_To_Zero extends IRcommand
{
	TEMP t;
	String label1;
	String label2;
	
	public IRcommand_Jump_If_Eq_To_Zero(TEMP t, String label1, String label2)
	{
		this.t      = t;
		this.label1 = label1;
		this.label2 = label2;
	}

	/*******************/
	/* LLVM bitcode me */
	/*******************/
	public void LLVM_bitcode_me()
	{
		LLVM.getInstance().beqz(t,label1,label2);
	}
	
	/***************/
	/* MIPS me !!! */
	/***************/
	public void MIPSme()
	{
		sir_MIPS_a_lot.getInstance().beqz(t,label1);
	}
}
