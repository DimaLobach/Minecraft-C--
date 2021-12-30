#define AIR 0
#define GRASS 1
#define SAND 2
#define STONE 3
#define DIRT 4
#define WATER 5
#define LAVA 6
#define CLOUD 7
#define WOOD 8
#define LEAVES 9
#define PLANKS 10
//	//Fooliage
//	static const int FLOWER_RED = 500;
//	static const int FLOWER_YELLOW = 501;
//	static const int BIRCH = 502;

GLuint box[11][6];
Texture items[11];

void drawBoxes(uint8_t block){
	createBox(box[block], size / 2,
				1, 1,
				1, 1,
				1, 1);
	
//	glutSolidCube(size);
}

void loadBoxes(){
	box[GRASS][0] = LoadTexture("resources/blocks/grassBox/side.jpg");
	box[GRASS][1] = LoadTexture("resources/blocks/grassBox/side.jpg");
	box[GRASS][2] = LoadTexture("resources/blocks/grassBox/side.jpg");
	box[GRASS][3] = LoadTexture("resources/blocks/grassBox/side.jpg");
	box[GRASS][4] = LoadTexture("resources/blocks/grassBox/bottom.jpg");
	box[GRASS][5] = LoadTexture("resources/blocks/grassBox/top.jpg");
	items[GRASS].loadFromFile("resources/blocks/grassBox/it.png");
	
	box[DIRT][0] = LoadTexture("resources/blocks/dirt/dirt.jpg");
	box[DIRT][1] = LoadTexture("resources/blocks/dirt/dirt.jpg");
	box[DIRT][2] = LoadTexture("resources/blocks/dirt/dirt.jpg");
	box[DIRT][3] = LoadTexture("resources/blocks/dirt/dirt.jpg");
	box[DIRT][4] = LoadTexture("resources/blocks/dirt/dirt.jpg");
	box[DIRT][5] = LoadTexture("resources/blocks/dirt/dirt.jpg");
	
	box[STONE][0] = LoadTexture("resources/blocks/stone/stone.png");
	box[STONE][1] = LoadTexture("resources/blocks/stone/stone.png");
	box[STONE][2] = LoadTexture("resources/blocks/stone/stone.png");
	box[STONE][3] = LoadTexture("resources/blocks/stone/stone.png");
	box[STONE][4] = LoadTexture("resources/blocks/stone/stone.png");
	box[STONE][5] = LoadTexture("resources/blocks/stone/stone.png");
	
	box[SAND][0] = LoadTexture("resources/blocks/sand/sand.png");
	box[SAND][1] = LoadTexture("resources/blocks/sand/sand.png");
	box[SAND][2] = LoadTexture("resources/blocks/sand/sand.png");
	box[SAND][3] = LoadTexture("resources/blocks/sand/sand.png");
	box[SAND][4] = LoadTexture("resources/blocks/sand/sand.png");
	box[SAND][5] = LoadTexture("resources/blocks/sand/sand.png");
	
	box[WATER][0] = LoadTexture("resources/blocks/water/water.jpg");
	box[WATER][1] = LoadTexture("resources/blocks/water/water.jpg");
	box[WATER][2] = LoadTexture("resources/blocks/water/water.jpg");
	box[WATER][3] = LoadTexture("resources/blocks/water/water.jpg");
	box[WATER][4] = LoadTexture("resources/blocks/water/water.jpg");
	box[WATER][5] = LoadTexture("resources/blocks/water/water.jpg");
	
	box[WOOD][0] = LoadTexture("resources/blocks/wood/side.jpg");
	box[WOOD][1] = LoadTexture("resources/blocks/wood/side.jpg");
	box[WOOD][2] = LoadTexture("resources/blocks/wood/side.jpg");
	box[WOOD][3] = LoadTexture("resources/blocks/wood/side.jpg");
	box[WOOD][4] = LoadTexture("resources/blocks/wood/top.jpg");
	box[WOOD][5] = LoadTexture("resources/blocks/wood/top.jpg");
	
	box[LEAVES][0] = LoadTexture("resources/blocks/leaves/leaves.jpg");
	box[LEAVES][1] = LoadTexture("resources/blocks/leaves/leaves.jpg");
	box[LEAVES][2] = LoadTexture("resources/blocks/leaves/leaves.jpg");
	box[LEAVES][3] = LoadTexture("resources/blocks/leaves/leaves.jpg");
	box[LEAVES][4] = LoadTexture("resources/blocks/leaves/leaves.jpg");
	box[LEAVES][5] = LoadTexture("resources/blocks/leaves/leaves.jpg");
	
	box[PLANKS][0] = LoadTexture("resources/blocks/planks/planks.png");
	box[PLANKS][1] = LoadTexture("resources/blocks/planks/planks.png");
	box[PLANKS][2] = LoadTexture("resources/blocks/planks/planks.png");
	box[PLANKS][3] = LoadTexture("resources/blocks/planks/planks.png");
	box[PLANKS][4] = LoadTexture("resources/blocks/planks/planks.png");
	box[PLANKS][5] = LoadTexture("resources/blocks/planks/planks.png");
}
