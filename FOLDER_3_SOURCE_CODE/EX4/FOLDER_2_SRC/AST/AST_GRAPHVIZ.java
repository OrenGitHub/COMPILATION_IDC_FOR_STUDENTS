package AST;

import java.io.*;
import java.io.PrintWriter;

public class AST_GRAPHVIZ
{
	/***********************/
	/* The file writer ... */
	/***********************/
	private PrintWriter fileWriter;
	
	/**************************************/
	/* USUAL SINGLETON IMPLEMENTATION ... */
	/**************************************/
	private static AST_GRAPHVIZ instance = null;

	/*****************************/
	/* PREVENT INSTANTIATION ... */
	/*****************************/
	private AST_GRAPHVIZ() {}

	/******************************/
	/* GET SINGLETON INSTANCE ... */
	/******************************/
	public static AST_GRAPHVIZ getInstance()
	{
		if (instance == null)
		{
			instance = new AST_GRAPHVIZ();
			
			/****************************/
			/* Initialize a file writer */
			/****************************/
			try
			{
				String dirname="./FOLDER_5_OUTPUT/";
				String filename="AST_IN_GRAPHVIZ_DOT_FORMAT.txt";
				instance.fileWriter = new PrintWriter(dirname+filename);
			}
			catch (Exception e)
			{
				e.printStackTrace();
			}

			/******************************************************/
			/* Print Directed Graph header in Graphviz dot format */
			/******************************************************/
			instance.fileWriter.print("digraph\n");
			instance.fileWriter.print("{\n");
			instance.fileWriter.print("graph [ordering = \"out\"]\n");
		}
		return instance;
	}

	/***********************************/
	/* Log node in graphviz dot format */
	/***********************************/
	public void logNode(int nodeSerialNumber,String nodeName)
	{
		fileWriter.format(
			"v%d [label = \"%s\"];\n",
			nodeSerialNumber,
			nodeName);
	}

	/***********************************/
	/* Log edge in graphviz dot format */
	/***********************************/
	public void logEdge(
		int fatherNodeSerialNumber,
		int sonNodeSerialNumber)
	{
		fileWriter.format(
			"v%d -> v%d;\n",
			fatherNodeSerialNumber,
			sonNodeSerialNumber);
	}
	
	/******************************/
	/* Finalize graphviz dot file */
	/******************************/
	public void finalizeFile()
	{
		fileWriter.print("}\n");
		fileWriter.close();
	}
}
