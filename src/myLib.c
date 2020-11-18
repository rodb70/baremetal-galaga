// Drew Teachout

#include "fontData.h"
#include "deluxegalaga.h"
#include "ship.h"
#include "space.h"
#include "bee.h"
#include "dragonfly.h"
#include "bullet.h"
#include "enemybullet.h"
#include <stdio.h>
#include "mylib.h"

enum GBAState state;
extern unsigned short *videoBuffer;
extern const unsigned char fontdata_6x8[12288];
int lives;
int currentState;
int numBees = 6;
int numDragonflys = 4;
int numBullets = 50;
int numEnemyBullets = 50;
int bulletCounter = 40;
int roundCounter = 0;

struct ship
{
    int row, col;
    int oldRow, oldCol;
} shippy;

struct bee
{
    int row, col;
    int oldRow, oldCol;
    int alive;
} bees[6];

struct dragonfly
{
    int row, col;
    int oldRow, oldCol;
    int alive;
} dragonflys[4];

struct bullet
{
    int row, col;
    int oldRow, oldCol;
    int alive;
} bullets[50];

struct enemyBullet
{
    int row, col;
    int oldRow, oldCol;
    int alive;
} enemyBullets[ 50 ];

void drawChar(int row, int col, char ch, uint16_t color)
{
    for( int c = 0; c < 8; c++ )
    {
        for( int r = 0; r < 6; r++ )
        {
            if( fontdata_6x8[ OFFSET( c, r, 6) + ch * 48 ])
            {
                setPixel( row + r, col + c, color );
            }
        }
    }
}

void drawString(int row, int col, char *str, unsigned short color)
{
    while( *str )
    {
        drawChar( row, col, *str++, color );
        row += 6;
    }
}

void initialize(void)
{
    currentState = 0;
    state = START;
}

void startGame(int l)
{
    lives = l;
    fillScreen( BLACK );
    resetShip();
    drawImage3( shippy.row, shippy.col, SHIP_WIDTH, SHIP_HEIGHT, ship );
    resetBees();
    drawBees();
    resetDragonflys();
    drawDragonflys();
    resetBullet();
    resetEnemyBullet();
    bulletCounter = 40;
    roundCounter = 0;
}

void loseLife(void)
{
    lives--;
    resetShip();
}

void moveShipRight(void)
{
    if( shippy.row < 226 )
    {
        shippy.oldRow = shippy.row;
        shippy.row++;
    }
}

void moveShipLeft(void)
{
    if( shippy.row > 0 )
    {
        shippy.oldRow = shippy.row;
        shippy.row--;
    }
}

void startScreen(void)
{
    drawImage3( 0, 0, DELUXEGALAGA_WIDTH, DELUXEGALAGA_HEIGHT, deluxegalaga );
}

void shoot(void)
{
    addNewBullet();
    for( int i = 0; i < numBullets; i++ )
    {
        drawBullet( i );
    }
}

void enemyShoot(int n)
{
    addEnemyBullet( n );
    for( int i = 0; i < numEnemyBullets; i++ )
    {
        drawEnemyBullet( i );
    }
}

void setCurrentState(int i)
{
    currentState = i;
}

int getCurrentState(void)
{
    return currentState;
}

void resetShip(void)
{
    shippy.row = (240 - SHIP_WIDTH) / 2 + 20;
    shippy.col = 130 - SHIP_HEIGHT;
    shippy.oldRow = shippy.row;
    shippy.oldCol = shippy.col;
}

void drawShip(void)
{
    drawRect( shippy.oldRow, shippy.oldCol, SHIP_WIDTH+1, SHIP_HEIGHT, BLACK );
    drawImage3( shippy.row, shippy.col, SHIP_WIDTH, SHIP_HEIGHT, ship );
}

void resetBees(void)
{
    for( int i = 0; i < numBees; i++ )
    {
        bees[ i ].col = 12;
        bees[ i ].row = 200 * (i + 1) / numBees;
        bees[ i ].alive = 1;
    }
}

void drawBees(void)
{
    for( int i = 0; i < numBees; i++ )
    {
        if( bees[i].alive )
        {
            //drawRect( bees[ i ].oldRow, bees[ i ].oldCol, BEE_WIDTH, BEE_HEIGHT, BLACK);
            drawImage3( bees[ i ].row, bees[ i ].col, BEE_WIDTH, BEE_HEIGHT, bee );
        }

    }
}

void resetDragonflys(void)
{
    for( int i = 0; i < numDragonflys; i++ )
    {
        dragonflys[ i ].col = 24;
        dragonflys[ i ].row = 20 + (i * 13);
        dragonflys[ i ].oldRow = dragonflys[ i ].row;
        dragonflys[ i ].oldCol = dragonflys[ i ].col;
        dragonflys[ i ].alive = 1;
    }
}

void drawDragonflys(void)
{
    for( int i = 0; i < numDragonflys; i++ )
    {
        if( dragonflys[ i ].alive )
        {
            drawRect( dragonflys[ i ].oldRow, dragonflys[ i ].oldCol, DRAGONFLY_WIDTH, DRAGONFLY_HEIGHT, BLACK );
            drawImage3( dragonflys[ i ].row, dragonflys[ i ].col, DRAGONFLY_WIDTH, DRAGONFLY_HEIGHT, dragonfly );
        }
    }
}

void addNewBullet( void )
{
    for( int i = 0; i < numBullets; i++ )
    {
        if( bullets[ i ].alive == 0 )
        {
            bullets[ i ].row = shippy.row + (( SHIP_WIDTH / 2 ) - 2 );
            bullets[ i ].col = shippy.col - ( SHIP_HEIGHT / 2 );
            bullets[ i ].alive = 1;
            bullets[ i ].oldRow = bullets[ i ].row;
            bullets[ i ].oldCol = bullets[ i ].col;
            break;
        }
    }
}

void addEnemyBullet(int n)
{
    for( int i = 0; i < numEnemyBullets; i++ )
    {
        if( enemyBullets[ i ].alive == 0 )
        {
            enemyBullets[ i ].col = dragonflys[ n ].col + (DRAGONFLY_HEIGHT + 7);
            enemyBullets[ i ].row = dragonflys[ n ].row + (DRAGONFLY_WIDTH / 2 - 2);
            enemyBullets[ i ].alive = 1;
            enemyBullets[ i ].oldRow = enemyBullets[ i ].row;
            enemyBullets[ i ].oldCol = enemyBullets[ i ].col;
            break;
        }
    }
}

void addBeeBullet( int n )
{
    for( int i = 0; i < numEnemyBullets; i++ )
    {
        if( enemyBullets[ i ].alive == 0 )
        {
            enemyBullets[ i ].col = bees[ n ].col + (BEE_HEIGHT + 7);
            enemyBullets[ i ].row = bees[ n ].row + ((BEE_WIDTH / 2 ) - 2);
            enemyBullets[ i ].alive = 1;
            enemyBullets[ i ].oldRow = enemyBullets[ i ].row;
            enemyBullets[ i ].oldCol = enemyBullets[ i ].col;
            break;
        }
    }
}

void resetBullet(void)
{
    for( int i = 0; i < numBullets; i++ )
    {
        bullets[ i ].alive = 0;
    }
}

void resetEnemyBullet(void)
{
    for( int i = 0; i < numEnemyBullets; i++ )
    {
        enemyBullets[ i ].alive = 0;
    }
}

void drawBullet(int i)
{
    if( bullets[ i ].alive )
    {
        setPixel( bullets[ i ].oldRow + 1, bullets[ i ].oldCol + BULLET_HEIGHT, BLACK );
        drawImage3( bullets[ i ].row, bullets[ i ].col, BULLET_WIDTH, BULLET_HEIGHT, bullet );
    }
}

void drawEnemyBullet(int i)
{
    if( enemyBullets[ i ].alive )
    {
        drawRect( enemyBullets[ i ].oldRow, enemyBullets[ i ].oldCol,
                  ENEMYBULLET_WIDTH+1, ENEMYBULLET_HEIGHT,
                  BLACK );
        drawImage3( enemyBullets[ i ].row, enemyBullets[ i ].col,
                    ENEMYBULLET_WIDTH, ENEMYBULLET_HEIGHT,
                    enemybullet );
    }
}

void moveBullets( void )
{
    for( int i = 0; i < numBullets; i++ )
    {
        if( bullets[ i ].alive )
        {
            bullets[ i ].oldCol = bullets[ i ].col;
            bullets[ i ].col--;
            if( bullets[ i ].col < -BULLET_HEIGHT - 1 )
            {
                bullets[ i ].alive = 0;
            }
        }
    }
    for( int i = 0; i < numBullets; i++ )
    {
        if( bullets[ i ].alive )
        {
            drawBullet( i );
        }
    }
}

void moveEnemyBullets( void )
{
    for( int i = 0; i < numEnemyBullets; i++ )
    {
        if( enemyBullets[ i ].alive )
        {
            enemyBullets[ i ].oldCol = enemyBullets[i].col;
            enemyBullets[ i ].col++;
            if( enemyBullets[ i ].col > SCREEN_HEIGHT )
            {
                enemyBullets[ i ].alive = 0;
            }
        }
    }

    for( int i = 0; i < numEnemyBullets; i++ )
    {
        drawEnemyBullet( i );
    }
}

void moveDragonflys( void )
{
    for( int i = 0; i < numDragonflys; i++ )
    {
        if( dragonflys[ i ].alive )
        {
            if( dragonflys[ i ].col < 100 )
            {
                dragonflys[ i ].oldCol = dragonflys[ i ].col;
                dragonflys[ i ].col++;
            }

            if( dragonflys[ i ].row < 160 + ( i * 13 ))
            {
                dragonflys[ i ].oldRow = dragonflys[ i ].row;
                dragonflys[ i ].row++;
            }

            if(( bulletCounter == 40 ) && ( roundCounter < 4 ))
            {
                enemyShoot( i );
            }
        }
    }

    if( bulletCounter == 50 )
    {
        bulletCounter = 0;
        roundCounter++;
    }

    bulletCounter++;
    drawDragonflys();
}

void updateCollision(void)
{
    for( int i = 0; i < numBullets; i++ )
    {
        //Bullet with bee
        for( int j = 0; j < numBees; j++ )
        {
            if( bees[ j ].alive && bullets[ i ].alive )
            {
                if( bullets[ i ].col < bees[ j ].col + BEE_HEIGHT &&
                    ( bullets[ i ].row + 2 > bees[ j ].row && bullets[ i ].row < bees[ j ].row + BEE_WIDTH ))
                {
                    drawRect( bees[ j ].row, bees[ j ].col, BEE_WIDTH, BEE_HEIGHT, BLACK );
                    bees[ j ].alive = 0;
                    drawRect( bullets[ i ].oldRow, bullets[ i ].oldCol, BULLET_WIDTH, BULLET_HEIGHT, BLACK );
                    bullets[ i ].alive = 0;
                }
            }
        }

        // Bullet with dragonfly
        for( int j = 0; j < numDragonflys; j++ )
        {
            if( dragonflys[ j ].alive && bullets[ i ].alive )
            {
                if(( bullets[ i ].col < dragonflys[ j ].col + DRAGONFLY_HEIGHT &&
                     bullets[ i ].col + BULLET_HEIGHT > dragonflys[ j ].col ) &&
                   ( bullets[ i ].row < dragonflys[ j ].row + DRAGONFLY_WIDTH &&
                     bullets[ i ].row + BULLET_WIDTH > dragonflys[ j ].row ))
                {
                    drawRect( dragonflys[ j ].row, dragonflys[ j ].col,
                              DRAGONFLY_WIDTH, DRAGONFLY_HEIGHT, BLACK );
                    dragonflys[ j ].alive = 0;
                    drawRect( bullets[ i ].oldRow, bullets[ i ].oldCol,
                              BULLET_WIDTH, BULLET_HEIGHT, BLACK );
                    bullets[ i ].alive = 0;
                }
            }
        }
    }

    for( int i = 0; i < numEnemyBullets; i++ )
    {
        if( enemyBullets[ i ].alive && lives )
        {
            if(( enemyBullets[ i ].col + ENEMYBULLET_HEIGHT > shippy.col && enemyBullets[ i ].col < shippy.col + SHIP_HEIGHT ) &&
               ( enemyBullets[ i ].row < shippy.row + SHIP_WIDTH && enemyBullets[ i ].row + ENEMYBULLET_WIDTH > shippy.row ))
            {
                lives--;
                enemyBullets[ i ].alive = 0;
                drawRect( enemyBullets[ i ].oldRow, enemyBullets[ i ].oldCol,
                          ENEMYBULLET_WIDTH, ENEMYBULLET_HEIGHT, BLACK );
                roundCounter = 0;
                break;
            }
        }
    }
}

int getLives( void )
{
    return lives;
}

int enemiesDead( void )
{
    int dead = 1;

    for( int i = 0; i < numBees; i++ )
    {
        if( bees[ i ].alive )
        {
            dead = 0;
        }
    }

    for( int i = 0; i < numDragonflys; i++ )
    {
        if( dragonflys[ i ].alive )
        {
            dead = 0;
        }
    }

    return dead;
}

void beeShoot( void )
{
    for( int i = 0; i < numBees; i++ )
    {
        if( bees[ i ].alive )
        {
            addBeeBullet( i );
        }
    }
}
