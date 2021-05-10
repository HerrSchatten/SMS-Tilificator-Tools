// mmframes.c
// reads project file from Tilificator and offset data, outputs metasprite frames (tiles and positions)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define zeroX 24
#define zeroY 24
#define linemax 1024

FILE *fINt;
FILE *fINo;
FILE *fOUTf;
FILE *fOUTt;

int framecounter, tilecounter = 0;
int xo, yo = 0;
int xtemp, ytemp, ttemp = 0;
int t[16];
int x[16];
int y[16];

bool activeframe = false;

const char activator[] = "spritetiles";

char linebuffer[linemax];


int main (int argc, char *argv[]) {

	if (argc != 3) {
		printf ("Usage: mmframes inputfile.tpr inputfile.txt\n");
		return EXIT_FAILURE;
	}

	fINt=fopen(argv[1],"r");
	if (fINt == NULL) {
		printf("Can't open %s\n", argv[1]);
		return EXIT_FAILURE;
	}
	fINo=fopen(argv[2],"r");
	if (fINt == NULL) {
		printf("Can't open %s\n", argv[2]);
		return EXIT_FAILURE;
	}
	fOUTf=fopen("frames.inc","w");
	if (fOUTf == NULL) {
		printf("Can't open frames output.\n");
		return EXIT_FAILURE;
	}
	fOUTt=fopen("tiles.inc","w");
	if (fOUTt == NULL) {
		printf("Can't open tiles output.\n");
		return EXIT_FAILURE;
	}

	while (fgets(linebuffer, linemax, fINt)) {
		if ((activeframe == false) && (strstr(linebuffer, activator) != NULL)) {
			activeframe = true;
			tilecounter = 0;
			fscanf(fINo, "%d, %d\n", &xo, &yo); // read offsets
			fgets(linebuffer, linemax, fINt);
		}
		if ((activeframe == true) && (strchr(linebuffer, 'x') != NULL)) {
			sscanf(linebuffer, " \"x\":%d,\n", &xtemp);
			x[tilecounter] = xtemp + xo - zeroX;
		}
		if ((activeframe == true) && (strchr(linebuffer, 'y') != NULL)) {
			sscanf(linebuffer, " \"y\":%d,\n", &ytemp);
			y[tilecounter] = ytemp + yo - zeroY;
		}
		if ((activeframe == true) && (strchr(linebuffer, 't') != NULL)) {
			sscanf(linebuffer, " \"t\":%d,\n", &ttemp);
			t[tilecounter] = ttemp;
			tilecounter = tilecounter + 1;
		}
		if ((activeframe == true) && (strchr(linebuffer, ']') != NULL)) {
			
			// dump tile numbers for this frame
			fprintf(fOUTt, "Tiles%d:\n", framecounter);
			fprintf(fOUTt, ".db %d\n", tilecounter);
			fprintf (fOUTt, ".db ");
			int i;
			for (i=0; i<(tilecounter-1); i++ ) {
				fprintf(fOUTt, "%d, ", t[i]);
			}
			fprintf(fOUTt, "%d\n\n", t[i]);
			
			// dump xy coordinates for this frame
			fprintf(fOUTf, "Frame%d:\n", framecounter);
			fprintf(fOUTf, ".db %d\n", tilecounter);
			fprintf (fOUTf, ".db ");
			for (i=0; i<(tilecounter-1); i++ ) {
				fprintf(fOUTf, "%d, %d, ", y[i], x[i]);
			}
			fprintf(fOUTf, "%d, %d\n\n", y[i], x[i]);
			
			activeframe = false;
			framecounter = framecounter + 1;
		}
	} 

	fclose (fINt);
	fclose (fINo);
	fclose (fOUTf);
	fclose (fOUTt);
  
	printf ("Info: Done!\n");
	return EXIT_SUCCESS;
}
