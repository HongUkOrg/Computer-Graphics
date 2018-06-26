
#include <iostream>
#include <GL/glut.h>
#include "SOIL.h"

#ifndef M_PI 
#define M_PI 3.14159265358979323846 
#endif 

typedef enum _VIEW_MODE {
	DEFAULT = 0, 
	CONTRAST_STRETCHING = 1,
	HISTOGRAM_EQUALIZATION = 2,
	GAUSSIAN_FILTER = 3,
	MEDIAN_FILTER_3 = 4,
	MEDIAN_FILTER_7 = 5
} ViewMode;

ViewMode s_mode = DEFAULT;

float clamp(float val, const float min, const float max)
{
	float cut_max = val < max ? val : max;
	return cut_max > min ? cut_max : min;
}

int clamp(int val, const int min, const int max)
{
	int cut_max = val < max ? val : max;
	return cut_max > min ? cut_max : min;
}

/* Flip Image (since OpenGL's origin is left-bottom) */
unsigned char* flipImageY(unsigned char* image, int width, int height, int channels) {
	unsigned char* flipImage = new unsigned char[width * height * channels];
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			for (int k = 0; k < channels; k++) {
				flipImage[(i + j * width) * channels + k] = image[(i + (height - 1 - j) * width) * channels + k];
			}
		}
	}
	return flipImage;
}

/* Contrast Stretching */
unsigned char* contrastStretchingGrayscale(unsigned char* image, int width, int height) {
	// Apply contrast stretching to an image
	//
	// Input:
	//      image - grayscale image
	//      width - width of the input image
	//      height - height of the input image
	//
	// Output:
	//      resultImage - an constrast-stretched image
	//

	unsigned char* resultImage = new unsigned char[width * height];
	// your code here...

	// Set Min & Max
	int min_value = 255, max_value = 0;
	for (int row=0; row<height; row++) {
		for (int col=0; col<width; col++) {
			int offset = row * width + col;
			if (min_value > image[offset])
				min_value = image[offset];
			if (max_value < image[offset])
				max_value = image[offset];
		}
	}

	// Convert By Stretching
	float factor = 255.0f / (max_value - min_value);
	for (int row=0; row<height; row++) {
		for (int col=0; col<width; col++) {
			int offset = row * width + col;
			resultImage[offset] = (unsigned char)((image[offset] - min_value) * factor + 0.5f); // Round
		}
	}

	return resultImage;
}

/* Histogram Equalization */
unsigned char* histogramEqualizationGrayscale(unsigned char* image, int width, int height) {
	// Apply histogram equalization to an image
	//
	// Input:
	//      image - grayscale image
	//      width - width of the input image
	//      height - height of the input image
	//
	// Output:
	//      resultImage - an histogram-equalized image
	//

	unsigned char* resultImage = new unsigned char[width * height];
	// your code here...

	// Init 
	unsigned int histogram[256];
	unsigned int sum_hist[256];
	for (int i=0; i<256; i++) histogram[i]=0;

	// Set Histogram 
	for (int row=0; row<height; row++) {
		for (int col=0; col<width; col++) {
			int offset = row * width + col;
			histogram[image[offset]]++;
		}
	}

	// Histogram Equalization 
	int sum = 0;
	float factor = 255.0f / (height * width);
	for (int i = 0; i < 256; i++) {
		sum += histogram[i];
		sum_hist[i] = (int)((sum * factor) + 0.5f); // Round
	}

	// Convert 
	for (int row=0; row<height; row++) {
		for (int col=0; col<width; col++) {
			int index = row * width + col;
			resultImage[index] = sum_hist[image[index]];
		}
	}

	return resultImage;
}

/* Gaussian Filter */
unsigned char* gaussianFilterGrayscale(unsigned char* image, int width, int height, int filter_size) {
	// Apply a gaussian filter to an image
	//
	// Input:
	//      image - grayscale image
	//      width - width of the input image
	//      height - height of the input image
	//
	// Output:
	//      filteredImage - an image filtered with a gaussian filter
	//

	unsigned char* filteredImage = new unsigned char[width * height];
	// your code here...

	// Init 
	if (filter_size < 3) filter_size = 3;
	if (filter_size % 2 == 0) filter_size++; // filter_size must be odd number
	int filter_center = filter_size / 2;

	float sigma = (filter_size - 1) / 8.0f;

	float* floatImage = new float[width * height];
	float* mask = new float[filter_size];

	// Set Mask
	for (int i = 0; i < filter_size; i++) {
		float offset = i - filter_center;
		mask[i] = exp(-(offset * offset) / (2 * sigma * sigma)) / (sqrt(2 * M_PI) * sigma);
	}

	// Vertical Filtering
	for (int col = 0; col < width; col++) {
		for (int row = 0; row < height; row++) {
			float sum_mask = 0.f, sum_value = 0.f;

			for (int i = 0; i < filter_size; i++) {
				int offset = i - filter_center + row;

				if (offset >= 0 && offset < height) {
					sum_mask += mask[i];
					sum_value += (mask[i] * image[width * offset + col]);
				}
			}

			floatImage[row * width + col] = sum_value / sum_mask;
		}
	}

	// Horizontal Filtering
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			float sum_mask = 0.f, sum_value = 0.f;

			for (int i = 0; i < filter_size; i++) {
				int offset = i - filter_center + col;

				if (offset >= 0 && offset < width) {
					sum_mask += mask[i];
					sum_value += (mask[i] * floatImage[width * row + offset]);
				}
			}

			filteredImage[row * width + col] = (unsigned char)(sum_value / sum_mask + 0.5f); // Round
		}
	}

	delete[] floatImage;
	delete[] mask;

	return filteredImage;
}

/* Median Filter */
int get_center_of_bubble_sort(int val[], int size)
{
	int temp;
	int center = size / 2;
	for (int i=1; i<size; i++) {
		for (int j=0; j<size-1; j++) {
			if (val[j] > val[j+1]) {
				temp = val[j];
				val[j] = val[j+1];
				val[j+1] = temp;
			}
		}
	}
	return val[center];
}

unsigned char* medianFilterGrayscale(unsigned char* image, int width, int height, int filter_size) {
	// Apply a median filter to an image
	//
	// Input:
	//      image - grayscale image
	//      width - width of the input image
	//      height - height of the input image
	//
	// Output:
	//      filteredImage - an image filtered with a median filter
	//

	unsigned char* filteredImage = new unsigned char[width * height];
	// your code here...

	// Init
	int* mask = new int[filter_size * filter_size];
	int filter_center = filter_size / 2;
	
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			// Set Mask
			for (int fr = 0; fr < filter_size; fr++) {
				for (int fc = 0; fc < filter_size; fc++) {
					// Limit filter in image resolution 
					int offset_row = clamp(row + fr - filter_center, 0, height - 1);
					int offset_col = clamp(col + fc - filter_center, 0, width - 1);

					mask[fr * filter_size + fc] = image[offset_row * width + offset_col];
				}
			}
			// Filter
			filteredImage[row * width + col] = get_center_of_bubble_sort(mask, filter_size * filter_size);
		}
	}
	//*/
	delete[] mask;

	return filteredImage;
}

/* Display Function
*
* You may edit this function to solve multiple tasks.
*
*/
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	int width, height;
	int numChannels = 1; // 1 for grayscale, 3 for RGB color
						 // Load Image (CHECK THE IMAGE'S PATH!)
	unsigned char* image = SOIL_load_image("Lenna.png" /* Check image path! */, &width, &height, 0, numChannels);
	if (image != NULL) {
		// Flip image (due to the upside-down property of OpenGL)
		unsigned char* flippedImage = flipImageY(image, width, height, numChannels);
		SOIL_free_image_data(image); // free memory

									 // Image Processing Operation
									 // Set this 'finalImage' variable to the resulting image of operation
		unsigned char* finalImage = flippedImage; // Edit this line, e.g. unsigned char* finalImage = GaussianFilterGrayscale(flippedImage, width, height);
		char* output_file;
		switch (s_mode)
		{
		case CONTRAST_STRETCHING:
			finalImage = contrastStretchingGrayscale(flippedImage, width, height);
			output_file = "CONTRAST_STRETCHING.bmp";
			break;
		case HISTOGRAM_EQUALIZATION:
			finalImage = histogramEqualizationGrayscale(flippedImage, width, height);
			output_file = "HISTOGRAM_EQUALIZATION.bmp";
			break;
		case GAUSSIAN_FILTER:
			finalImage = gaussianFilterGrayscale(flippedImage, width, height, 5);
			output_file = "GAUSSIAN_FILTER.bmp";
			break;
		case MEDIAN_FILTER_3:
			finalImage = medianFilterGrayscale(flippedImage, width, height, 3);
			output_file = "MEDIAN_FILTER_3.bmp";
			break;
		case MEDIAN_FILTER_7:
			finalImage = medianFilterGrayscale(flippedImage, width, height, 7);
			output_file = "MEDIAN_FILTER_7.bmp";
			break;
		default:
			output_file = "output.bmp";
			break;
		}
												  // Draw final image on screen
		glDrawPixels(width, height, GL_LUMINANCE, GL_UNSIGNED_BYTE, finalImage /* manipulated image to display */);
		// Save the result
		int saveResult = SOIL_save_image(output_file,
			SOIL_SAVE_TYPE_BMP,
			width,
			height,
			numChannels,
			flipImageY(finalImage, width, height, numChannels)
		); // re-flip image before saving
		if (saveResult == 0) {
			std::cout << "Image save failed" << std::endl;
		}
		SOIL_free_image_data(flippedImage); // free memory
	}
	else {
		// CHECK THE IMAGE'S PATH!
		std::cout << "Image read failed" << std::endl;
	}
	glutSwapBuffers();
}

/****************************************************************/
/* Common OpenGL functions to open a window                     */
/****************************************************************/
void init(void)
{
	glClearColor(0, 0, 0, 1.0);
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);       // maps to window 0,0, width * height
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);    // set model transformation
	glLoadIdentity();
}

/* Setup Keyboard */
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:  /*  Escape Key  */
		exit(0);
		break;
	case '0':
		s_mode = DEFAULT;
		glutPostRedisplay();
		break;
	case '1':
		s_mode = CONTRAST_STRETCHING;
		glutPostRedisplay();
		break;
	case '2':
		s_mode = HISTOGRAM_EQUALIZATION;
		glutPostRedisplay();
		break;
	case '3':
		s_mode = GAUSSIAN_FILTER;
		glutPostRedisplay();
		break;
	case '4':
		s_mode = MEDIAN_FILTER_3;
		glutPostRedisplay();
		break;
	case '5':
		s_mode = MEDIAN_FILTER_7;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

/* Idle call back */
void idle()
{
	// We don't need to constantly update the screen; just show an static image
	//glutPostRedisplay();
}

/*  Main Loop
*  Open window with initial window size, title bar,
*  RGB display mode, and handle input events.
*/
int main(int argc, char** argv)
{
	glutInit(&argc, argv);   // not necessary unless on Unix
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(512, 512);
	glutCreateWindow(argv[0]);
	init();
	glutReshapeFunc(reshape);       // register respace (anytime window changes)
	glutKeyboardFunc(keyboard);     // register keyboard (anytime keypressed)                                        
	glutDisplayFunc(display);       // register display function
	glutIdleFunc(idle);             // reister idle function
	glutMainLoop();
	return 0;
}
