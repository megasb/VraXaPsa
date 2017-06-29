
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <cstring>
#include <math.h>

using namespace std;

bool hascolourPlOne = false, hascolourPlTwo = false;
bool hasChosenPlOne = false, hasChosenPlTwo = false;
int blockcolourPlOne, blockcolourPlTwo; //Colour of the new Block
bool game = false; //Game startup flag
GLsizei winWidth = 520, winHeight = 560; // Window size
int game_blocksPlOne[13][6]; //Our blocks matrix
int game_blocksPlTwo[13][6];
int plOnePosi, plOnePosj, plTwoPosi, plTwoPosj; //NewBlock position
float WPlOne = 0, WPlTwo = 0, H = 0, heightPlOne = -40, heightPlTwo = 0;
int plOneScore = 0, plTwoScore = 0;
int playerTurn = 1;
int dstrdblocksPlOne = 0, dstrdblocksPlTwo = 0;
bool gameover = false;
int opponentEmptySpots;
GLuint* rock= (GLuint*) malloc(sizeof(GLuint)*1600);
GLuint* paper= (GLuint*) malloc(sizeof(GLuint)*1600);
GLuint* scissors= (GLuint*) malloc(sizeof(GLuint)*1600);
GLuint* drawPgm;

void matrixInit (void) //Initialize matrix to 0
{
	int i,j;
	for(i=0; i<13; i++)
	{
		for(j=0; j<6; j++)
		{
			game_blocksPlOne[i][j] = 0;
			game_blocksPlTwo[i][j] = 0;
		}
	}
}

void output(char* string, int msgj, int msgi ){

	int len, j;
	glColor3f(0.0,0.0,0.0);
	glRasterPos2f(msgj, msgi);
	len = (int) strlen(string);
	for (j = 0; j<len; j++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[j]);
	}
}

void messagePrint(void)
{
	int i;
	char msg[100];
	if (gameover == false)
	{
		if (game == false)
		{
			sprintf(msg," Press <b> to Start ");
			output(msg, 10, 10);
		}
		else
		{
			sprintf(msg," Player 1 Score: %d <S>left .. <D>right",plOneScore);
			output(msg, 5, 10);
			sprintf(msg," Player 2 Score: %d <K>left .. <L>right",plTwoScore);
			output(msg, 285, 10);
		}
	}
	else
	{
		matrixInit();
		heightPlOne = -40;
		heightPlTwo = -40;
		sprintf(msg,"Game Over///Player One Score: %d Player Two Score: %d/// Press <b> to Restart", plOneScore, plTwoScore);
		output(msg, 5, 390);
	}
}
void keyPress (unsigned char key, int x, int y)
{
	switch(key)
	{
		system("PAUSE");
		case 27:
			exit(0);
		case 'b':
			game = true;
			if (gameover == true)
			{
				gameover = false;
				plOneScore = 0;
				plTwoScore = 0;
			}
	}
	switch(key)
	{
		case 27:
			exit(0);
		case 'd':
			if (plOnePosi <= 4 && game_blocksPlOne[plOnePosj][plOnePosi+1] == 0 && game_blocksPlOne[plOnePosj-1][plOnePosi+1] == 0 && playerTurn%2==1) 
			{
				WPlOne -= 40;
			}
	}
	switch(key)
	{
		case 27:
			exit(0);
		case 's':
			if (plOnePosi >=1 && game_blocksPlOne[plOnePosj][plOnePosi-1] == 0 && game_blocksPlOne[plOnePosj-1][plOnePosi-1] == 0 && playerTurn%2==1)
			{
				WPlOne += 40;
			}
	}
	switch(key)
	{
		case 27:
			exit(0);
		case 'l':
			if (plTwoPosi <= 4 && game_blocksPlTwo[plTwoPosj][plTwoPosi+1] == 0 && game_blocksPlTwo[plTwoPosj-1][plTwoPosi+1] == 0 && playerTurn%2==0) 
			{
				WPlTwo -= 40;
			}
	}
	switch(key)
	{
		case 27:
			exit(0);
		case 'k':
			if (plTwoPosi >=1 && game_blocksPlTwo[plTwoPosj][plTwoPosi-1] == 0 && game_blocksPlTwo[plTwoPosj-1][plTwoPosi-1] == 0 && playerTurn%2==0)
			{
				WPlTwo += 40;
			}
	}
}

void pgmInit (void)
{
	char temp[50];
	FILE* fp;
	fp = fopen("rock.pgm", "r");
	for (int i=0; i<4; i++)
	{
		fscanf(fp, "%[^\n] ", temp);
	}
	for (int i=0; i<1600; i++)
	{
		fscanf(fp, "%d", &rock[i]);
	}
	fp = fopen("paper.pgm", "r");
	for (int i=0; i<4; i++)
	{
		fscanf(fp, "%[^\n] ", temp);
	}
	for (int i=0; i<1600; i++)
	{
		fscanf(fp, "%d", &paper[i]);
	}
	fp = fopen("scissors.pgm", "r");
	for (int i=0; i<4; i++)
	{
		fscanf(fp, "%[^\n] ", temp);
	}
	for (int i=0; i<1600; i++)
	{
		fscanf(fp, "%d", &scissors[i]);
	}
}

void drawBlock (int i,int j,int Player)
{
	if (Player == 1)
	{
		if(game_blocksPlOne[i][j] == 1)
		{
			drawPgm = rock;
		}	
		else if(game_blocksPlOne[i][j] == 2)
		{
			drawPgm = scissors;
		}
		else if(game_blocksPlOne[i][j] == 3)
		{
			drawPgm = paper;	
		}
		else if(game_blocksPlOne[i][j] == 6)
		{
			glColor3f(0.0f,0.0f,0.0f);
		}	
		else if(game_blocksPlOne[i][j] == 7)
		{
			glColor3f(1.0f,0.0f,0.0f);
		}
		else if(game_blocksPlOne[i][j] == 8)
		{
			glColor3f(0.0f,0.0f,1.0f);	
		}
		if (game_blocksPlOne[i][j] >= 1 && game_blocksPlOne[i][j] <= 3)
		{
			glRasterPos2d(j*40,i*40+40);
			glDrawPixels(40, 40, GL_LUMINANCE, GL_UNSIGNED_INT, drawPgm);
			glPixelStorei(GL_UNPACK_SWAP_BYTES,GL_TRUE);
		}
		else
		{
			glBegin(GL_QUADS);
				glVertex2f(j*40,i*40+40);
				glVertex2f(j*40,i*40+40+40);
				glVertex2f(j*40+40,i*40+40+40);
				glVertex2f(j*40+40,i*40+40);
			glEnd();
		}
		glFlush();
	}
	else
	{
		if(game_blocksPlTwo[i][j] == 1)
		{
			drawPgm = rock;
		}	
		else if(game_blocksPlTwo[i][j] == 2)
		{
			drawPgm = scissors;
		}
		else if(game_blocksPlTwo[i][j] == 3)
		{
			drawPgm = paper;
		}
		if(game_blocksPlTwo[i][j] == 6)
		{
			glColor3f(0.0f,0.0f,0.0f);
		}	
		else if(game_blocksPlTwo[i][j] == 7)
		{
			glColor3f(1.0f,0.0f,0.0f);
		}
		else if(game_blocksPlTwo[i][j] == 8)
		{
			glColor3f(0.0f,0.0f,1.0f);	
		}
		if (game_blocksPlTwo[i][j] >= 1 && game_blocksPlTwo[i][j] <= 3)
		{
			glRasterPos2d(j*40 + 280,i*40+40);
			glDrawPixels(40, 40, GL_LUMINANCE, GL_UNSIGNED_INT, drawPgm);
			glPixelStorei(GL_UNPACK_SWAP_BYTES,GL_TRUE);
		}
		else
		{
			glBegin(GL_QUADS);
				glVertex2f(j*40 + 280,i*40+40);
				glVertex2f(j*40 + 280,i*40+40+40);
				glVertex2f(j*40+40 + 280,i*40+40+40);
				glVertex2f(j*40+40 + 280,i*40+40);
			glEnd();
		}
		glFlush();
	}
}

void displayBlocks (void)
{
	int i,j;
	for(i=0; i<13; i++)
	{
		for(j=0; j<6; j++)
		{
			if (game_blocksPlOne[i][j] != 0)
			{
				drawBlock(i,j, 1);
			}
			if (game_blocksPlTwo[i][j] != 0)
			{
				drawBlock(i,j, 2);
			}
		}
	}
}

void newBlock (void)
{
	int bwBomb;
	if (playerTurn%2==1)
	{
		if (hasChosenPlOne == false)
		{
			bwBomb = rand()%100 + 1;
			hasChosenPlOne = true;
		}
		if (hascolourPlOne == false)
		{
			if (bwBomb <= 70)
			{
				blockcolourPlOne = rand()%3+1;
			}
			else
			{
				blockcolourPlOne = rand()%3+6;
			}
			hascolourPlOne = true;
		}
		if(blockcolourPlOne == 1)
		{
			drawPgm = rock;
		}	
		else if(blockcolourPlOne == 2)
		{
			drawPgm = scissors;
		}
		else if(blockcolourPlOne == 3)
		{
			drawPgm = paper;
		}
		else if(blockcolourPlOne == 6)
		{
			glColor3f(0.0f,0.0f,0.0f);
		}	
		else if(blockcolourPlOne == 7)
		{
			glColor3f(1.0f,0.0f,0.0f);
		}
		else if(blockcolourPlOne == 8)
		{
			glColor3f(0.0f,0.0f,1.0f);	
		}
		plOnePosi=(80 - WPlOne)/40;
		plOnePosj=(480 - heightPlOne)/40;
		if (blockcolourPlOne >= 1 && blockcolourPlOne <= 3)
		{
			glRasterPos2d(80 - WPlOne,520 - heightPlOne);
			glDrawPixels(40, 40, GL_LUMINANCE, GL_UNSIGNED_INT, drawPgm);
			glPixelStorei(GL_UNPACK_SWAP_BYTES,GL_TRUE);
		}
		else
		{
			glBegin(GL_QUADS);
				glVertex2f(80 - WPlOne,520 - heightPlOne);
				glVertex2f(120 - WPlOne,520 - heightPlOne);
				glVertex2f(120 - WPlOne,560 - heightPlOne);
				glVertex2f(80 - WPlOne,560 - heightPlOne);
			glEnd();
		}
		glFlush();
	}
	else
	{
		if (hasChosenPlTwo == false)
		{
			bwBomb = rand()%100 + 1;
			hasChosenPlTwo = true;
		}
		if (hascolourPlTwo == false)
		{
			if (bwBomb <= 70)
			{
				blockcolourPlTwo = rand()%3+1;
			}
			else
			{
				blockcolourPlTwo = rand()%3+6;
			}
			hascolourPlTwo = true;
		}
		if(blockcolourPlTwo == 1)
		{
			drawPgm = rock;
		}	
		else if(blockcolourPlTwo == 2)
		{
			drawPgm = scissors;
		}
		else if(blockcolourPlTwo == 3)
		{
			drawPgm = paper;
		}
		else if(blockcolourPlTwo == 6)
		{
			glColor3f(0.0f,0.0f,0.0f);
		}	
		else if(blockcolourPlTwo == 7)
		{
			glColor3f(1.0f,0.0f,0.0f);
		}
		else if(blockcolourPlTwo == 8)
		{
			glColor3f(0.0f,0.0f,1.0f);	
		}
		plTwoPosi=((360 - WPlTwo)-280)/40;
		plTwoPosj=(480 - heightPlTwo)/40;
		if (blockcolourPlTwo >= 1 && blockcolourPlTwo <= 3)
		{
			glRasterPos2d(360 - WPlTwo,520 - heightPlTwo);
			glDrawPixels(40, 40, GL_LUMINANCE, GL_UNSIGNED_INT, drawPgm);
			glPixelStorei(GL_UNPACK_SWAP_BYTES,GL_TRUE);
		}
		else
		{
			glBegin(GL_QUADS);
				glVertex2f(360 - WPlTwo,520 - heightPlTwo);
				glVertex2f(400 - WPlTwo,520 - heightPlTwo);
				glVertex2f(400 - WPlTwo,560 - heightPlTwo);
				glVertex2f(360 - WPlTwo,560 - heightPlTwo);
			glEnd();
		}
		glFlush();
	}
}

void display (void)
{
	int i,j;
	for (i=0; i<=5; i++)
	{
		if (game_blocksPlOne[12][i] == 1 || game_blocksPlTwo[12][i])
		{
			gameover = true;
		}
	}
	
	glClearColor (1.0f, 0.5f, 0.0f, 1.0f);
	glClear (GL_COLOR_BUFFER_BIT);
	messagePrint();
	if (game == true && gameover == false)
	{
		for (j=1; j <=13; j++)
		{
			glBegin(GL_LINES);
				glVertex2f(j*40,40);
				glVertex2f(j*40,560);
			glEnd();
			glBegin(GL_LINES);
				glVertex2f(0,40*j);
				glVertex2f(240,40*j);
			glEnd();
			glBegin(GL_LINES);
				glVertex2f(280,40*j);
				glVertex2f(520,40*j);
			glEnd();
		}
		glBegin(GL_LINES);
			glVertex2f(0,560);
			glVertex2f(240,560);
		glEnd();
		glBegin(GL_LINES);
			glVertex2f(280,560);
			glVertex2f(520,560);
		glEnd();
		newBlock();
	}
	displayBlocks();
	glFlush();
}

void winReshapeFnc (GLint newWidth, GLint newHeight)
{
	glViewport (0, 0, newWidth, newHeight); //  Reset viewport and projection parameters
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D (0.0, newWidth, 0.0, newHeight);

	winWidth  = newWidth; // Reset display-window size parameters
	winHeight = newHeight;
}

void init (void)
{
	glClearColor (1.0f, 0.5f, 0.0f, 1.0f);// Set display-window .
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0, 520.0, 40.0, 520.0);
}

void pollposition (void)
{
	int i,j,k;
	bool hasfound = false;
	for (i=5; i>=0; i--)
	{
		for (j=0; j<=12; j++)
		{
			if (playerTurn%2 == 1)
			{
				if (game_blocksPlOne[j][i] == 4 && hasfound == false)
				{
					game_blocksPlOne[j][i] = game_blocksPlOne[plOnePosj][plOnePosi];
					game_blocksPlOne[plOnePosj][plOnePosi]=0;
					hasfound = true;
				}	
				else if (game_blocksPlOne[j][i] == 4)
				{
					game_blocksPlOne[j][i] = 0;
				}
			}
			else
			{
				if (game_blocksPlTwo[j][i] == 4 && hasfound == false)
				{
					game_blocksPlTwo[j][i] = game_blocksPlTwo[plTwoPosj][plTwoPosi];
					game_blocksPlTwo[plTwoPosj][plTwoPosi]=0;
					hasfound = true;
				}	
				else if (game_blocksPlTwo[j][i] == 4)
				{
					game_blocksPlTwo[j][i] = 0;
				}
			}
		}
	}
}

void construction (int game_blocks[13][6])
{
	int j, i, k, column;
	bool above;
	for (j=0; j<=12; j++)
	{
		for (i=0; i<=5; i++)
		{
			above = false;
			column = j+1;
			while (above == false && column <= 12)
			{
				if (game_blocks[column][i] !=0)
				{
					above = true;
				}
				column ++;
			}	
			while (game_blocks[j][i] == 0 && above == true)
			{
				for (k=j; k<=11; k++)
				{
					game_blocks[k][i]=game_blocks[k+1][i];
				}
			}
		}
	}
}

void pollpositionNo2 (int Posj, int Posi, int game_blocks[13][6])
{
	int i,j,k;
	bool hasfound = false;
	for (i=5; i>=0; i--)
	{
		for (j=0; j<=12; j++)
		{
			if (game_blocks[j][i] == 4 && hasfound == false)
			{
				game_blocks[j][i] = game_blocks[Posj][Posi];
				game_blocks[Posj][Posi]=0;
				hasfound = true;
			}	
			else if (game_blocks[j][i] == 4)
			{
				game_blocks[j][i] = 0;
			}
		}
	}
}

void destructionNo2 (int j, int i,int game_blocks[13][6], int dstrNo2)
{
	if (j+1 <= 11 && game_blocks[j+1][i] == dstrNo2)
	{
		game_blocks[j+1][i] = 4;
		destructionNo2(j+1, i, game_blocks, dstrNo2);
	}
	if (j-1 >= 0 && game_blocks[j-1][i] == dstrNo2)
	{
		game_blocks[j-1][i] = 4;
		destructionNo2(j-1, i, game_blocks, dstrNo2);
	}
	if (i+1 <= 5 && game_blocks[j][i+1] == dstrNo2)
	{
		game_blocks[j][i+1] = 4;
		destructionNo2(j, i+1, game_blocks, dstrNo2);
	}
	if (i-1 >= 0 && game_blocks[j][i-1] == dstrNo2)
	{
		game_blocks[j][i-1] = 4;
		destructionNo2(j, i-1, game_blocks, dstrNo2);
	}
}

void sendBlock (int game_blocks[13][6],int sentcolour)
{
	int i = 0, j = 0, Posi, Posj;
	while (i<=5)
	{
		while (j<=12 && game_blocks[j][i] != 0)
		{
			j++;
		}
		if (game_blocks[j][i] == 0)
		{
			game_blocks[j][i] = 5;
		}
		i++;
		j = 0;
	}
	i = rand()%6;
	j = rand()%13;
	while (game_blocks[j][i] != 5)
	{
		i = rand()%6;
		j = rand()%13;
	}
	Posi = i;
	Posj = j;
	game_blocks[Posj][Posi] = sentcolour;
	i = 0;
	j = 0;
	while (i<=5)
	{
		while (j<=12 && game_blocks[j][i] != 5)
		{
			j++;
		}
		if (game_blocks[j][i] == 5)
		{
			game_blocks[j][i] = 0;
		}
		i++;
		j = 0;
	}
	if (sentcolour == 1)
	{
		destructionNo2(Posj, Posi, game_blocks, 2);
	}
	else if (sentcolour == 2)
	{
		destructionNo2(Posj, Posi, game_blocks, 3);
	}
	else if (sentcolour == 3)
	{
		destructionNo2(Posj, Posi, game_blocks, 1);
	}
	pollpositionNo2(Posj, Posi, game_blocks);
	construction(game_blocks);
}

void destruction (int j, int i, int dstr) // dstr colour to be destroyed
{
	if (playerTurn%2==1)
	{
		if (j+1 <= 11 && game_blocksPlOne[j+1][i] == dstr)
		{
			game_blocksPlOne[j+1][i] = 4;
			if (dstrdblocksPlOne <= opponentEmptySpots)
			{
				sendBlock(game_blocksPlTwo, dstr);
			}
			dstrdblocksPlOne++;
			destruction(j+1, i, dstr);
		}
		if (j-1 >= 0 && game_blocksPlOne[j-1][i] == dstr)
		{
			game_blocksPlOne[j-1][i] = 4;
			if (dstrdblocksPlOne <= opponentEmptySpots)
			{
				sendBlock(game_blocksPlTwo, dstr);
			}
			dstrdblocksPlOne++;
			destruction(j-1, i, dstr);
		}
		if (i+1 <= 5 && game_blocksPlOne[j][i+1] == dstr)
		{
			game_blocksPlOne[j][i+1] = 4;
			if (dstrdblocksPlOne <= opponentEmptySpots)
			{
				sendBlock(game_blocksPlTwo, dstr);
			}
			dstrdblocksPlOne++;
			destruction(j, i+1, dstr);
		}
		if (i-1 >= 0 && game_blocksPlOne[j][i-1] == dstr)
		{
			game_blocksPlOne[j][i-1] = 4;
			if (dstrdblocksPlOne <= opponentEmptySpots)
			{
				sendBlock(game_blocksPlTwo, dstr);
			}
			dstrdblocksPlOne++;
			destruction(j, i-1, dstr);
		}
	}
	else
	{
		if (j+1 <= 11 && game_blocksPlTwo[j+1][i] == dstr)
		{
			game_blocksPlTwo[j+1][i] = 4;
			if (dstrdblocksPlTwo <= opponentEmptySpots)
			{
				sendBlock(game_blocksPlOne, dstr);
			}
			dstrdblocksPlTwo++;
			destruction(j+1, i, dstr);
		}
		if (j-1 >= 0 && game_blocksPlTwo[j-1][i] == dstr)
		{
			game_blocksPlTwo[j-1][i] = 4;
			if (dstrdblocksPlTwo <= opponentEmptySpots)
			{
				sendBlock(game_blocksPlOne, dstr);
			}
			dstrdblocksPlTwo++;
			destruction(j-1, i, dstr);
		}
		if (i+1 <= 5 && game_blocksPlTwo[j][i+1] == dstr)
		{
			game_blocksPlTwo[j][i+1] = 4;
			if (dstrdblocksPlTwo <= opponentEmptySpots)
			{
				sendBlock(game_blocksPlOne, dstr);
			}
			dstrdblocksPlTwo++;
			destruction(j, i+1, dstr);
		}
		if (i-1 >= 0 && game_blocksPlTwo[j][i-1] == dstr)
		{
			game_blocksPlTwo[j][i-1] = 4;
			if (dstrdblocksPlTwo <= opponentEmptySpots)
			{
				sendBlock(game_blocksPlOne, dstr);
			}
			dstrdblocksPlTwo++;
			destruction(j, i-1, dstr);
		}
	}
}

void solidDestruction (int j, int i, int game_blocks[13][6], int solidcolour)
{
	if (j+1 <= 11 && game_blocks[j+1][i] == solidcolour)
	{
		game_blocks[j+1][i] = 0;
		solidDestruction(j+1, i, game_blocks, solidcolour);
	}
	if (j-1 >= 0 && game_blocks[j-1][i] == solidcolour)
	{
		game_blocks[j-1][i] = 0;
		solidDestruction(j-1, i, game_blocks, solidcolour);
	}
	if (i+1 <= 5 && game_blocks[j][i+1] == solidcolour)
	{
		game_blocks[j][i+1] = 0;
		solidDestruction(j, i+1, game_blocks, solidcolour);
	}
	if (i-1 >= 0 && game_blocks[j][i-1] == solidcolour)
	{
		game_blocks[j][i-1] = 0;
		solidDestruction(j, i-1, game_blocks, solidcolour);
	}
}

void bombFunc(int game_blocks[13][6], int j, int i)
{
	if (j+1 <= 11 && game_blocks[j+1][i] == 7)
	{
		solidDestruction(j+1, i, game_blocks, 7);
	}
	else if (j+1 <= 11 && game_blocks[j+1][i] == 8)
	{
		solidDestruction(j+1, i, game_blocks, 8);
	}
	if (j-1 >= 0 && game_blocks[j-1][i] == 7)
	{
		solidDestruction(j-1, i, game_blocks, 7);
	}
	else if (j-1 >= 0 && game_blocks[j-1][i] == 8)
	{
		solidDestruction(j-1, i, game_blocks, 8);
	}
	if (i+1 <= 5 && game_blocks[j][i+1] == 7)
	{
		solidDestruction(j, i+1, game_blocks, 7);
	}
	else if (i+1 <= 5 && game_blocks[j][i+1] == 8)
	{
		solidDestruction(j, i+1, game_blocks, 8);
	}
	if (i-1 >= 0 && game_blocks[j][i-1] == 7)
	{
		solidDestruction(j, i-1, game_blocks, 7);
	}
	else if (i-1 >= 0 && game_blocks[j][i-1] == 8)
	{
		solidDestruction(j, i-1, game_blocks, 8);
	}
	if (j+1 <= 11)
	{
		game_blocks[j+1][i] = 0;
	}
	if (j-1 >= 0)
	{
		game_blocks[j-1][i] = 0;
	}
	if (i+1 <= 5)
	{
		game_blocks[j][i+1] = 0;
	}
	if (i-1 <= 5)
	{
		game_blocks[j][i-1] = 0;
	}
	game_blocks[j][i] = 0;
	
}

void difficulty (int H)
{
	if(game == true)
	{	
		if (playerTurn%2==1)
		{
			heightPlOne += H;
			if (heightPlOne == 520 || game_blocksPlOne[plOnePosj-1][plOnePosi] != 0)
			{
				dstrdblocksPlOne = 0;
				opponentEmptySpots = 0;
				for (int j=0; j<=12; j++)
				{
					for (int i=0; i<=5; i++)
					{
						if (game_blocksPlTwo[j][i] == 0)
						{
							opponentEmptySpots++;
						}
					}
				}
				game_blocksPlOne[plOnePosj][plOnePosi] = blockcolourPlOne;
				if (blockcolourPlOne == 1)
				{
					destruction(plOnePosj, plOnePosi, 2);
				}
				if (blockcolourPlOne == 2)
				{
					destruction(plOnePosj, plOnePosi, 3);
				}
				if (blockcolourPlOne == 3)
				{
					destruction(plOnePosj, plOnePosi, 1);
				}
				if (blockcolourPlOne == 6)
				{
					bombFunc(game_blocksPlOne, plOnePosj, plOnePosi);
				}
				plOneScore += (10*dstrdblocksPlOne + pow(dstrdblocksPlOne,2));
				if (dstrdblocksPlOne > opponentEmptySpots)
				{
					gameover = true;
				}
				pollposition();
				construction(game_blocksPlOne);
				hascolourPlOne = false;
				hasChosenPlOne = false;
				heightPlOne = 0;
				WPlOne = 0;
				playerTurn++;
			}
		}
		else
		{
			heightPlTwo += H;
			if (heightPlTwo == 520 || game_blocksPlTwo[plTwoPosj-1][plTwoPosi] != 0)
			{
				dstrdblocksPlTwo = 0;
				opponentEmptySpots = 0;
				for (int j=0; j<=12; j++)
				{
					for (int i=0; i<=5; i++)
					{
						if (game_blocksPlOne[j][i] == 0)
						{
							opponentEmptySpots++;
						}
					}
				}
				game_blocksPlTwo[plTwoPosj][plTwoPosi] = blockcolourPlTwo;
				if (blockcolourPlTwo == 1)
				{
					destruction(plTwoPosj, plTwoPosi, 2);
				}
				if (blockcolourPlTwo == 2)
				{
					destruction(plTwoPosj, plTwoPosi, 3);
				}
				if (blockcolourPlTwo == 3)
				{
					destruction(plTwoPosj, plTwoPosi, 1);
				}
				if (blockcolourPlTwo == 6)
				{
					bombFunc(game_blocksPlTwo, plTwoPosj, plTwoPosi);
				}
				plTwoScore += (10*dstrdblocksPlTwo + pow(dstrdblocksPlTwo,2));
				if (dstrdblocksPlTwo > opponentEmptySpots)
				{
					gameover = true;
				}
				pollposition();
				construction(game_blocksPlTwo);
				hascolourPlTwo = false;
				hasChosenPlTwo = false;
				heightPlTwo = 0;
				WPlTwo = 0;
				playerTurn++;
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(400,difficulty,H);
}

int main (int argc, char** argv)
{	
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (200, 200);
	glutInitWindowSize (winWidth, winHeight);
	glutCreateWindow ("VraXaPsa");
	init ();
	glutReshapeFunc (winReshapeFnc);
	matrixInit ();
	pgmInit();
	glutDisplayFunc (display);
	glutKeyboardFunc (keyPress);
	H=40;
	glutTimerFunc (200, difficulty, H);
	glutMainLoop ();
	return 0;
}
