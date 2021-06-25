/* Code modified from http://www.lousodrome.net/opengl/ */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <SOIL.h>
#include <emscripten.h>
#include <iostream>
#include "fstream"
#include <vector>
#include <string>

using namespace std;


#define		SIZE	256

static int window_width = 500;
static int window_height = 500;


static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";


static inline bool is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}


std::string base64_decode(std::string const& encoded_string) {
    int in_len = encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;

    while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 4; j++)
            char_array_4[j] = 0;

        for (j = 0; j < 4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }

    return ret;
}

/*
** Just a textured cube
*/
void Cube(void) {
	glBegin(GL_QUADS);

 
	glTexCoord2i(0, 0); glVertex3f(-1, 1, 1);
	glTexCoord2i(0, 1); glVertex3f(-1, -1, 1);
	glTexCoord2i(1, 1); glVertex3f(1, -1, 1);
	glTexCoord2i(1, 0); glVertex3f(1, 1, 1);

	glEnd();
}

/*
** Function called to update rendering
*/
void DisplayFunc(void) {
	static float alpha = 20;

	glLoadIdentity();
	glTranslatef(0, 0, -10);
	

	/* Define a view-port adapted to the texture */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20, 1, 5, 15);
	glViewport(0, 0, SIZE, SIZE);
	glMatrixMode(GL_MODELVIEW);

	/* Render to buffer */
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Cube();
	glFlush();

	/* Render to screen */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20, window_width / (float)window_height, 5, 15);
	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Cube();

	/* End */
	glFlush();
	glutSwapBuffers();

	/* Update again and again */
	alpha = alpha + 0.1;
	glutPostRedisplay();
}

/*
** Function called when the window is created or resized
*/
void ReshapeFunc(int width, int height) {
	window_width = width;
	window_height = height;
	glutPostRedisplay();
}





EMSCRIPTEN_KEEPALIVE
void set_texture(const char* fileName) {
	string encoded_string = "";
	encoded_string = fileName;
	string decoded_string = base64_decode(encoded_string);
	
	GLubyte texels[decoded_string.length()+1];
	for(int i=0;i<decoded_string.length();i++){
		texels[i]= decoded_string[i];
	}
	
	ofstream outfile;
	outfile.open("test.png", ofstream::binary);

	string temp = decoded_string;

	outfile.write(temp.c_str(), temp.size());
	outfile.close();

	int texture_width, texture_height,nrChannels;
	
	unsigned char* texture = SOIL_load_image("test.png", &texture_width, &texture_height, 0, SOIL_LOAD_RGB);

	 
	 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 72, 72, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
}

int main(int argc, char **argv) {

	if (argc != 2) {
		printf("You should supply one and only one parameter: the initial texture image\n");
		return -1;
	}


	/* Creation of the window */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
	glutInitWindowSize(500, 500);
	glutCreateWindow("Render to texture");

	/* OpenGL settings */
	glEnable(GL_DEPTH_TEST);

	/* Texture setting */
	unsigned int texture_id;
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	/* Load and apply the texture */
	set_texture(argv[1]);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	/* Declaration of the callbacks */
	glutDisplayFunc(&DisplayFunc);



	/* Loop */
	glutMainLoop();

	/* Never reached */
	return 0;
}	

