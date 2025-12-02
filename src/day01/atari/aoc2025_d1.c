#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<stdio.h>

//compiled with cc65:
//cl65 -t atari -o aoc2025d1.xex aoc2025_d1.c

/*
#define ROWS 10
char testData[ROWS][4] = {
	"L68", "L30", "R48", "L5" , "R60",
	"L55", "L1" , "L99", "R14", "L82"
};
*/
#include"aocData.h"

int part1()
{
	int i, val;
	int answer1 = 0;
	int pos = 50;
	for(i = 0; i < ROWS; i++)
	{
		if((i % 100) == 0) cputc('.');
		val = atoi(&testData[i][1]);
		if(testData[i][0] == 'R')
			pos += val;
		else
			pos -= val;
		while(pos > 99) pos -= 100;
		while(pos <  0) pos += 100;
		if(pos == 0) answer1++;
	}
	return answer1;
}

int part2()
{
	int i, j, ii;
	int answer2 = 0;
	int pos = 50;
	for(i = 0; i < ROWS; i++)
	{
		if((i % 100) == 0) cputc('x');
		ii = atoi(&testData[i][1]);
		if(testData[i][0] == 'R')
		{
			for(j = 0; j < ii; j++)
			{
				pos++;
				if(pos > 99) pos -= 100;
				if(pos == 0) answer2++;
			}
		}
		else
		{
			for(j = 0; j < ii; j++)
			{
				pos--;
				if(pos <  0) pos += 100;
				if(pos == 0) answer2++;
			}
		}
	}
	return answer2;
}

int main(void)
{
	int answer1, answer2;
    unsigned char xSize, ySize;
    char text0[] = "Atari 800XL";
	char text1[] = "AOC 2025 - Day 1 - Part 1 = ";
	char text2[] = "AOC 2025 - Day 1 - Part 2 = ";

    clrscr();
    screensize(&xSize, &ySize);

	answer1 = part1();
	answer2 = part2();

    while(1)
    {
        gotoxy((xSize - strlen(text0)) / 2, ySize / 2 - 4);
        cprintf("%s", text0);

        gotoxy((xSize - strlen(text1)) / 2, ySize / 2 - 2);
        cprintf("%s", text1);
        cprintf("%d", answer1);

        gotoxy((xSize - strlen(text2)) / 2, ySize / 2);
        cprintf("%s", text2);
        cprintf("%d", answer2);

		cgetc();
        clrscr();
    }

    return EXIT_SUCCESS;
}
