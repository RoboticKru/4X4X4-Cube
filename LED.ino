#include "HC4x4x4.h"

HC4x4x4 HC4x4x4;

void setup() {
  HC4x4x4.init();
}

void loop() {
  // Declare the spin array once at the top so all rotating animations can share it
  int spinAngles[4] = {FRONT_0, RIGHT_0, BACK_0, LEFT_0};

  // --- SEQUENCE 1: Scroll "KCL" ---
  HC4x4x4.clear();
  HC4x4x4.setDrawDir(FRONT_0); // Ensure this points to your front face!
  HC4x4x4.printScroll("KCL", 150, 3); 
  delay(500);
// --- SEQUENCE 2: Flashing K-C-L Around the Cube ---
  
  // We define an array of the three faces we want to flash the letters on.
  // (If these don't match your physical Front/Back/Right, you can easily 
  // swap in FRONT_0, BACK_0, RIGHT_0, or LEFT_0 until they are perfect!)
  int flashSides[3] = {LEFT_0, FRONT_0}; 
  
  // Loop through each of the 3 faces
  for (int face = 0; face < 2; face++) {
    HC4x4x4.setDrawDir(flashSides[face]); // Point to the new face
    
    HC4x4x4.clear();
    HC4x4x4.printChar('K', 0, 3); 
    delay(500); 
    
    HC4x4x4.clear();
    HC4x4x4.printChar('C', 0, 3);
    delay(500); 
    
    HC4x4x4.clear();
    HC4x4x4.printChar('L', 0, 3);
    delay(500); 
    
    HC4x4x4.clear();
    delay(200); // Brief pause before moving to the next face
  }


// --- SEQUENCE 2: Flashing K - C - L (Back Face with Base LEDs) ---
  HC4x4x4.clear();
  
  // Set the drawing direction to face the BACK of the cube.
  // (If this draws on the front instead of the back, simply change this to FRONT_0!)
  HC4x4x4.setDrawDir(FRONT_0); 
  
  // 1. Flash 'K'
  HC4x4x4.baseLEDs(ON);          // Turn on the bottom accent lights
  HC4x4x4.printChar('K', 0, 3);  // Draw the letter
  delay(600);                    // Hold them both on screen
  
  HC4x4x4.clear();               // Clear the letter
  HC4x4x4.baseLEDs(OFF);         // Turn off the accent lights
  delay(200);                    // Brief dark pause
  
  
  // 2. Flash 'C'
  HC4x4x4.baseLEDs(ON);
  HC4x4x4.printChar('C', 0, 3);
  delay(600);
  
  HC4x4x4.clear();
  HC4x4x4.baseLEDs(OFF);
  delay(200);
  
  
  // 3. Flash 'L'
  HC4x4x4.baseLEDs(ON);
  HC4x4x4.printChar('L', 0, 3);
  delay(600);
  
  HC4x4x4.clear();
  HC4x4x4.baseLEDs(OFF);
  delay(600); // Slightly longer pause before the next animation begins

  // --- SEQUENCE 5: Digital Rain ---
  HC4x4x4.clear();
  HC4x4x4.setDrawDir(FRONT_0); 
  
  for (int drops = 0; drops < 25; drops++) {
    int x = random(0, 4); 
    int z = random(0, 4); 
    for (int y = 3; y >= 0; y--) {
      HC4x4x4.plot(x, y, z, ON);
      delay(60);
      HC4x4x4.plot(x, y, z, OFF);
    }
  }

  // --- SEQUENCE 6: Breathing 3D Box ---
  HC4x4x4.clear();
  for(int pulse = 0; pulse < 3; pulse++) {
    HC4x4x4.cube(1, 1, 1, 2, 2, 2, false, ON);
    delay(400); 
    HC4x4x4.cube(1, 1, 1, 2, 2, 2, false, OFF);
    
    HC4x4x4.cube(0, 0, 0, 3, 3, 3, false, ON);
    delay(400); 
    HC4x4x4.cube(0, 0, 0, 3, 3, 3, false, OFF);
  }

  // --- SEQUENCE 7: 3-LED Auto-Snake ---
  HC4x4x4.clear();
  int sX[3] = {1, 1, 1}; 
  int sY[3] = {1, 1, 1}; 
  int sZ[3] = {1, 1, 1}; 
  
  for(int moves = 0; moves < 40; moves++) {
    HC4x4x4.plot(sX[2], sY[2], sZ[2], OFF); 
    sX[2] = sX[1]; sY[2] = sY[1]; sZ[2] = sZ[1]; 
    sX[1] = sX[0]; sY[1] = sY[0]; sZ[1] = sZ[0]; 
    
    int axis = random(0, 3);
    int step = (random(0, 2) == 0) ? -1 : 1;
    
    if(axis == 0) sX[0] = constrain(sX[0] + step, 0, 3);
    if(axis == 1) sY[0] = constrain(sY[0] + step, 0, 3);
    if(axis == 2) sZ[0] = constrain(sZ[0] + step, 0, 3);

    HC4x4x4.plot(sX[0], sY[0], sZ[0], ON); 
    HC4x4x4.plot(sX[1], sY[1], sZ[1], ON); 
    delay(150); 
  }

  // --- SEQUENCE 8: Revolving Radar ---
  for (int spins = 0; spins < 5; spins++) {
    HC4x4x4.clear();
    for (int y = 0; y < 4; y++) HC4x4x4.line(0, y, 1, 3, y, 1, ON);
    delay(150);
    
    HC4x4x4.clear();
    for (int y = 0; y < 4; y++) HC4x4x4.line(0, y, 0, 3, y, 3, ON);
    delay(150);

    HC4x4x4.clear();
    for (int y = 0; y < 4; y++) HC4x4x4.line(1, y, 0, 1, y, 3, ON);
    delay(150);

    HC4x4x4.clear();
    for (int y = 0; y < 4; y++) HC4x4x4.line(0, y, 3, 3, y, 0, ON);
    delay(150);
  }

  // --- SEQUENCE 9: 3D Rolling Wave ---
  int waveHeight[4] = {0, 1, 2, 1}; 
  for (int phase = 0; phase < 20; phase++) { 
    HC4x4x4.clear();
    for (int x = 0; x < 4; x++) {
      for (int z = 0; z < 4; z++) {
        int y = waveHeight[(x + z + phase) % 4];
        HC4x4x4.plot(x, y, z, ON);
        if (y > 0) HC4x4x4.plot(x, y - 1, z, ON); 
      }
    }
    delay(120); 
  }

  // --- SEQUENCE 10: Wobbling Tornado ---
  int topX[8] = {0, 1, 3, 3, 3, 2, 0, 0}; 
  int topZ[8] = {0, 0, 0, 1, 3, 3, 3, 2};
  
  for (int spins = 0; spins < 6; spins++) {
    for (int frame = 0; frame < 8; frame++) {
      HC4x4x4.clear();
      HC4x4x4.line(1, 0, 1, topX[frame], 3, topZ[frame], ON);
      HC4x4x4.line(2, 0, 2, topX[(frame + 4) % 8], 3, topZ[(frame + 4) % 8], ON);
      delay(90); 
    }
  }
}
