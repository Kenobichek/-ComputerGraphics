# ComputerGraphics
lab1


Familiarize yourself with the capabilities of OpenGL, with the principles of building a two-dimensional coordinate system. Using the selected graphics library, draw a creature based on primitives. Using the library that is responsible for the system level of input-output operations - to implement the movement of the creature. Control keys - ADWS

![image](https://user-images.githubusercontent.com/76412011/204275390-aec2280d-a463-41a9-b413-dc6468e6203e.png)


lab2
1) Get acquainted with the principles of building a three-dimensional coordinate system.
2) Build a scene consisting of three objects: two basic shapes and a plane. We believe that the center of the plane coincides with the center of the scene, and the figures are located at an equal distance on both sides of it.
2.1) In accordance with your option, display basic library objects on the screen in the form of a frame and in the form of a solid object. Set two different fill colors.
2.2) Create a surface from vertices using the functions glVertexPointer and glVertex3f, according to the function of your variant
3) Using the gluLookAt command and key processing functions, create a moving camera for the depicted objects. (We move the camera around the center of the scene - full rotation in the horizontal and vertical planes)
4) Obtain images of objects in orthogonal and perspective projections using the functions glOrtho, glFrustum, gluLookAt (switching between projections is programmed to press the "P" and "O" keys, respectively).
At the same time, it is necessary to take into account that object matrices and displays must be selected directly by the glMatrixMode command and pre-normalized by the glLoadIdentity function.

![image](https://user-images.githubusercontent.com/76412011/204274613-3a355279-15a2-4727-8979-b9bb75042e1f.png)
![image](https://user-images.githubusercontent.com/76412011/204274714-eee403ec-039b-4559-a1e1-93587d2364a6.png)


lab3
1) Using the gluLookAt command and key processing functions, create a moving camera for the depicted objects. (We move the camera around the center of the scene - full rotation in the horizontal and vertical planes)
2) Loading and using models and textures
3) Add a light source by connecting the use of specular maps and the lighting calculation model

I used the Assimp library to import the 3D models.
Assimp is a very popular library for importing models, which stands for Open Asset Import Library. This library can import many different formats containing models, storing the imported data as a simple hierarchical data structure. When Assimp finishes loading the models, we can get all the data we need from this structure. It doesn't matter what file format we import, the access to the data in the structures does not change, the structure remains the same for all the different file formats.
A Mesh object contains all relevant data required for rendering: vertex coordinates, normal vector, texture coordinates, faces, and object material information.

![image](https://user-images.githubusercontent.com/76412011/211675215-7407d17f-52ca-45bf-831c-b913f64e381f.png)

A searchlight was used as a light source, the position and direction of which are constantly updated depending on the position and orientation of the player (flashlight).
Running the program results in a spotlight that illuminates only those fragments that are directly inside the spotlight cone. It will look something like this:

![image](https://user-images.githubusercontent.com/76412011/211917937-618028a7-5c2d-48ff-86c2-2eddd3f7596e.png)
