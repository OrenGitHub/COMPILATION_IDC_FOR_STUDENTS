typedef union
{
	union
	{
		int			ival;
		float		fval;
		string		sval;
	}
	gval;
} YYSTYPE;
#define	INT	258
#define	LPAREN	259
#define	RPAREN	260
#define	LBRACE	261
#define	RBRACE	262
#define	COMMA	263
#define	DIVIDE	264


extern YYSTYPE cclval;
