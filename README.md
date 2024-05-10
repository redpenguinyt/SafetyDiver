# Safety Diver for the Playdate
[Safety Diver](https://redpenguin777.itch.io/safety-diver) is a game made for the [Uncrank'd Jam](https://itch.io/jam/uncrankdjam) using the theme "Float"  

![playdate-20240510-135751](https://github.com/redpenguinyt/SafetyDiver/assets/79577742/a68c0957-881e-4983-8f11-fe0551025553)  
You can find the download [on the itch.io page](https://redpenguin777.itch.io/safety-diver)!

# Devlog
Here's a short record of what I did each day:

## Day 1 (3/5):
- implemented basic buoyancy!
	- the player is calculated as a sphere with a radius of 15
	- had to figure out how to calculate the volume of a cut sphere
	- player's rotor is significantly less influential in the air
- made a simple animated player sprite  
![playdate-20240503-192018](https://github.com/redpenguinyt/SafetyDiver/assets/79577742/fbadcdbd-8a86-49c3-9832-86b76ea4132e)

## Day 2:
- made the camera move freely on the vertical axis!
- with camera drag too!
- added some super simple water and air resistance physics - the player is slowed down more in water (but not too much, otherwise it wouldnt be fun!)  
![playdate-20240504-124532](https://github.com/redpenguinyt/SafetyDiver/assets/79577742/1449c49b-1450-4ae0-9a9d-66bf24b55367)
- also added a depth HUD  
![playdate-20240504-130535](https://github.com/redpenguinyt/SafetyDiver/assets/79577742/2c5ebd5a-275b-4744-a74b-2ea3f40ec856)
- im thinking the basic premise can be that you dive down for gold and stuff while avoiding hazards, and have to make it back to the surface for all the collected items to count!
- i'm very much enjoying taking a little break from spaceshipment, this has been fun so far!

## Day 3:
- added coins for the player to collect!
- added a score display to show how many coins the player has collected  
![playdate-20240505-142708](https://github.com/redpenguinyt/SafetyDiver/assets/79577742/76822988-aa71-41f6-8fb5-6fbde948f89c)
- next we add hazards for the player to avoid (and maybe tweak the movement to give the player a chance to avoid it)

(Took a break on Day 4)

## Day 5:
- added hazards!
- the player now carries an amount of treasure with them (which they lose if they touch a hazard) which gets added to the main score when they resurface  
![playdate-20240507-225931](https://github.com/redpenguinyt/SafetyDiver/assets/79577742/c8245877-b26f-499c-ad26-7d0bcea16cc9)
- also added a splash and coin pickup sound effects
- next will end the game if the player comes up with 0 held coins
	- and proper hazard collisions
	- as well as motor, bringing treasure to surface and zap (colliding with hazard) sounds

## Day 6:
 - added a camera limit at the bottom of the sea  
![playdate-20240508-165007](https://github.com/redpenguinyt/SafetyDiver/assets/79577742/aab73197-fb05-4940-b3c7-1d3de12bcebc)
 - and added real hazard collisions!  
![playdate-20240508-164815](https://github.com/redpenguinyt/SafetyDiver/assets/79577742/b28c1f9d-490b-4d18-b2e3-aa09307bda01)
 - zap sound when colliding with hazards
 - rewrote the entire codebase to access `PlaydateAPI *pd` from one place - pd_pointer.h
 - more abstraction!
 - fixed bug where you can often see past the floor of the ocean when approaching it

## Day 7:
- tomorrow's the second to last day, so it's time to get cracking on what's left to finish for the game!
- added a game over/restart sequence (might add high score storage later)
- resurface score increase sound effects
- restructured my code to move all level logic from game.c to level/level.c
- made a nice pretty game over screen  
![playdate-20240510-135906](https://github.com/redpenguinyt/SafetyDiver/assets/79577742/1c75cacd-cef6-4a38-b12f-09bfdea8eb7e)
- simple motor sound (sounds the same out of water and in)

## Day 8: The FINAL Day
- with the final day today, i took the time to clean up the game and its itch.io page
- added a little bonk sound for hitting the walls
- improved the motor sound
- released the game and the github page!
