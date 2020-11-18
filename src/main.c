// Drew Teachout

#include "space.h"
#include "ship.h"
#include <stdio.h>
#include "mylib.h"

int main(void)
{
    volatile int canShoot = 1;
    int bulletSlow = 0;
    int oldLives = 3;
    int beeBullets = 350;
    char startKey[] = "Press Start";
    char gameOver[] = "Game Over";
    string nextStage = "Next Stage Loading...";
    hardware_video_init();
    char buffer[41];
    initialize();
    resetBullet();
    while( 1 )
    {
        waitForVblank();
        switch( state )
        {
        case START:
            startScreen();
            drawString( 80, 120, startKey, WHITE );
            state = NODRAW;
            setCurrentState( 0 );
            break;

        case GAME:
            startGame( oldLives );
            state = NODRAW;
            setCurrentState( 1 );
            break;

        case GAMEOVER:
            drawImage3( 0, 0, 240, 160, space );
            drawString( 120, 100, gameOver, WHITE );
            delay( 30 );
            oldLives = 3;
            state = START;
            break;

        case NODRAW:
            if( getCurrentState() != 0 && KEY_DOWN_NOW( BUTTON_SELECT ) )
            {
                state = START;
            }
            else if( getCurrentState() == 0 )
            {
                if( KEY_DOWN_NOW( BUTTON_START ) )
                {
                    state = GAME;
                }
            }
            else if( getCurrentState() == 1 )
            {
                if( KEY_DOWN_NOW( BUTTON_RIGHT ) )
                {
                    moveShipRight();
                    drawShip();
                }
                if( KEY_DOWN_NOW( BUTTON_LEFT ) )
                {
                    moveShipLeft();
                    drawShip();
                }
                if( KEY_DOWN_NOW( BUTTON_SELECT ) )
                {
                    state = START;
                }
                if( KEY_DOWN_NOW( BUTTON_A ) )
                {
                    if( canShoot )
                    {
                        shoot();
                        canShoot = 0;
                    }
                }
                if( KEY_DOWN_NOW(BUTTON_A) == 0 )
                {
                    canShoot = 1;
                }
                moveBullets();
                if( beeBullets == 400 )
                {
                    beeShoot();
                    beeBullets = 0;
                }
                if( bulletSlow == 2 )
                {
                    moveDragonflys();
                    moveEnemyBullets();
                    bulletSlow = 0;
                }
                beeBullets++;
                bulletSlow++;
                updateCollision();
                sprintf( buffer, "Lives: %d", getLives() );
                drawString( 190, 3, buffer, RED );
                if( enemiesDead() )
                {
                    fillScreen( BLACK );
                    drawString( 50, 80, nextStage, WHITE );
                    delay( 25 );
                    state = GAME;
                    setCurrentState( 1 );
                }
                else if( getLives() == 0 )
                {
                    state = GAMEOVER;
                    setCurrentState( -1 );
                }
                if( getLives() < oldLives )
                {
                    setCurrentState( 1 );
                    state = GAME;
                }
                oldLives = getLives();
            }
            break;
        }
    }
}
