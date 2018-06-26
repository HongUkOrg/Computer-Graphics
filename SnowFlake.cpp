#include <GL/glut.h>
#include <iostream>
#include <ctime>
#include <cmath>

const double PIE = 3.14159;
const double K = 8.5;
int n;							
int snow_height = 0;
using namespace std;

class object
{

	double x;
	double y;
	double velo;
	double rad;
	BOOLEAN end;
	double bot_x;
	double bot_rad;
	double x_offset;
	double y_offset;
	int remain_count;
	int color;



public:

	object::object()
	{
		x = 0;
		y = 50;
		velo = 0;
		end = false;
		x_offset = 0;
		remain_count=0;
		color = rand() % 2;

	};
	object::object(int new_x, int new_y, double new_velo)

	{
		x = new_x;
		y = new_y;
		velo = new_velo;

	};
	void set_x(double new_x) { x = new_x; }
	void set_y(double new_y) { y = new_y; }
	void set_velo(double new_velo) { velo = new_velo; }
	void set_end(BOOLEAN a) { end = a; }
	void set_bot_x(double x) { bot_x = x; }
	void set_bot_rad(double radius) { bot_rad = radius; }
	void set_x_offset(double off) { x_offset = off; }
	void set_remain_count(int a) { remain_count = a; }
	void set_remain_count_plus(int a) { remain_count += a; }
	void initializing(double x_pos, double radius, double velocity,int new_color)
	{
		x = x_pos;
		rad = radius;
		velo = velocity;
		color = new_color;
	}

	int get_remain_count()
	{
		return remain_count;
	}

	double get_y()
	{
		return y;
	}
	double get_x()
	{
		return x;
	}
	double get_velo()
	{
		return velo;
	}
	double get_radius()
	{
		return rad;
	}
	BOOLEAN get_end()
	{
		return end;
	}
	double get_bot_x()
	{
		return bot_x;
	}
	double get_bot_rad()
	{
		return bot_rad;
	}
	double get_x_offset()
	{

		return x_offset;
	}
	int get_color()
	{
		return color;
	}
};

double velo_percent = 0.01;
double temp_velo_percent;
BOOLEAN stop = false;
double x_offset = 0;
double y_offset = 0;


object* obj;

void init2(void)
{
	
	glClearColor(0, 0, 0, 1.0);
	glColor3f(1, 1, 1);
	n = 30;
	obj = new object[n];

	for (int i = 0; i < n; i++)
	{
		double x_pos = rand() % 100 - 50;			
		double radius = (rand() % 100)*0.02 + 1;
		double velo = 9.8 - K / ((radius)*(radius));	
		int new_color = rand() % 2;
		obj[i].initializing(x_pos, radius, velo,new_color);
	}


}



void reshape(int w, int h)
{
	glViewport(0, 0, w, h);       
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();             

								   
	if (w <= h)                    
		gluOrtho2D(-50.0, 50.0,
			-50.0*(GLfloat)h / (GLfloat)w, 50.0*(GLfloat)h / (GLfloat)w);
	else
		gluOrtho2D(-50.0*(GLfloat)w / (GLfloat)h,
			50.0*(GLfloat)w / (GLfloat)h, -50.0, 50.0);

	glMatrixMode(GL_MODELVIEW);    
	glLoadIdentity();              
}


void drawBox(double new_x, double new_y, double radius, BOOLEAN end, int number)
{
	double rad = radius;
	
	if (obj[number].get_color() == 1)
	{
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		for (int i = 1; i < 360; i++)
		{

			double angle = (double)i*PIE / (180.0);

			double x = new_x + rad*cos(angle) + x_offset*(3 / radius);

			double y = new_y + rad*sin(angle) - y_offset*(3 / radius);

			glVertex2f(x, y);

		}
		glEnd();
	}
	else
	{
		double rotate = 0;
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 0);
		double pro = 1.0;
		if (!stop)
		{
			rotate = rand() % 6 * 60;
		}
		for (int i = 0; i < 10; i++)
		{
			
			if (i % 2 == 0)
			{
				pro = 0.5;
			}
			else
			{
				pro = 1.0;
			}
			double angle = rotate +(double)i*PIE*(36.0) / (180.0);

			double x = new_x + pro*rad*cos(angle) + x_offset*(3 / radius);

			double y = new_y + pro*rad*sin(angle) - y_offset*(3 / radius);

			glVertex2f(x, y);

		}
		glEnd();

	}

	
	
	glBegin(GL_POLYGON);
	
	glColor3f(1, 1, 0.8);
	

	glVertex2f(-50, -50);
	glVertex2f(+50, -50);
	glVertex2f(+50, -50 + snow_height*0.1);
	glVertex2f(-50, -50 + snow_height*0.1);


	glEnd();

	if (obj[number].get_end()==TRUE)

	{

		if ((new_y < -49.0 + snow_height*0.1) && (new_y>-50.0 + snow_height*0.1))
		{
			obj[number].set_bot_x(new_x + x_offset*(3/radius));
			obj[number].set_bot_rad(radius);
		}
		glBegin(GL_POLYGON);
		
		
		glColor3f(1, 1, 0.8);
	
		if (obj[number].get_remain_count() < 300)
		{
			for (int l = 1; l < 180; l++)
			{

				double angle2 = (double)l*PIE / (180.0);

				double x2 = obj[number].get_bot_x() + obj[number].get_bot_rad()*cos(angle2);

				double y2 = -51 + obj[number].get_bot_rad()*sin(angle2) + snow_height*0.1;


				glVertex2f(x2, y2);
			}
		}
		else
		{
			
			obj[number].set_end(FALSE);
			obj[number].set_remain_count(0);

		}
		if (!stop)
		{
			obj[number].set_remain_count_plus(1);
		}



		glEnd();



	}

	glFlush();
}



void display2(void)
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	

	for (int i = 0; i < n; i++)
	{
		drawBox(obj[i].get_x(), obj[i].get_y(), obj[i].get_radius(), obj[i].get_end(), i);



		obj[i].set_y(obj[i].get_y() - obj[i].get_velo()*velo_percent);


		if ((obj[i].get_y() > (-(50.0)) + snow_height*0.1) && (obj[i].get_y() < ((-(49.0)) + snow_height*0.1) ))
		{
			obj[i].set_end(TRUE);

		}

		if (obj[i].get_y() <= -(50.0)+snow_height*0.1)
		{
			obj[i].set_y(50);

			double x_pos = rand() % 100 - 50;

			double radius = (rand() % 100)*0.02 + 1;
			double velo = 9.8 - K / ((radius)*(radius));
			snow_height++;
			int new_color = rand() % 2;
			
			obj[i].initializing(x_pos - x_offset*(3 / radius), radius, velo,new_color);
		}
	}



	glutSwapBuffers();


}
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case ' ':    /* Call display function */
		stop = !stop;
		if (stop)
		{
			temp_velo_percent = velo_percent;
			velo_percent = 0.0;
		}
		else
			velo_percent = temp_velo_percent;
		break;
	case 'a':
		x_offset -= 0.5;
		break;
	case 'd':
		x_offset += 0.5;
		break;
	case 'w':
		
		if (velo_percent > 0.1)
		{
			cout << "max speed" << endl;
			break;
		}
		else
		{
			velo_percent += 0.01;

		}
		break;
	case 's':
		
		if(velo_percent < 0.01)
		{
			cout << "min speed"<<endl;
			break;
		}
		else
		{
			velo_percent -= 0.01;
		}
		break;
	
	case 27: 
		exit(0);
		break;
	default:
		break;
	}
}


void idle()
{
	glutPostRedisplay();
}





GLfloat v[4][3] = { { 0.0, 0.0, 1.0 },		
{ 0.0, 0.942809, -0.33333 },										
{ -0.816497, -0.471405, -0.333333 },	
{ 0.816497, -0.471405, -0.333333 } };	

										

void triangle(GLfloat *a, GLfloat *b, GLfloat *c)

{
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
}


void divide_triangle(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int m)
{

	GLfloat v1[3], v2[3], v3[3], v4[3], v5[3], v6[3];
	int t;
	if (m>0)
	{
		for (t = 0; t<3; t++) v1[t] = (a[t] + b[t]) / 2;
		for (t = 0; t<3; t++) v2[t] = (a[t] + d[t]) / 2;
		for (t = 0; t<3; t++) v3[t] = (a[t] + c[t]) / 2;
		for (t = 0; t<3; t++) v4[t] = (b[t] + c[t]) / 2;
		for (t = 0; t<3; t++) v5[t] = (b[t] + d[t]) / 2;
		for (t = 0; t<3; t++) v6[t] = (c[t] + d[t]) / 2;
		divide_triangle(a, v1, v3, v2, m - 1);
		divide_triangle(v3, v4, c, v6, m - 1);
		divide_triangle(v2, v5, v6, d, m - 1);
		divide_triangle(v1, b, v4, v5, m - 1);
	}
	else(triangle(b, c, d));
}




void tetrahedron(int m)
{
	

	glColor3f(1.0, 0.0, 0.0);	
	divide_triangle(v[3], v[0], v[1], v[2], m);
	glColor3f(0.0, 1.0, 0.0); 
	divide_triangle(v[2], v[0], v[3], v[1], m);
	glColor3f(0.0, 0.0, 1.0);
	divide_triangle(v[1], v[0], v[2], v[3], m);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
	glLoadIdentity();
	glBegin(GL_TRIANGLES);
	tetrahedron(n);
	glEnd();
	glFlush();
}

void init()
{
	glEnable(GL_DEPTH_TEST);   
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
			2.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-2.0 * (GLfloat)w / (GLfloat)h,
			2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y)
{
	
	if (key == 27)
		exit(0);
}


int main(int argc, char **argv)
{
	int num;
	cout << "과제를 선택하세요 1 or 2 ";
	cin >> num;
	if (num == 1)
	{
		
		cout << "Recursion(0~10): ";
		cin >> n;
		if (n < -1 || n > 10)
		{
			cout << "Error!" << endl;
			exit(0);
		}
		glutInit(&argc, argv);                        
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); 
		glutInitWindowSize(500, 500);                 
		glutCreateWindow("Volume division in 3D Gasket");
		glutReshapeFunc(myReshape);
		glutDisplayFunc(display);
		glutKeyboardFunc(myKeyboard);

		init();  

		glutMainLoop();

	}
	else if (num==2)
	{
		glutInit(&argc, argv);   // not necessary unless on Unix
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
		glutInitWindowSize(512, 512);
		glutCreateWindow(argv[0]);
		init2();

		glutReshapeFunc(reshape);       // register respace (anytime window changes)
		glutKeyboardFunc(keyboard);     // register keyboard (anytime keypressed)                                        
		glutDisplayFunc(display2);       // register display function
		glutIdleFunc(idle);             // reister idle function
		glutMainLoop();
		return 0;

	}
	else

	{
		cout << "오류";
	}
	
}
