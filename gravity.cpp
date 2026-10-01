#include "linker.h"
#include <iostream>
//9,8m/s^2
//The player is constantly falling but the ground is stopping that, thanks to collision check
//It should not hinder movement, as well as jumping
//But i can not use -fall speed every frame
//Make it so that when falling, moving left or right becomes harder
//When jump, trigger a process of moving up, not just 1 frame but multiple
//Cant jump if on ground
//Keep a state: Jump, idle, walking, falling, moving up&down a ladder