// mixbpls.c
// reads raw tile data exported from Tilificator, interlaces the bitplanes, and outputs as many of them as desired
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

FILE *fIN;
FILE *fOUT;

int bitplanes = 4;

int bpl1[8];
int bpl2[8];
int bpl3[8];
int bpl4[8];

int main (int argc, char *argv[]) {

	if (argc == 4) {
		bitplanes = atoi(argv[3]);
	}

	if ((argc<3) || (argc>4) || (bitplanes<1) || (bitplanes>4)) {
		printf ("Usage: mixbpls inputfile.bin outputfile.bin [1|2|3|4]\n");
		return EXIT_FAILURE;
	}

	fIN=fopen(argv[1],"rb");
	if (fIN == 0) {
		printf("Can't open %s\n", argv[1]);
		return EXIT_FAILURE;
	}
	fOUT=fopen(argv[2],"w+b");
	if (fOUT == 0) {
		printf("Can't open %s\n", argv[2]);
		return EXIT_FAILURE;
	}

	while ( (bpl1[0]=fgetc(fIN)) != EOF ) {
		for (int i=1; i<8; i++) {
			bpl1[i]=fgetc(fIN); 
		}
		for (int i=0; i<8; i++) {
			bpl2[i]=fgetc(fIN); 
		}
		for (int i=0; i<8; i++) {
			bpl3[i]=fgetc(fIN); 
		}
		for (int i=0; i<8; i++) {
			bpl4[i]=fgetc(fIN); 
		}
		for (int i=0; i<8; i++) {
			fputc(bpl1[i], fOUT);
			if (bitplanes>=2) {
				fputc(bpl2[i], fOUT);
			}
			if (bitplanes>=3) {
				fputc(bpl3[i], fOUT);
			}
			if (bitplanes==4) {
				fputc(bpl4[i], fOUT);
			}
		}
		
	} 

	fclose (fIN);
	fclose (fOUT);
  
	printf ("Info: done!\n");
	return EXIT_SUCCESS;
}
