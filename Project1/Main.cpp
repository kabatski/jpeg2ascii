#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include <fstream>

//symbols array to choose from
const char* symbols = "@%#*+=:.";


double containswhite(int x, int y, int dimension,sf::Image picture) {
	double avgsum = 0;
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension ; j++) {
			sf::Color pixel = picture.getPixel(x + j, y + i);
			avgsum += (((double)pixel.r + pixel.g + pixel.b) / 3);
		}
	}
	return (avgsum/(dimension*dimension));
}

int main() {
	int blocksize;
	std::cout << "Enter image to convert" << std::endl;
	std::string image;
	std::cin >> image;
	sf::Image testPic = sf::Image();

	if (testPic.loadFromFile(image)) {
		std::cout << "file opened succesfully" << std::endl;
	}
	else {
		std::cout << "file opened unsuccesfully :(" << std::endl;
		return 0;
	}

	std::cout << "Give pixel dimension for each ascii character" << std::endl;
	std::cin >> blocksize;

	sf::Vector2u size = testPic.getSize();
	std::ofstream outfile("blank.txt");
	std::cout << "converting..." << std::endl;

	for (int i = 0; i < size.y; i+=blocksize) {
		for (int j = 0; j < size.x; j+=blocksize) {
			if (i + blocksize > size.y || j + blocksize > size.x) {
				continue;
			}
			double val = containswhite(j, i, blocksize, testPic);

			outfile << symbols[(int)(val / 25.5)];
		}
		outfile << std::endl;
	}

	std::cout << "all done!" << std::endl;
	return 0;
}