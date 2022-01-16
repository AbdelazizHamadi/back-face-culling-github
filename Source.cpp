
#include "olcConsoleGameEngine.h"
using namespace std;



struct vec3d
{
	float x, y, z;
};

struct triangle
{
	vec3d p[3];
	int Id;
};


				// point 1			  // point 2		   //point 3	    //Id
triangle t1  = { 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f , 0 };
triangle t2  = { 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f , 1 };
triangle t3  = { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f , 2};
triangle t4  = { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f , 3};
triangle t5  = { 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f , 4};
triangle t6  = { 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f , 5};
triangle t7  = { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f , 6};
triangle t8  = { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f , 7};
triangle t9  = { 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f , 8};
triangle t10 = { 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f , 9};
triangle t11 = { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f , 10};
triangle t12 = { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f , 11};

struct mesh
{
	vector<triangle> tris;
};

struct mat4x4
{
	float m[4][4] = { 0 };
};

class olcEngine3D : public olcConsoleGameEngine
{
public:
	olcEngine3D()
	{
		m_sAppName = L"3D Demo";
	}


private:

	mesh meshCube;
	mat4x4 matProj;
	mesh meshCube2;


	vec3d vCamera;

	float fTheta;
	float ftheta2;

	void MultiplyMatrixVector(vec3d &i, vec3d &o, mat4x4 &m)
	{
		o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
		o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
		o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
		float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

		if (w != 0.0f)
		{
			o.x /= w; o.y /= w; o.z /= w;
		}
	}

	

public:

	bool OnUserCreate() override
	{

		meshCube.tris = {
		// SOUTH	
		t1,t2,
		// EAST                                                      
		t3,t4,
		// NORTH                                                     
		t5,t6,
		// WEST                                                      
		t7,t8,
		// TOP                                                       
		t9,t10,
		// BOTTOM                                                    
		t11,t12,
		};

		meshCube2.tris = {

			// SOUTH
			t1,t2,

			// EAST                                                      
			t3,t4,

			// NORTH                                                     
			t5,t6,

			// WEST                                                      
			t7,t8,

			// TOP                                                       
			t9,t10,

			// BOTTOM                                                    
			t11,t12,

		};

		// Projection Matrix
		float fNear = 0.1f;
		float fFar = 1000.0f;
		float fFov = 90.0f;
		float fAspectRatio = (float)ScreenHeight() / (float)ScreenWidth();
		float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

		matProj.m[0][0] = fAspectRatio * fFovRad;
		matProj.m[1][1] = fFovRad;
		matProj.m[2][2] = fFar / (fFar - fNear);
		matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
		matProj.m[2][3] = 1.0f;
		matProj.m[3][3] = 0.0f;

		

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Clear Screen
		Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

		// Set up rotation matrices
		mat4x4 matRotZ, matRotX;
		fTheta += 1.0f * fElapsedTime;
		
		//fTheta = 1.0f;

		// Rotation Z 1 
		matRotZ.m[0][0] = cosf(fTheta);
		matRotZ.m[0][1] = sinf(fTheta);
		matRotZ.m[1][0] = -sinf(fTheta);
		matRotZ.m[1][1] = cosf(fTheta);
		matRotZ.m[2][2] = 1;
		matRotZ.m[3][3] = 1;

		// Rotation X 1 
		matRotX.m[0][0] = 1;
		matRotX.m[1][1] = cosf(fTheta * 0.5f);
		matRotX.m[1][2] = sinf(fTheta * 0.5f);
		matRotX.m[2][1] = -sinf(fTheta * 0.5f);
		matRotX.m[2][2] = cosf(fTheta * 0.5f);
		matRotX.m[3][3] = 1;
		
		
		// Draw Triangles
		

		for (auto tri : meshCube.tris)
		{
		
			//triangle Clone = tri;
			//std :: vector<triangle>::iterator it = std ::find(meshCube.tris.begin(), meshCube.tris.end(), Clone);
			
			
		
			//triangle tri = t1;
			triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;

			// Rotate in Z-Axis
			MultiplyMatrixVector(tri.p[0], triRotatedZ.p[0], matRotZ);
			MultiplyMatrixVector(tri.p[1], triRotatedZ.p[1], matRotZ);
			MultiplyMatrixVector(tri.p[2], triRotatedZ.p[2], matRotZ);

			// Rotate in X-Axis
			MultiplyMatrixVector(triRotatedZ.p[0], triRotatedZX.p[0], matRotX);
			MultiplyMatrixVector(triRotatedZ.p[1], triRotatedZX.p[1], matRotX);
			MultiplyMatrixVector(triRotatedZ.p[2], triRotatedZX.p[2], matRotX);

			// Offset into the screen

			triTranslated = triRotatedZX;
			triTranslated.p[0].z = triRotatedZX.p[0].z + 4.0f;
			triTranslated.p[1].z = triRotatedZX.p[1].z + 4.0f;
			triTranslated.p[2].z = triRotatedZX.p[2].z + 4.0f;

			//offset x axis 
			triTranslated.p[0].x = triRotatedZX.p[0].x - 1.0f;
			triTranslated.p[1].x = triRotatedZX.p[1].x - 1.0f;
			triTranslated.p[2].x = triRotatedZX.p[2].x - 1.0f;
													   	


			vec3d normal, line1, line2;

			//calculating lines between triangle vertices for the cross product to get normal of a surface

			//calculate line one (between 0 and 1) aka line A
			line1.x = triTranslated.p[1].x - triTranslated.p[0].x;
			line1.y = triTranslated.p[1].y - triTranslated.p[0].y;
			line1.z = triTranslated.p[1].z - triTranslated.p[0].z;

			//calculate line one (between 0 and 2) aka Line B

			line2.x = triTranslated.p[2].x - triTranslated.p[0].x;
			line2.y = triTranslated.p[2].y - triTranslated.p[0].y;
			line2.z = triTranslated.p[2].z - triTranslated.p[0].z;
									  
			//caculating  Normal

			normal.x = line1.y * line2.z - line1.z * line2.y;
			normal.y = line1.z * line2.x - line1.x * line2.z;
			normal.z = line1.x * line2.y - line1.y * line2.x;

			float normalLength = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
			normal.x /= normalLength; normal.y /= normalLength; normal.z /= normalLength;


		
			float  dotProduct = normal.x * (triTranslated.p[0].x + vCamera.x) +
								normal.y * (triTranslated.p[0].y + vCamera.y) +
								normal.z * (triTranslated.p[0].z + vCamera.z);

		//if (dotProduct < 0.0f)

		//	{

		//		// Project triangles from 3D --> 2D
		//		MultiplyMatrixVector(triTranslated.p[0], triProjected.p[0], matProj);
		//		MultiplyMatrixVector(triTranslated.p[1], triProjected.p[1], matProj);
		//		MultiplyMatrixVector(triTranslated.p[2], triProjected.p[2], matProj);

		//		// Scale into view
		//		triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
		//		triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
		//		triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;
		//		triProjected.p[0].x *= 0.5f * (float)ScreenWidth();
		//		triProjected.p[0].y *= 0.5f * (float)ScreenHeight();
		//		triProjected.p[1].x *= 0.5f * (float)ScreenWidth();
		//		triProjected.p[1].y *= 0.5f * (float)ScreenHeight();
		//		triProjected.p[2].x *= 0.5f * (float)ScreenWidth();
		//		triProjected.p[2].y *= 0.5f * (float)ScreenHeight();

		//		// Rasterize triangle
		//	
		//		if (tri.Id == 0 || tri.Id == 1)
		//		{

		//			FillTriangle(triProjected.p[0].x, triProjected.p[0].y,
		//				triProjected.p[1].x, triProjected.p[1].y,
		//				triProjected.p[2].x, triProjected.p[2].y,
		//				PIXEL_SOLID, FG_CYAN);

		//		}
		//		
		//		if (tri.Id == 2 || tri.Id == 3) {

		//			FillTriangle(triProjected.p[0].x, triProjected.p[0].y,
		//				triProjected.p[1].x, triProjected.p[1].y,
		//				triProjected.p[2].x, triProjected.p[2].y,
		//				PIXEL_SOLID, FG_RED);

		//		}

		//		if (tri.Id == 4 || tri.Id == 5) {

		//			FillTriangle(triProjected.p[0].x, triProjected.p[0].y,
		//				triProjected.p[1].x, triProjected.p[1].y,
		//				triProjected.p[2].x, triProjected.p[2].y,
		//				PIXEL_SOLID, FG_GREEN);

		//		}

		//		if (tri.Id == 6 || tri.Id == 7) {

		//			FillTriangle(triProjected.p[0].x, triProjected.p[0].y,
		//				triProjected.p[1].x, triProjected.p[1].y,
		//				triProjected.p[2].x, triProjected.p[2].y,
		//				PIXEL_SOLID, FG_YELLOW);

		//		}

		//		if (tri.Id == 8 || tri.Id == 9) {

		//			FillTriangle(triProjected.p[0].x, triProjected.p[0].y,
		//				triProjected.p[1].x, triProjected.p[1].y,
		//				triProjected.p[2].x, triProjected.p[2].y,
		//				PIXEL_SOLID, FG_BLUE);

		//		}

		//		if (tri.Id == 10 || tri.Id == 11) {

		//			FillTriangle(triProjected.p[0].x, triProjected.p[0].y,
		//				triProjected.p[1].x, triProjected.p[1].y,
		//				triProjected.p[2].x, triProjected.p[2].y,
		//				PIXEL_SOLID, FG_WHITE);

		//		}
		//							
		//	
		//	}

				
		}
		
		for (auto tri : meshCube2.tris)
		{

			//triangle Clone = tri;
			//std :: vector<triangle>::iterator it = std ::find(meshCube.tris.begin(), meshCube.tris.end(), Clone);



			//triangle tri = t1;
			triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;

			// Rotate in Z-Axis
			MultiplyMatrixVector(tri.p[0], triRotatedZ.p[0], matRotZ);
			MultiplyMatrixVector(tri.p[1], triRotatedZ.p[1], matRotZ);
			MultiplyMatrixVector(tri.p[2], triRotatedZ.p[2], matRotZ);

			// Rotate in X-Axis
			MultiplyMatrixVector(triRotatedZ.p[0], triRotatedZX.p[0], matRotX);
			MultiplyMatrixVector(triRotatedZ.p[1], triRotatedZX.p[1], matRotX);
			MultiplyMatrixVector(triRotatedZ.p[2], triRotatedZX.p[2], matRotX);

			// Offset into the screen
			triTranslated = triRotatedZX;
			triTranslated.p[0].z = triRotatedZX.p[0].z + 4.0;
			triTranslated.p[1].z = triRotatedZX.p[1].z + 4.0;
			triTranslated.p[2].z = triRotatedZX.p[2].z + 4.0;

			//offset x axis 

			triTranslated.p[0].x = triRotatedZX.p[0].x + 2.0;
			triTranslated.p[1].x = triRotatedZX.p[1].x + 2.0;
			triTranslated.p[2].x = triRotatedZX.p[2].x + 2.0;


			vec3d normal, line1, line2;
			//calculating line0 between triangle vertices for the cross product to get normal of a surface

			//calculate line one (between 0 and 1) aka line A
			line1.x = triTranslated.p[1].x - triTranslated.p[0].x;
			line1.y = triTranslated.p[1].y - triTranslated.p[0].y;
			line1.z = triTranslated.p[1].z - triTranslated.p[0].z;

			//calculate line one (between 0 and 2) aka Line B

			line2.x = triTranslated.p[2].x - triTranslated.p[0].x;
			line2.y = triTranslated.p[2].y - triTranslated.p[0].y;
			line2.z = triTranslated.p[2].z - triTranslated.p[0].z;

			//caculating  Normal

			normal.x = line1.y * line2.z - line1.z * line2.y;
			normal.y = line1.z * line2.x - line1.x * line2.z;
			normal.z = line1.x * line2.y - line1.y * line2.x;

			float normalLength = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
			normal.x /= normalLength; normal.y /= normalLength; normal.z /= normalLength;



			float  dotProduct = normal.x * (triTranslated.p[0].x + vCamera.x) +
				normal.y * (triTranslated.p[0].y + vCamera.y) +
				normal.z * (triTranslated.p[0].z + vCamera.z);

			if (dotProduct > 0.0f)
			{

				// Project triangles from 3D --> 2D
				MultiplyMatrixVector(triTranslated.p[0], triProjected.p[0], matProj);
				MultiplyMatrixVector(triTranslated.p[1], triProjected.p[1], matProj);
				MultiplyMatrixVector(triTranslated.p[2], triProjected.p[2], matProj);

				// Scale into view
				triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
				triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
				triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;
				triProjected.p[0].x *= 0.5f * (float)ScreenWidth();
				triProjected.p[0].y *= 0.5f * (float)ScreenHeight();
				triProjected.p[1].x *= 0.5f * (float)ScreenWidth();
				triProjected.p[1].y *= 0.5f * (float)ScreenHeight();
				triProjected.p[2].x *= 0.5f * (float)ScreenWidth();
				triProjected.p[2].y *= 0.5f * (float)ScreenHeight();

				// Rasterize triangle

				if (tri.Id == 0 || tri.Id == 1)
				{

					FillTriangle(triProjected.p[0].x, triProjected.p[0].y,
						triProjected.p[1].x, triProjected.p[1].y,
						triProjected.p[2].x, triProjected.p[2].y,
						PIXEL_SOLID, FG_CYAN);

				}

				if (tri.Id == 2 || tri.Id == 3) {

					FillTriangle(triProjected.p[0].x, triProjected.p[0].y,
						triProjected.p[1].x, triProjected.p[1].y,
						triProjected.p[2].x, triProjected.p[2].y,
						PIXEL_SOLID, FG_RED);

				}

				if (tri.Id == 4 || tri.Id == 5) {

					FillTriangle(triProjected.p[0].x, triProjected.p[0].y,
						triProjected.p[1].x, triProjected.p[1].y,
						triProjected.p[2].x, triProjected.p[2].y,
						PIXEL_SOLID, FG_GREEN);

				}

				if (tri.Id == 6 || tri.Id == 7) {

					FillTriangle(triProjected.p[0].x, triProjected.p[0].y,
						triProjected.p[1].x, triProjected.p[1].y,
						triProjected.p[2].x, triProjected.p[2].y,
						PIXEL_SOLID, FG_YELLOW);

				}

				if (tri.Id == 8 || tri.Id == 9) {

					FillTriangle(triProjected.p[0].x, triProjected.p[0].y,
						triProjected.p[1].x, triProjected.p[1].y,
						triProjected.p[2].x, triProjected.p[2].y,
						PIXEL_SOLID, FG_BLUE);

				}

				if (tri.Id == 10 || tri.Id == 11) {

					FillTriangle(triProjected.p[0].x, triProjected.p[0].y,
						triProjected.p[1].x, triProjected.p[1].y,
						triProjected.p[2].x, triProjected.p[2].y,
						PIXEL_SOLID, FG_WHITE);

				}


			}


		}

		return true;
	}

};




int main()
{
	olcEngine3D demo;
	if (demo.ConstructConsole(200, 160, 4, 4))
		demo.Start();
    return 0;
}
