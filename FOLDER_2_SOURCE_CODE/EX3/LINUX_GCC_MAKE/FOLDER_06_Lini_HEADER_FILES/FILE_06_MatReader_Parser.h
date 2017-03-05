typedef union
{
	union
	{
		int			ival;
		float		fval;
		string		sval;
		AST_Mat		Mat;
		AST_RowVec	RowVec;
		Fraction	Number;
	}
	gval;
} YYSTYPE;
#define	INT	258
#define	SEMICOLON	259
#define	LBRACK	260
#define	RBRACK	261
#define	MINUS	262
#define	DIVIDE	263


extern YYSTYPE aalval;
