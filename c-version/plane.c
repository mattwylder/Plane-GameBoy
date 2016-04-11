#include <stdio.h>
#include <gb/gb.h>
#include <stdlib.h>
#include "plane_tile.c"

typedef struct _bullet{
  UBYTE spriteNum;
  int posx;
  int posy;
  UBYTE active;
} bullet;

/**
 * Moves the sprite to posx, posy.
 */
void move_plane(int posx, int posy){
  move_sprite(0,posx,posy); //Place tile 0 to x: 0x0F, y:0x0F
  move_sprite(1,posx+0x08,posy-0x05);
  move_sprite(2,posx+0x08,posy+0x03);
  move_sprite(3,posx+0x10,posy);
}

void INIT(){
  //For some reason this is required to print anything to the screen
  printf(" ");

  HIDE_BKG;
  HIDE_SPRITES;
  HIDE_WIN;
  DISPLAY_OFF;

  //Not sure how map data works yet
  set_sprite_data(0,7, plane_tile2);
  set_sprite_tile(0,2); //tile 0 is left wing
  set_sprite_tile(1,0);
  set_sprite_tile(2,1); //tile 1 is plane body
  set_sprite_tile(3,3); //tile 2 is right wing

  //bullets
  set_sprite_tile(4,5);
  set_sprite_tile(5,5);
  set_sprite_tile(6,5);

  SHOW_BKG;
	SHOW_SPRITES;
	DISPLAY_ON;
}

void main(){

  UBYTE key; //The key pressed
  UBYTE moved = 0;
  int posx = 0x2F; // X position of Mario's top left sprite
  int posy = 0x5F; // Y position of Mario's top left sprite
  UBYTE gamespeed = 15;
  UBYTE animate = 0;
  UBYTE numbullets = 3;
  UBYTE i;
  UBYTE cooldown_timer = 101;


  INIT();
  move_plane(posx,posy);
  //XXX: Causes the screen to be stripes
  // for(i = 0; i < numbullets; ++i){
  //   bullet_ptr[i].spriteNum = 4+i;
  //   bullet_ptr[i].posx = 0x0F;
  //   bullet_ptr[i].posy = 0x0F + i*0x10;
  //   move_sprite(bullet_ptr[i].spriteNum, bullet_ptr[i].posx, bullet_ptr[i].posy);
  // }

  // move_sprite(4,0x0F,0x0F);
  // move_sprite(5,0x0F,0x1F);
  // move_sprite(6,0x0F,0x2F);


  while(1){
      key = joypad();
      // for(i = 0; i < numbullets; i++){
        // cbullet.posy--;
        // move_sprite(cbullet.spriteNum, cbullet.posx,cbullet.posy );
        // if(cbullet.posy < 0x10){
        //   free(cbullet);
        //   numbullets--;
        // }
      //
      // }

      if(key & J_DOWN &&posy < 0x95 ){
        ++posy;
        moved = 1;
      }
      if (key & J_LEFT && posx > 0x08){
        --posx;
        moved = 1;
      }
      if (key & J_RIGHT &&  posx < 0x97 ){
        ++posx;
        moved = 1;
      }
      if(key & J_UP && posy > 0x014 ){
        --posy;
        moved = 1;
      }
      if(key & J_A && cooldown_timer > 100){
        numbullets++;

      }

      if(moved){
        move_plane(posx,posy);
      }


      delay(gamespeed);
      if(animate % 16==0){
        set_sprite_tile(1,4);
      }
      else if (animate % 8 == 0){
        set_sprite_tile(1,0);
      }
      animate++;
      cooldown_timer++;
      moved=0;
  }

}
