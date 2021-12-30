GLuint skybox[6];
Texture inv;
Texture tc;

void loadAllRecourses() {
	skybox[0] = LoadTexture("resources/skybox/skybox_front.bmp");
	skybox[1] = LoadTexture("resources/skybox/skybox_back.bmp");
	skybox[2] = LoadTexture("resources/skybox/skybox_left.bmp");
	skybox[3] = LoadTexture("resources/skybox/skybox_right.bmp");
	skybox[4] = LoadTexture("resources/skybox/skybox_bottom.bmp");
	skybox[5] = LoadTexture("resources/skybox/skybox_top.bmp");

	loadBoxes();
	tc.loadFromFile("resources/cursor.png");
	inv.loadFromFile("resources/inventory.png");
}
