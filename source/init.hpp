#define GL_CLAMP_TO_EDGE 0x812F
float xs = 400;
float ys = 300;
float size = 20.f;
RenderWindow window(VideoMode(xs, ys), "Minecraft 1.18");
void tp(int x, int y, int z);
typedef unsigned char uint8_t;
bool invOp = false;

void init() {
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
	glClearDepth(1.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.f, 1.f, 1.f, 1000.f);// 100.f - RenderDistance
	glEnable(GL_TEXTURE_2D);
//	initl();
}

