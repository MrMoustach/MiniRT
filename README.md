# What is MiniRT

A mini RayTracer made using c and a 42 mini graphics library _MiniLibX_.

# How to install
Only for testing, if you are doing this project for school too, or simply intrested in creating a RayTracer, i encourage you to write you own code instead of copying it.

if you haven't already, you have to install MinilibX (MLX) in order to use this project

[MinilibX for linux](https://github.com/42Paris/minilibx-linux), 

[MinilibX for mac (latest i could find)](https://github.com/gcamerli/minilibx)
## MAC 
Clone this repo :
```
    git clone --recurse-submodules https://github.com/MrMoustach/MiniRT.git
```
Then :
```
    Make
```
## LINUX
Also clone : 
```
    git clone --recurse-submodules https://github.com/MrMoustach/MiniRT.git
```
Then :
```
    Make linux
```

# How to use

After making the program, all you need now is to create your own .rt file or use the ones provided in /scenes folder 

then you can run the following command :

```
    ./miniRT path/to/file/filename.rt
```
example :
```
    ./MiniRT scenes/scene.rt
```
To save an image :
```
    ./MiniRT filename.rt --save
```
# Some images 
Here is Wolf.rt :

![alt text](https://github.com/MrMoustach/MiniRT/images/wolf.bmp "Wolf.rt")

Here is scene.rt with all the objects:

![alt text](https://github.com/MrMoustach/MiniRT/images/scene.bmp "scene.rt")
