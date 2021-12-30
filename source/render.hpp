void renderScene() {
	Sprite cursor(tc);
	cursor.setOrigin(8,8);
	cursor.setPosition(xs / 2, ys / 2);

	glTranslatef(p.x, p.y, p.z);
	createBox(skybox, 500, 1, 1, 1, 1, 1, 1);
	glTranslatef(-p.x, -p.y, -p.z);
	
	int R = 4; // 4 blocks render distance

	int X = p.x / size;
	int Y = p.y / size;
	int Z = p.z / size;

	for(int x = X - R; x < X + R; x++)
		for(int y = Y - R; y < Y + R; y++)
			for(int z = Z - R; z < Z + R; z++) {
				if (chunks.check(x, y, z) == AIR) continue;
				glTranslatef( size * x + size / 2, size * y + size / 2, size * z + size / 2);
//				createBox(box[0], size / 2,
//				chunks.check(x, y, z - 1) != AIR, chunks.check(x, y, z + 1) != AIR,
//				chunks.check(x - 1, y, z) != AIR, chunks.check(x + 1, y, z) != AIR,
//				chunks.check(x, y - 1, z) != AIR, chunks.check(x, y + 1, z) != AIR);
				drawBoxes(chunks.check(x, y, z));
				glTranslatef(-size * x - size / 2, -size * y - size / 2, -size * z - size / 2);
			}

	window.pushGLStates();
	window.draw(cursor);
	window.popGLStates();
}

void draw() {
	renderScene();
}
