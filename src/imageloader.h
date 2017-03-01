/**
 * \class ImageLoader
 */


#ifndef IMAGE_LOADER_H_INCLUDED
#define IMAGE_LOADER_H_INCLUDED
///Class used to load an image from memory
class Image {
	public:
		///Constructor to create
		Image(char* ps, int w, int h);
		///Destructor for the class
		~Image();
		char* pixels; ///< Character array used to store the pixels of the image
		int width;   ///< width of the image
		int height;  ///< height of the image
};
///Load a bmp image from a file
Image* loadBMP(const char* filename);
#endif
