// Drew Teachout
#ifndef MYLIB_H
#define MYLIB_H
#include "hardware.h"

typedef char* string;

enum GBAState {
	START,
	GAME,
	GAMEOVER,
	NODRAW
	};
extern enum GBAState state;

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160

// Colors
#define COLOR(r, g, b)  ((r) | (g)<<5  | (b)<<10)
#define RED COLOR(31,0,0)
#define BLUE COLOR(0,0,31)
#define MAGENTA COLOR(31, 0, 31)
#define CYAN COLOR(0, 31, 31)
#define YELLOW COLOR(31, 31, 0)
#define WHITE COLOR(31, 31, 31)
#define BLACK COLOR(0, 0, 0)
#define GREEN COLOR(0, 31, 0)

#define OFFSET(row, col, rowlen) ((row)*(rowlen)+(col))

// Buttons
#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)

#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)

// Prototypes
void delay(int n);
void drawChar(int row, int col, char ch, unsigned short color);
void drawRect(int r, int c, int width, int height, volatile unsigned short color);
void drawString(int row, int col, string str, unsigned short color);
void drawImage3(int r, int c, int width, int height, const unsigned short* image);
void initialize(void);
void startGame(int l);
void loseLife(void);
void moveMissiles(void);
void moveShipLeft(void);
void moveShipRight(void);
void startScreen(void);
void setPixel(int r, int c, unsigned short color);
void shoot(void);
void enemyShoot(int n);
void waitForVblank(void);
void fillScreen(unsigned short color);
void setCurrentState(int i);
int getCurrentState(void);
void resetShip(void);
void drawShip(void);
void resetBees(void);
void drawBees(void);
void resetDragonflys(void);
void drawDragonflys(void);
void resetBullet(void);
void resetEnemyBullet(void);
void addNewBullet(void);
void addEnemyBullet(int n);
void addManBullet(int oldRow, int oldCol, int row, int col);
void drawBullet(int i);
void drawEnemyBullet(int i);
void moveBullets(void);
void moveEnemyBullets(void);
void moveDragonflys(void);
void updateCollision(void);
int getLives(void);
int enemiesDead(void);
void beeShoot(void);
#endif
