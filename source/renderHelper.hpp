const float PI = 3.141592653;

void drawBox(GLuint skybox[], GLfloat size) {
  static GLfloat n[6][3] =
  {
    {-1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, -1.0}
  };
  static GLint faces[6][4] =
  {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {5, 6, 2, 1},
    {7, 4, 0, 3}
  };
  GLfloat v[8][3];
  GLint i;

  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

  for (i = 5; i >= 0; i--) {
  	glBindTexture(GL_TEXTURE_2D, skybox[i]);
    glBegin(GL_QUADS);
    glNormal3fv(&n[i][0]);
    glVertex3fv(&v[faces[i][0]][0]);
    glVertex3fv(&v[faces[i][1]][0]);
    glVertex3fv(&v[faces[i][2]][0]);
    glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
  }
}

GLuint LoadTexture(sf::String name) {
	sf::Image image;
	if (!image.loadFromFile(name))
//        	printf("Error loading texture:%s\n", name);
		return EXIT_FAILURE;

	image.flipVertically();

	GLuint texture=0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return texture;
}

void createBox(GLuint skybox[], float size, bool l, bool r, bool f, bool b, bool t, bool bt) {
//	l = r = f = b = t = bt = 1;
	if(f) {
		glBindTexture(GL_TEXTURE_2D, skybox[0]);
		glBegin(GL_QUADS);
		//front
		glTexCoord2f(0, 0);
		glVertex3f(-size, -size, -size);
		glTexCoord2f(1, 0);
		glVertex3f(size,  -size, -size);
		glTexCoord2f(1, 1);
		glVertex3f( size,  size, -size);
		glTexCoord2f(0, 1);
		glVertex3f( -size, size, -size);
		glEnd();
	}

	if(b) {
		glBindTexture(GL_TEXTURE_2D, skybox[1]);
		glBegin(GL_QUADS);
		//back
		glTexCoord2f(0, 0);
		glVertex3f(size, -size, size);
		glTexCoord2f(1, 0);
		glVertex3f(-size,  -size, size);
		glTexCoord2f(1, 1);
		glVertex3f( -size,  size, size);
		glTexCoord2f(0, 1);
		glVertex3f( size, size, size);
		glEnd();
	}

	if(l) {
		glBindTexture(GL_TEXTURE_2D, skybox[2]);
		glBegin(GL_QUADS);
		//left
		glTexCoord2f(0, 0);
		glVertex3f(-size, -size,  size);
		glTexCoord2f(1, 0);
		glVertex3f(-size, -size, -size);
		glTexCoord2f(1, 1);
		glVertex3f(-size,  size, -size);
		glTexCoord2f(0, 1);
		glVertex3f(-size,  size,  size);
		glEnd();
	}

	if(r) {
		glBindTexture(GL_TEXTURE_2D, skybox[3]);
		glBegin(GL_QUADS);
		//right
		glTexCoord2f(0, 0);
		glVertex3f(size, -size, -size);
		glTexCoord2f(1, 0);
		glVertex3f(size,  -size, size);
		glTexCoord2f(1, 1);
		glVertex3f(size,  size,  size);
		glTexCoord2f(0, 1);
		glVertex3f(size, size,  -size);
		glEnd();
	}

	if(bt) {
		glBindTexture(GL_TEXTURE_2D, skybox[4]);
		glBegin(GL_QUADS);
		//bottom
		glTexCoord2f(0, 0);
		glVertex3f(-size, -size,  size);
		glTexCoord2f(1, 0);
		glVertex3f(size, -size, size);
		glTexCoord2f(1, 1);
		glVertex3f( size, -size, -size);
		glTexCoord2f(0, 1);
		glVertex3f( -size, -size,  -size);
		glEnd();
	}

	if(t) {
		glBindTexture(GL_TEXTURE_2D, skybox[5]);
		glBegin(GL_QUADS);
		//top
		glTexCoord2f(0, 0);
		glVertex3f(-size, size,  -size);
		glTexCoord2f(1, 0);
		glVertex3f(size, size, -size);
		glTexCoord2f(1, 1);
		glVertex3f( size, size, size);
		glTexCoord2f(0, 1);
		glVertex3f( -size, size,  size);
		glEnd();
	}
}

