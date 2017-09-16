/*****************************************************************************/
/*                                                                           */
/*                                		                                     */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/* (C) 2017      Fabrizio Caruso                                  		     */
/*                					                                         */
/*              				                                             */
/* EMail:        Fabrizio_Caruso@hotmail.com                                 */
/*                                                                           */
/*                                                                           */
/* This software is provided 'as-is', without any expressed or implied       */
/* warranty.  In no event will the authors be held liable for any damages    */
/* arising from the use of this software.                                    */
/*                                                                           */
/* Permission is granted to anyone to use this software for any purpose,     */
/* including commercial applications, and to alter it and redistribute it    */
/* freely, subject to the following restrictions:                            */
/*                                                                           */
/* 1. The origin of this software must not be misrepresented; you must not   */
/*    claim that you wrote the original software. If you use this software   */
/*    in a product, an acknowledgment in the product documentation would be  */
/*    appreciated but is not required.                                       */
/* 2. Altered source versions must be plainly marked as such, and must not   */
/*    be misrepresented as being the original software.                      */
/* 3. This notice may not be removed or altered from any source              */
/*    distribution.                                                          */
/*                                                                           */
/*****************************************************************************/
 
#include "text.h"

#include "display_macros.h"

#include "settings.h"

#include "sleep_macros.h"

#ifdef __ATMOS__
	#include<peekpoke.h>
#endif

// TODO: DEBUG
	// #include <stdio.h>

extern unsigned char XSize;
extern unsigned char YSize;

extern unsigned char level;
extern unsigned char lives;
extern unsigned char guns;
extern unsigned long points;
extern unsigned char ghostCount;
extern unsigned short ghostLevel;
extern unsigned long highScore;

extern Image PLAYER_IMAGE;
extern Image GHOST_IMAGE;
extern Image GUN_IMAGE;
extern Image INVINCIBLE_GHOST_IMAGE;
extern Image PLAYER_IMAGE;
extern Image MISSILE_IMAGE;

// TODO: This is SLOW
void displayStatsTitles(void)
{	
	#if defined(__CBM__) && !defined(__VIC20__)
		SET_TEXT_COLOR(COLOR_BLUE);		
		//PRINT(2-X_OFFSET,0-Y_OFFSET,"speed:");
		PRINT(2-X_OFFSET,0-Y_OFFSET,"score:");
		PRINT(2-X_OFFSET,1-Y_OFFSET,"level:");
		SET_TEXT_COLOR(TEXT_COLOR);
		
		SET_TEXT_COLOR(COLOR_RED);	
		PRINT(24,0-Y_OFFSET,"-----------");
		PRINT(24,1-Y_OFFSET,"cross chase");
		//PRINT(24,2-Y_OFFSET,"-----------");
		SET_TEXT_COLOR(TEXT_COLOR);
	#elif defined(__ATMOS__)
		//PRINT(2,0-Y_OFFSET,"SPEED:");
		PRINT(2,0-Y_OFFSET,"SCORE:");
		PRINT(2,1-Y_OFFSET,"LEVEL:");
		
		POKE(0xBB80+22+0*40,10);
		POKE(0xBB80+22+1*40,10);	
		
		gotoxy(23,0); 
		cputc('C'+128); 
		cputc('R'+128);
		cputc('O'+128); 
		cputc('S'+128); 
		cputc('S'+128); 
		cputc(' '+128);	
		cputc('C'+128);
		cputc('H'+128);		
		cputc('A'+128);	
		cputc('S'+128);		
		cputc('E'+128); 
		
		gotoxy(23,1); 
		cputc('C'+128); 
		cputc('R'+128);
		cputc('O'+128); 
		cputc('S'+128); 
		cputc('S'+128); 
		cputc(' '+128);	
		cputc('C'+128);	
		cputc('H'+128);
		cputc('A'+128);
		cputc('S'+128);	
		cputc('E'+128); 		
	#elif (defined(__ATARI__) || defined(__ATARIXL__)) && defined(ATARI_MODE1)
		SET_TEXT_COLOR(TEXT_COLOR);	
		PRINT(0,0-Y_OFFSET,"SCORE:");
		PRINT(0,1-Y_OFFSET,"LEVEL:");
	#elif defined(__VG5K__)	
		SET_TEXT_COLOR(TEXT_COLOR);	
		PRINT(2,0-Y_OFFSET,"SCORE:");
		PRINT(2,1-Y_OFFSET,"LEVEL:");
		SET_TEXT_COLOR(TEXT_COLOR);	
		PRINT(24,0-Y_OFFSET,"CROSS CHASE");
		SET_TEXT_COLOR(TEXT_COLOR);	
	#else
		SET_TEXT_COLOR(TEXT_COLOR);	
		PRINT(2,0-Y_OFFSET,"SCORE:");
		PRINT(2,1-Y_OFFSET,"LEVEL:");
		#if !(defined(__SPECTRUM__) && defined(SPECTRUM_32COL)) && !defined(__VIC20__) && (!defined(__ATARI__) && !defined(__ATARIXL__) || !defined(ATARI_MODE1))
			SET_TEXT_COLOR(TEXT_COLOR);	
			PRINT(24,0-Y_OFFSET,"CROSS CHASE");
			SET_TEXT_COLOR(TEXT_COLOR);	
		#endif
	#endif

	
	#if defined (__ATMOS__)
		gotoxy(18+1,0); cputc(GUN_IMAGE._imageData);cputc(':');
		gotoxy(18-3,0); cputc(GHOST_IMAGE._imageData);cputc(':');
		gotoxy(18,1); cputc(PLAYER_IMAGE._imageData);cputc(':');	
	#elif (defined(__ATARI__) || defined(__ATARIXL__)) && defined(ATARI_MODE1)
		SET_TEXT_COLOR(TEXT_COLOR);	
		gotoxy(15+1,0); cputc(GUN_IMAGE._imageData);cputc(':');
		gotoxy(15-3,0); cputc(GHOST_IMAGE._imageData);cputc(':');
		gotoxy(15+20,0); cputc(PLAYER_IMAGE._imageData);cputc(':');
	#elif defined(__APPLE2__) || defined(__APPLE2ENH__) || defined(__CBM__) 
		SET_TEXT_COLOR(TEXT_COLOR);	
		gotoxy(18+1,0); cputc(GUN_IMAGE._imageData);cputc(':');
		gotoxy(18-3,0); cputc(GHOST_IMAGE._imageData);cputc(':');
		gotoxy(18,1); cputc(PLAYER_IMAGE._imageData);cputc(':');
	#elif defined(__CPC__)
		// TODO: to implement
		SET_TEXT_COLOR(TEXT_COLOR);	
		gotoxy(18+1,0+1); cputc(GUN_IMAGE._imageData);cputc(':');
		gotoxy(18-3,0+1); cputc(GHOST_IMAGE._imageData);cputc(':');
		gotoxy(18,1+1); cputc(PLAYER_IMAGE._imageData);cputc(':');	
	#elif defined(__VG5K__)
		SET_TEXT_COLOR(TEXT_COLOR);	

		gotoxy(18-3+1,0); cputc(GHOST_IMAGE._imageData);cputc(':');
		gotoxy(18+1,0); cputc(GUN_IMAGE._imageData);cputc(':');
		
		//18+2+1-X_OFFSET,1-Y_OFFSET
		gotoxy(18+1,2); cputc(PLAYER_IMAGE._imageData);cputc(':');	
	#else
		// TODO: to implement
		SET_TEXT_COLOR(TEXT_COLOR);	
		gotoxy(18+1,0); cputc(GUN_IMAGE._imageData);cputc(':');
		gotoxy(18-3,0); cputc(GHOST_IMAGE._imageData);cputc(':');
		gotoxy(18,1); cputc(PLAYER_IMAGE._imageData);cputc(':');
	#endif

}


void printGunsStats(void)
{
	SET_TEXT_COLOR(TEXT_COLOR);
	
	#if defined (__ATMOS__)
		PRINTF(19-1+1,0-Y_OFFSET,"%hu",guns);
	#elif (defined(__ATARI__) || defined(__ATARIXL__)) && defined(ATARI_MODE1)
		PRINTF(15+2+1-X_OFFSET,0-Y_OFFSET,"%hu",guns);
	#elif defined(__APPLE2__) || defined(__APPLE2ENH__) || defined(__CBM__) 
		PRINTF(18+2+1-X_OFFSET,0-Y_OFFSET,"%hu",guns);
	#elif defined(__SPECTRUM__) || defined(__CPC__)
		PRINTF(18+2+1-X_OFFSET,0-Y_OFFSET,"%d",guns);	
	#elif defined(__VG5K__)	
		PRINTF(18+2+1-X_OFFSET,0-Y_OFFSET,"%u",guns);	
	#else
		PRINTF(18+2+1-X_OFFSET,0-Y_OFFSET,"%hu",guns);
	#endif			
}

void printLevelStats(void)
{	
	SET_TEXT_COLOR(TEXT_COLOR);
	
	#if defined(__ATMOS__) 
		PRINTF(8,1-Y_OFFSET,"%02hu", level);
	#elif (defined(__ATARI__) || defined(__ATARIXL__)) && defined(ATARI_MODE1)
		PRINTF(7-1,1-Y_OFFSET,"%02hu", level);
	#elif defined(__APPLE2__) || defined(__APPLE2ENH__) || defined(__CBM__) 
		PRINTF(8,1-Y_OFFSET,"%02hu", level);
	#elif defined(__SPECTRUM__) || defined(__CPC__)
		PRINTF(8,1-Y_OFFSET,"%02d", level);	
	#elif defined(__VG5K__)	
		PRINTF(8,1-Y_OFFSET,"%02u", level);	
	#else
		PRINTF(8,1-Y_OFFSET,"%02hu", level);	
	#endif	
}

void printGhostCountStats(void)
{
	SET_TEXT_COLOR(TEXT_COLOR);
	
	#if defined (__ATMOS__)
		PRINTF(19-1-3,0-Y_OFFSET,"%hu",ghostCount);
	#elif (defined(__ATARI__) || defined(__ATARIXL__)) && defined(ATARI_MODE1)
		PRINTF(15+2-X_OFFSET-3,0-Y_OFFSET,"%hu",ghostCount);
	#elif defined(__APPLE2__) || defined(__APPLE2ENH__) || defined(__CBM__) 
		PRINTF(18+2-X_OFFSET-3,0-Y_OFFSET,"%hu",ghostCount);
	#elif defined(__SPECTRUM__) || defined(__CPC__)
		PRINTF(18+2-X_OFFSET-3,0-Y_OFFSET,"%d",ghostCount);	
	#elif defined(__VG5K__)		
		PRINTF(18+1+2-X_OFFSET-3,0-Y_OFFSET,"%u",ghostCount);	
	#else
		PRINTF(18+2-X_OFFSET-3,0-Y_OFFSET,"%hu",ghostCount);
	#endif		
}

void printLivesStats(void)
{
	SET_TEXT_COLOR(TEXT_COLOR);
		
	#if defined (__ATMOS__)
		PRINTF(19-1,1-Y_OFFSET,"%02hu",lives);	
	#elif (defined(__ATARI__) || defined(__ATARIXL__)) && defined(ATARI_MODE1)
		PRINTF(15+2-X_OFFSET,1-Y_OFFSET,"%02hu",lives);
	#elif defined(__APPLE2__) || defined(__APPLE2ENH__) || defined(__CBM__) 
		PRINTF(18+2-X_OFFSET,1-Y_OFFSET,"%02hu",lives);
	#elif defined(__SPECTRUM__) || defined(__CPC__)
		PRINTF(18+2-X_OFFSET,1-Y_OFFSET,"%02d",lives);	
	#elif defined(__VG5K__)	
		PRINTF(18+2+1-X_OFFSET,1-Y_OFFSET,"%02u",lives);	
	#else
		PRINTF(18+2-X_OFFSET,1-Y_OFFSET,"%02hu",lives);
	#endif		
}

void displayStats(void)
{	
	SET_TEXT_COLOR(TEXT_COLOR);
	
	#if defined(__ATMOS__) 
		PRINTF(8,0-Y_OFFSET,"%06lu",points);
	#elif (defined(__ATARI__) || defined(__ATARIXL__)) && defined(ATARI_MODE1)
		PRINTF(7-1,0-Y_OFFSET,"%05lu",points);
	#elif defined(__APPLE2__) || defined(__APPLE2ENH__) || defined(__CBM__) 
		PRINTF(8,0-Y_OFFSET,"%06lu",points);
	#elif defined(__SPECTRUM__) || defined(__CPC__)
		PRINTF(8,0-Y_OFFSET,"%06lu",points);	
	#elif defined(__VG5K__)	
		PRINTF(8,0-Y_OFFSET,"%06lu",points);	
	#else
		PRINTF(8,0-Y_OFFSET,"%06lu",points);
	#endif
}


void setScreenColors(void)
{
	#if !(defined(__CBM__) || defined(__ATARI__) || defined(__ATARIXL__) || defined(__APPLE2__) || defined(__APPLE2ENH__))
	#else
		SET_TEXT_COLOR(TEXT_COLOR);
		
		SET_BORDER_COLOR(BORDER_COLOR);
		
		SET_BACKGROUND_COLOR(BACKGROUND_COLOR);
	#endif
}



void printCenteredMessage(char *Text)
{
	SET_TEXT_COLOR(TEXT_COLOR);
	PRINTF((XSize - strlen (Text)) / 2, YSize / 2,"%s", Text);
}

#if defined(__C64__)
void printKillTheSkull(void)
{
	printCenteredMessage("kill the skull!");	
}
#else
void printKillTheSkull(void)
{
	printCenteredMessage("Kill the skull!");
}	
#endif	

#ifdef __C64__
void printLevel(void)
{
	char levelString[22];

	sprintf(levelString, "level %d", level);

	printCenteredMessage(levelString);
}
#else
void printLevel(void)
{
	char levelString[22];

	sprintf(levelString, "LEVEL %d", level);

	printCenteredMessage(levelString);
}
#endif


void _printScore(char * text, unsigned int score)
{
	char levelString[22];

	sprintf(levelString, text, score);

	printCenteredMessage(levelString);
	sleep(1);
}

#ifdef __C64__

	void gameCompleted(void)
	{
		printCenteredMessage("y o u   m a d e   i t !"); 
		sleep(1);
		printCenteredMessage("    t h e   e n d    "); 
		sleep(1);
	}

	void printExtraLife(void)
	{
		printCenteredMessage("e x t r a   l i f e ! ! !"); 
		sleep(1);
	}
#else

	void gameCompleted(void)
	{
		printCenteredMessage("Y O U   M A D E   I T !"); 
		sleep(1);
		printCenteredMessage("     T H E   E N D     "); 
		sleep(1);
	}
	
	#if defined(__VIC20__) || defined(__ATARI__) || defined(__ATARIXL__)
		void printExtraLife(void)
		{
			printCenteredMessage("E X T R A   L I F E!"); 
			sleep(1);
		}
	#else
		void printExtraLife(void)
		{
			printCenteredMessage("E X T R A   L I F E ! ! !"); 
			sleep(1);
		}		
	#endif
#endif


#ifdef __C64__
	void printPressKeyToStart(void)
	{
		printCenteredMessage("press any key to start");
	}

	void deleteCenteredMessage(void)
	{
		PRINT((XSize - 22) / 2, YSize / 2, "                      ");
	}


	void printGameOver(void)
	{
		printCenteredMessage("g a m e   o v e r");
		sleep(1);
	}

	void printVictoryMessage(void)
	{
		printCenteredMessage("y o u   w o n !");
		sleep(1);
	}

	void printDefeatMessage(void)
	{
		printCenteredMessage("y o u   l o s t !");
		sleep(1);
	}
#else
	#if defined(__VIC20__) || defined(__ATARI__) || defined(__ATARIXL__)
		void printPressKeyToStart(void)
		{
			printCenteredMessage("PRESS ANY KEY");
		}
		
		void deleteCenteredMessage(void)
		{
			PRINT(1, YSize / 2, "                      ");
		}		
	#else
		void printPressKeyToStart(void)
		{
			printCenteredMessage("PRESS ANY KEY TO START");
		}	
		
		void deleteCenteredMessage(void)
		{
			PRINT((XSize - 22) / 2 - 2, YSize / 2, "                      ");
		}		
	#endif


	void printGameOver(void)
	{
		printCenteredMessage("G A M E   O V E R");
		sleep(1);
	}

	void printVictoryMessage(void)
	{
		printCenteredMessage("Y O U   W O N ! !");
		sleep(1);
	}

	void printDefeatMessage(void)
	{
		printCenteredMessage("Y O U   L O S T !");
		sleep(1);
	}

#endif


void printStartMessage(void)
{
	#if defined(__C64__)
		SET_TEXT_COLOR(COLOR_RED);
		PRINT((XSize - 22) / 2, 2, "c r o s s   c h a s e");
		//SET_TEXT_COLOR(TEXT_COLOR);
		
		SET_TEXT_COLOR(COLOR_BROWN);
		PRINT((XSize - 22) / 2, YSize / 2 - 7,  "by fabrizio caruso");
		SET_TEXT_COLOR(TEXT_COLOR);	
	#elif defined(__ATMOS__)
		POKE(0xBB80+3*40,16);POKE(0xBB80+1+3*40,1); POKE(0xBB80+2+3*40,14);
		POKE(0xBB80+4*40,16);POKE(0xBB80+1+4*40,1); POKE(0xBB80+2+4*40,14);
		POKE(0xBB80+5*40,16);POKE(0xBB80+1+5*40,1); POKE(0xBB80+2+5*40,14);
		
		POKE(0xBB80+6*40,16);POKE(0xBB80+1+6*40,3); POKE(0xBB80+2+6*40,10);
		POKE(0xBB80+7*40,16);POKE(0xBB80+1+7*40,3); POKE(0xBB80+2+7*40,10);
		
		POKE(0xBB80+8*40,16);POKE(0xBB80+1+8*40,1); POKE(0xBB80+2+8*40,10);
		POKE(0xBB80+9*40,16);POKE(0xBB80+1+9*40,1); POKE(0xBB80+2+9*40,10);
		POKE(0xBB80+10*40,16);POKE(0xBB80+1+10*40,3); POKE(0xBB80+2+10*40,10);
		POKE(0xBB80+11*40,16);POKE(0xBB80+1+11*40,3); POKE(0xBB80+2+11*40,10);

		gotoxy(19,6); cputc(PLAYER_IMAGE._imageData);
		gotoxy(19,7); cputc(PLAYER_IMAGE._imageData);
		
		gotoxy(15,10); cputc(GHOST_IMAGE._imageData);
		gotoxy(15,11); cputc(GHOST_IMAGE._imageData);
		
		gotoxy(19,10); cputc(INVINCIBLE_GHOST_IMAGE._imageData);
		gotoxy(19,11); cputc(INVINCIBLE_GHOST_IMAGE._imageData);
		
		gotoxy(23,10); cputc('>');
		gotoxy(23,11); cputc('>');
		
		gotoxy(9, 5); 
		cputc('C'); 
		cputc(' ');
		cputc('R');
		cputc(' ');
		cputc('O');
		cputc(' ');		
		cputc('S');
		cputc(' ');		
		cputc('S');
		cputc(' ');		
		cputc(' ');
		cputc(' ');		
		cputc('C');
		cputc(' ');		
		cputc('H');
		cputc(' ');		
		cputc('A');
		cputc(' ');		
		cputc('S');
		cputc(' ');		
		cputc('E'); 
		
		gotoxy(9, 4); 
		cputc('C'); 
		cputc(' ');
		cputc('R');
		cputc(' ');
		cputc('O');
		cputc(' ');		
		cputc('S');
		cputc(' ');		
		cputc('S');
		cputc(' ');		
		cputc(' ');
		cputc(' ');		
		cputc('C');
		cputc(' ');		
		cputc('H');
		cputc(' ');		
		cputc('A');
		cputc(' ');		
		cputc('S');
		cputc(' ');		
		cputc('E'); 
	#elif defined(__VIC20__) || ((defined(__ATARI__) || defined(__ATARIXL__)) && defined(ATARI_MODE1))
		SET_TEXT_COLOR(TEXT_COLOR);	
		#if defined(__VIC20__)
			PRINT(1, YSize / 2 - 9, "C R O S S  C H A S E");
		#else
			PRINT(0, YSize / 2 - 9, "C R O S S  C H A S E");			
		#endif
		SET_TEXT_COLOR(TEXT_COLOR);
		
		SET_TEXT_COLOR(COLOR_RED);
		PRINT(1, YSize / 2 - 7,  "by fabrizio caruso");	
	#else
		SET_TEXT_COLOR(TEXT_COLOR);	
		PRINT((XSize - 22) / 2, YSize / 2 - 9, "C R O S S  C H A S E");
		SET_TEXT_COLOR(TEXT_COLOR);
		
		SET_TEXT_COLOR(COLOR_RED);
		PRINT((XSize - 22) / 2, YSize / 2 - 7,  "by Fabrizio Caruso");
		SET_TEXT_COLOR(TEXT_COLOR);
	#endif
	
	#if defined(__PLUS4__) || defined(__C16__)
	#else
		SET_TEXT_COLOR(COLOR_BLUE);
	#endif // __PLUS4__

	#if defined(__VIC20__) 
		PRINT(1, YSize / 2 - 3, "You are chased by O");
		
		PRINT(1, YSize / 2 - 2, "Force O into X");
		
		PRINT(1, YSize / 2 - 1, "S to slows O down");
		
		PRINT(1, YSize / 2, "Catch ! for bullets");
		
		PRINT(1, YSize / 2 + 1, "Flee from +!");
	#elif (defined(__ATARI__) || defined(__ATARIXL__)) && defined(ATARI_MODE1)
		PRINT(1, YSize / 2 - 3, "you are chased by O");
		
		PRINT(1, YSize / 2 - 2, "force O into X");
		
		PRINT(1, YSize / 2 - 1, "S to slows O down");
		
		PRINT(1, YSize / 2, "catch ! for bullets");
		
		PRINT(1, YSize / 2 + 1, "flee from +");		
	#elif defined(__PET__) || defined(__CBM610__) || (defined(__C128__) && defined(C128_80COL_VIDEO_MODE))
		PRINT(22, YSize / 2 - 3, "You * are chased by O. Force O into X");
		
		PRINT(20, YSize / 2 - 1,  "Take S to slow O down. Catch ! for bullets.");
		
		PRINT(30, YSize / 2 + 1, "Flee from +!");
	#elif defined(__C64__) 
		PRINT((XSize - 22) / 2, YSize / 2 - 3, "escape the enemies");
		
		PRINT((XSize - 22) / 2, YSize / 2 - 1, "force them into the mines");
		
		PRINT((XSize - 22) / 2, YSize / 2 + 1, "catch the gun for bullets");
		SET_TEXT_COLOR(COLOR_BROWN);
		PRINT((XSize - 22) / 2, YSize / 2 + 4, "use joystick in port 1");
		SET_TEXT_COLOR(TEXT_COLOR);
	#elif defined(__ATMOS__)
		PRINT(7, YSize / 2 - 1, "Escape from the enemies");
		
		PRINT(7, YSize / 2, "Forse them into the mines");
		
	#elif defined(__C16__) || defined(__PLUS4__)
		PRINT(1, YSize / 2 - 3, "You % are chased by \"! Lure \" into /!");
		
		PRINT(1, YSize / 2 - 1, "# slows \" down! ,. gives you 3 bullets");
		
		PRINT(5, YSize / 2 + 1,     "Use the gun or flee from +!");	
	#elif defined(__SPECTRUM__) && !defined(SPECTRUM_NATIVE_DIRECTIVES)
		PRINT(0, YSize / 2 - 3, "Lure the enemies into the mines!");
		
		PRINT(0, YSize / 2 - 1, "Take the power-ups! Use the gun!");
		
		PRINT(2, YSize / 2 + 1,   "Shoot or flee from the skull!");	
	#elif defined(__SPECTRUM__) && defined(SPECTRUM_NATIVE_DIRECTIVES)
		PRINT(0, YSize / 2 - 3, "Lure the enemies into the mines!");
		
		PRINT(0, YSize / 2 - 1, "Take the power-ups! Use the gun!");
		
		PRINT(2, YSize / 2 + 1,   "Shoot or flee from the skull!");			
	#else
		PRINT(2, YSize / 2 - 3, "You * are chased by O. Lure O into X");
		
		PRINT(0, YSize / 2 - 1, "Take S to slow O down. ! gives 3 bullets");
		
		PRINT(7, YSize / 2 + 1, "Flee from +!");
	#endif

	#if defined(__C64__) || defined(__C128__) || defined(__PET__)
	#elif defined(__C16__) || defined(__PLUS4__)
		SET_TEXT_COLOR(COLOR_GRAY1);
		PRINT((XSize - 22) / 2 - 2, YSize / 2 + 4, "Use Joystick in first port");
		SET_TEXT_COLOR(TEXT_COLOR);
	#elif defined(__VIC20__)
		SET_TEXT_COLOR(COLOR_GREEN);
		PRINT(1, YSize / 2 + 4, "Use the Joystick");
		SET_TEXT_COLOR(TEXT_COLOR);	
	#elif defined(__APPLE2__) || defined(__APPLE2ENH__) || defined(__SPECTRUM__)
		PRINT((XSize - 22) / 2, YSize / 2 + 4, "Use W A S D <SPACE>");
	#elif defined(__ATMOS__) 
		POKE(0xBB80+(YSize / 2 + 4 + 1)*40,16);POKE(0xBB81+(YSize / 2 + 4 +1)*40,4);
		POKE(0xBB80+(YSize / 2 + 4 + 2)*40,16);POKE(0xBB81+(YSize / 2 + 4 +2)*40,4);
		POKE(0xBB80+(YSize / 2 + 4 + 3)*40,16);POKE(0xBB81+(YSize / 2 + 4 +3)*40,4);
		PRINT((XSize - 22) / 2-2, YSize / 2 + 4 - 1,"Controls: Use W A S D SPACE");	
		POKE(0xBB80+(YSize / 2 + 4 + 4)*40,16);POKE(0xBB81+(YSize / 2 + 4 +4)*40,12);
		POKE(0xBB80+(YSize / 2 + 4 + 5)*40,16);POKE(0xBB81+(YSize / 2 + 4 +5)*40,12);
		POKE(0xBB80+(YSize / 2 + 4 + 6)*40,16);POKE(0xBB81+(YSize / 2 + 4 +6)*40,12);

		gotoxy(19,8); cputc(MISSILE_IMAGE._imageData);
		gotoxy(19,9); cputc(MISSILE_IMAGE._imageData);
	#elif (defined(__ATARI__) || defined(__ATARIXL__)) && defined(ATARI_MODE1)
		PRINT(1, YSize / 2 + 4, "use the joystick");
	#elif defined(__VG5K__)
		PRINT((XSize - 22) / 2, YSize / 2 + 4, "Use I J K L SPACE");
	#else 
		PRINT((XSize - 22) / 2, YSize / 2 + 4, "Use the Joystick");
	#endif
	SET_TEXT_COLOR(TEXT_COLOR);

	#if defined(__VIC20__) || ((defined(__ATARI__) || defined(__ATARIXL__)) && defined(ATARI_MODE1))
		PRINT(3, YSize / 2 + 7, "press any key");
	#elif defined(__C64__)
		PRINT((XSize - 22) / 2, YSize / 2 + 6, "press any key");
	#else
		PRINT((XSize - 22) / 2 + 3, YSize / 2 + 6, "Press any key");
	#endif
}


