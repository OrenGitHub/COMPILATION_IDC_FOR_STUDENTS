package AST;

import TYPES.*;
import SYMBOL_TABLE.*;

public class AST_DEC_FUNC extends AST_DEC
{
	/****************/
	/* DATA MEMBERS */
	/****************/
	public String returnTypeName;
	public String name;
	public AST_TYPE_NAME_LIST params;
	public AST_STMT_LIST body;
	
	/******************/
	/* CONSTRUCTOR(S) */
	/******************/
	public AST_DEC_FUNC(
		String returnTypeName,
		String name,
		AST_TYPE_NAME_LIST params,
		AST_STMT_LIST body)
	{
		/******************************/
		/* SET A UNIQUE SERIAL NUMBER */
		/******************************/
		SerialNumber = AST_Node_Serial_Number.getFresh();

		this.returnTypeName = returnTypeName;
		this.name = name;
		this.params = params;
		this.body = body;
	}

	/************************************************************/
	/* The printing message for a function declaration AST node */
	/************************************************************/
	public void PrintMe()
	{
		/*************************************************/
		/* AST NODE TYPE = AST NODE FUNCTION DECLARATION */
		/*************************************************/
		System.out.format("FUNC(%s):%s\n",name,returnTypeName);

		/***************************************/
		/* RECURSIVELY PRINT params + body ... */
		/***************************************/
		if (params != null) params.PrintMe();
		if (body   != null) body.PrintMe();
		
		/***************************************/
		/* PRINT Node to AST GRAPHVIZ DOT file */
		/***************************************/
		AST_GRAPHVIZ.getInstance().logNode(
			SerialNumber,
			String.format("FUNC(%s)\n:%s\n",name,returnTypeName));
		
		/****************************************/
		/* PRINT Edges to AST GRAPHVIZ DOT file */
		/****************************************/
		if (params != null) AST_GRAPHVIZ.getInstance().logEdge(SerialNumber,params.SerialNumber);		
		if (body   != null) AST_GRAPHVIZ.getInstance().logEdge(SerialNumber,body.SerialNumber);		
	}

	public TYPE SemantMe()
	{
		TYPE t;
		TYPE returnType = null;
		TYPE_LIST type_list = null;

		/*******************/
		/* [0] return type */
		/*******************/
		returnType = SYMBOL_TABLE.getInstance().find(returnTypeName);
		if (returnType == null)
		{
			System.out.format(">> ERROR [%d:%d] non existing return type %s\n",6,6,returnType);				
		}
	
		/****************************/
		/* [1] Begin Function Scope */
		/****************************/
		SYMBOL_TABLE.getInstance().beginScope();

		/***************************/
		/* [2] Semant Input Params */
		/***************************/
		for (AST_TYPE_NAME_LIST it = params; it  != null; it = it.tail)
		{
			t = SYMBOL_TABLE.getInstance().find(it.head.type);
			if (t == null)
			{
				System.out.format(">> ERROR [%d:%d] non existing type %s\n",2,2,it.head.type);				
			}
			else
			{
				type_list = new TYPE_LIST(t,type_list);
				SYMBOL_TABLE.getInstance().enter(it.head.name,t);
			}
		}

		/*******************/
		/* [3] Semant Body */
		/*******************/
		body.SemantMe();

		/*****************/
		/* [4] End Scope */
		/*****************/
		SYMBOL_TABLE.getInstance().endScope();

		/***************************************************/
		/* [5] Enter the Function Type to the Symbol Table */
		/***************************************************/
		SYMBOL_TABLE.getInstance().enter(name,new TYPE_FUNCTION(returnType,name,type_list));

		/*********************************************************/
		/* [6] Return value is irrelevant for class declarations */
		/*********************************************************/
		return null;		
	}
	
}
