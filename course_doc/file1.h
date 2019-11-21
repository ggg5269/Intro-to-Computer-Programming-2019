int Add(int a,int b)
{ return (a+b);
}
int Sub(int a,int b)
{ return (a-b);
}
int Mul(int a,int b)
{ return (a*b);
}
int Div(int a,int b)
{ return (a/b);
}
double sin1(double c)
{
	double c1=c*3.14159/180;  //轉弧度
	// sin 泰勒展開
	double c2=c1-(c1*c1*c1/6)+(c1*c1*c1*c1*c1/120);
		return c2;
}

double cos1(double c)
{
	double c1=c*3.14159/180;  //轉弧度
	// cos 泰勒展開
	double c2=1-c1*c1/2-(c1*c1*c1*c1/24)+(c1*c1*c1*c1*c1*c1/720);
		return c2;
}