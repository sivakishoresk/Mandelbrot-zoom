NOTE :
This code has been run and tested on Linux.

Google drive link to the demo video :
https://drive.google.com/file/d/15vSEtdDCB7Ti7SXTMRKppceXuwuG146V/view?usp=sharing

Command for SFML installation(Linux) :
sudo apt-get install libsfml-dev

Commands for compilation and execution : 
make mandelbrot
./mandelbrot

Brief info :
I have implemented the mandelbrot zoom using the SFML Graphics Package.
I have primarily used three classes namely, complex, Button and Mandelbrot.
I used complex class to deal with complex numbers, Button class to facilitate user experience using buttons created in SFML and Mandelbrot class to implement all the core featues.
In the main function, I have taken care of various mouse-click events and handled them using the functions implemented in the above classes.
If the zoom level crosses a certain threshold, the process stops and outputs the coordinates of the boundaries. The threshold can be customised.
Left mouse click is used to zoom in and right mouse click is used to zoom out.
I have also added a User Interface to faciliatate user experience.

The user has the following options available to him/her:
(i) Choose a preferred coloring style
(ii) Pause the zoom at a particular point.
(iii) Stop the zoom, reset it to the initial configuration and start again.
(iv) Save a particular state of the animation as an image.
(v) Save all the image states generated during the process and then play an animation using all the saved images.(Based on the user's reply of course)

**The above features have been shown in the Demo video**

**A FEW IMPORTANT THINGS TO NOTE**
(i) Rendering text in SFML requires a font and hence I have added the Roboto font file in my submission.
(ii) Please make sure that the directory structure is as shown in the demo video or as in the screenshot(DirectoryStructure.png) attached as SFML may fail to save images if the specified folder is not present at runtime. 
(iii) I have also added a file named "t.cpp" in which I tried to use a technique for optimising the number of computations but it hasn't worked as expected. I would like to explain my idea during the demo if possible.
(iv) During the large number of computations involved, the process becomes slower as you zoom deeper. However, you can still use left mouse click manually to speed up the process.
