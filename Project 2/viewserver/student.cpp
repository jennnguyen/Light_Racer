//CST 231 Project 2
//Jennifer Nguyen
#include "ground.h"
#define GAMESTART 0
#define GAMESINGLEPLAYER 1
#define GAMETWOPLAYER 2
#define GAMEBREAK 3
#define GAMEOVER 4


void initialize_board(int board[485][470])
{
	for (int x = 0; x < 485; x++)
	{
		for (int y = 0; y < 470; y++)
		{
			board[x][y] = 0;
			draw_pixel(x, y, 0, 0, 0, 1); //Black background
		}
	}
}


void choice()
{
	draw_text("Light Racer", 220, 120, 255, 255, 255);
	for (int bg_x = 180; bg_x < 320; bg_x++) //Box
	{
		for (int bg_y = 275; bg_y < 325; bg_y++)
		{
			draw_pixel(bg_x, bg_y, 250, 0, 0, 1);
		}
	}
	draw_text("SINGLE PLAYER", 195, 295, 255, 255, 255);

	for (int bg_x = 180; bg_x < 320; bg_x++) //Box
	{
		for (int bg_y = 375; bg_y < 425; bg_y++)
		{
			draw_pixel(bg_x, bg_y, 250, 0, 0, 1);
		}
	}
	draw_text("TWO PLAYER", 205, 395, 255, 255, 255);
}


void draw_main(input input_info)
{
	static int p1PosX = 300;
	static int p1PosY = 240;
	static int p1Dir = 4; //no direction
	static int score = 0; //initial score
	static int p1Life = 3;
	char p1_Life[100];
	static int flag = 1;

	static int p2PosX = 200;
	static int p2PosY = 240;
	static int p2Dir = 4; //no direction
	static int p2Life = 3;
	char p2_Life[100];
	static int flag2 = 1;

	static int collision_detection[485][470];
	char playerscore[100];
	char playerloses[100];
	static int gameMode = GAMESTART;
	int sqLength = 3;
	static int player=0;
	static int init = 0;

	if (gameMode == GAMESTART)
	{
		initialize_board(collision_detection);
		choice();
		if (input_info.l_button_down == 1)
		{
			//If clicked within the square, game starts
			if (input_info.x_mouse >= 180 && input_info.x_mouse <= 320 && input_info.y_mouse >= 275 && input_info.y_mouse <= 325)
			{
				gameMode = GAMESINGLEPLAYER;
			}

			if (input_info.x_mouse >= 180 && input_info.x_mouse <= 320 && input_info.y_mouse >= 375 && input_info.y_mouse <= 425)
			{
				gameMode = GAMETWOPLAYER;
			}
			
		}
	}


	if (gameMode == GAMESINGLEPLAYER)
	{
		static int init = 0;
		if (init == 0) //Board initialized
		{
			initialize_board(collision_detection);
			init = 1;
		}

		//Score
		sprintf(playerscore, "Score: %d", score / 5);
		draw_text(playerscore, 15, 15, 255, 255, 255);

		//Directions
		if (input_info.up_cursor_down == 1 && p1Dir != 1)
			p1Dir = 0;
		if (input_info.down_cursor_down == 1 && p1Dir != 0)
			p1Dir = 1;
		if (input_info.left_cursor_down == 1 && p1Dir != 3)
			p1Dir = 2;
		if (input_info.right_cursor_down == 1 && p1Dir != 2)
			p1Dir = 3;
		if (flag == 1)
		{
			if (p1Dir == 0) //Up
			{
				p1PosY -= sqLength;
				score++;
				flag = 0;

			}
			if (p1Dir == 1) //Down
			{
				p1PosY += sqLength;
				score++;
				flag = 0;
			}
			if (p1Dir == 2) //Left
			{
				p1PosX -= sqLength;
				score++;
				flag = 0;
			}
			if (p1Dir == 3) //Right
			{
				p1PosX += sqLength;
				score++;
				flag = 0;
			}
		}

		//Border Collision Detection
		if (p1PosX < -5)
			gameMode = GAMEOVER;
		if (p1PosX > 480)
			gameMode = GAMEOVER;
		if (p1PosY < -5)
			gameMode = GAMEOVER;
		if (p1PosY > 480)
			gameMode = GAMEOVER;

		//Collision Detection
		if (flag == 0)
		{
			if (collision_detection[p1PosX][p1PosY] != 0 && collision_detection[p1PosX + sqLength][p1PosY] != 0 && collision_detection[p1PosX][p1PosY + sqLength] != 0 && collision_detection[p1PosX + sqLength][p1PosY + sqLength] != 0)
				gameMode = GAMEOVER;
			flag = 1;
		}

		//Draws squares and sets array to 1
		if (flag == 1)
		{
			for (int ii = 0; ii <= sqLength; ii++)
			{
				draw_pixel(p1PosX + ii, p1PosY, 255, 0, 0, 1);
				collision_detection[p1PosX + ii][p1PosY] = 1;
				draw_pixel(p1PosX, p1PosY + ii, 255, 0, 0, 1);
				collision_detection[p1PosX][p1PosY + ii] = 1;
				draw_pixel(p1PosX + sqLength, p1PosY + ii, 255, 0, 0, 1);
				collision_detection[p1PosX + sqLength][p1PosY + ii] = 1;
				draw_pixel(p1PosX + ii, p1PosY + sqLength, 255, 0, 0, 1);
				collision_detection[p1PosX + ii][p1PosY + sqLength] = 1;
			}
		}
	}

	if (gameMode == GAMETWOPLAYER)
	{
		if (init == 0) //Board initialized
		{
			initialize_board(collision_detection);
			init = 1;
		}

		//Lifes 
		sprintf(p2_Life, "Player 2 Lives: %d", p2Life);
		draw_text(p2_Life, 20, 430, 0, 255, 0);
		sprintf(p1_Life, "Player 1 Lives: %d", p1Life);
		draw_text(p1_Life, 350, 430, 255, 0, 0);

		//Directions P1
		if (input_info.up_cursor_down == 1 && p1Dir != 1)
			p1Dir = 0;
		if (input_info.down_cursor_down == 1 && p1Dir != 0)
			p1Dir = 1;
		if (input_info.left_cursor_down == 1 && p1Dir != 3)
			p1Dir = 2;
		if (input_info.right_cursor_down == 1 && p1Dir != 2)
			p1Dir = 3;
		if (flag == 1)
		{
			if (p1Dir == 0) //Up
			{
				p1PosY -= sqLength;
				flag = 0;
			}
			if (p1Dir == 1) //Down
			{
				p1PosY += sqLength;
				flag = 0;
			}
			if (p1Dir == 2) //Left
			{
				p1PosX -= sqLength;
				flag = 0;
			}
			if (p1Dir == 3) //Right
			{
				p1PosX += sqLength;
				flag = 0;
			}
		}

		//Directions P2
		if (input_info.w_key_down == 1 && p2Dir != 1)
			p2Dir = 0;
		if (input_info.s_key_down == 1 && p2Dir != 0)
			p2Dir = 1;
		if (input_info.a_key_down == 1 && p2Dir != 3)
			p2Dir = 2;
		if (input_info.d_key_down == 1 && p2Dir != 2)
			p2Dir = 3;
		if (flag2 == 1)
		{
			if (p2Dir == 0) //Up
			{
				p2PosY -= sqLength;
				flag2 = 0;
			}
			if (p2Dir == 1) //Down
			{
				p2PosY += sqLength;
				flag2 = 0;
			}
			if (p2Dir == 2) //Left
			{
				p2PosX -= sqLength;
				flag2 = 0;
			}
			if (p2Dir == 3) //Right
			{
				p2PosX += sqLength;
				flag2 = 0;
			}
		}

		//Border Collision Detection P1
		if (p1PosX < -5)
		{
			player = 1;
			p1Life--;
			gameMode = GAMEBREAK;
		}
		if (p1PosX > 480)
		{
			player = 1;
			p1Life--;
			gameMode = GAMEBREAK;
		}
		if (p1PosY < -5)
		{
			player = 1;
			p1Life--;
			gameMode = GAMEBREAK;
		}
		if (p1PosY > 480)
		{
			player = 1;
			p1Life--;
			gameMode = GAMEBREAK;
		}

		//Border Collision Detection P2
		if (p2PosX < -5)
		{
			player = 2;
			p2Life--;
			gameMode = GAMEBREAK;
		}
		if (p2PosX > 480)
		{
			player = 2;
			p2Life--;
			gameMode = GAMEBREAK;
		}
		if (p2PosY < -5)
		{
			player = 2;
			p2Life--;
			gameMode = GAMEBREAK;
		}
		if (p2PosY > 480)
		{
			player = 2;
			p2Life--;
			gameMode = GAMEBREAK;
		}

		//Collision Detection P1
		if (flag == 0)
		{
			if (collision_detection[p1PosX][p1PosY] != 0 && collision_detection[p1PosX + sqLength][p1PosY] != 0 && collision_detection[p1PosX][p1PosY + sqLength] != 0 && collision_detection[p1PosX + sqLength][p1PosY + sqLength] != 0)
			{
				player = 1;
				p1Life--;
				gameMode = GAMEBREAK;
			}
			flag = 1;
		}
		//Collision Detection P2
		if (flag2 == 0)
		{
			if (collision_detection[p2PosX][p2PosY] != 0 && collision_detection[p2PosX + sqLength][p2PosY] != 0 && collision_detection[p2PosX][p2PosY + sqLength] != 0 && collision_detection[p2PosX + sqLength][p2PosY + sqLength] != 0)
			{
				player = 2;
				p2Life--;
				gameMode = GAMEBREAK;
			}
			flag2 = 1;
		}


		//Draws squares and sets area to 1 for P1
		if (flag == 1)
		{
			for (int ii = 0; ii <= sqLength; ii++)
			{
				draw_pixel(p1PosX + ii, p1PosY, 255, 0, 0, 1);
				collision_detection[p1PosX + ii][p1PosY] = 1;
				draw_pixel(p1PosX, p1PosY + ii, 255, 0, 0, 1);
				collision_detection[p1PosX][p1PosY + ii] = 1;
				draw_pixel(p1PosX + sqLength, p1PosY + ii, 255, 0, 0, 1);
				collision_detection[p1PosX + sqLength][p1PosY + ii] = 1;
				draw_pixel(p1PosX + ii, p1PosY + sqLength, 255, 0, 0, 1);
				collision_detection[p1PosX + ii][p1PosY + sqLength] = 1;
			}
		}
		//Draws squares and sets area to 1 for P2
		if (flag2 == 1)
		{
			for (int ii = 0; ii <= sqLength; ii++)
			{
				draw_pixel(p2PosX + ii, p2PosY, 0, 255, 0, 1);
				collision_detection[p2PosX + ii][p2PosY] = 1;
				draw_pixel(p2PosX, p2PosY + ii, 0, 255, 0, 1);
				collision_detection[p2PosX][p2PosY + ii] = 1;
				draw_pixel(p2PosX + sqLength, p2PosY + ii, 0, 255, 0, 1);
				collision_detection[p2PosX + sqLength][p2PosY + ii] = 1;
				draw_pixel(p2PosX + ii, p2PosY + sqLength, 0, 255, 0, 1);
				collision_detection[p2PosX + ii][p2PosY + sqLength] = 1;
			}
		}
	}

	if (gameMode == GAMEBREAK) //Break for TWOPLAYER
	{
		if (player == 1)
		{
			draw_text("Player 1 Loses", 190, 130, 255, 0, 0);
			if (init == 1) //Board initialized
			{
				if (p1Life == 0)
				{
					draw_text("Player 2 is the Winner!", 170, 150, 0, 255, 0);
				}
				else
				{
					draw_text("CLICK TO START AGAIN", 170, 295, 255, 255, 255);
					if (input_info.l_button_down == 1)
					{
						gameMode = GAMETWOPLAYER;
						init = 0;
					}
				}
			}
		}

		if (player == 2)
		{
			draw_text("Player 2 Loses", 190, 130, 0, 255, 0);
			if (init == 1) //Board initialized
			{
				if (p2Life == 0)
				{
					draw_text("Player 1 is the Winner!", 170, 150, 255, 0, 0);
				}
				else
				{
					draw_text("CLICK TO START AGAIN", 170, 295, 255, 255, 255);
					if (input_info.l_button_down == 1)
					{
						gameMode = GAMETWOPLAYER;
						init = 0;
					}
				}
			}
		}
		//Restart positions
		p1PosX = 300;
		p1PosY = 240;
		flag = 1;
		p1Dir = 4;
		p2PosX = 200;
		p2PosY = 240;
		flag2 = 1;
		p2Dir = 4;

		sprintf(p1_Life, "Player 1 Lives: %d", p1Life);
		sprintf(p2_Life, "Player 2 Lives: %d", p2Life);
		draw_text(p1_Life, 350, 430, 255, 0, 0);
		draw_text(p2_Life, 20, 430, 0, 255, 0);
	}

	if (gameMode == GAMEOVER) //Break for SINGLEPLAYER
	{
		draw_text("Game Over", 210, 150, 255, 255, 255);
		sprintf(playerscore, "Score: %d", score / 5);
		draw_text(playerscore, 15, 15, 255, 255, 255);
	}

}