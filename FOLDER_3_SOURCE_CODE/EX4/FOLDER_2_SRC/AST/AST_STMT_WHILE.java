package AST;

import TEMP.*;
import IR.*;
import MIPS.*;

public class AST_STMT_WHILE extends AST_STMT
{
	public AST_EXP cond;
	public AST_STMT_LIST body;

	/*******************/
	/*  CONSTRUCTOR(S) */
	/*******************/
	public AST_STMT_WHILE(AST_EXP cond,AST_STMT_LIST body)
	{
		this.cond = cond;
		this.body = body;
	}
	public TEMP IRme()
	{
		/*******************************/
		/* [1] Allocate 2 fresh labels */
		/*******************************/
		String label_loop_exit   = IRcommand.getFreshLabel("while.end");
		String label_loop_header = IRcommand.getFreshLabel("while.cond");
	
		/*********************************/
		/* [2] entry label for the while */
		/*********************************/
		IR.getInstance().Add_IRcommand(
			new IRcommand_Jump_Label(
				label_loop_header));
		IR.getInstance().Add_IRcommand(
			new IRcommand_Label(
				label_loop_header));

		/********************/
		/* [3] cond.IRme(); */
		/********************/
		TEMP cond_temp = cond.IRme();

		/******************************************/
		/* [4] Jump conditionally to the loop end */
		/******************************************/
		IR.getInstance().Add_IRcommand(
			new IRcommand_Jump_If_Eq_To_Zero(
				cond_temp,
				label_loop_exit));		

		/*******************/
		/* [5] body.IRme() */
		/*******************/
		body.IRme();

		/******************************/
		/* [6] Jump to the loop entry */
		/******************************/
		IR.getInstance().Add_IRcommand(
			new IRcommand_Jump_Label(
				label_loop_header));		

		/**********************/
		/* [7] Loop end label */
		/**********************/
		IR.getInstance().Add_IRcommand(
			new IRcommand_Label(label_loop_exit));

		/*******************/
		/* [8] return null */
		/*******************/
		return null;
	}
}
