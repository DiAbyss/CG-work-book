#include <CanvasTriangle.h>
#include <DrawingWindow.h>
#include <Utils.h>
#include <fstream>
#include <vector>
#include <iostream>


#define WIDTH 320
#define HEIGHT 240

void draw(DrawingWindow &window) {
	window.clearPixels();
	for (size_t y = 0; y < window.height; y++) {

		for (size_t x = 0; x < window.width; x++) {
			std::vector<float>gradient = interpolateSingleFloats(255,0,window.width);

			float  red = gradient[x];
			float green = gradient[x];
			float blue = gradient[x];
			uint32_t colour = (255 << 24) + (int(red) << 16) + (int(green) << 8) + int(blue);
			window.setPixelColour(x, y, colour);
		}
	}
}

void handleEvent(SDL_Event event, DrawingWindow &window) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_LEFT) std::cout << "LEFT" << std::endl;
		else if (event.key.keysym.sym == SDLK_RIGHT) std::cout << "RIGHT" << std::endl;
		else if (event.key.keysym.sym == SDLK_UP) std::cout << "UP" << std::endl;
		else if (event.key.keysym.sym == SDLK_DOWN) std::cout << "DOWN" << std::endl;
	} else if (event.type == SDL_MOUSEBUTTONDOWN) {
		window.savePPM("output.ppm");
		window.saveBMP("output.bmp");
	}
}

std::vector<float>interpolateSingleFloats(float from, float to, int numberOfValues) {
	float result = from ;

	std::vector<float>v;

	for (int i = 0; i < numberOfValues; i++) {
		result = (to - from) / (numberOfValues - 1) + result;
		v.push_back(result);
		
		return v ;
	}

}

int main(int argc, char *argv[]) {
	DrawingWindow window = DrawingWindow(WIDTH, HEIGHT, false);
	SDL_Event event;
	while (true) {
		// We MUST poll for events - otherwise the window will freeze !
		if (window.pollForInputEvents(event)) handleEvent(event, window);
		draw(window);
		// Need to render the frame at the end, or nothing actually gets shown on the screen !
		window.renderFrame();
	}
	std::vector<float> result;
	result = interpolateSingleFloats(2.2, 8.5, 7);
	for (size_t i = 0; i < result.size(); i++) std::cout << result[i] << " ";
	std::cout << std::endl;
}

