

#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

int m_right_c = 0;
int m_left_c = 0;
int up_c = 0;
int down_c = 0;
double a = 30;
double d_x, d_y, d_z;
bool sky = false;
bool select = false;
double mouseX, mouseZ;
double winW, winH;
bool view_3 = false;
bool sky_select = false;;

double c_x = 0.001, c_y = 0, c_z = 10;
double l_x = 0, l_y = 0, l_z = 0;


double length = 0;
double d_u_x, d_u_y, d_u_z;
int sel_ob = 0;
double b = 0;
double n = 0;
double a2 = 0;
double b2 = 0;
double m = 0;
int light = 1;

class Object
{
public:
	double x;
	double y;
	double z;


	Object::Object()
	{
		x = 0;
		y = 0;
		z = 0;

	};
	void move_r()
	{
		x++;

	}
	void move_l()
	{

		x--;
	}
	void move_b()
	{

		z++;
	}
	void move_f()
	{

		z--;
	}

};

list<Object> obj_list;
list<Object>::iterator temp;

void cal_d()
{

	d_x = l_x - c_x;
	d_y = l_y - c_y;
	d_z = l_z - c_z;
	length = sqrt(pow(abs(d_x), 2) + pow(abs(d_z), 2));

	d_u_x = d_x / length /2;
	d_u_y = d_y / length/2;
	d_u_z = d_z / length/2;

}

void move_w()
{
	for (temp = obj_list.begin(); temp != obj_list.end(); temp++)
	{
		if (sqrt(pow(abs(c_x + d_u_x - temp->x),2) + pow(abs( c_z + d_u_z - temp->z),2))<1)
		{
			return;

		}

	}
	c_x += d_u_x;
	l_x += d_u_x;

	c_z += d_u_z;
	l_z += d_u_z;

}

void move_s()
{
	for (temp = obj_list.begin(); temp != obj_list.end(); temp++)
	{
		if (sqrt(pow(abs(c_x - d_u_x - temp->x), 2) + pow(abs(c_z  - d_u_z - temp->z), 2))<1)
		{
			return;

		}

	}
	c_x -= d_u_x;
	l_x -= d_u_x;

	c_z -= d_u_z;
	l_z -= d_u_z;

}

void move_d()
{
	for (temp = obj_list.begin(); temp != obj_list.end(); temp++)
	{
		if (sqrt(pow(abs(c_x - d_u_z - temp->x), 2) + pow(abs(c_z + d_u_x - temp->z), 2))<1)
		{
			return;

		}

	}
	c_x -= d_u_z;
	l_x -= d_u_z;

	c_z += d_u_x;
	l_z += d_u_x;

}

void move_a()
{
	for (temp = obj_list.begin(); temp != obj_list.end(); temp++)
	{
		if (sqrt(pow(abs(c_x + d_u_z - temp->x), 2) + pow(abs(c_z - d_u_x - temp->z), 2))<1)
		{
			return;

		}

	}
	c_x += d_u_z;
	l_x += d_u_z;

	c_z -= d_u_x;
	l_z -= d_u_x;

}
void rot_j()
{
	l_x = cos(a)*d_u_x - sin(a)*d_u_z;
	l_z = sin(a)*d_u_x + cos(a)*d_u_z;



}



typedef struct
{
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;

} material;

int toggle = 1;

/* advance C to initialize structs -- awesome, huh? */
material PolishedGold = { { 0.24725, 0.2245, 0.0645, 1.0 },
{ 0.34615, 0.3143, 0.0903, 1.0 },
{ 0.797357, 0.723991, 0.208006, 1.0 },
83.2 };

material Pearl = { { 0.25, 0.20725, 0.20725, 0.922 },
{ 1.0, 0.829, 0.829, 0.922 },
{ 0.296648, 0.296648, 0.296648, 0.922 },
11.264 };
material Red = { { 1.0, 0, 0, 1.00 },{ 0.34615, 0.3143, 0.0903, 1.0 },
{ 0.797357, 0.723991, 0.208006, 1.0 },				93.2 };
material Yellow = { { 0.25, 0.80725, 0.80725, 0.922 },
{ 1.0, 0.829, 0.829, 0.922 },
{ 0.296648, 0.296648, 0.296648, 0.922 },
11.264 };
material Blue = { { 0.025, 0.00725, 0.50725, 0.922 },
{ 1.0, 0.829, 0.829, 0.922 },
{ 0.296648, 0.296648, 0.296648, 0.922 },
11.264 };
material Green = { { 0.125, 0.80725, 0.00725, 0.222 },
{ 1.0, 0.829, 0.829, 0.922 },
{ 0.296648, 0.296648, 0.296648, 0.922 },
11.264 };
material earth = { { 0.125, 0.80725, 0.11725, 0 },
{ 0.1, 0.129, 0.129, 0.122 },
{ 0.296648, 0.296648, 0.296648, 0.922 },
0 };
material ran = { { 0.525, 0.50725, 0.51725, 0.111 },
{ 1.0, 0.829, 0.829, 0.922 },
{ 0.296648, 0.296648, 0.296648, 0.922 },
11.264 };
material av = { { 0.1, 0.5, 0.5, 0.111 },
{ 1.0, 0.829, 0.829, 0.922 },
{ 0.296648, 0.296648, 0.296648, 0.922 },
11.264 };
material Brwon = { { 0.6, 0.45, 0.12, 0.51 },
{ 1.0, 0.829, 0.829, 0.922 },
{ 0.296648, 0.296648, 0.296648, 0.922 },
11.264 };

material sel = { { 0, 0, 0, 0.111 },
{ 0.5, 0.529, 0.529, 0.522 },
{ 0.296648, 0.296648, 0.296648, 0.922 },
11.264 };

void init(void)
{
	/* 100% white light */
	GLfloat light_ambient[] = { 0,0,0, 1.0 };
	GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_specular[] = { 0.5, 0.5, 0.5,1.0 };

	GLfloat light_ambient1[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_diffuse1[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_specular1[] = { 0.5, 0.5, 0.5,1.0 };

	GLfloat light_ambient2[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_diffuse2[] = { 1, 1, 1, 1.0 };
	GLfloat light_specular2[] = { 0.8, 0.8, 0.8,1.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular2);



	glClearColor(0.5, 0.8, 0.9, 1.0);
	glShadeModel(GL_SMOOTH);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);


	Object a0;
	a0.x = 2;
	a0.y = 0;
	a0.z = 3;
	obj_list.push_back(a0);

	Object a1;
	a1.x = -4;
	a1.y = 0.5;
	a1.z = -4;
	obj_list.push_back(a1);

	Object a2;
	a2.x = -6;
	a2.y = -0.6;
	a2.z = 0;
	obj_list.push_back(a2);

	Object a3;
	a3.x = 1;
	a3.y = 1;
	a3.z = -8;
	obj_list.push_back(a3);

	Object a4;
	a4.x = -0.5;
	a4.y = 0;
	a4.z = -3;
	obj_list.push_back(a4);

	Object a5;
	a5.x = -1;
	a5.y = 0;
	a5.z = 0;
	obj_list.push_back(a5);

	Object a6;
	a6.x = 6;
	a6.y = 3;
	a6.z = 0;
	obj_list.push_back(a6);



}
void mousePassiveMotion(int x, int y)
{


	mouseX = (x - winW / 2) / winW * 20;
	mouseZ = (y - winH / 2) / winH * 20;
	

	glutPostRedisplay();
}


void idle()
{
	glutPostRedisplay();
}

void setMaterial(material M)
{
	glMaterialfv(GL_FRONT, GL_SPECULAR, M.specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, M.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, M.diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, M.shininess);
}
void mousePress(GLint button, GLint state, GLint x, GLint y)
{


	if (button == GLUT_LEFT_BUTTON  && state == GLUT_DOWN&&sky_select)
	{
		int k = 0;
		
		for (temp = obj_list.begin(); temp != obj_list.end(); temp++)
		{

			if (abs(mouseX - temp->x) < 0.5&&abs(mouseZ - temp->z) < 0.5)
			{

				if (!select)select = true;
				else select = false;
				sel_ob = k;

			}
			k++;

		}

	}



}

void display()
{
	cal_d();
	static float rot = 0;
	static float rotL = 0;
	static float position[4] = { 0,2,0,1 }; /* point light at (0,2,0) */
	float position2[4] = { a2, 2, 0, light };

	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/* Setup the view of the world */
	glMatrixMode(GL_PROJECTION);           // Switch to projection mode (P)
	glLoadIdentity();                      // P <- I

	gluPerspective(60.0, 1.0, 1.0, 400); // P <- P

	glMatrixMode(GL_MODELVIEW);           // Switch to model view mode  (M)
	glLoadIdentity();                     // M = I




	if (sky)
	{
		gluLookAt(0, 19, 0,   // M = RT(view)
			0, 0, 0,
			0, 1, -1);
	}


	else if (view_3)
	{
		
		gluLookAt(c_x, c_y, c_z + 1.3,   // M = RT(view)
			l_x, l_y, l_z,
			0, 1, 0);


	}

	else
	{
		gluLookAt(c_x, c_y, c_z,   // M = RT(view)
			l_x, l_y, l_z,
			0, 1, 0);
	}


	/* Draw a sphere to represent the light-source */
	// glDisable(GL_LIGHTING);   /* turn off lighting so I can use glColor */
	// if (toggle)
	//	glColor3f(1,1,1);
	//else
	//    glColor3f(0,0,0);

	//	glPushMatrix();
	//  glTranslatef(0,1.5,0);
	// glutSolidSphere(0.1,30,30);
	// glPopMatrix();
	// glEnable(GL_LIGHTING);  /* turn the lighting back on */


	

	//ROTATING LIGHT
	glDisable(GL_LIGHTING);   // turn off lighting so I can use glColor
	
	glColor3f(1, 1, 0);
	glPushMatrix();
	glRotatef(rotL / 2, 0, 1, 0);

	glTranslatef(8, 5, 0);

	glutSolidSphere(0.5, 30, 30);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glPopMatrix();
	glEnable(GL_LIGHTING);  // turn the lighting back on
	

							/* Light rotated */

	glDisable(GL_LIGHTING);   // turn off lighting so I can use glColor
	if (light != 0) {
		glColor3f(0.8, 0.2, 0.5);
		glPushMatrix();
		//glRotatef(rotL / 5, 0, 1, 0);
		glTranslatef(5 + b, 20 + n, 0);
		glutSolidSphere(1, 30, 30);
	}
	glLightfv(GL_LIGHT2, GL_POSITION, position2);
	glPopMatrix();
	glEnable(GL_LIGHTING);


	/* draw teapot one in Gold */


	setMaterial(ran);
	if (select&&sel_ob == 0) setMaterial(sel);

	list<Object>::iterator it;
	it = obj_list.begin();

	glPushMatrix();
	glTranslatef(it->x, 0, it->z);
	//glRotatef(rot, 0, 1, 0);
	glutSolidSphere(0.5, 20, 20);
	glPopMatrix();

	it++;
	setMaterial(Green);
	if (select&&sel_ob == 1) setMaterial(sel);
	glPushMatrix();
	glTranslatef(it->x, it->y, it->z);
	glRotatef(rot, 1, 0, 0);
	glutSolidTorus(0.2, 0.5, 20, 20);
	glPopMatrix();
	it++;

	setMaterial(Red);
	if (select&&sel_ob == 2) setMaterial(sel);
	glPushMatrix();
	glTranslatef(it->x, it->y, it->z);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(1.5, 4, 100, 20);
	glPopMatrix();

	it++;
	setMaterial(Blue);
	if (select&&sel_ob == 3) setMaterial(sel);
	glPushMatrix();
	glTranslatef(it->x, it->y, it->z);
	glRotatef(rot, 0, 1, 0);
	glutSolidOctahedron();
	glPopMatrix();

	it++;
	setMaterial(Yellow);
	if (select&&sel_ob == 4) setMaterial(sel);
	glPushMatrix();
	glTranslatef(it->x, it->y, it->z);
	//glRotatef(rot,0,1,0);
	glutSolidCube(1);
	glPopMatrix();

	it++;
	setMaterial(Pearl);
	if (select&&sel_ob == 5) setMaterial(sel);
	glPushMatrix();
	glTranslatef(it->x, it->y, it->z);
	//glRotatef(rot,0,1,0);
	glutSolidTeapot(0.5);
	glPopMatrix();

	it++;
	setMaterial(Brwon); //tree
	if (select&&sel_ob == 6) setMaterial(sel);
	glPushMatrix();
	glTranslatef(it->x, 0, it->z);
	glScalef(0.5, 3, 0.5);
	//glRotatef(rot,0,1,0);
	glutSolidCube(2);
	glPopMatrix();

	setMaterial(Green);
	if (select&&sel_ob == 6) setMaterial(sel);
	glPushMatrix();
	glTranslatef(it->x, 3, it->z);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(2, 5, 10, 10);
	glPopMatrix();

	/* draw teapot one in Pearl */








	setMaterial(av);

	glPushMatrix();
	glTranslatef(c_x, 0, c_z);
	glRotatef(rot, 0, 1, 0);
	glutSolidTorus(0.1, 0.2, 10, 10);
	glPopMatrix();



	setMaterial(earth);

	glPushMatrix();
	glTranslatef(0, -0.6, 0);
	glRotatef(90, 1, 0, 0);
	glutSolidCone(300, 10, 100, 20);
	glPopMatrix();






	rot = rot + 0.5;
	rotL = rotL + 0.5;

	//  glFlush();


	glutSwapBuffers();
}

// SETUP KEYBOARD -- this program updates the square when the user presses ' '(space))
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:  /*  Escape Key  */
		exit(0);
		break;
	case 'w':  /*  Escape Key  */
		cal_d();
	
		move_w();
		break;
	case 's':  /*  Escape Key  */
		cal_d();
	
		move_s();
		break;

	case 'd':  /*  Escape Key  */
		cal_d();
		
		move_d();
		break;
	case 'a':
		cal_d();

		move_a();
		break;
	case 'j':
		l_x--;
		break;
	case 'f':
		temp = obj_list.begin();
		for (int i = 0; i<sel_ob; i++)
		{
			temp++;
		}
		if (select)temp->move_l();

		break;
	case 't':
		temp = obj_list.begin();
		for (int i = 0; i<sel_ob; i++)
		{
			temp++;
		}
		if (select)temp->move_f();

		break;
	case 'g':
		temp = obj_list.begin();
		for (int i = 0; i<sel_ob; i++)
		{
			temp++;
		}
		if (select)temp->move_b();
		break;
	case 'h':
		temp = obj_list.begin();
		for (int i = 0; i<sel_ob; i++)
		{
			temp++;
		}
		if (select)temp->move_r();
		break;
	case 'l':
		l_x++;
		break;
	case 'i':
		l_y++;
		break;
	case 'k':
		l_y--;;
		break;
	case 'z':
		if (!select)	select = true;
		else select = false;
		break;
	case 'x':
		sel_ob++;
		if (sel_ob > 6) sel_ob = 0;
		break;

	case 'p':
		if (toggle == 1)
		{
			glDisable(GL_LIGHT0);
			toggle = 0;
		}
		else
		{
			glEnable(GL_LIGHT0);
			toggle = 1;
		}
		break;

	case ' ':

		if (sky == false)
			sky = true;
		else sky = false;

		break;
	case 'v':
		if (!view_3) view_3 = true;
		else view_3 = false;
		break;

	case 'c':
		if (!sky_select) sky_select = true;
		else sky_select = false;
		break;

	case 'b':
		b --;
		break;

	case 'n':
		b++;
		break;

	case 'm':
		if(light==1) light =0;
		else light = 1;
		printf("%d", light);
		break;
	case ',':
		a2++;
		break;

	case '.':
		a2--;
		break;



	}

}

void reshape(int w, int h)
{
	winW = w;
	winH = h;
	glViewport(0, 0, winW, winH);
}


int main(int argc, char** argv)
{
	printf("조작법 \n");
	printf("이동 앞(w) 뒤(s) 오른쪽(d) 왼쪽(a) \n");
	printf("카메라 위로(i) 밑으로 (k) 왼쪽 (j) 오른쪽 (l) \n");
	printf("셀렉션 모드 (c) 스카이뷰 에서만 작동 (마우스로 선택) \n");
	printf("물체 선택 후 이동 위(t) 아래 (g) 오른쪽(h) 왼쪽(f) \n");
	printf("light 2 이동 (b) , (n) \n");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	//glutInitWindowSize (500, 500); 
	//glutInitWindowPosition (100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutFullScreen();
	glutReshapeFunc(reshape);       // register respace (anytime window changes)
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutPassiveMotionFunc(mousePassiveMotion); // Passive motion
	glutMouseFunc(mousePress);
	glutMainLoop();
	return 0;
}
