#include "include.hpp"

int main() {
	//init
	init();
	initGame();
    window.setFramerateLimit(1000);

	//terrain
//	for(int x=-CX; x<CX; x++)
//		for(int z=-CZ; z<CZ; z++) {
//			int c = 3;
//			for(int y=0; y<c; y++)
//				chunks.set(x, y, z, 1);
//		}

	//load
	loadAllRecourses();

	//main loop
	Clock clock;
	while (window.isOpen()) {
		//clock
		float time = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		time = time / 50;
		if (time > 3) time = 3;

		//process events
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();

			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))
				window.close();

			if (event.type == Event::MouseButtonPressed) {
				if (event.key.code == Mouse::Right) p.mRight = 1;
				if (event.key.code == Mouse::Left)  p.mLeft = 1;
			}
		}
		if(!invOp){
			p.keyboard(time);
			p.update(time);
		}
		
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		draw();
		if(invOp){
			ShowCursor(TRUE);
			p.inventory.draw();
		}else{
			ShowCursor(FALSE);
		}
		window.display();
	}
	return 0;
}
