/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 03:29:39 by iharchi           #+#    #+#             */
/*   Updated: 2020/11/25 03:43:07 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

char	*g_errs[] = {"You serious bro?. File is not an RT \
	file, it needs to be terminated by .rt\n",
	"Your file has an empty line, that's a no-no\n",
	"Hey bro nice second argument you got there, though it should be --save\n",
	"I know you are excited to check this beautiful code, \
	but u need to supply either a scene file alone or the \
	scene file followed by --save\n",
	"Hey, The file you provided doesn't exist or this \
	user lack permission to acces it\n",
	"I think you declare the resolution twice ma dude\n",
	"The resolution needs 2 parameters to function, \
	come on you already know this, R height width\n",
	"Are you seriously providing a negative width?\n",
	"That's a negative height ma dude, come on\n",
	"Are you this excited about this project \
	you added more parameters to resolution?\n",
	"You kinda declared the ambient 2 times, RTFM!\n",
	"Ambient needs to have an intensity and a color, i know you can do it\n",
	"You know the drill dude, its A intensity color .. don't add stuff\n",
	"Can please supply a positive float for the intensity? thank you\n",
	"Well if you can't declare a proper RGB imma teach you, \
	its ([0-255],[0-255],[0-255])\n",
	"Hey, bro a camera needs its origin, a vector and an FOV\n",
	"I swear it's like you are doing this on purpose, the camera \
	origin should be (x,y,z)\n",
	"Sorry i mustn't have trusted you with this, a direction is \
	(x,y,z) but with one of them atleast different to 0\n",
	"Well an FOV is a simple integer between 0 and 180 ma dude, \
	you can do this\n",
	"Yo, i think you light is missing stuff, light must have an origin, \
	an intensity and a color..\n",
	"I think you aren't taking this seriously, the origin of the light \
	should be (x,y,z)\n",
	"We've been through this dude, The light color should be \
	([0-255],[0-255],[0-255])\n",
	"Well, idk anymore man.. the intensity must be between 0 and 1 ma dude\n",
	"Yo bro, your sphere is either missing or an excess of parameters \
	(sp x,y,z d r,g,b)\n",
	"Yoda says: sphere origin (x,y,z) must be\n",
	"Are you even trying ma dude? the sphere color must be \
	([0-255],[0-255],[0-255])\n",
	"I think u mistook this project with that Cubic project, \
	this is a sphere it needs a prositive float as a diameter\n",
	"Its plane simple, your plane needs an origin a normal and \
	a color, hehe see what i did there\n",
	"An origin, a point, the planes origin must be (x,y,z)\n",
	"NORMAL.., the plane normal must be (x,y,z) with atleast \
	one of them different to 0\n",
	"How are you expecting this plane to be rendered without a proper color?\n",
	"MASTER SQUARE DEMANDS ONLY 3 PARAMETERS (sq x,y,z s r,g,b)\n",
	"Hello fellow traveller it seems that you are looking for the \
	square origin, its (x,y,z)\n",
	"Squares normal must be (x,y,z) with atleast one of them different \
	to 0. Shoot this one seems a bit serious isn't it\n",
	"Okay, imma dumb this for you, its a size, for a square, \
	it must be a positive float, thank you\n",
	"Square, color, ([0-255],[0-255],[0-255])\n",
	"Your cylinder isnt quite a cylinder, (cy x.y.z x,y,z r h r,g,b)\n",
	"Cylinders origin should be (x,y,z) ma dude\n",
	"The more you know : Cylinder normal should be (x,y,z) unlike you \
	grades in highschool atleast one of the parameters should be different \
	from 0\n",
	"Sir cylinder must have a thickness, so the diameter should be a positive \
	float\n",
	"Its a cylinder bro, it needs some positive height\n",
	"Unlike you, the cylinder isn't sad, it needs some color \
	([0-255],[0-255],[0-255])\n",
	"Triangles needs more love, provide the right amount of parameter sir\n",
	"Wahd : triangles first point is quite right (x,y,z)\n",
	"Joj : This is the second point, it needs to be (x,y,z)\n",
	"Tlata : Finally, the third point should be (x,y,z) too, i mean you \
	managed to fix the first 2 dude what's up ?\n",
	"We coloring, Colors are great, with this simple paramter add color to \
	your triangle ([0-255],[0-255],[0-255])\n",
	"Ouf, I think you have the wrong number, i mean the object you gave isn't \
	supported, call us later\n",
	"Okay, so you know how you have eyes to see? so you basically need a \
	camera to see what's going on here",
	"Let's see.., you didn't add an ambient light? not cool bro",
	"Ma dude how do u want this window to show if you dont have a window? add \
some resolution to the file"};

int		ft_err(t_scene scene)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd("line ", 1);
	ft_putnbr_fd(scene.line, 1);
	ft_putstr_fd(" : ", 1);
	ft_putstr_fd(g_errs[abs(scene.err_code) - 1], 1);
	close_win(0, &scene);
	return (-1);
}
