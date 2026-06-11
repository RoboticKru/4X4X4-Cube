#include <HC4x4x4.h>
#include <math.h> 

HC4x4x4 Cube;

// Global speed control
int animDelay = 80; 

void setup() {
  Cube.init();
}

void loop() {
  slidingPlanes();
  rotatingPlane();
  tunnelSpiral();
  drawTesseract();
  randomFive();
  firework();
  spiralUpwards();
  snake3D();
  liftingHinge();
  digitalRain();
  rollingWave();
  fluidLava();
}

// ==========================================
// ANIMATION FUNCTIONS (Protected with Memory Locks)
// ==========================================

void slidingPlanes() {
  for(int x = 0; x < 4; x++) { noInterrupts(); Cube.clear(); drawPlaneX(x); interrupts(); delay(animDelay); }
  for(int x = 2; x >= 0; x--) { noInterrupts(); Cube.clear(); drawPlaneX(x); interrupts(); delay(animDelay); }
  
  for(int y = 0; y < 4; y++) { noInterrupts(); Cube.clear(); drawPlaneY(y); interrupts(); delay(animDelay); }
  for(int y = 2; y >= 0; y--) { noInterrupts(); Cube.clear(); drawPlaneY(y); interrupts(); delay(animDelay); }
  
  for(int z = 0; z < 4; z++) { noInterrupts(); Cube.clear(); drawPlaneZ(z); interrupts(); delay(animDelay); }
  for(int z = 2; z >= 0; z--) { noInterrupts(); Cube.clear(); drawPlaneZ(z); interrupts(); delay(animDelay); }
}

void drawPlaneX(int x) { for(int y=0; y<4; y++) for(int z=0; z<4; z++) Cube.plot(x,y,z, ON); }
void drawPlaneY(int y) { for(int x=0; x<4; x++) for(int z=0; z<4; z++) Cube.plot(x,y,z, ON); }
void drawPlaneZ(int z) { for(int x=0; x<4; x++) for(int y=0; y<4; y++) Cube.plot(x,y,z, ON); }

void rotatingPlane() {
  for(int i=0; i<3; i++) { 
    noInterrupts(); Cube.clear(); drawPlaneX(1); drawPlaneX(2); interrupts(); delay(150);
    
    noInterrupts(); Cube.clear(); 
    for(int y=0; y<4; y++) { Cube.plot(0,y,0, ON); Cube.plot(1,y,1, ON); Cube.plot(2,y,2, ON); Cube.plot(3,y,3, ON); }
    interrupts(); delay(150);
    
    noInterrupts(); Cube.clear(); drawPlaneZ(1); drawPlaneZ(2); interrupts(); delay(150);
    
    noInterrupts(); Cube.clear(); 
    for(int y=0; y<4; y++) { Cube.plot(3,y,0, ON); Cube.plot(2,y,1, ON); Cube.plot(1,y,2, ON); Cube.plot(0,y,3, ON); }
    interrupts(); delay(150);
  }
}

void tunnelSpiral() {
  int spiralPathX[] = {0, 1, 2, 3, 3, 3, 3, 2, 1, 0, 0, 0};
  int spiralPathZ[] = {0, 0, 0, 0, 1, 2, 3, 3, 3, 3, 2, 1};
  for(int loops = 0; loops < 4; loops++) {
    for(int s = 0; s < 12; s++) { 
      noInterrupts();
      Cube.clear();
      for(int y = 0; y < 4; y++) {
        int index = (s + y) % 12; 
        Cube.plot(spiralPathX[index], y, spiralPathZ[index], ON);
      }
      interrupts();
      delay(80);
    }
  }
}

void drawTesseract() {
  noInterrupts();
  Cube.clear();
  for(int x=1; x<=2; x++) for(int y=1; y<=2; y++) for(int z=1; z<=2; z++) {
    if(x==1||x==2||y==1||y==2||z==1||z==2) Cube.plot(x,y,z, ON);
  }
  Cube.plot(0,0,0, ON); Cube.plot(3,0,0, ON); Cube.plot(0,3,0, ON); Cube.plot(3,3,0, ON);
  Cube.plot(0,0,3, ON); Cube.plot(3,0,3, ON); Cube.plot(0,3,3, ON); Cube.plot(3,3,3, ON);
  interrupts();
  delay(1500); 
}

void randomFive() {
  for(int r = 0; r < 15; r++) { 
    int rx[5], ry[5], rz[5];
    for(int i = 0; i < 5; i++) { rx[i] = random(4); ry[i] = random(4); rz[i] = random(4); }
    
    noInterrupts();
    Cube.clear();
    for(int i = 0; i < 5; i++) Cube.plot(rx[i], ry[i], rz[i], ON);
    interrupts();
    delay(150);
  }
}

void firework() {
  noInterrupts(); Cube.clear(); drawPlaneZ(0); interrupts(); delay(200);
  
  noInterrupts();
  Cube.clear();
  for(int x=0; x<4; x++) for(int y=0; y<4; y++) for(int z=0; z<4; z++) {
    if(x==0 || x==3 || y==0 || y==3 || z==0 || z==3) Cube.plot(x,y,z, ON);
  }
  interrupts(); delay(300);
  
  noInterrupts(); Cube.clear(); drawPlaneZ(3); interrupts(); delay(200);
  noInterrupts(); Cube.clear(); interrupts(); delay(200);
}

void spiralUpwards() {
  int spiralX[] = {0, 1, 2, 3, 3, 3, 3, 2, 1, 0, 0, 0};
  int spiralY[] = {0, 0, 0, 0, 1, 2, 3, 3, 3, 3, 2, 1};
  
  noInterrupts(); Cube.clear(); interrupts();
  for(int z = 0; z < 4; z++) {
    for(int i = 0; i < 12; i++) { 
      noInterrupts(); Cube.plot(spiralX[i], spiralY[i], z, ON); interrupts();
      delay(40); 
    }
  }
  delay(300);
}

void snake3D() {
  int sX[4] = {1, 1, 1, 1}; int sY[4] = {1, 1, 1, 1}; int sZ[4] = {3, 2, 1, 0}; 
  for(int moves = 0; moves < 60; moves++) { 
    noInterrupts();
    Cube.clear();
    for(int i=0; i<4; i++) Cube.plot(sX[i], sY[i], sZ[i], ON);
    interrupts();
    delay(150);
    
    for(int i=3; i>0; i--) { sX[i] = sX[i-1]; sY[i] = sY[i-1]; sZ[i] = sZ[i-1]; }
    
    bool validMove = false;
    while(!validMove) {
      int newX = sX[0]; int newY = sY[0]; int newZ = sZ[0];
      int axis = random(3); 
      int dir = (random(2) == 0) ? -1 : 1; 
      
      if(axis == 0) newX += dir;
      else if(axis == 1) newY += dir;
      else newZ += dir;
      
      if(newX >= 0 && newX <= 3 && newY >= 0 && newY <= 3 && newZ >= 0 && newZ <= 3) {
        bool hitSelf = false;
        for(int b = 1; b < 4; b++) { 
           if(newX == sX[b] && newY == sY[b] && newZ == sZ[b]) { hitSelf = true; break; }
        }
        if(!hitSelf) { sX[0] = newX; sY[0] = newY; sZ[0] = newZ; validMove = true; }
      }
    }
  }
}

void liftingHinge() {
  noInterrupts(); Cube.clear(); drawPlaneZ(0); interrupts(); delay(250);
  
  noInterrupts(); Cube.clear();
  for(int x=0; x<4; x++) { Cube.plot(x,3,0, ON); Cube.plot(x,2,0, ON); Cube.plot(x,1,1, ON); Cube.plot(x,0,1, ON); }
  interrupts(); delay(250);
  
  noInterrupts(); Cube.clear();
  for(int x=0; x<4; x++) { Cube.plot(x,3,0, ON); Cube.plot(x,2,1, ON); Cube.plot(x,1,2, ON); Cube.plot(x,0,2, ON); }
  interrupts(); delay(250);
  
  noInterrupts(); Cube.clear();
  for(int x=0; x<4; x++) { Cube.plot(x,3,0, ON); Cube.plot(x,2,1, ON); Cube.plot(x,1,2, ON); Cube.plot(x,0,3, ON); }
  interrupts(); delay(500);
  
  noInterrupts(); Cube.clear();
  for(int x=0; x<4; x++) { Cube.plot(x,3,0, ON); Cube.plot(x,2,1, ON); Cube.plot(x,1,2, ON); Cube.plot(x,0,2, ON); }
  interrupts(); delay(250);
  
  noInterrupts(); Cube.clear();
  for(int x=0; x<4; x++) { Cube.plot(x,3,0, ON); Cube.plot(x,2,0, ON); Cube.plot(x,1,1, ON); Cube.plot(x,0,1, ON); }
  interrupts(); delay(250);
}

void digitalRain() {
  int dropsX[4]; int dropsY[4]; int dropsZ[4];
  for(int i=0; i<4; i++) { dropsX[i]=random(4); dropsY[i]=random(4); dropsZ[i]=random(4, 8); } 
  
  for(int step=0; step<40; step++) { 
    noInterrupts();
    Cube.clear();
    for(int i=0; i<4; i++) {
      if(dropsZ[i] < 4 && dropsZ[i] >= 0) Cube.plot(dropsX[i], dropsY[i], dropsZ[i], ON);
    }
    interrupts();
    
    for(int i=0; i<4; i++) {
      dropsZ[i]--; 
      if(dropsZ[i] < -1) { dropsX[i]=random(4); dropsY[i]=random(4); dropsZ[i]=random(3, 6); }
    }
    delay(animDelay + 20); 
  }
}

void rollingWave() {
  for(int step=0; step<30; step++) { 
    int heights[4];
    for(int x=0; x<4; x++) heights[x] = (int)(1.5 + sin((x * 0.8) + (step * 0.4)) * 1.5);
    
    noInterrupts();
    Cube.clear();
    for(int x=0; x<4; x++) {
      for(int y=0; y<4; y++) {
        if(heights[x] >= 0 && heights[x] < 4) Cube.plot(x, y, heights[x], ON);
      }
    }
    interrupts();
    delay(animDelay);
  }
}

void fluidLava() {
  static int b1[3] = {0, 10, 0}; static int v1[3] = {1, 2, 1}; 
  static int b2[3] = {30, 20, 30}; static int v2[3] = {-1, -1, -2}; 

  for(int step = 0; step < 120; step++) { 
    for(int i = 0; i < 3; i++) {
       b1[i] += v1[i]; if(b1[i] < 0 || b1[i] > 30) v1[i] = -v1[i]; 
       b2[i] += v2[i]; if(b2[i] < 0 || b2[i] > 30) v2[i] = -v2[i];
    }

    bool buffer[4][4][4] = {false}; 
    for(int x = 0; x < 4; x++) {
      for(int y = 0; y < 4; y++) {
        for(int z = 0; z < 4; z++) {
          int d1x = (x*10) - b1[0]; int d1y = (y*10) - b1[1]; int d1z = (z*10) - b1[2];
          long dist1_sq = (long)(d1x*d1x + d1y*d1y + d1z*d1z); if (dist1_sq == 0) dist1_sq = 1; 

          int d2x = (x*10) - b2[0]; int d2y = (y*10) - b2[1]; int d2z = (z*10) - b2[2];
          long dist2_sq = (long)(d2x*d2x + d2y*d2y + d2z*d2z); if (dist2_sq == 0) dist2_sq = 1;

          if (((4000 / dist1_sq) + (4000 / dist2_sq)) > 16) buffer[x][y][z] = true;
        }
      }
    }

    noInterrupts();
    Cube.clear();
    for(int x = 0; x < 4; x++) {
      for(int y = 0; y < 4; y++) {
        for(int z = 0; z < 4; z++) {
           if(buffer[x][y][z]) Cube.plot(x,y,z, ON);
        }
      }
    }
    interrupts();
    delay(animDelay); 
  }
}
