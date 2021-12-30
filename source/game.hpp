#include "chunk.hpp"
Chunks chunks;

float angleX, angleY;
struct Slot {
	uint8_t item;
	uint8_t count;
};

class Inventory {
	public:
		Slot slots[27];
		Slot hotbar[9];
		Slot brona[4];
		Slot craftingSlots[4];
		void add(uint8_t item) {
			for(int i = 0; i < 9; i++) {
				if(hotbar[i].item == item || hotbar[i].item == AIR) {
					hotbar[i].item = item;
					hotbar[i].count++;
					return;
				}
			}

			for(int i = 0; i < 27; i++) {
				if(slots[i].item == item || slots[i].item == AIR) {
					slots[i].item = item;
					slots[i].count++;
					return;
				}
			}
		}
		void update(){
			for(int i = 0; i < 9; i++) {
				if(hotbar[i].count == 0) {
					hotbar[i].item = AIR;
					return;
				}
			}

			for(int i = 0; i < 27; i++) {
				if(slots[i].count == 0) {
					slots[i].item = AIR;
					return;
				}
			}
			
			for(int i = 0; i < 4; i++) {
				if(brona[i].count == 0) {
					brona[i].item = AIR;
					return;
				}
			}
			
			for(int i = 0; i < 4; i++) {
				if(craftingSlots[i].count == 0) {
					craftingSlots[i].item = AIR;
					return;
				}
			}
			if(craftingSlots[0].item == WOOD){
				craftingSlots[0].count--;
				add(PLANKS);
			}
		}
		
		void draw(){
			int is = 10;
			Sprite invS(inv);
			invS.setScale(xs / inv.getSize().x, ys / inv.getSize().y);
			invS.setPosition(xs / 2 - inv.getSize().x / 2 * invS.getScale().x, ys / 2 - inv.getSize().y / 2 * invS.getScale().y);
			window.pushGLStates();
			window.draw(invS);
			for(int i = 0; i < 27; i++) {
				if(slots[i].count != 0) {
					Sprite it(items[slots[i].item]);
					it.setPosition(invS.getPosition().x + is * (i % 10), invS.getPosition().y + is * (i / 10));
					it.setScale(invS.getScale());
					window.draw(it);
					return;
				}
			}
			for(int i = 0; i < 9; i++) {
				if(hotbar[i].count != 0) {
					Sprite it(items[hotbar[i].item]);
					it.setPosition(invS.getPosition().x + is * i, invS.getPosition().y + is * 4);
					it.setScale(invS.getScale());
					window.draw(it);
					return;
				}
			}
			window.popGLStates();
			if (Keyboard::isKeyPressed(Keyboard::E)) {
				invOp = false;
				ShowCursor(FALSE);
				sleep(milliseconds(200));
			}
		}
};

class Player {
	public:
		Inventory inventory;
		float x,y,z;
		float dx,dy,dz;
		float w,h,d;  // width, height, depth
		bool onGround;
		float speed;
		bool mLeft=0,mRight=0; // mouse buttons
		uint8_t selected;

		Player(float x0, float y0, float z0) {
			x=x0;
			y=y0;
			z=z0;
			dx=0;
			dy=0;
			dz=0;
			w = size / 2;
			h = size + 5;
			d = size / 2;
			speed=5;
			onGround=true;
		}

		void update(float time) {
			chunks.generate(x / size, z / size, false, 12345);
			if (!onGround) dy-= 1.5 * time;
			onGround = 0;

			x+=dx * time;
			collision(dx,0,0);
			y+=dy * time;
			collision(0,dy,0);
			z+=dz * time;
			collision(0,0,dz);

			dx=dz=0;

			POINT mousexy;
			GetCursorPos(&mousexy);
			int xt = window.getPosition().x + xs / 1;
			int yt = window.getPosition().y + ys / 2;

			angleX += (xt - mousexy.x) / 4; //4 — sensivity
			angleY += (yt - mousexy.y) / 4;

			if (angleY<-89.0) {
				angleY=-89.0;
			}
			if (angleY>89.0) {
				angleY=89.0;
			}
	
			inventory.update();

			SetCursorPos(xt,yt);

			if (mRight || mLeft) {
				float x = x;
				float y = y + h/2;
				float z = z;

				int X,Y,Z,oldX,oldY,oldZ;
				int dist=0;
				while(dist < 120) { // ?????? ????????
					dist++;

					x += -sin(angleX/180*PI);
					X= x / size;
					y +=  tan(angleY/180*PI);
					Y=y/size;
					z += -cos(angleX/180*PI);
					Z=z/size;

					if (chunks.check(X,Y,Z)) {
						if (mLeft) {
							inventory.add(chunks.set(X, Y, Z, AIR));
							break;
						} else {
							if(inventory.hotbar[selected].count > 0) {
								chunks.set(oldX, oldY, oldZ, inventory.hotbar[selected].item);
								inventory.hotbar[selected].count--;
								cout << "Placed : " << inventory.hotbar[selected].item << "\n";
							}
							break;
						}
					}
					oldX=X;
					oldY=Y;
					oldZ=Z;
				}
			}
			mLeft=mRight=0;

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(x, y + h / 2, z,
			          x - sin( angleX / 180 * PI), y + h / 2 + (tan(angleY / 180 * PI)), z - cos(angleX / 180 * PI),
			          0, 1, 0);
		}

		void collision(float Dx,float Dy,float Dz) {
			for (int X=(x-w)/size; X<(x+w)/size; X++)
				for (int Y=(y-h)/size; Y<(y+h)/size; Y++)
					for (int Z=(z-d)/size; Z<(z+d)/size; Z++)
						if (chunks.check(X,Y,Z) != AIR && chunks.check(X,Y,Z) != WATER && chunks.check(X,Y,Z) != LAVA && chunks.check(X,Y,Z) != CLOUD)  {
							if (Dx>0)  x = X*size-w;
							if (Dx<0)  x = X*size+size+w;
							if (Dy>0)  y = Y*size-h;
							if (Dy<0) {
								y = Y*size+size+h;
								onGround=true;
								dy=0;
							}
							if (Dz>0)  z = Z*size-d;
							if (Dz<0)  z = Z*size+size+d;
						}
		}

		void keyboard(float time) {
			mLeft = Mouse::isButtonPressed(Mouse::Left);
			mRight = Mouse::isButtonPressed(Mouse::Right);
			if (Keyboard::isKeyPressed(Keyboard::Space))
				if (onGround) {
					onGround=false;
					dy += speed * time;
				}

			if (Keyboard::isKeyPressed(Keyboard::W)) {
				dx =- sin(angleX/180*PI) * speed;
				dz =- cos(angleX/180*PI) * speed;
			}

			if (Keyboard::isKeyPressed(Keyboard::S)) {
				dx = sin(angleX/180*PI) * speed;
				dz = cos(angleX/180*PI) * speed;
			}

			if (Keyboard::isKeyPressed(Keyboard::D)) {
				dx = sin((angleX+90)/180*PI) * speed;
				dz = cos((angleX+90)/180*PI) * speed;
			}

			if (Keyboard::isKeyPressed(Keyboard::A)) {
				dx = sin((angleX-90)/180*PI) * speed;
				dz = cos((angleX-90)/180*PI) * speed;
			}

			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				if(onGround)
					dy += speed * 32;
			}
			
			if (Keyboard::isKeyPressed(Keyboard::E)) {
				invOp = true;
				sleep(milliseconds(200));
			}
		}

};

Player p(30, 15 * size, 30);

void tp(int x1, int y1, int z1) {
	p.x = x1;
	p.y = y1;
	p.z = z1;
}

void initGame() {
	chunks.generate(0, 0, true, 12345);
}
