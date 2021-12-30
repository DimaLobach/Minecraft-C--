#define WATER_LEVEL 0
#define CLOUD_LEVEL CY - 3
#define SIZE_GEN 16

#define CX 600
#define CY 256
#define CZ 600
//#define CX 16
//#define CY 16
//#define CZ 16
//
//struct chunk {
//	uint8_t blk[CX][CY][CZ];
//
//	uint8_t get(int x, int y, int z) {
//		return blk[x][y][z];
//	}
//
//	void set(int x, int y, int z, uint8_t type) {
//		blk[x][y][z] = type;
//	}
//
//	String getSave() {
//		String r;
//		for(int i = 0;i < CX;i++)
//			for(int j = 0;j < CY;j++)
//				for(int k = 0;k < CZ;k++)
//					r += get(i, j, k) + 'a';
//		return r;
//	}
//
//	void load(int x, int z) {
//		FILE f = fopen
//	}
//};

struct chunk {
	uint8_t c[CX * 2][CY * 2][CZ * 2];
};

class Chunks {
	public:
		bool superflat = false;
		uint8_t c[CX * 2][CY * 2][CZ * 2];
		double n[SIZE_GEN * 4][SIZE_GEN * 4];
		double nc[SIZE_GEN * 4][SIZE_GEN * 4];
		
		uint8_t check(int x, int y, int z) {
			if ((x < -CX + 1) || (x>CX) ||
			        (y<-CY + 1) || (y>CY) ||
			        (z<-CZ + 1) || (z > CZ)) return 0;
			return c[x + CX][y + CY][z + CZ];
		}

		uint8_t set(int x, int y, int z, uint8_t block) {
			if ((x < -CX) || (x>=CX) ||
			        (y<-CY) || (y>=CY) ||
			        (z<-CZ) || (z>=CZ)) return 0;
			        uint8_t blockP = c[x + CX][y + CY][z + CZ];
			c[x + CX][y + CY][z + CZ] = block;
			return blockP;
		}

		bool Generated(int x1, int z1) {
			for(int y = 0; y < CY * 2; y++) {
				if(c[x1 + CX][y][z1 + CZ] != AIR)	return true;
			}
			return false;
		}

		void generate(int x, int z, bool big = false, int seed = rand()) {
			genNoise(seed, big);
			for (int x1 = x - SIZE_GEN * (big ? 1 : 2); x1 < SIZE_GEN * (big? 1 : 2) + z; x1++) {
				for (int z1 = z - SIZE_GEN * (big? 1 : 2); z1 < SIZE_GEN * (big? 1 : 2) + z; z1++) {
					if(Generated(x1, z1)) continue;
					if(!superflat) {
						int terrain = noise(x1, z1);

						if(x1 == 0 && z1 == 0){
							tp(0, terrain + 1, 0);
						}
						
						for (int y = -CY + 1; y < CY; y++) {
							int h = y;

							//Generate terrain
							set(x1, y, z1, getBlock(h, terrain));

							//Generate clouds
							if (h == CLOUD_LEVEL) {
								int cloud = noisec(x1, z1) * 2;

								if (cloud > CLOUD_LEVEL) {
									set(x1, y, z1, CLOUD);
								}
							}
						}
						if(check(x1, terrain, z1) == GRASS &&
							check(x1, terrain + 1, z1) == AIR &&
							check(x1, terrain + 2, z1) == AIR &&
							check(x1, terrain + 3, z1) == AIR){
							if(rand() % 81 == 1){
								tree(x1, z1, 3);
							}
						}
					} else {
						//superflat
						
						if(x1 == 0 && z1 == 0){
							tp(0, 4, 0);
						}
						
						set(x1, -2, z1, GRASS);
						set(x1, -1, z1, GRASS);
						set(x1, 0, z1, GRASS);
						set(x1, 1, z1, GRASS);
						set(x1, 2, z1, GRASS);
						set(x1, 3, z1, GRASS);
						if(x1 == 0){
							set(x1, 4, z1, STONE);
						}
						if(z1 == 0){
							set(x1, 4, z1, STONE);
						}
						if(z1 == 0 && x1 == 0){
							set(x1, 5, z1, STONE);
						}
						if(z1 == 1 && x1 == 0){
							set(x1, 5, z1, STONE);
						}
						if(z1 == -1 && x1 == 0){
							set(x1, 5, z1, STONE);
						}
						if(z1 == 0 && x1 == 1){
							set(x1, 5, z1, STONE);
						}
						if(z1 == 0 && x1 == -1){
							set(x1, 5, z1, STONE);
						}
						
						if(check(x1, 3, z1) == GRASS &&
							check(x1, 4, z1) == AIR &&
							check(x1, 5, z1) == AIR &&
							check(x1, 6, z1) == AIR){
							if(rand() % 81 == 1){
								tree(x1, z1, 3);
							}
						}
					}
				}
			}
		}
		
		int noise(int x, int y){
			return n[x][y];
		}
		
		int noisec(int x, int y){
			return nc[x][y];
		}
		
		double turbulence(double x, double y, double size, bool big)
		{
			double value = 0.0, initialSize = size;
			
			while(size >= 1)
			{
				value += smoothNoise(x / size, y / size, big) * size;
				size /= 2.0;
			}
			
			return(1.5 * value / initialSize);
		}
				
		genNoise(int seed, bool big){
			for (int x = 0; x < SIZE_GEN * (big ? 2 : 4); x++) {
				for (int y = 0; y < SIZE_GEN * (big ? 2 : 4); y++) {
					n[x][y] = Noise(x, y, seed);
					nc[x][y] = Noise(x, y, seed * 2);
				}
			}
			for (int x = 0; x < SIZE_GEN * (big ? 2 : 4); x++) {
				for (int y = 0; y < SIZE_GEN * (big ? 2 : 4); y++) {
					n[x][y] = turbulence(x, y, 256, big);
					nc[x][y] = turbulence(x, y, 256, big);
				}
			}
		}
		
		void tree(int x, int z, int terrain){
			set(x, terrain + 1, z, WOOD);
			set(x, terrain + 2, z, WOOD);
			set(x, terrain + 3, z, WOOD);
			set(x, terrain + 4, z, WOOD);
			set(x, terrain + 5, z, LEAVES);
			set(x, terrain + 5, z + 1, LEAVES);
			set(x, terrain + 5, z - 1, LEAVES);
			set(x + 1, terrain + 5, z, LEAVES);
			set(x - 1, terrain + 5, z, LEAVES);
			
			set(x - 1, terrain + 4, z - 1, LEAVES);
			set(x - 1, terrain + 4, z    , LEAVES);
			set(x - 1, terrain + 4, z + 1, LEAVES);
			set(x + 1, terrain + 4, z - 1, LEAVES);
			set(x + 1, terrain + 4, z    , LEAVES);
			set(x + 1, terrain + 4, z + 1, LEAVES);
			set(x    , terrain + 4, z + 1, LEAVES);
			set(x    , terrain + 4, z - 1, LEAVES);
		}
		
		double Noise(int x, int y, int seed){
			srand(seed * x + y);
			return (rand() % 100) / 100.0;
		}
		
		
		double smoothNoise(double x, double y, bool big)
		{
			//get fractional part of x and y
			double fractX = x - int(x);
			double fractY = y - int(y);
			
			//wrap around
			int x1 = (int(x) + SIZE_GEN * (big ? 2 : 4)) % SIZE_GEN * (big ? 2 : 4);
			int y1 = (int(y) + SIZE_GEN * (big ? 2 : 4)) % SIZE_GEN * (big ? 2 : 4);
			
			//neighbor values
			int x2 = (x1 + SIZE_GEN * (big ? 2 : 4) - 1) % SIZE_GEN * (big ? 2 : 4);
			int y2 = (y1 + SIZE_GEN * (big ? 2 : 4) - 1) % SIZE_GEN * (big ? 2 : 4);
			
			//smooth the noise with bilinear interpolation
			double value = 0.0;
			value += fractX     * fractY     * n[y1][x1];
			value += (1 - fractX) * fractY     * n[y1][x2];
			value += fractX     * (1 - fractY) * n[y2][x1];
			value += (1 - fractX) * (1 - fractY) * n[y2][x2];
			
			return value;
		}
		
		double smoothNoisec(double x, double y, bool big)
		{
			//get fractional part of x and y
			double fractX = x - int(x);
			double fractY = y - int(y);
			
			//wrap around
			int x1 = (int(x) + SIZE_GEN * (big ? 2 : 4)) % SIZE_GEN * (big ? 2 : 4);
			int y1 = (int(y) + SIZE_GEN * (big ? 2 : 4)) % SIZE_GEN * (big ? 2 : 4);
			
			//neighbor values
			int x2 = (x1 + SIZE_GEN * (big ? 2 : 4) - 1) % SIZE_GEN * (big ? 2 : 4);
			int y2 = (y1 + SIZE_GEN * (big ? 2 : 4) - 1) % SIZE_GEN * (big ? 2 : 4);
			
			//smooth the noise with bilinear interpolation
			double value = 0.0;
			value += fractX     * fractY     * nc[y1][x1];
			value += (1 - fractX) * fractY     * nc[y1][x2];
			value += fractX     * (1 - fractY) * nc[y2][x1];
			value += (1 - fractX) * (1 - fractY) * nc[y2][x2];
			
			return value;
		}
		
		int getBlock(int z, int height) {
			//Above water level
			if (z > WATER_LEVEL) {
				if (z > height) {
					return AIR;
				}
				if (z == height) {
					return GRASS;
				}
				if (z > height - 7) {
					return DIRT;
				}
			}
			//Under water
			else {
				if (z > height + 5) {
					return WATER;
				}
				if (z > height - 5) {
					return SAND;
				}
				if (z > height - 10) {
					return DIRT;
				}
			}
			return STONE;
		}
};
