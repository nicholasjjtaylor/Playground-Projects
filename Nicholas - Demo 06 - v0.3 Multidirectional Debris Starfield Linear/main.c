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

static int cos_32767[256]; // 256 degrees in our circles

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

const int SCREEN_WIDTH_4 = 320 * 4;
const int SCREEN_HEIGHT_4 = 244 * 4;

struct obj_debris
{
	bool active;
	int x_4; // The _4 is to remind me to divide by 4 before rendering
	int y_4; // The _4 is to remind me to divide by 4 before rendering
	int angle_256; //The _256 is to remind me that circles have 256 degrees
	int speed;
	int sprite_id;
};

struct obj_debris debris[256];

int mycos(int angle_256)
{
	return cos_32767[angle_256];
}

int mysin(int angle_256)
{
	if(angle_256 < 64)
	{
		angle_256+=192;
	}
	else
	{
		angle_256-=64;
	}
	return cos_32767[angle_256];
}

void init_debris_screen_edge_rnd(int i)
{	
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
	debris[i].speed = jo_random(7) + 1;		
	debris[i].angle_256 = jo_random(255);
	if(debris[i].angle_256 >= 96 && debris[i].angle_256 < 160) // specifically moving north (angle 128 moves up the screen)
	{
		debris[i].x_4 = jo_random(SCREEN_WIDTH_4) - (SCREEN_WIDTH_4/2);
		debris[i].y_4 = (SCREEN_HEIGHT_4/2);
	}
	if((debris[i].angle_256 >= 0 && debris[i].angle_256 < 32) || (debris[i].angle_256 >= 224 && debris[i].angle_256 <= 256)) // specifically moving south (angle 0 moves down the screen)
	{
		debris[i].x_4 = jo_random(SCREEN_WIDTH_4) - (SCREEN_WIDTH_4/2);
		debris[i].y_4 = 0 - (SCREEN_HEIGHT_4/2);
	}
	if(debris[i].angle_256 >= 32 && debris[i].angle_256 < 96) // specifically moving east (angle 64 moves right along the screen)
	{
		debris[i].x_4 = 0 - (SCREEN_WIDTH_4/2);
		debris[i].y_4 = jo_random(SCREEN_HEIGHT_4) - (SCREEN_HEIGHT_4/2);		
	}
	if(debris[i].angle_256 >= 160 && debris[i].angle_256 < 224) // specifically moving west (angle 64 moves left along the screen)
	{
		debris[i].x_4 = (SCREEN_WIDTH_4/2);
		debris[i].y_4 = jo_random(SCREEN_HEIGHT_4) - (SCREEN_HEIGHT_4/2);							
	}				
	debris[i].active = 1;	
}

/*
void init_debris(int i, int sprite_id, int angle_256, int speed, int x_4, int y_4)
{			
	switch(sprite_id)
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
	debris[i].angle_256 = angle_256;
	debris[i].speed = speed;
	debris[i].x_4 = x_4;
	debris[i].y_4 = y_4;
	debris[i].active = 1;
}

void init_debris_screen_edge(int i, int sprite_id, int angle_256, int speed)
{	
	if(debris[i].angle_256 >= 96 && debris[i].angle_256 < 160) // specifically moving north (angle 128 moves up the screen)
	{
		init_debris(i, sprite_id, angle_256, speed, jo_random(SCREEN_WIDTH_4) - (SCREEN_WIDTH_4/2), (SCREEN_HEIGHT_4/2));
	}
	if(debris[i].angle_256 >= 0 && debris[i].angle_256 < 256 && debris[i].angle_256 >= 224 && debris[i].angle_256 < 32) // specifically moving south (angle 0 moves down the screen)
	{
		init_debris(i, sprite_id, angle_256, speed, jo_random(SCREEN_WIDTH_4) - (SCREEN_WIDTH_4/2), 0 - (SCREEN_HEIGHT_4/2));		
	}
	if(debris[i].angle_256 >= 32 && debris[i].angle_256 < 96) // specifically moving east (angle 64 moves right along the screen)
	{
		init_debris(i, sprite_id, angle_256, speed, 0 - (SCREEN_WIDTH_4/2), jo_random(SCREEN_HEIGHT_4) - (SCREEN_HEIGHT_4/2));		
	}
	if(debris[i].angle_256 >= 160 && debris[i].angle_256 < 224) // specifically moving west (angle 64 moves left along the screen)
	{
		init_debris(i, sprite_id, angle_256, speed, (SCREEN_WIDTH_4/2), jo_random(SCREEN_HEIGHT_4) - (SCREEN_HEIGHT_4/2));							
	}				
}

void init_debris_screen_edge_rnd(int i)
{
	init_debris_screen_edge(i, (jo_random(7)+1), jo_random(255), (jo_random(7)+1));
}
*/
void deinit_debris(int i)
{
	debris[i].active = 0;	
}

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
				jo_printf(1, 2, "Demo 06 v0.3 - Multidirectional");
				jo_printf(1, 3, "Starfield/Debris Linear");
				jo_printf(1, 4, "by Segata Sanshiro");
					
				// Init debris positions
				for(int i = 0; i < MAX_DEBRIS; i++)
				{					
					if(debris[i].active == 0)
					{
						init_debris_screen_edge_rnd(i);
					}
				}			
				scene_state = 1;
				
				break;
				
			case 1: // Update				
				// Update debris	
				for(int i = 0; i < MAX_DEBRIS; i++)
				{
					if(debris[i].active == 1)
					{
						debris[i].x_4 = debris[i].x_4 + ((mysin(debris[i].angle_256) * debris[i].speed) / 8192); //32767/4= ...will be divided at render time
						debris[i].y_4 = debris[i].y_4 + ((mycos(debris[i].angle_256) * debris[i].speed) / 8192); //32767/4= ...will be divided at render time
												
						if((debris[i].angle_256 >= 0 && debris[i].angle_256 < 64) || (debris[i].angle_256 >= 192 && debris[i].angle_256 <= 256)) // angle 0 moves down the screen
						{
							if(debris[i].y_4 > (SCREEN_HEIGHT_4/2) + debris[i].speed)
							{
								deinit_debris(i);
							}							
						}
						
						if(debris[i].angle_256 >= 64 && debris[i].angle_256 < 192) // angle 128 moves up the screen
						{
							if(debris[i].y_4 < 0 - (SCREEN_HEIGHT_4/2) - debris[i].speed)
							{
								deinit_debris(i);
							}							
						}
						
						if(debris[i].angle_256 >= 0 && debris[i].angle_256 < 128) // angle 64 moves right along the screen
						{			
							if(debris[i].x_4 > (SCREEN_WIDTH_4/2) + debris[i].speed)
							{
								deinit_debris(i);
							}					
						}
						
						if(debris[i].angle_256 >= 128 && debris[i].angle_256 < 256) // angle 192 moves left along the screen
						{
							if(debris[i].x_4 < 0 - (SCREEN_WIDTH_4/2) - debris[i].speed)
							{
								deinit_debris(i);
							}						
						}
						
						jo_sprite_draw3D(debris[i].sprite_id, debris[i].x_4/4, debris[i].y_4/4, 450);
					}
					else
					{
						init_debris_screen_edge_rnd(i);
					}
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
	//Tables
cos_32767[0] = 32767;
cos_32767[1] = 32757;
cos_32767[2] = 32728;
cos_32767[3] = 32678;
cos_32767[4] = 32609;
cos_32767[5] = 32521;
cos_32767[6] = 32412;
cos_32767[7] = 32285;
cos_32767[8] = 32137;
cos_32767[9] = 31971;
cos_32767[10] = 31785;
cos_32767[11] = 31580;
cos_32767[12] = 31356;
cos_32767[13] = 31113;
cos_32767[14] = 30852;
cos_32767[15] = 30571;
cos_32767[16] = 30273;
cos_32767[17] = 29956;
cos_32767[18] = 29621;
cos_32767[19] = 29268;
cos_32767[20] = 28898;
cos_32767[21] = 28510;
cos_32767[22] = 28105;
cos_32767[23] = 27683;
cos_32767[24] = 27245;
cos_32767[25] = 26790;
cos_32767[26] = 26319;
cos_32767[27] = 25832;
cos_32767[28] = 25329;
cos_32767[29] = 24811;
cos_32767[30] = 24279;
cos_32767[31] = 23731;
cos_32767[32] = 23170;
cos_32767[33] = 22594;
cos_32767[34] = 22005;
cos_32767[35] = 21403;
cos_32767[36] = 20787;
cos_32767[37] = 20159;
cos_32767[38] = 19519;
cos_32767[39] = 18868;
cos_32767[40] = 18204;
cos_32767[41] = 17530;
cos_32767[42] = 16846;
cos_32767[43] = 16151;
cos_32767[44] = 15446;
cos_32767[45] = 14732;
cos_32767[46] = 14010;
cos_32767[47] = 13279;
cos_32767[48] = 12539;
cos_32767[49] = 11793;
cos_32767[50] = 11039;
cos_32767[51] = 10278;
cos_32767[52] = 9512;
cos_32767[53] = 8739;
cos_32767[54] = 7962;
cos_32767[55] = 7179;
cos_32767[56] = 6393;
cos_32767[57] = 5602;
cos_32767[58] = 4808;
cos_32767[59] = 4011;
cos_32767[60] = 3212;
cos_32767[61] = 2410;
cos_32767[62] = 1608;
cos_32767[63] = 804;
cos_32767[64] = 0;
cos_32767[65] = -804;
cos_32767[66] = -1608;
cos_32767[67] = -2410;
cos_32767[68] = -3212;
cos_32767[69] = -4011;
cos_32767[70] = -4808;
cos_32767[71] = -5602;
cos_32767[72] = -6393;
cos_32767[73] = -7179;
cos_32767[74] = -7962;
cos_32767[75] = -8739;
cos_32767[76] = -9512;
cos_32767[77] = -10278;
cos_32767[78] = -11039;
cos_32767[79] = -11793;
cos_32767[80] = -12539;
cos_32767[81] = -13279;
cos_32767[82] = -14010;
cos_32767[83] = -14732;
cos_32767[84] = -15446;
cos_32767[85] = -16151;
cos_32767[86] = -16846;
cos_32767[87] = -17530;
cos_32767[88] = -18204;
cos_32767[89] = -18868;
cos_32767[90] = -19519;
cos_32767[91] = -20159;
cos_32767[92] = -20787;
cos_32767[93] = -21403;
cos_32767[94] = -22005;
cos_32767[95] = -22594;
cos_32767[96] = -23170;
cos_32767[97] = -23731;
cos_32767[98] = -24279;
cos_32767[99] = -24811;
cos_32767[100] = -25329;
cos_32767[101] = -25832;
cos_32767[102] = -26319;
cos_32767[103] = -26790;
cos_32767[104] = -27245;
cos_32767[105] = -27683;
cos_32767[106] = -28105;
cos_32767[107] = -28510;
cos_32767[108] = -28898;
cos_32767[109] = -29268;
cos_32767[110] = -29621;
cos_32767[111] = -29956;
cos_32767[112] = -30273;
cos_32767[113] = -30571;
cos_32767[114] = -30852;
cos_32767[115] = -31113;
cos_32767[116] = -31356;
cos_32767[117] = -31580;
cos_32767[118] = -31785;
cos_32767[119] = -31971;
cos_32767[120] = -32137;
cos_32767[121] = -32285;
cos_32767[122] = -32412;
cos_32767[123] = -32521;
cos_32767[124] = -32609;
cos_32767[125] = -32678;
cos_32767[126] = -32728;
cos_32767[127] = -32757;
cos_32767[128] = -32767;
cos_32767[129] = -32757;
cos_32767[130] = -32728;
cos_32767[131] = -32678;
cos_32767[132] = -32609;
cos_32767[133] = -32521;
cos_32767[134] = -32412;
cos_32767[135] = -32285;
cos_32767[136] = -32137;
cos_32767[137] = -31971;
cos_32767[138] = -31785;
cos_32767[139] = -31580;
cos_32767[140] = -31356;
cos_32767[141] = -31113;
cos_32767[142] = -30852;
cos_32767[143] = -30571;
cos_32767[144] = -30273;
cos_32767[145] = -29956;
cos_32767[146] = -29621;
cos_32767[147] = -29268;
cos_32767[148] = -28898;
cos_32767[149] = -28510;
cos_32767[150] = -28105;
cos_32767[151] = -27683;
cos_32767[152] = -27245;
cos_32767[153] = -26790;
cos_32767[154] = -26319;
cos_32767[155] = -25832;
cos_32767[156] = -25329;
cos_32767[157] = -24811;
cos_32767[158] = -24279;
cos_32767[159] = -23731;
cos_32767[160] = -23170;
cos_32767[161] = -22594;
cos_32767[162] = -22005;
cos_32767[163] = -21403;
cos_32767[164] = -20787;
cos_32767[165] = -20159;
cos_32767[166] = -19519;
cos_32767[167] = -18868;
cos_32767[168] = -18204;
cos_32767[169] = -17530;
cos_32767[170] = -16846;
cos_32767[171] = -16151;
cos_32767[172] = -15446;
cos_32767[173] = -14732;
cos_32767[174] = -14010;
cos_32767[175] = -13279;
cos_32767[176] = -12539;
cos_32767[177] = -11793;
cos_32767[178] = -11039;
cos_32767[179] = -10278;
cos_32767[180] = -9512;
cos_32767[181] = -8739;
cos_32767[182] = -7962;
cos_32767[183] = -7179;
cos_32767[184] = -6393;
cos_32767[185] = -5602;
cos_32767[186] = -4808;
cos_32767[187] = -4011;
cos_32767[188] = -3212;
cos_32767[189] = -2410;
cos_32767[190] = -1608;
cos_32767[191] = -804;
cos_32767[192] = 0;
cos_32767[193] = 804;
cos_32767[194] = 1608;
cos_32767[195] = 2410;
cos_32767[196] = 3212;
cos_32767[197] = 4011;
cos_32767[198] = 4808;
cos_32767[199] = 5602;
cos_32767[200] = 6393;
cos_32767[201] = 7179;
cos_32767[202] = 7962;
cos_32767[203] = 8739;
cos_32767[204] = 9512;
cos_32767[205] = 10278;
cos_32767[206] = 11039;
cos_32767[207] = 11793;
cos_32767[208] = 12539;
cos_32767[209] = 13279;
cos_32767[210] = 14010;
cos_32767[211] = 14732;
cos_32767[212] = 15446;
cos_32767[213] = 16151;
cos_32767[214] = 16846;
cos_32767[215] = 17530;
cos_32767[216] = 18204;
cos_32767[217] = 18868;
cos_32767[218] = 19519;
cos_32767[219] = 20159;
cos_32767[220] = 20787;
cos_32767[221] = 21403;
cos_32767[222] = 22005;
cos_32767[223] = 22594;
cos_32767[224] = 23170;
cos_32767[225] = 23731;
cos_32767[226] = 24279;
cos_32767[227] = 24811;
cos_32767[228] = 25329;
cos_32767[229] = 25832;
cos_32767[230] = 26319;
cos_32767[231] = 26790;
cos_32767[232] = 27245;
cos_32767[233] = 27683;
cos_32767[234] = 28105;
cos_32767[235] = 28510;
cos_32767[236] = 28898;
cos_32767[237] = 29268;
cos_32767[238] = 29621;
cos_32767[239] = 29956;
cos_32767[240] = 30273;
cos_32767[241] = 30571;
cos_32767[242] = 30852;
cos_32767[243] = 31113;
cos_32767[244] = 31356;
cos_32767[245] = 31580;
cos_32767[246] = 31785;
cos_32767[247] = 31971;
cos_32767[248] = 32137;
cos_32767[249] = 32285;
cos_32767[250] = 32412;
cos_32767[251] = 32521;
cos_32767[252] = 32609;
cos_32767[253] = 32678;
cos_32767[254] = 32728;
cos_32767[255] = 32757;
	
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
