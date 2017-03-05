typedef union
{
	union
	{
		int							row;
		int							op;
		int							ival;
		float						fval;
		string						sval;
		Fraction					Number;
		AST_RowOp					RowOp;
		AST_RowOpList				RowOpList;
		AST_Ri_Swap_Rj				Ri_Swap_Rj;
		AST_Ri_Equals_cRi			Ri_Equals_cRi;
		AST_Ri_Equals_Ri_Plus_cRj	Ri_Equals_Ri_Plus_cRj;
	}
	gval;
} YYSTYPE;
#define	INT	258
#define	FLOAT	259
#define	STRING	260
#define	LPAREN	261
#define	RPAREN	262
#define	LBRACK	263
#define	RBRACK	264
#define	L_ARROW	265
#define	PLUS	266
#define	MINUS	267
#define	TIMES	268
#define	DIVIDE	269
#define	LR_ARROW	270
#define	ROW	271


extern YYSTYPE bblval;
