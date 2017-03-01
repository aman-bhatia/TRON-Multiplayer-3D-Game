/**
 * \class objloader
 */


#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>
 

struct coordinate{
	float x,y,z;
	coordinate(float a,float b,float c);
};
 
///for faces, it can contain triangles and quads as well, the four variable contain which is that
struct face{
	int facenum;
	bool four;
	int faces[4];
	face(int facen,int f1,int f2,int f3);

	face(int facen,int f1,int f2,int f3,int f4);
};

///the main class for the object loader
class objloader{
	public:
		///Constructor of the object loader class
		objloader();
		///the main model load function
		int load(const char* filename);
		///Deletes the temporary vertices and faces vectors
		void clean();
	private:
		std::vector<std::string*> coord;       ///< read every single line of the obj file as a string
		std::vector<coordinate*> vertex;
		std::vector<face*> faces;
		std::vector<coordinate*> normals;       ///< normal vectors for every face
};

#endif
