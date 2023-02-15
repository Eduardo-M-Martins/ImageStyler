# imageStyler
By Eduardo Machado Martins
## Description
This project aims to stylize an image in JPG format. The algorithm chooses some specific pixels from the original image as seeds to form a new image, where each pixel of the output image must be composed of the color of the closest seed. Two different methodologies were used to select the seeds in the input image, the first is a safety technique to guarantee that the image has a minimum number of them scattered, in this way a seed is placed in each coordinate where Y and X are multiples of 12. The second methodology used was an algorithm to detect the edges in the image, for this, each pixel of the input image is compared with those around it, and if there is a big difference in color, a seed is defined for that specific position. The values ​​of these two methods can be changed as they are stored in the 'seg' and 'rgb' variables respectively. Therefore, these two methods are applied simultaneously to form the output image. To read the image more effectively, an OpenMP parallel for was used. Lastly, 5 exemples were set to test the algorithm. Use keys '1', '2' and '3' to switch between images.
## Dependencies
This application works on Linux and uses OpenGL libraries, C and C++.
## Execution
The following command compiles the application.
```
make
```
The following command execute the application.
```
./artistic [imageFileName].jpg
```