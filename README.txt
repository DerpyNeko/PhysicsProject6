											INFO 6022
											PROJECT 6
									By Jenny Moon and Ryan O'Donnell

Builds in either debug or release mode x64.
Copy the fmod64.dll from the Project6 folder into the x64/Debug or x64/Release folder, depending on which one you built.

Controls:
	- Left and right arrow keys control their respective paddle.
	- Space bar for the launcher.

Graded Items
	- Have 6 different shapes included: Box, Cylinder, Triangles, Capsules, Spheres, and Cones. Tetrahedrons were swapped for cones as Blender is not kind to work with.

	- Contraints implemented are: 6 degrees of freedom, hinge, and slider. Code can be found in cBullet6DoFConstraint/cBulletHingeConstraint/cBulletSliderConstraint
		- The 6DoF on the player ball that is meant to keep the ball from escaping the play area. The constraint has a set upper and lower limit to it, making it stay in the 		designated area.
		- The hinge constraint is on the player controlled paddles and the white thin box that acts like a flapper. They have their own pivot spot and axis in which it is supposed 		to rotate around
		- The slider is on the light blue box in the lower right area and it acts like the plunger. There is a line of code in the constructor that rotates the constraint so it will 		slide on the z axis, rather than the default x axis. The slider also has a upper and lower limit for the axis.

	- Have playable sounds on both press and release of the arrow keys to signify to moving of the paddles. Space bar release has a launcher sound as well.

The game is currently unplayable. All of the objects in the json file have a mass of 0, changing the mass will result in the object blasting off into space. We have spent 3 days straight combing over every line of code trying to fix this issue. If this issue was fixed then everything else should be functional but because of this bug we cant actually see if it works or not.

There are some collision code in the project but it is not implemented because it would not trigger with the current bug that we have. It would have used the different shapes that we have, and made them do something. The spheres would have given like points when hit. The cylinders would have multiplied the force, making the ball gain speed if it came in contact with them, as well as granting points. The white square in the top right would spin when hit, while the capsules and cones were just there as obstacles.

Lines 303 - 306 in the main will look at the third object loaded in the json file, which would be the player ball, and will print out the position of the object. When the project is ran with these lines active, it states the proper position that it is loaded with for the first two frames and then the values will drastically change for no reason. 