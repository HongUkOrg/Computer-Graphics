#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

int width, height;

int pt_mouse_cur[2];
int pt_mouse_last[2];

float q_rotation_cur[4] = { 1.0, 0.0, 0.0, 0.0 }; // current rotation
float q_rotation_last[4] = { 1.0, 0.0, 0.0, 0.0 }; // last rotation

float mat_rotation[16] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0,
}; // rotation matrix

bool drag = false;

void convert_sphere_coordinate(int pt_mouse[], float v_sphere[])
{
	v_sphere[0] = 2.0f * ((float)pt_mouse[0] / width) - 1.0f;
	v_sphere[1] = 2.0f * ((float)(height - pt_mouse[1]) / height) - 1.0f;
	v_sphere[2] = 0.0f;

	float dist2 = v_sphere[0] * v_sphere[0] + v_sphere[1] * v_sphere[1] + v_sphere[2] * v_sphere[2];
	if (dist2 > 1.0f) { // mouse out of window => roll
		float dist = sqrt(dist2);
		v_sphere[0] /= dist;
		v_sphere[1] /= dist;
	}
	else { // mouse in window => yaw, pitch
		v_sphere[2] = sqrt(1.0f - v_sphere[0] * v_sphere[0] + v_sphere[1] * v_sphere[1]);
	}
}

void get_rotation(float v_from[], float v_to[], float q_rotation[])
{
	q_rotation[0] = v_from[0] * v_to[0] + v_from[1] * v_to[1] + v_from[2] * v_to[2];
	q_rotation[1] = v_from[1] * v_to[2] - v_from[2] * v_to[1];
	q_rotation[2] = v_from[2] * v_to[0] - v_from[0] * v_to[2];
	q_rotation[3] = v_from[0] * v_to[1] - v_from[1] * v_to[0];
}

void q2m(float q[], float m[])
{
	double l = q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3];
	double s = (l > 0.0) ? (2.0 / l) : 0.0;

	double xs = q[1] * s;
	double ys = q[2] * s;
	double zs = q[3] * s;

	double wx = q[0] * xs;
	double wy = q[0] * ys;
	double wz = q[0] * zs;

	double xx = q[1] * xs;
	double xy = q[1] * ys;
	double xz = q[1] * zs;

	double yy = q[2] * ys;
	double yz = q[2] * zs;

	double zz = q[3] * zs;

	m[0] = 1.0 - (yy + zz); m[1] = xy + wz;		m[2] = xz - wy;		m[3] = 0.0;
	m[4] = xy - wz;		m[5] = 1.0 - (xx + zz); m[6] = yz + wx;		m[7] = 0.0;
	m[8] = xz + wy;		m[9] = yz - wx;		m[10] = 1.0 - (xx + yy); m[11] = 0.0;
	m[12] = 0.0;			m[13] = 0.0;			m[14] = 0.0;			m[15] = 1.0;
}

void set_rotation_matrix(void)
{
	float v_from[3], v_to[3];
	convert_sphere_coordinate(pt_mouse_last, v_from);
	convert_sphere_coordinate(pt_mouse_cur, v_to);
	if (drag) {
		float q_rotation[4];
		get_rotation(v_from, v_to, q_rotation);
		q_rotation_cur[0] =
			q_rotation[0] * q_rotation_last[0] - q_rotation[1] * q_rotation_last[1] -
			q_rotation[2] * q_rotation_last[2] - q_rotation[3] * q_rotation_last[3];
		q_rotation_cur[1] =
			q_rotation[0] * q_rotation_last[1] + q_rotation[1] * q_rotation_last[0] +
			q_rotation[2] * q_rotation_last[3] - q_rotation[3] * q_rotation_last[2];
		q_rotation_cur[2] =
			q_rotation[0] * q_rotation_last[2] + q_rotation[2] * q_rotation_last[0] +
			q_rotation[3] * q_rotation_last[1] - q_rotation[1] * q_rotation_last[3];
		q_rotation_cur[3] =
			q_rotation[0] * q_rotation_last[3] + q_rotation[3] * q_rotation_last[0] +
			q_rotation[1] * q_rotation_last[2] - q_rotation[2] * q_rotation_last[1];
	}
	q2m(q_rotation_cur, mat_rotation);
}

void set_mouse_position(int x, int y)
{
	pt_mouse_cur[0] = x;
	pt_mouse_cur[1] = y;

	set_rotation_matrix();
}

double vertices[8][3] = {
	{ 1.0f, 1.0f, 1.0f }, //0
	{ 1.0f, 1.0f,-1.0f }, //1
	{ 1.0f,-1.0f,-1.0f }, //2
	{ -1.0f,-1.0f,-1.0f }, //3
	{ -1.0f,-1.0f, 1.0f }, //4
	{ -1.0f, 1.0f, 1.0f }, //5
	{ -1.0f, 1.0f,-1.0f }, //6
	{ 1.0f,-1.0f, 1.0f }  //7
};

static void reshape(int w, int h)
{
	width = w;
	height = h;

	float aspect = (double)w / (double)h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, 0.1, 150.0);
	glMatrixMode(GL_MODELVIEW);
}

void draw_cube()
{
	glPushMatrix();
	glBegin(GL_LINES);
	// Front
	glColor4f(1.0, 0.0, 0.0, 1.0);
	glVertex3f(vertices[5][0], vertices[5][1], vertices[5][2]);
	glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]);

	glVertex3f(vertices[5][0], vertices[5][1], vertices[5][2]);
	glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]);

	glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]);
	glVertex3f(vertices[7][0], vertices[7][1], vertices[7][2]);

	glVertex3f(vertices[7][0], vertices[7][1], vertices[7][2]);
	glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]);
	// Middle
	glColor4f(0.0, 1.0, 0.0, 1.0);
	glVertex3f(vertices[6][0], vertices[6][1], vertices[6][2]);
	glVertex3f(vertices[5][0], vertices[5][1], vertices[5][2]);

	glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);
	glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]);

	glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);
	glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]);

	glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
	glVertex3f(vertices[7][0], vertices[7][1], vertices[7][2]);
	// Back
	glColor4f(0.0, 0.0, 1.0, 1.0);
	glVertex3f(vertices[6][0], vertices[6][1], vertices[6][2]);
	glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);

	glVertex3f(vertices[6][0], vertices[6][1], vertices[6][2]);
	glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);

	glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);
	glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);

	glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
	glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);
	glEnd();
	glPopMatrix();
}

static void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(
		0.0, 0.0, 5.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);
	glMultMatrixf(mat_rotation);

	draw_cube();

	glFlush();
	glutSwapBuffers();
}

static void mouse(int b, int s, int x, int y)
{
	if (b == GLUT_LEFT_BUTTON) {
		set_mouse_position(x, y);
		if (s == GLUT_DOWN) {
			drag = true;
			pt_mouse_last[0] = pt_mouse_cur[0];
			pt_mouse_last[1] = pt_mouse_cur[1];
		}
		else {
			drag = false;
			q_rotation_last[0] = q_rotation_cur[0];
			q_rotation_last[1] = q_rotation_cur[1];
			q_rotation_last[2] = q_rotation_cur[2];
			q_rotation_last[3] = q_rotation_cur[3];
		}
		glutPostRedisplay();
	}
}

static void motion(int x, int y)
{
	set_mouse_position(x, y);
	glutPostRedisplay();
}

static void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:  /*  Escape Key  */
		exit(0);
		break;
	}
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(512, 512);
	glutCreateWindow(argv[0]);

	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);

	glShadeModel(GL_SMOOTH);
	glutMainLoop();
	return 0;
}

