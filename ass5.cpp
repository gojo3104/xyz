#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<cstdio>
#include<math.h>
float xd1,yd1,xd2,yd2;
int ymax=100; 
int ymin=-100;
int xmax=100;
int xmin=-100;
static int p=0;
void disp(); 
float round_value(float v) 
{
return (v+0.5);
}
void plotpoint(float a,float b)
{
glBegin(GL_POINTS);
glVertex2f(a,b);
glEnd();
}
void dda(float X1,float Y1,float X2,float Y2) 
{
float dx,dy,x,y,xinc,yinc;
int k,steps;
dx=X2-X1; 
dy=Y2-Y1; 
steps=abs(dx)>abs(dy)?abs(dx):abs(dy);
xinc=dx/(float)steps;
yinc=dy/(float)steps; 
x=X1,y=Y1;
plotpoint(x,y); 
for(k=0;k<steps;k++) 
{
x+=xinc; 
y+=yinc; 
plotpoint(round_value(x),round_value(y)); 
}
glFlush();
}
int code(int x,int y)
{
int c=0; 
if(y<ymin) c=4; 
if(x>xmax) c=c|2; 
if(x<xmin) c=c|1; 
return c;
}
void cohen(float x1,float y1,float x2,float y2) 
{
int c1=code(x1,y1); 
int c2=code(x2,y2); 
float m=(y2-y1)/(x2-x1);
while((c1|c2)>0) 
{
if((c1 & c2)>0) 
{
disp();
return;
}
int c;
float xi=x1;
float yi=y1;
c=c1;
float x,y;
if(c==0)
{
c=c2; 
xi=x2; 
yi=y2; 
}
if((c & 8)>0)
{
y=ymax; 
x=xi+1.0/(m*(ymax-yi));
}
if((c & 4)>0)
{
y=ymin; 
x=xi+1.0/(m*(ymin-yi));
}
if((c & 2)>0) 
{
x=xmax;
y=yi+m*(xmax-xi);
}
if((c & 1)>0) 
{
x=xmin;
y=yi+m*(xmin-xi);
}
if(c==c1) 
{
xd1=x;
yd1=y;
c1=code(xd1,yd1);
}
if(c==c2) 
{
xd2=x;
yd2=y;
c2=code(xd2,yd2);
}
}
p++;
disp(); 
}
void mykey(unsigned char ch,int x,int y)
{
if(ch=='c')
{
cohen(xd1,yd1,xd2,yd2);
glFlush();
}
}
void disp()
{
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0,0.0,0.0); 
dda(xmin,ymin,xmax,ymin);
dda(xmax,ymin,xmax,ymax);
dda(xmax,ymax,xmin,ymax);
dda(xmin,ymax,xmin,ymin);
glColor3f(0.0,0.0,1.0);
dda(xd1,yd1,xd2,yd2); 
glFlush();
}
void init()
{
glClearColor(1.0,1.0,1.0,0); 
glClear(GL_COLOR_BUFFER_BIT);
glPointSize(2); 
gluOrtho2D(-320,320,-240,240);
glFlush();
}
int main(int argc,char **argv)
{
printf("Window coordinates are (-100,100,-100,100)\n");
printf("\nEnter coordinates of the line(limits : -320,320,-240,240) \nAfter entering enter c to clip\n");
printf("\nCoordinates of first point");
printf("\nX1: ");
scanf("%f",&xd1); 
printf("\nY1: "); 
scanf("%f",&yd1);
printf("\nCoordinates of second point");
printf("\nX2: ");
scanf("%f",&xd2); 
printf("\nY2: "); 
scanf("%f",&yd2);
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowPosition(100,100);
glutInitWindowSize(640,480);
glutCreateWindow("Name-rohit");
init();
glutDisplayFunc(disp);
glutKeyboardFunc(mykey);
glutMainLoop();
return 0;
}

