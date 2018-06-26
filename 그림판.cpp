#include <GL/glut.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <list>
#include <vector>

const double PIE = 3.14159;
int win_x, win_y;
using namespace std;
int num = 0;
int k = 0;
int mouseX = 0, mouseY = 0;
int s_x, s_y;
bool mouse_on;
bool mouse_moving;
int mode = 1;
bool draw_mode = true;
bool selc_mode = false;
bool translate = false;
bool moving_now = false;
bool rot = false;
bool solo = false;
bool chan = false;
bool multi = false;
bool chan2 = false;
bool cir_chan = false;
bool mur = false;
int mouse_var;

int move_index = 1;
class Last
{
public:

	int index;
	Last::Last()
	{
		index = 0;
	};
};
class Line
{

public:

	int x1, y1;
	int x2, y2;
	int p_x1, p_x2;
	int p_y1, p_y2;
	int color;
	bool tran;


	Line::Line()
	{
		x1 = 0;
		x2 = 0;
		y1 = 0;
		y2 = 0;
		color = 0;
		tran = false;
	};



};
class Rect
{
public:
	int x1, x2, y1, y2,x3,x4,y4,y3;

	int p_x1, p_x2;
	int p_y1, p_y2;
	int p_x3, p_x4;
	int p_y3, p_y4;
	bool tran;
	int color;

	Rect::Rect()
	{
		x1 = 0;
		x2 = 0;
		y1 = 0;
		y2 = 0;
		x3 = 0;
		y3 = 0;
		x4 = 0;
		y4 = 0;
		color = 0;
		tran = false;
	};



};
class Tri
{
public:
	int x1, x2, y1, y2, x3, y3;
	int p_x1, p_x2, p_y1, p_y2;
	int p_x3, p_y3;
	bool tran;
	int color;

	Tri::Tri()
	{
		x1 = 0;
		x2 = 0;
		y1 = 0;
		y2 = 0;
		color = 0;
		tran = false;
	};



};
class Circle
{
public:
	int x1, x2, y1, y2;
	bool tran;
	int color;
	int p_x1, p_x2, p_y1, p_y2;

	Circle::Circle()
	{
		x1 = 0;
		x2 = 0;
		y1 = 0;
		y2 = 0;
		color = 0;
		tran = false;
	};



};

list<Last> last_list;
list<Line> Line_list;
list<Rect> Rect_list;
list<Tri> Tri_list;
list<Circle> Circle_list;
list<Line>::iterator temp;
list<Rect>::iterator temp2;
list<Tri>::iterator temp3;
list<Circle>::iterator temp4;


bool search()
{
	if (!moving_now)
	{
		double distance = 10000;
		double distance2 = 10000;
		double distance3 = 10000;
		double distance4 = 10000;
		list<Line>::iterator it;
		list<Rect>::iterator it2;
		list<Tri>::iterator it3;
		list<Circle>::iterator it4;
		double x, y;
		int new_y = win_y - mouseY;
		int count = 0;
		for (it = Line_list.begin(); it != Line_list.end(); it++)
		{
			
			if (it->x1 < it->x2)
			{
				for (int i = (it->x1); i != (it->x2); i++)
				{
					if (!multi)
					{
						it->tran = false;
					}
						translate = false;
						double temp_dis;
						int length = abs(it->x2 - it->x1);
						x = i;

						y = (((double)(it->y2 - it->y1) / (double)(it->x2 - it->x1))
							* (i - it->x1)) + it->y1;

						temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


						if (temp_dis < distance)
						{
							
							distance = temp_dis;
							temp = it;
						}
										}
			}
	else if (it->x1 > it->x2)
	{
		for (int i = (it->x1); i != (it->x2); i--)
		{
			if (!multi)
			{
				it->tran = false;
			}
			translate = false;
			double temp_dis;
			int length = abs(it->x2 - it->x1);
			x = i;
			y = (((double)(it->y2 - it->y1) / (double)(it->x2 - it->x1))
				* (i - it->x1)) + it->y1;

			temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


			if (temp_dis < distance)
			{
				
				distance = temp_dis;
				temp = it;
			}
		}
	}

		}
		for (it2 = Rect_list.begin(); it2 != Rect_list.end(); it2++)
		{
			
			if ((it2->y2 > it2->y1) && it2->x1<it2->x2)
			{


				for (int i = (it2->x1); i != (it2->x2); i++)
				{
					if (!multi)
					{
						it2->tran = false;
					}
					translate = false;
					double temp_dis;

					x = i;
					y = double(it2->y1);

					temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


					if (temp_dis < distance2)
					{
						
						distance2 = temp_dis;
						temp2 = it2;
					}
				}
				for (int i = (it2->x1); i != (it2->x2); i++)
				{
					if (!multi)
					{
						it2->tran = false;
					}
					translate = false;
					double temp_dis;

					x = i;
					y = double(it2->y2);

					temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


					if (temp_dis < distance2)
					{
						
						distance2 = temp_dis;
						temp2 = it2;
					}
				}
				for (int i = (it2->y1); i != (it2->y2); i++)
				{
					if (!multi)
					{
						it2->tran = false;
					}
					translate = false;
					double temp_dis;

					x = (double)it2->x1;
					y = i;

					temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


					if (temp_dis < distance2)
					{
						
						distance2 = temp_dis;
						temp2 = it2;
					}
				}
				for (int i = (it2->y1); i != (it2->y2); i++)
				{
					if (!multi)
					{
						it2->tran = false;
					}
					translate = false;
					double temp_dis;

					x = (double)it2->x2;
					y = i;

					temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


					if (temp_dis < distance2)
					{
						
						distance2 = temp_dis;
						temp2 = it2;
					}
				}

			}
			else if ((it2->y2 < it2->y1) && it2->x1<it2->x2)
			{
				for (int i = (it2->x1); i != (it2->x2); i++)
				{
					if (!multi)
					{
						it2->tran = false;
					}
					translate = false;
					double temp_dis;

					x = i;
					y = double(it2->y1);

					temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


					if (temp_dis < distance2)
					{
						
						distance2 = temp_dis;
						temp2 = it2;
					}
				}
				for (int i = (it2->x1); i != (it2->x2); i++)
				{
					if (!multi)
					{
						it2->tran = false;
					}
					translate = false;
					double temp_dis;

					x = i;
					y = double(it2->y2);

					temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


					if (temp_dis < distance2)
					{
					
						distance2 = temp_dis;
						temp2 = it2;
					}
				}
				for (int i = (it2->y1); i != (it2->y2); i--)
				{
					if (!multi)
					{
						it2->tran = false;
					}
					translate = false;
					double temp_dis;

					x = (double)it2->x1;
					y = i;

					temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


					if (temp_dis < distance2)
					{
						
						distance2 = temp_dis;
						temp2 = it2;
					}
				}
				for (int i = (it2->y1); i != (it2->y2); i--)
				{
					if (!multi)
					{
						it2->tran = false;
					}translate = false;
					double temp_dis;

					x = (double)it2->x2;
					y = i;

					temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


					if (temp_dis < distance2)
					{
						
						distance2 = temp_dis;
						temp2 = it2;
					}
				}



			}
			else if ((it2->y2 > it2->y1) && it2->x1>it2->x2)
			{
				for (int i = (it2->x1); i != (it2->x2); i--)
				{
					if (!multi)
					{
						it2->tran = false;
					}
					translate = false;
					double temp_dis;

					x = i;
					y = double(it2->y1);

					temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


					if (temp_dis < distance2)
					{
					
						distance2 = temp_dis;
						temp2 = it2;
					}
				}
				for (int i = (it2->x1); i != (it2->x2); i--)
				{
					if (!multi)
					{
						it2->tran = false;
					}
					translate = false;
					double temp_dis;

					x = i;
					y = double(it2->y2);

					temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


					if (temp_dis < distance2)
					{
						
						distance2 = temp_dis;
						temp2 = it2;
					}
				}
				for (int i = (it2->y1); i != (it2->y2); i++)
				{
					if (!multi)
					{
						it2->tran = false;
					}
					translate = false;
					double temp_dis;

					x = (double)it2->x1;
					y = i;

					temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


					if (temp_dis < distance2)
					{
						
						distance2 = temp_dis;
						temp2 = it2;
					}
				}
				for (int i = (it2->y1); i != (it2->y2); i++)
				{
					if (!multi)
					{
						it2->tran = false;
					}
					translate = false;
					double temp_dis;

					x = (double)it2->x2;
					y = i;

					temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


					if (temp_dis < distance2)
					{
						
						distance2 = temp_dis;
						temp2 = it2;
					}
				}



			}
			else if ((it2->y2 < it2->y1) && it2->x1>it2->x2)
			{
				for (int i = (it2->x1); i != (it2->x2); i--)
				{
					if (!multi)
					{
						it2->tran = false;
					}
					translate = false;
					double temp_dis;

					x = i;
					y = double(it2->y1);

					temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


					if (temp_dis < distance2)
					{
						
						distance2 = temp_dis;
						temp2 = it2;
					}
				}
				for (int i = (it2->x1); i != (it2->x2); i--)
				{
					if (!multi)
					{
						it2->tran = false;
					}
					translate = false;
					double temp_dis;

					x = i;
					y = double(it2->y2);

					temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


					if (temp_dis < distance2)
					{
						
						distance2 = temp_dis;
						temp2 = it2;
					}
				}
				for (int i = (it2->y1); i != (it2->y2); i--)
				{
					if (!multi)
					{
						it2->tran = false;
					}
					translate = false;
					double temp_dis;

					x = (double)it2->x1;
					y = i;

					temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


					if (temp_dis < distance2)
					{
						
						distance2 = temp_dis;
						temp2 = it2;
					}
				}
				for (int i = (it2->y1); i != (it2->y2); i--)
				{
					if (!multi)
					{
						it2->tran = false;
					}
					translate = false;
					double temp_dis;

					x = (double)it2->x2;
					y = i;

					temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


					if (temp_dis < distance2)
					{
						
						distance2 = temp_dis;
						temp2 = it2;
					}
				}



			}

		}
		for (it3 = Tri_list.begin(); it3 != Tri_list.end(); it3++) //tri 서치
		{
			
			if (it3->x1 < it3->x2)
			{
				for (int i = (it3->x1); i != (it3->x2); i++) //1
				{
					if (!multi)
					{
						it3->tran = false;
					}
					translate = false;
					double temp_dis;
					x = i;
					y = (((double)(it3->y2 - it3->y1) / (double)(it3->x2 - it3->x1))
						* (i - it3->x1)) + it3->y1;

					temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


					if (temp_dis < distance3)
					{
						
						distance3 = temp_dis;
						temp3 = it3;
					}
				}

				for (int i = (it3->x1); i != (it3->x2); i++) //2
				{
					if (!multi)
					{
						it3->tran = false;
					}
					translate = false;
					double temp_dis;
					x = i;
					y = (double)(it3->y2);

					temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


					if (temp_dis < distance3)
					{
						
						distance3 = temp_dis;
						temp3 = it3;
					}
				}

				for (int i = (it3->x1); i != (2 * it3->x1 - it3->x2); i--) //3
				{
					if (!multi)
					{
						it3->tran = false;
					}
					translate = false;
					double temp_dis;
					x = i;
					y = (((double)(it3->y2 - it3->y1) / (double)(-it3->x2 + it3->x1))
						* (i - it3->x1)) + it3->y1;

					temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


					if (temp_dis < distance3)
					{
						
						distance3 = temp_dis;
						temp3 = it3;
					}
				}

			}


				else if (it3->x1 > it3->x2) 
				{
					for (int i = (it3->x1); i != (it3->x2); i--) //1
					{
						if (!multi)
						{
							it3->tran = false;
						}
						translate = false;
						double temp_dis;
						x = i;
						y = (((double)(it3->y2 - it3->y1) / (double)(it3->x2 - it3->x1))
							* (i - it3->x1)) + it3->y1;

						temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


						if (temp_dis < distance3)
						{
						
							distance3 = temp_dis;
							temp3 = it3;
						}
					}

					for (int i = (it3->x1); i != (it3->x2); i--) //2
					{
						if (!multi)
						{
							it3->tran = false;
						}
						translate = false;
						double temp_dis;
						x = i;
						y = (double)(it3->y2);

						temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


						if (temp_dis < distance3)
						{
							
							distance3 = temp_dis;
							temp3 = it3;
						}
					}

					for (int i = (it3->x1); i != (2 * it3->x1 - it3->x2); i++) //3
					{
						if (!multi)
						{
							it3->tran = false;
						}
						translate = false;
						double temp_dis;
						x = i;
						y = (((double)(it3->y2 - it3->y1) / (double)(-it3->x2 + it3->x1))
							* (i - it3->x1)) + it3->y1;

						temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


						if (temp_dis < distance3)
						{
							
							distance3 = temp_dis;
							temp3 = it3;
						}
					}
				}

			}

		for (it4 = Circle_list.begin(); it4 != Circle_list.end(); it4++) //crcle
		{
			
			if (!multi)
			{
				it4->tran = false;
			}
					translate = false;
					double temp_dis;
								
					double a = (double)abs(it4->x2 - it4->x1) / (double)2.0f;
					double b = (double)abs(it4->y2 - it4->y1) / (double)2.0f;
					double x, y;
					
					for (int i = 0; i != 360; i++)
					{
						
						x = a * cos(i*PIE / 180.0);
						y = b * sin(i*PIE / 180.0);
						
						x += (double)(it4->x1 + it4->x2) / (double)2.0f;
						y += (double)(it4->y1 + it4->y2) / (double)2.0f;



						temp_dis = sqrt(pow((x - mouseX), 2) + pow((y - (new_y)), 2));


						if (temp_dis < distance4)
						{
							
							distance4 = temp_dis;
							temp4 = it4;
						}

					}
				
			
		}
		
		if (distance<30.0&&distance < distance2&&distance<distance3&&distance<distance4)
		{
			move_index = 1;
			translate = true;
			temp->tran = true;
			temp->color = 1;
			printf("find !!");
			return true;
		}
		else if (distance2<30.0&&distance2 < distance&&distance2<distance3<distance2<distance4)
		{
			move_index = 2;
			translate = true;
			temp2->tran = true;
			temp2-> color = 1;
			printf("find !!");
			return true;
		}
		else if (distance3<30.0&&distance3 < distance&&distance3<distance2&&distance3<distance4)
		{
			move_index = 3;
			translate = true;
			temp3->tran = true;
			temp3->color = 1;
			printf("find !!");
			return true;
		}
		else if (distance4<30.0&&distance4 < distance&&distance4<distance2&&distance4<distance3)
		{
			move_index = 4;
			translate = true;
			temp4->tran = true;
			temp4->color = 1;
			printf("find !!");
			return true;
		}
		else
		{
			return false;

		}





	}
	else
	{
		return true;
	}
}

void mouseMotion(int x, int y)
{

	mouse_moving = false;
	mouseX = x;
	mouseY = y;
	
	glutPostRedisplay();
}
void mousePress(GLint button, GLint state, GLint x, GLint y)
{

	
	if (button == GLUT_LEFT_BUTTON  && state == GLUT_DOWN)
	{
		cir_chan = false;
		mouse_moving = true;
		mouse_on = true;
		mouseX = x;
		mouseY = y;
		solo = true;

		s_x = mouseX;
		s_y = win_y - mouseY;
		
		glutPostRedisplay();
	}

	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		solo = false;
		if (draw_mode)
		{
			if (mode == 1)
			{
				Line a;
				
				a.x1 = s_x;
				a.y1 = s_y;
				a.x2 = mouseX;
				a.y2 = win_y - mouseY;

				a.p_x1 = s_x;
				a.p_x2 = mouseX;
				a.p_y1 = s_y;
				a.p_y2 = win_y - mouseY;
				Line_list.push_back(a);
				Last k;
				k.index = 1;
				last_list.push_front(k);
			}
			else if (mode == 2)
			{
				Rect b;
				b.x1 = s_x;
				b.y1 = s_y;
				b.x3 = mouseX;
				b.y3 = s_y;
				b.x2 = mouseX;
				b.y2 = win_y - mouseY;
				b.x4 = s_x;
				b.y4 = win_y - mouseY;
				b.p_x1 = s_x;
				b.p_x2 = mouseX;
				b.p_y1 = s_y;
				b.p_y2 = win_y - mouseY;
				b.p_x3 = mouseX;
				b.p_y3 = s_y;
				b.p_x4 = s_x;
				b.p_y4 = win_y - mouseY;
				Rect_list.push_back(b);
				Last k;
				k.index = 2;
				last_list.push_front(k);
			}
			else if (mode == 3)
			{
				Tri c;
				c.x1 = s_x;
				c.y1 = s_y;
				c.x2 = mouseX;
				c.y2 = win_y - mouseY;
				c.x3 = 2 * s_x - mouseX;
				c.y3 = win_y - mouseY;
				c.p_x1 = s_x;
				c.p_x2 = mouseX;
				c.p_y1 = s_y;
				c.p_y2 = win_y - mouseY;
				c.p_x3 = 2 * s_x - mouseX;
				c.p_y3 = win_y - mouseY;
				Tri_list.push_back(c);
				Last k;
				k.index = 3;
				last_list.push_front(k);
			}
			else if (mode == 4)
			{
				Circle d;
				d.x1 = s_x;
				d.y1 = s_y;
				d.x2 = mouseX;
				d.y2 = win_y - mouseY;
				d.p_x1 = s_x;
				d.p_x2 = mouseX;
				d.p_y1 = s_y;
				d.p_y2 = win_y - mouseY;
				Circle_list.push_back(d);
				Last k;
				k.index = 4;
				last_list.push_front(k);
			}
		}
		else if (selc_mode&&translate&&!rot)
		
		{
			moving_now = false;
			if (move_index == 1)
			{
				
				temp->p_x1 = temp->x1;
				temp->p_x2 = temp->x2;
				temp->p_y1 = temp->y1;
				temp->p_y2 = temp->y2;
				if (!multi)
				{
					temp->color = 0;
				}
				
			}
			else if (move_index == 2)
			{
				temp2->p_x1 = temp2->x1;
				temp2->p_x2 = temp2->x2;
				temp2->p_y1 = temp2->y1;
				temp2->p_y2 = temp2->y2;
				temp2->p_x3 = temp2->x3;
				temp2->p_x4 = temp2->x4;
				temp2->p_y3 = temp2->y3;
				temp2->p_y4 = temp2->y4;
				if (!multi)
				{
					temp2->color = 0;
				}

			}
			else if (move_index == 3)
			{
				temp3->p_x1 = temp3->x1;
				temp3->p_x2 = temp3->x2;
				temp3->p_y1 = temp3->y1;
				temp3->p_y2 = temp3->y2;
				temp3->p_x3 = temp3->x3;
				temp3->p_y3 = temp3->y3;
			
				if (!multi)
				{
					temp3->color = 0;
				}

			}
			else if (move_index == 4)
			{
				temp4->p_x1 = temp4->x1;
				temp4->p_x2 = temp4->x2;
				temp4->p_y1 = temp4->y1;
				temp4->p_y2 = temp4->y2;
				if (!multi)
				{
					temp4->color = 0;
				}

			}
			
			

		}
		else if (selc_mode&&rot)
		{
			moving_now = false;
			if (move_index == 1)
			{

				temp->p_x1 = temp->x1;
				temp->p_x2 = temp->x2;
				temp->p_y1 = temp->y1;
				temp->p_y2 = temp->y2;
				if (!multi)
				{
					temp->color = 0;
				}
				
			}
			else if (move_index == 2)
			{
				temp2->p_x1 = temp2->x1;
				temp2->p_x2 = temp2->x2;
				temp2->p_y1 = temp2->y1;
				temp2->p_y2 = temp2->y2;
				temp2->p_x3 = temp2->x3;
				temp2->p_x4 = temp2->x4;
				temp2->p_y3 = temp2->y3;
				temp2->p_y4 = temp2->y4;
				if (!multi)
				{
					temp2->color = 0;
				}

			}
			else if (move_index == 3)
			{
				temp3->p_x1 = temp3->x1;
				temp3->p_x2 = temp3->x2;
				temp3->p_y1 = temp3->y1;
				temp3->p_y2 = temp3->y2;
				temp3->p_x3 = temp3->x3;
				temp3->p_y3 = temp3->y3;
				if (!multi)
				{
					temp3->color = 0;
				}

			}
			
			else if (move_index == 4)temp4->color = 0;

		}

		mouse_on = false;
		mouse_moving = false;

		glutPostRedisplay();
	}
}
void mousePassiveMotion(int x, int y)
{

	mouse_moving = false;
	mouseX = x;
	mouseY = y;
	
	glutPostRedisplay();
}



void idle()
{
	glutPostRedisplay();
}


void display(void)
{
	list<Line>::iterator it;
	list<Rect>::iterator it2;
	list<Tri>::iterator it3;
	list<Circle>::iterator it4;
	num = 0;
	glColor3f(0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
	if (draw_mode)
	{
		if (mouse_on)
		{
			for (it = Line_list.begin(); it != Line_list.end(); it++)
			{

				glBegin(GL_LINES);
				

				glColor3f(0, 0, 0);
				glVertex2i(it->x1, it->y1);
				glVertex2i(it->x2, it->y2);
				glEnd();
				
				num++;


			}
			for (it2 = Rect_list.begin(); it2 != Rect_list.end(); it2++)
			{
				double m_x = (it2->x1 + it2->x2) / 2;
				double m_y = (it2->y1 + it2->y2) / 2;

				

				glBegin(GL_LINE_LOOP);
				glColor3f(0, 0, 0);
				glVertex2i(it2->x1, it2->y1);
				glVertex2i(it2->x3, it2->y3);
				glVertex2i(it2->x2, it2->y2);
				glVertex2i(it2->x4, it2->y4);
				glEnd();




			}
			for (it3 = Tri_list.begin(); it3 != Tri_list.end(); it3++)
			{

				glBegin(GL_LINE_LOOP);
				glColor3f(0, 0, 0);
				glVertex2i(it3->x1, it3->y1);
				glVertex2i(it3->x2, it3->y2);
				glVertex2i(it3->x3,it3->y3);
				glEnd();




			}
			for (it4 = Circle_list.begin(); it4 != Circle_list.end(); it4++)
			{


				glBegin(GL_LINE_LOOP);
				glColor3f(0, 0, 0);
				double a = (double)abs(it4->x2 - it4->x1) / (double)2.0f;
				double b = (double)abs(it4->y2 - it4->y1) / (double)2.0f;
				double x, y;
			
				for (int i = 0; i != 360; i++)
				{
					
					x = a * cos(i*PIE / 180.0);
					y = b * sin(i*PIE / 180.0);
					
					x += (double)(it4->x1 + it4->x2) / (double)2.0f;
					y += (double)(it4->y1 + it4->y2) / (double)2.0f;
					glVertex2d(x, y);
				}
				glEnd();
			}

			if (mode == 1)
			{





				glBegin(GL_LINES);
				glColor3f(0, 0, 0);
				glVertex2i(s_x, s_y);
				glVertex2i(mouseX, win_y - mouseY);

				glEnd();

			}
			if (mode == 2)
			{


				glBegin(GL_LINE_LOOP);
				glColor3f(0, 0, 0);
				glVertex2i(s_x, s_y);
				glVertex2i(mouseX, s_y);
				glVertex2i(mouseX, win_y - mouseY);
				glVertex2i(s_x, win_y - mouseY);

				glEnd();



			}
			if (mode == 3)
			{


				glBegin(GL_LINE_LOOP);
				glColor3f(0, 0, 0);
				glVertex2i(s_x, s_y);
				glVertex2i(mouseX, win_y - mouseY);
				glVertex2i(2 * s_x - mouseX, win_y - mouseY);

				glEnd();



			}
			if (mode == 4)
			{


				glBegin(GL_LINE_LOOP);
				glColor3f(0, 0, 0);
				double a = (double)abs(mouseX - s_x) / (double)2.0f;
				double b = (double)abs(win_y - mouseY - s_y) / (double)2.0f;
				double x, y;
				
				for (int i = 0; i != 360; i++)
				{
					
					x = a * cos(i*PIE / 180.0);
					y = b * sin(i*PIE / 180.0);
					
					x += (double)(s_x + mouseX) / (double)2.0f;
					y += (double)(s_y + win_y - mouseY) / (double)2.0f;
					glVertex2d(x, y);
				}
				glEnd();



			}


		}

	}
	else if (selc_mode)
	{
		if (mouse_on)
		{


			if (search())
			{
				moving_now = true;
				if (!rot)
				{
					
					
					if (move_index == 1||multi)
					{
						for (it = Line_list.begin(); it != Line_list.end(); it++)
						{

							if (it->tran == true)
							{

								
								
								temp->x1 = temp->p_x1 + mouseX - s_x;
								temp->y1 = temp->p_y1 + (win_y - mouseY) - s_y;
								temp->x2 = temp->p_x2 + mouseX - s_x;
								temp->y2 = temp->p_y2 + (win_y - mouseY) - s_y;
								

							}


						}
					}
					if (move_index == 2||multi)
					{
						for (it2 = Rect_list.begin(); it2 != Rect_list.end(); it2++)
						{

							if (it2->tran == true)
							{


								temp2->x1 = temp2->p_x1 + mouseX - s_x;
								temp2->y1 = temp2->p_y1 + (win_y - mouseY) - s_y;
								temp2->x2 = temp2->p_x2 + mouseX - s_x;
								temp2->y2 = temp2->p_y2 + (win_y - mouseY) - s_y;
								temp2->x3 = temp2->p_x2 + mouseX - s_x;
								temp2->y3 = temp2->p_y1 + (win_y - mouseY) - s_y;
								temp2->x4 = temp2->p_x1 + mouseX - s_x;
								temp2->y4 = temp2->p_y2 + (win_y - mouseY) - s_y;
							

							}


						}


					}

					if (move_index == 3||multi)
					{
						for (it3 = Tri_list.begin(); it3 != Tri_list.end(); it3++)
						{

							if (it3->tran == true)
							{


								temp3->x1 = temp3->p_x1 + mouseX - s_x;
								temp3->y1 = temp3->p_y1 + (win_y - mouseY) - s_y;
								temp3->x2 = temp3->p_x2 + mouseX - s_x;
								temp3->y2 = temp3->p_y2 + (win_y - mouseY) - s_y;
								temp3->x3 = temp3->p_x3 + mouseX - s_x;
								temp3->y3 = temp3->p_y3 + (win_y - mouseY) - s_y;
							}


						}
					}

					if (move_index == 4||multi)
					{
						for (it4 = Circle_list.begin(); it4 != Circle_list.end(); it4++)
						{

							if (it4->tran == true)
							{


								temp4->x1 = temp4->p_x1 + mouseX - s_x;
								temp4->y1 = temp4->p_y1 + (win_y - mouseY) - s_y;
								temp4->x2 = temp4->p_x2 + mouseX - s_x;
								temp4->y2 = temp4->p_y2 + (win_y - mouseY) - s_y;
							

							}


						}
					}
				}//if(!rot)
				else//
				{
					
					if (move_index == 1||mur)
					{
						for (it = Line_list.begin(); it != Line_list.end(); it++)
						{
							
							if (it->tran == true)
							{
								
								int mid_x = (temp->p_x1 + temp->p_x2)/ 2;
								int mid_y = (temp->p_y1 + temp->p_y2)/ 2;
								double radius= sqrt(pow( (mid_x - temp->p_x1),2) + pow(mid_y - temp->p_y1, 2));
								double mc_size = sqrt(pow(mid_x - mouseX, 2) + pow(mid_y - (win_y - mouseY), 2));
								double mc_x = (mouseX - mid_x);
								if (mc_x == 0)
								{
									mc_x++;
								}
								int mc_y = ((win_y - mouseY) - mid_y);
								
								
								if (temp->x1 <= temp->x2)
								{
									temp->x2 = (mid_x + radius*(mc_x / mc_size));
									temp->y2 = (mid_y + radius*(mc_y / mc_size));
									temp->x1 = (mid_x - (radius*(mc_x / mc_size)));
									temp->y1 = (mid_y - (radius*(mc_y / mc_size)));
								}
								
								else 
								{
									temp->x2 = (mid_x - radius*(mc_x / mc_size));
									temp->y2 = (mid_y - radius*(mc_y / mc_size));
									temp->x1 = (mid_x + (radius*(mc_x / mc_size)));
									temp->y1 = (mid_y + (radius*(mc_y / mc_size)));
								}
								
								

							}


						}


					}

					if (move_index == 2||mur)
					{
						for (it2 = Rect_list.begin(); it2 != Rect_list.end(); it2++)
						{
							
							
							if (it2->tran == true)
							{
								
								bool direc = true;
								int mid_x = (temp2->p_x1 + temp2->p_x2) / 2;
								int mid_y = (temp2->p_y1 + temp2->p_y2) / 2;
								double radius = sqrt(pow((mid_x - temp2->p_x1), 2) + pow(mid_y - temp2->p_y1, 2));
								double mc_size = sqrt(pow(mid_x - mouseX, 2) + pow(mid_y - (win_y - mouseY), 2));
								double mc1_x = (s_x - mid_x);
								double mc1_y = (s_y - mid_y);
								double mc_x = (mouseX - mid_x);
								double mc_y = ((win_y - mouseY) - mid_y);
								double a = mc1_x*mc_x;
								double b = mc1_y*mc_y;
									
								double cos = (a + b) / sqrt(pow(mc_x, 2) + pow(mc_y, 2)) / sqrt(pow(mc1_x, 2) + pow(mc1_y, 2));
								double theta = acos(cos);
								double temp = sin(theta);
								double sin = temp;
								
								if (cos < -0.999||chan)
								{
									sin *= -1;
									chan = true;

								}
								if (cos >= 0.999)
								{
									chan = false;
								}
								//printf("cos : %f \n",cos);
								//printf("sin : %f \n",sin);
								
								
									temp2->x1 = cos*(it2->p_x1 - mid_x) - sin*(it2->p_y1 - mid_y) + mid_x;
									temp2->y1 = sin*(it2->p_x1 - mid_x) + cos*(it2->p_y1 - mid_y) + mid_y;
									temp2->x2 = cos*(it2->p_x2 - mid_x) - sin*(it2->p_y2 - mid_y) + mid_x;
									temp2->y2 = sin*(it2->p_x2 - mid_x) + cos*(it2->p_y2 - mid_y) + mid_y;
									temp2->x3 = cos*(it2->p_x3 - mid_x) - sin*(it2->p_y3 - mid_y) + mid_x;
									temp2->y3 = sin*(it2->p_x3 - mid_x) + cos*(it2->p_y3 - mid_y) + mid_y;
									temp2->x4 = cos*(it2->p_x4 - mid_x) - sin*(it2->p_y4 - mid_y) + mid_x;
									temp2->y4 = sin*(it2->p_x4 - mid_x) + cos*(it2->p_y4 - mid_y) + mid_y;
								/*
								else
								{
									temp2->x1 = cos*(it2->p_x1 - mid_x) + sin*(it2->p_y1 - mid_y) + mid_x;
									temp2->y1 = -sin*(it2->p_x1 - mid_x) + cos*(it2->p_y1 - mid_y) + mid_y;
									temp2->x2 = cos*(it2->p_x2 - mid_x) + sin*(it2->p_y2 - mid_y) + mid_x;
									temp2->y2 = -sin*(it2->p_x2 - mid_x) + cos*(it2->p_y2 - mid_y) + mid_y;
									temp2->x3 = cos*(it2->p_x3 - mid_x) + sin*(it2->p_y3 - mid_y) + mid_x;
									temp2->y3 = -sin*(it2->p_x3 - mid_x) + cos*(it2->p_y3 - mid_y) + mid_y;
									temp2->x4 = cos*(it2->p_x4 - mid_x) + sin*(it2->p_y4 - mid_y) + mid_x;
									temp2->y4 = -sin*(it2->p_x4 - mid_x) + cos*(it2->p_y4 - mid_y) + mid_y;

								}
								*/

							}


						}


					}

					
					if (move_index == 3||mur)
					{
						for (it3 = Tri_list.begin(); it3 != Tri_list.end(); it3++)
						{

							
							if (it3->tran == true||mur)
							{

								bool direc = true;
								int mid_x = (temp3->p_x1 + temp3->p_x2+temp3->p_x3) / 3;
								int mid_y = (temp3->p_y1 + temp3->p_y2+temp3->p_y3) / 3;
								double radius = sqrt(pow((mid_x - temp3->p_x1), 2) + pow(mid_y - temp3->p_y1, 2));
								double mc_size = sqrt(pow(mid_x - mouseX, 2) + pow(mid_y - (win_y - mouseY), 2));
								double mc1_x = (s_x - mid_x);
								double mc1_y = (s_y - mid_y);
								double mc_x = (mouseX - mid_x);
								double mc_y = ((win_y - mouseY) - mid_y);
								double a = mc1_x*mc_x;
								double b = mc1_y*mc_y;

								double cos = (a + b) / sqrt(pow(mc_x, 2) + pow(mc_y, 2)) / sqrt(pow(mc1_x, 2) + pow(mc1_y, 2));
								double theta = acos(cos);
								double temp = sin(theta);
								double sin = temp;

								if (cos < -0.999 || chan2)
								{
									sin *= -1;
									chan2 = true;

								}
								if (cos >= 0.999)
								{
									chan2 = false;
								}
								//printf("cos : %f \n", cos);
								//printf("sin : %f \n", sin);


								temp3->x1 = cos*(it3->p_x1 - mid_x) - sin*(it3->p_y1 - mid_y) + mid_x;
								temp3->y1 = sin*(it3->p_x1 - mid_x) + cos*(it3->p_y1 - mid_y) + mid_y;
								temp3->x2 = cos*(it3->p_x2 - mid_x) - sin*(it3->p_y2 - mid_y) + mid_x;
								temp3->y2 = sin*(it3->p_x2 - mid_x) + cos*(it3->p_y2 - mid_y) + mid_y;
								temp3->x3 = cos*(it3->p_x3 - mid_x) - sin*(it3->p_y3 - mid_y) + mid_x;
								temp3->y3 = sin*(it3->p_x3 - mid_x) + cos*(it3->p_y3 - mid_y) + mid_y;
								
								/*
								else
								{
								temp2->x1 = cos*(it2->p_x1 - mid_x) + sin*(it2->p_y1 - mid_y) + mid_x;
								temp2->y1 = -sin*(it2->p_x1 - mid_x) + cos*(it2->p_y1 - mid_y) + mid_y;
								temp2->x2 = cos*(it2->p_x2 - mid_x) + sin*(it2->p_y2 - mid_y) + mid_x;
								temp2->y2 = -sin*(it2->p_x2 - mid_x) + cos*(it2->p_y2 - mid_y) + mid_y;
								temp2->x3 = cos*(it2->p_x3 - mid_x) + sin*(it2->p_y3 - mid_y) + mid_x;
								temp2->y3 = -sin*(it2->p_x3 - mid_x) + cos*(it2->p_y3 - mid_y) + mid_y;
								temp2->x4 = cos*(it2->p_x4 - mid_x) + sin*(it2->p_y4 - mid_y) + mid_x;
								temp2->y4 = -sin*(it2->p_x4 - mid_x) + cos*(it2->p_y4 - mid_y) + mid_y;

								}
								*/

							}


						}


					} //3 끝

					if (move_index == 4)
					{
						for (it4 = Circle_list.begin(); it4 != Circle_list.end(); it4++)
						{

							if (it4->tran == true)
							{
								
								int mid_x = (temp4->p_x1 + temp4->p_x2) / 2;
								int mid_y = (temp4->p_y1 + temp4->p_y2) / 2;
								cir_chan = true;

								/*
								double radius = sqrt(pow((mid_x - temp4->p_x1), 2) + pow(mid_y - temp4->p_y1, 2));
								double mc_size = sqrt(pow(mid_x - mouseX, 2) + pow(mid_y - (win_y - mouseY), 2));
								double mc_x = (mouseX - mid_x);
								if (mc_x == 0)
								{
									mc_x++;
								}
								int mc_y = ((win_y - mouseY) - mid_y);


								if (temp4->x1 <= temp4->x2)
								{
									temp4->x2 = (mid_x + radius*(mc_x / mc_size));
									temp4->y2 = (mid_y + radius*(mc_y / mc_size));
									temp4->x1 = (mid_x - (radius*(mc_x / mc_size)));
									temp4->y1 = (mid_y - (radius*(mc_y / mc_size)));
								}

								else
								{
									temp4->x2 = (mid_x - radius*(mc_x / mc_size));
									temp4->y2 = (mid_y - radius*(mc_y / mc_size));
									temp4->x1 = (mid_x + (radius*(mc_x / mc_size)));
									temp4->y1 = (mid_y + (radius*(mc_y / mc_size)));
								}
								*/

								
							}


						}


					}

				}
			}

		}
		if (mouse_moving == false)
		{
			for (it = Line_list.begin(); it != Line_list.end(); it++)
			{


				if (it->color == 1)
				{
					glColor3f(1, 0, 0);
					glLineWidth(5.0);
				}



				glBegin(GL_LINES);
				glVertex2i(it->x1, it->y1);
				glVertex2i(it->x2, it->y2);
				glEnd();
				
				glColor3f(0, 0, 0);
				glLineWidth(0.1);

				num++;


			}

			for (it2 = Rect_list.begin(); it2 != Rect_list.end(); it2++)
			{

				if (it2->color == 1)
				{
					glColor3f(1, 0, 0);
					glLineWidth(5.0);
				}
				double m_x = (it2->x1 + it2->x2) / 2;
				double m_y = (it2->y1 + it2->y2) / 2;



				glBegin(GL_LINE_LOOP);

				glVertex2i(it2->x1, it2->y1);
				glVertex2i(it2->x3, it2->y3);
				glVertex2i(it2->x2, it2->y2);
				glVertex2i(it2->x4, it2->y4);
				glEnd();

				glColor3f(0, 0, 0);
				glLineWidth(0.1);



			}

			for (it3 = Tri_list.begin(); it3 != Tri_list.end(); it3++)
			{

				if (it3->color == 1)
				{
					glColor3f(1, 0, 0);
					glLineWidth(5.0);
				}
				glBegin(GL_LINE_LOOP);

				glVertex2i(it3->x1, it3->y1);
				glVertex2i(it3->x2, it3->y2);
				glVertex2i(it3->x3, it3->y3);
				glEnd();

				glColor3f(0, 0, 0);
				glLineWidth(0.1);



			}
			for (it4 = Circle_list.begin(); it4 != Circle_list.end(); it4++)
			{
				
				if (it4->color == 1)
				{
					int mid_x = (temp4->p_x1 + temp4->p_x2) / 2;
					int mid_y = (temp4->p_y1 + temp4->p_y2) / 2;
					glColor3f(1, 0, 0);
					glLineWidth(5.0);
					
					
					
					if (rot)
					{
						glMatrixMode(GL_MODELVIEW);
						glLoadIdentity();

						glTranslated(mid_x, mid_y, 0);
						glRotated(mouseX % 360, 0, 0, 1);
						glTranslated(-mid_x, -mid_y, 0);
					}
					

				}
				glBegin(GL_LINE_LOOP);

				double a = (double)abs(it4->x2 - it4->x1) / (double)2.0f;
				double b = (double)abs(it4->y2 - it4->y1) / (double)2.0f;
				double x, y;
				
				for (int i = 0; i != 360; i++)
				{
				
					x = a * cos(i*PIE / 180.0);
					y = b * sin(i*PIE / 180.0);
					
					x += (double)(it4->x1 + it4->x2) / (double)2.0f;
					y += (double)(it4->y1 + it4->y2) / (double)2.0f;
					glVertex2d(x, y);
				}
				glEnd();

				glColor3f(0, 0, 0);
				glLineWidth(0.1);
			}

		}


	}
	
		for (it = Line_list.begin(); it != Line_list.end(); it++)
		{

			
			glBegin(GL_LINES);
			glColor3f(0, 0, 0);
			glVertex2i(it->x1, it->y1);
			glVertex2i(it->x2, it->y2);
			glEnd();
			

			num++;


		}
		for (it2 = Rect_list.begin(); it2 != Rect_list.end(); it2++)
		{
			double m_x = (it2->x1 + it2->x2) / 2;
			double m_y = (it2->y1 + it2->y2) / 2;

			
			glBegin(GL_LINE_LOOP);
			glColor3f(0, 0, 0);
			glVertex2i(it2->x1, it2->y1);
			glVertex2i(it2->x3, it2->y3);
			glVertex2i(it2->x2, it2->y2);
			glVertex2i(it2->x4, it2->y4);
			glEnd();
			




		}
		for (it3 = Tri_list.begin(); it3 != Tri_list.end(); it3++)
		{
			
			glBegin(GL_LINE_LOOP);
			glColor3f(0, 0, 0);
			glVertex2i(it3->x1, it3->y1);
			glVertex2i(it3->x2, it3->y2);
			glVertex2i(it3->x3, it3->y3);
			glEnd();
		



		}
		for (it4 = Circle_list.begin(); it4 != Circle_list.end(); it4++)
		{


			glBegin(GL_LINE_LOOP);
			glColor3f(0, 0, 0);
			double a = (double)abs(it4->x2 - it4->x1) / (double)2.0f;
			double b = (double)abs(it4->y2 - it4->y1) / (double)2.0f;
			double x, y;
			
			for (int i = 0; i != 360; i++)
			{
				
				x = a * cos(i*PIE / 180.0);
				y = b * sin(i*PIE / 180.0);
				
				x += (double)(it4->x1 + it4->x2) / (double)2.0f;
				y += (double)(it4->y1 + it4->y2) / (double)2.0f;
				glVertex2d(x, y);
			}
			glEnd();


		}

	


	glFlush();




}

void init()
{
	glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h)
{
	win_x = w;
	win_y = h;

	glMatrixMode(GL_PROJECTION);  // set the projection matrix (will talk about this later)
	glLoadIdentity();             // This clear any existing matrix

	gluOrtho2D(0, w, 0, h);     // use new windows coords as dimensions

	glMatrixMode(GL_MODELVIEW);    // set model transformation
	glLoadIdentity();              // to be empty (will talk about this later
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{

	case 'l': mode = 1; break;
	case 'r': mode = 2; break;
	case 't': mode = 3; break;
	case 'c': mode = 4; break;
	case 's': draw_mode = false; selc_mode = true; rot = false; multi = false; mur = false; break;
	case 'd': draw_mode = true; selc_mode = false; rot = false; multi = false; mur = false; break;
	case 'o': draw_mode = false; selc_mode = true; rot = true; multi = false; break;
	case 'm': draw_mode = false; selc_mode = true; multi = true; rot = false; break;
	case 'p': draw_mode = false; selc_mode = true; multi = true; rot = true; mur = true;  break;
	case 'u': 
	{
		list<Last>::iterator it;
		it = last_list.begin();
		if (it != last_list.end())
		{
			k = it->index;
			last_list.pop_front();
			switch(k)
			{
			case 1:Line_list.pop_back(); glutPostRedisplay();  break;
			case 2:Rect_list.pop_back(); glutPostRedisplay();  break;
			case 3:Tri_list.pop_back(); glutPostRedisplay();  break;
			case 4:Circle_list.pop_back(); glutPostRedisplay();  break;
			default: break;
			}

		}
		else
		{
			break;
		}
		break;
	}	
	case 'a': while (1) {
							if (Line_list.empty()) break;
								Line_list.pop_back(); 
	
						}
			  while (1) {
				  if (Rect_list.empty()) break;
				  Rect_list.pop_back();

			  }
			  while (1) {
				  if (Tri_list.empty()) break;
				  Tri_list.pop_back();

			  }
			  while (1) {
				  if (Circle_list.empty()) break;
				  Circle_list.pop_back();

			  }
			  glutPostRedisplay();
			  break;
	case 'z':
	{
		printf("%d, %d 원래위치\n", Line_list.begin()->p_x1, Line_list.begin()->p_y1);
		printf("%d, %d 나중위치\n", Line_list.begin()->x1, Line_list.begin()->y1);

		printf("%d, %d 2원래위치\n", Line_list.begin()->p_x2, Line_list.begin()->p_y2);
		printf("%d, %d 2나중위치\n", Line_list.begin()->x2, Line_list.begin()->y2);
		
		break;

	}
	
	case 27:	exit(0);	break;
	default:	break;
	}
}



int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(512, 512);

	glutCreateWindow("Volume division in 3D Gasket");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutReshapeFunc(reshape);
	glutMotionFunc(mouseMotion);
	glutMouseFunc(mousePress);
	glutPassiveMotionFunc(mousePassiveMotion);
	glutDisplayFunc(display);
	glutKeyboardFunc(myKeyboard);

	init();

	glutMainLoop();




}
