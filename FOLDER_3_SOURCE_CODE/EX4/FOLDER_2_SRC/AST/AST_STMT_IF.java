package AST;

import TYPES.*;
import SYMBOL_TABLE.*;
import TEMP.*;
import IR.*;
import MIPS.*;

public class AST_STMT_IF extends AST_STMT
{
	public AST_EXP cond;
	public AST_STMT_LIST body;

	/*******************/
	/*  CONSTRUCTOR(S) */
	/*******************/
	public AST_STMT_IF(AST_EXP cond,AST_STMT_LIST body)
	{
		/******************************/
		/* SET A UNIQUE SERIAL NUMBER */
		/******************************/
		SerialNumber = AST_Node_Serial_Number.getFresh();

		this.cond = cond;
		this.body = body;
	}

	/*************************************************/
	/* The printing message for a binop exp AST node */
	/*************************************************/
	public void PrintMe()
	{
		/*************************************/
		/* AST NODE TYPE = AST SUBSCRIPT VAR */
		/*************************************/
		System.out.print("AST NODE STMT IF\n");

		/**************************************/
		/* RECURSIVELY PRINT left + right ... */
		/**************************************/
		if (cond != null) cond.PrintMe();
		if (body != null) body.PrintMe();

		/***************************************/
		/* PRINT Node to AST GRAPHVIZ DOT file */
		/***************************************/
		AST_GRAPHVIZ.getInstance().logNode(
			SerialNumber,
			"IF (left)\nTHEN right");
		
		/****************************************/
		/* PRINT Edges to AST GRAPHVIZ DOT file */
		/****************************************/
		if (cond != null) AST_GRAPHVIZ.getInstance().logEdge(SerialNumber,cond.SerialNumber);
		if (body != null) AST_GRAPHVIZ.getInstance().logEdge(SerialNumber,body.SerialNumber);
	}

	public TYPE SemantMe()
	{
		/****************************/
		/* [0] Semant the Condition */
		/****************************/
		if (cond.SemantMe() != TYPE_INT.getInstance())
		{
			System.out.format(">> ERROR [%d:%d] condition inside IF is not integral\n",2,2);
		}
		
		/*************************/
		/* [1] Begin Class Scope */
		/*************************/
		SYMBOL_TABLE.getInstance().beginScope();

		/***************************/
		/* [2] Semant Data Members */
		/***************************/
		body.SemantMe();

		/*****************/
		/* [3] End Scope */
		/*****************/
		SYMBOL_TABLE.getInstance().endScope();

		/*********************************************************/
		/* [4] Return value is irrelevant for class declarations */
		/*********************************************************/
		return null;		
	}	

	public TEMP IRme()
	{
		/*******************************/
		/* [1] Allocate 2 fresh labels */
		/*******************************/
		String label_if_cond = IRcommand.getFreshLabel("if.cond");
		String label_if_body = IRcommand.getFreshLabel("if.body");
		String label_if_exit = IRcommand.getFreshLabel("if.exit");
	
		/*********************************/
		/* [2] entry label for the while */
		/*********************************/
		IR.getInstance().Add_IRcommand(
			new IRcommand_Jump_Label(
				label_if_cond));
		IR.getInstance().Add_IRcommand(
			new IRcommand_Label(
				label_if_cond));

		/********************/
		/* [3] cond.IRme(); */
		/********************/
		TEMP cond_temp = cond.IRme();

		/************************************/
		/* [4] Jump conditionally to if end */
		/************************************/
		IR.getInstance().Add_IRcommand(
			new IRcommand_Jump_If_Eq_To_Zero(
				cond_temp,
				label_if_exit,
				label_if_body));

		/*******************/
		/* [5] body.IRme() */
		/*******************/
		body.IRme();

		/***************************/
		/* [6] Jump to the if exit */
		/***************************/
		IR.getInstance().Add_IRcommand(
			new IRcommand_Jump_Label(
				label_if_exit));		

		/**********************/
		/* [7] Loop end label */
		/**********************/
		IR.getInstance().Add_IRcommand(
			new IRcommand_Label(label_if_exit));

		/*******************/
		/* [8] return null */
		/*******************/
		return null;
	}
}
