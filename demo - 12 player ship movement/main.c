/*
** Gamepad Routine
** Copyright (c) 2021, Nicholas John Joseph Taylor (nicholas.john.joseph.taylor@gmail.com)
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in the
**       documentation and/or other materials provided with the distribution.
**     * Neither the name of the Johannes Fetz nor the
**       names of its contributors may be used to endorse or promote products
**       derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL Johannes Fetz BE LIABLE FOR ANY
** DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
** (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
** ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <jo/jo.h>

const int MAX_SHIP_SPEED = 4;

static int ship_sprite_id;
static int bullet_sprite_id;

static bool is_in_cb_gamepad = false;
static bool is_in_cb_draw = false;

struct obj_player
{
	int x;
	int x_throttle;
	int y;
	int y_throttle;
};

struct obj_player player[12];

void cb_draw(void)
{	
	if(!is_in_cb_draw)
	{
		is_in_cb_draw = true;
		
		// Draw 12 players
		for(int i = 0; i < JO_INPUT_MAX_DEVICE; i++)
		{
			jo_sprite_draw3D(ship_sprite_id, player[i].x, player[i].y, 450);
			
		}
		
		is_in_cb_draw = false;
		
	}
	
}

void cb_gamepad(void)
{
	if(!is_in_cb_gamepad)
	{
		is_in_cb_gamepad = true;
			
		// 1 - 12 players
		// 0..5 multitap 1
		// 6..11 multitap 2
		for(int i = 0; i < JO_INPUT_MAX_DEVICE; i++)
		{			
			// If controller is not available then check next controller
			if (!jo_is_input_available(i))
			{
				
				continue;
			}
	
			// Switch DPad
			switch (jo_get_input_direction_pressed(i))
			{
			    case DOWN:
			    	//Down
			    	if(player[i].y_throttle < MAX_SHIP_SPEED)
		    		{
		    				player[i].y_throttle+=2;
		    		}
			    	break;
			    	
			    case DOWN_LEFT:
			    	//Down
			    	if(player[i].y_throttle < MAX_SHIP_SPEED)
		    		{
		    				player[i].y_throttle+=2;
		    		}
		    		//Left
			    	if(player[i].x_throttle > 0-MAX_SHIP_SPEED)
		    		{
		    				player[i].x_throttle-=2;
		    		}
			    	break;
			    	
			    case LEFT:
		    		//Left
			    	if(player[i].x_throttle > 0-MAX_SHIP_SPEED)
		    		{
		    				player[i].x_throttle-=2;
		    		}			    	
			    	break;
			    	
			    case UP_LEFT: 
			    	//Up
			    	if(player[i].y_throttle > 0-MAX_SHIP_SPEED)
		    		{
		    				player[i].y_throttle-=2;
		    		}
		    		//Left
			    	if(player[i].x_throttle > 0-MAX_SHIP_SPEED)
		    		{
		    				player[i].x_throttle-=2;
		    		}
			    	break;
			    	
			    case UP:
			    	//Up
			    	if(player[i].y_throttle > 0-MAX_SHIP_SPEED)
		    		{
		    				player[i].y_throttle-=2;
		    		}
			    	break;
			    	
			    case UP_RIGHT:
			    	//Up
			    	if(player[i].y_throttle > 0-MAX_SHIP_SPEED)
		    		{
		    				player[i].y_throttle-=2;
		    		}
		    		//Right
			    	if(player[i].x_throttle < MAX_SHIP_SPEED)
		    		{
		    				player[i].x_throttle+=2;
		    		}
			    	break;
			    	
			    case RIGHT:
		    		//Right
			    	if(player[i].x_throttle < MAX_SHIP_SPEED)
		    		{
		    				player[i].x_throttle+=2;
		    		}
			    	break;
			    	
			    case DOWN_RIGHT:
			    	//Down
			    	if(player[i].y_throttle < MAX_SHIP_SPEED)
		    		{
		    				player[i].y_throttle+=2;
		    		}
		    		//Right
			    	if(player[i].x_throttle < MAX_SHIP_SPEED)
		    		{
		    				player[i].x_throttle+=2;
		    		}
			    	break;
			    	
			    case NONE: 
			    	
			    	break;
			}
	

    	//Center y
    	if(player[i].y_throttle > 0)
  		{
  				player[i].y_throttle--;
  		}
    	if(player[i].y_throttle < 0)
  		{
  				player[i].y_throttle++;
  		}
  		//Center x
    	if(player[i].x_throttle < 0)
  		{
  				player[i].x_throttle++;
  		}
    	if(player[i].x_throttle > 0)
  		{
  				player[i].x_throttle--;
  		}
			// Update x and y
			player[i].x = player[i].x + player[i].x_throttle;
			player[i].y = player[i].y + player[i].y_throttle;
			
	
			// Inividual buttons
			if (jo_is_input_key_pressed(i, JO_KEY_START))
			{
				
			}
			
			if (jo_is_input_key_pressed(i, JO_KEY_L))
			{
				
			}
			
			if (jo_is_input_key_pressed(i, JO_KEY_R))
			{
				
			}
			
			if (jo_is_input_key_pressed(i, JO_KEY_A))
			{
				
			}
			
			if (jo_is_input_key_pressed(i, JO_KEY_B))
			{
				
			}
			
			if (jo_is_input_key_pressed(i, JO_KEY_C))
			{
				
			}
	
			if (jo_is_input_key_pressed(i, JO_KEY_X))
			{
				
			}
			
			if (jo_is_input_key_pressed(i, JO_KEY_Y))
			{
				
			}
			
			if (jo_is_input_key_pressed(i, JO_KEY_Z))
			{
				
			}
					
		}

		is_in_cb_gamepad = false;

	}
	
}

void jo_main(void)
{
	//clear screen
	jo_core_init(JO_COLOR_Black);
	
	//Load graphics
	ship_sprite_id = jo_sprite_add_tga(JO_ROOT_DIR, "TRISHIP.TGA", JO_COLOR_Green);
	bullet_sprite_id = jo_sprite_add_tga(JO_ROOT_DIR, "BULLET.TGA", JO_COLOR_Green);
	
	//Add callbacks called once per frame
	jo_core_add_callback(cb_gamepad);
	jo_core_add_callback(cb_draw);
	
	jo_core_run();
	
}
