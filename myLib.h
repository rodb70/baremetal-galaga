// Drew Teachout

typedef char* string;

enum GBAState {
	START,
	GAME,
	GAMEOVER,
	NODRAW
	};
enum GBAState state;

// DMA Stuff
typedef struct {
	const volatile void *src;
	volatile void *dst;
	volatile unsigned int cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER*) 0x40000B0)
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

#define REG_DISPCNT *(unsigned short*)0x4000000
#define MODE_3 3
#define BG2_EN (1<<10)
#define VIDEOBUFFERADDRESS (unsigned short *)0x6000000
#define SCANLINECOUNTER *(volatile unsigned short *)0x4000006

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

#define BUTTONS *(volatile unsigned int *)0x4000130

// Prototypes
void delay(int n);
void drawChar(int row, int col, char ch, unsigned short color);
void drawRect(int r, int c, int width, int height, volatile unsigned short color);
void drawString(int row, int col, string str, unsigned short color);
void drawImage3(int r, int c, int width, int height, const unsigned short* image);
void initialize();
void startGame(int l);
void loseLife();
void moveMissiles();
void moveShipLeft();
void moveShipRight();
void startScreen();
void setPixel(int r, int c, unsigned short color);
void shoot();
void enemyShoot(int n);
void waitForVblank();
void fillScreen(unsigned short color);
void setCurrentState(int i);
int getCurrentState();
void resetShip();
void drawShip();
void resetBees();
void drawBees();
void resetDragonflys();
void drawDragonflys();
void resetBullet();
void resetEnemyBullet();
void addNewBullet();
void addEnemyBullet();
void addManBullet(int oldRow, int oldCol, int row, int col);
void drawBullet(int i);
void drawEnemyBullet(int i);
void moveBullets();
void moveEnemyBullets();
void moveDragonflys();
void updateCollision();
int getLives();
int enemiesDead();
void beeShoot();	