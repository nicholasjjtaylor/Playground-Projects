/*
** Playground Projects - Starfield
** Detonation Hyperdrive Demo
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

static int logo_sprite_id;
static int debris1_sprite_id;
static int debris2_sprite_id;
static int debris3_sprite_id;
static int debris4_sprite_id;
static int debris5_sprite_id;
static int debris6_sprite_id;
static int debris7_sprite_id;
static int debris8_sprite_id;

static bool is_in_cb_draw_scene = false;

static int scene_state = 0;

const int MAX_DEBRIS = 256;

struct obj_debris
{
	bool active;
	int x;
	int y;
	int speed;
	int sprite_id;
};

struct obj_debris debris[256];

void cb_draw_scene(void)
{	
	if(!is_in_cb_draw_scene)
	{
		is_in_cb_draw_scene = true;
		
		switch(scene_state)
		{
			default:
			case 0: // Initialisation			
				// Text
				//jo_printf(1, 1, "Brightness value: %d", brightness);
				jo_printf(1, 1, "Playground Projects");
				jo_printf(1, 2, "Demo 05 - Starfield/Debris");
				jo_printf(1, 4, "by Segata Sanshiro");
					
				// Init debris positions
				for(int i = 0; i < MAX_DEBRIS; i++)
				{
					debris[i].x = jo_random(320) - 160;
					debris[i].y = jo_random(244) - 122;					
					debris[i].speed = jo_random(8);			
					switch(jo_random(8))
					{
						case 1:
							debris[i].sprite_id = debris1_sprite_id;
							break;
						case 2:
							debris[i].sprite_id = debris2_sprite_id;
							break;
						case 3:
							debris[i].sprite_id = debris3_sprite_id;
							break;
						case 4:
							debris[i].sprite_id = debris4_sprite_id;
							break;
						case 5:
							debris[i].sprite_id = debris5_sprite_id;
							break;
						case 6:
							debris[i].sprite_id = debris6_sprite_id;
							break;
						case 7:
							debris[i].sprite_id = debris7_sprite_id;
							break;
						default:
						case 8:
							debris[i].sprite_id = debris8_sprite_id;
							break;
					}
				}			
				scene_state = 1;
				
				break;
				
			case 1: // Update								
				// Update debris
				for(int i = 0; i < MAX_DEBRIS; i++)
				{
					debris[i].y = debris[i].y + debris[i].speed;
					
					while(debris[i].y > 122)
					{
						debris[i].y = debris[i].y - 244;
						debris[i].x = jo_random(320) - 160;				
						debris[i].speed = jo_random(8);			
						switch(jo_random(8))
						{
							case 1:
								debris[i].sprite_id = debris1_sprite_id;
								break;
							case 2:
								debris[i].sprite_id = debris2_sprite_id;
								break;
							case 3:
								debris[i].sprite_id = debris3_sprite_id;
								break;
							case 4:
								debris[i].sprite_id = debris4_sprite_id;
								break;
							case 5:
								debris[i].sprite_id = debris5_sprite_id;
								break;
							case 6:
								debris[i].sprite_id = debris6_sprite_id;
								break;
							case 7:
								debris[i].sprite_id = debris7_sprite_id;
								break;
							default:
							case 8:
								debris[i].sprite_id = debris8_sprite_id;
								break;
						}
					}
					
						jo_sprite_draw3D(debris[i].sprite_id, debris[i].x, debris[i].y, 450);
					
				}
				
				// Add logo				
				jo_sprite_draw3D(logo_sprite_id, 0, 0, 450);
				
				break;
		}
			
		is_in_cb_draw_scene = false;
		
	}
	
}

void jo_main(void)
{	
	//clear screen
	jo_core_init(JO_COLOR_Black);
	
	//Load graphics
	logo_sprite_id = jo_sprite_add_tga(JO_ROOT_DIR, "LOGO1.TGA", JO_COLOR_Green);
	debris1_sprite_id = jo_sprite_add_tga(JO_ROOT_DIR, "DEBRIS1.TGA", JO_COLOR_Green);
	debris2_sprite_id = jo_sprite_add_tga(JO_ROOT_DIR, "DEBRIS2.TGA", JO_COLOR_Green);
	debris3_sprite_id = jo_sprite_add_tga(JO_ROOT_DIR, "DEBRIS3.TGA", JO_COLOR_Green);
	debris4_sprite_id = jo_sprite_add_tga(JO_ROOT_DIR, "DEBRIS4.TGA", JO_COLOR_Green);
	debris5_sprite_id = jo_sprite_add_tga(JO_ROOT_DIR, "DEBRIS5.TGA", JO_COLOR_Green);
	debris6_sprite_id = jo_sprite_add_tga(JO_ROOT_DIR, "DEBRIS6.TGA", JO_COLOR_Green);
	debris7_sprite_id = jo_sprite_add_tga(JO_ROOT_DIR, "DEBRIS7.TGA", JO_COLOR_Green);
	debris8_sprite_id = jo_sprite_add_tga(JO_ROOT_DIR, "DEBRIS8.TGA", JO_COLOR_Green);
	
	//Add callbacks called once per frame
	jo_core_add_callback(cb_draw_scene);
	
	jo_core_run();
	
}
