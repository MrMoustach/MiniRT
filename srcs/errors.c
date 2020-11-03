/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 03:29:39 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/03 05:55:43 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int ft_err(t_scene scene)
{
    ft_printf("Error\n");
    ft_printf("line %d : ", scene.line);
    if (scene.err_code == -1)
        ft_printf("You serious bro?. File is not an RT file, it needs to be terminated by .rt\n");
    if (scene.err_code == -2)
        ft_printf("Your file has an empty line, that's a no-no\n");
    if (scene.err_code == -3)
        ft_printf("Hey bro nice second argument you got there, though it should be --save\n");
    if (scene.err_code == -4)
        ft_printf("I know you are excited to check this beautiful code, but u need to supply either a scene file alone or the scene file followed by --save\n");
    if (scene.err_code == -5)
        ft_printf("Hey, The file you provided doesn't exist or this user lack permission to acces it\n");
    if (scene.err_code == -6)
        ft_printf("I think you declare the resolution twice ma dude\n");
    if (scene.err_code == -7)
        ft_printf("The resolution needs 2 parameters to function, come on you already know this, R height width\n");
    if (scene.err_code == -8)
        ft_printf("Are you seriously providing a negative width?\n");
    if (scene.err_code == -9)
        ft_printf("That's a negative height ma dude, come on\n");
    if (scene.err_code == -10)
        ft_printf("Are you this excited about this project you added more parameters?\n");
    if (scene.err_code == -11)
        ft_printf("You kinda declared the ambient 2 times, RTFM!\n");
    if (scene.err_code == -12)
        ft_printf("Ambient needs to have an intensity and a color, i know you can do it\n");
    if (scene.err_code == -13)
        ft_printf("You know the drill dude, its A intensity color .. don't add stuff\n");
    if (scene.err_code == -14)
        ft_printf("Can please supply a positive float for the intensity? thank you\n");
    if (scene.err_code == -15)
        ft_printf("Well if you can't declare a proper RGB imma teach you, its ([0-255],[0-255],[0-255])\n");
    if (scene.err_code == -16)
        ft_printf("Hey, bro a camera needs its origin, a vector and an FOV\n");
    if (scene.err_code == -17)
        ft_printf("I swear it's like you are doing this on purpose, the camera origin should be (x,y,z)\n");
    if (scene.err_code == -18)
        ft_printf("Sorry i mustn't have trusted you with this, a direction is (x,y,z) but with one of them atleast different to 0\n");
    if (scene.err_code == -19)
        ft_printf("Well an FOV is a simple integer between 0 and 180 ma dude, you can do this\n");
    if (scene.err_code == -20)
        ft_printf("Yo, i think you light is missing stuff, light must have an origin, an intensity and a color..\n");
    if (scene.err_code == -21)
        ft_printf("I think you aren't taking this seriously, the origin of the light should be (x,y,z)\n");
    if (scene.err_code == -22)
        ft_printf("We've been through this dude, The light color should be ([0-255],[0-255],[0-255])\n");
    if (scene.err_code == -23)
        ft_printf("Well, idk anymore man.. the intensity must be between 0 and 1 ma dude\n");
    if (scene.err_code == -24)
        ft_printf("Yo bro, your sphere is either missing or an excess of parameters (sp x,y,z d r,g,b)\n");
    if (scene.err_code == -25)
        ft_printf("Yoda says: sphere origin (x,y,z) must be\n");
    if (scene.err_code == -26)
        ft_printf("Are you even trying ma dude? the sphere color must be ([0-255],[0-255],[0-255])\n");
    if (scene.err_code == -27)
        ft_printf("I think u mistook this project with that Cubic project, this is a sphere it needs a prositive float as a diameter\n");
    if (scene.err_code == -28)
        ft_printf("Its plane simple, your plane needs an origin a normal and a color, hehe see what i did there\n");
    if (scene.err_code == -29)
        ft_printf("An origin, a point, the planes origin must be (x,y,z)\n");
    if (scene.err_code == -30)
        ft_printf("NORMAL.., the plane normal must be (x,y,z) with atleast one of them different to 0\n");
    if (scene.err_code == -31)
        ft_printf("How are you expecting this plane to be rendered without a proper color?\n");
    if (scene.err_code == -32)
        ft_printf("MASTER SQUARE DEMANDS ONLY 3 PARAMETERS (sq x,y,z s r,g,b)\n");
    if (scene.err_code == -33)
        ft_printf("Hello fellow traveller it seems that you are looking for the square origin, its (x,y,z)\n");
    if (scene.err_code == -34)
        ft_printf("Squares normal must be (x,y,z) with atleast one of them different to 0. Shoot this one seems a bit serious isn't it\n");
    if (scene.err_code == -35)
        ft_printf("Okay, imma dumb this for you, its a size, for a square, it must be a positive float, thank you\n");
    if (scene.err_code == -36)
        ft_printf("Square, color, ([0-255],[0-255],[0-255])\n");
    if (scene.err_code == -37)
        ft_printf("Your cylinder isnt quite a cylinder, (cy x.y.z x,y,z r h r,g,b)\n");
    if (scene.err_code == -38)
        ft_printf("Cylinders origin should be (x,y,z) ma dude\n");
    if (scene.err_code == -39)
        ft_printf("The more you know : Cylinder normal should be (x,y,z) unlike you grades in highschool atleast one of the parameters should be different from 0\n");
    if (scene.err_code == -40)
        ft_printf("Sir cylinder must have a thickness, so the diameter should be a positive float\n");
    if (scene.err_code == -41)
        ft_printf("Its a cylinder bro, it needs some positive height\n");
    if (scene.err_code == -42)
        ft_printf("Unlike you, the cylinder isn't sad, it needs some color ([0-255],[0-255],[0-255])\n");
    if (scene.err_code == -43)
        ft_printf("Triangles needs more love, provide the right amount of parameter sir\n");
    if (scene.err_code == -44)
        ft_printf("Wahd : triangles first point is quite right (x,y,z)\n");
    if (scene.err_code == -45)
        ft_printf("Joj : This is the second point, it needs to be (x,y,z)\n");
    if (scene.err_code == -46)
        ft_printf("Tlata : Finally, the third point should be (x,y,z) too, i mean you managed to fix the first 2 dude what's up ?\n");
    if (scene.err_code == -47)
        ft_printf("We coloring, Colors are great, with this simple paramter add color to you triangle ([0-255],[0-255],[0-255])\n");
    if (scene.err_code == -48)
        ft_printf("Ouf, I think you have the wrong number, i mean the object you gave isn't supported, call us later\n");
    return (0);
}