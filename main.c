#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

void wait() {
	fflush(stdin);
	fgetc(stdin);
}

int isNumber(char c) {
	return (c >= '0' && c <= '9') ? 1 : 0;
}

int isAlphanumeric(char c) {
	if (c >= 'a' && c <= 'z') return 1;
	if (c >= 'A' && c <= 'Z') return 1;
	if (isNumber(c)) return 1;
	return 0;
}

int main(int argc, char *argv[]){
	char *tmp;
	
	if (argc < 2) {
		printf("No input files.\n");
		wait();
		return -1;
	}
	
	char *argFile = argv[1];
	
	// Output file
	char file[1024];
	sprintf(file, "%s.h", argFile);
	
	// Get input file name
	char *name = argFile;
	for (tmp = argFile; *tmp != '\0'; tmp++) {
		if (*tmp == '\\' || *tmp == '/' ) {
			name = tmp + 1;
		}
	}
	
	// Input file name to upper case
	char nameUpper[256];
	sprintf(nameUpper, "_%s", name);
	for (tmp = nameUpper; *tmp != '\0'; tmp++) {
		if (isAlphanumeric(*tmp)) {
			*tmp = toupper(*tmp);
		} else {
			*tmp = '_';
		}
	}
	
	// Input file name to lower case
	char nameLower[256];
	if (isNumber(*name)) {
		sprintf(nameLower, "_%s", name);
	} else {
		sprintf(nameLower, "%s", name);
	}
	for (tmp = nameLower; *tmp != '\0'; tmp++) {
		if (isAlphanumeric(*tmp)) {
			*tmp = toupper(*tmp);
		} else {
			*tmp = '_';
		}
	}
	
	// Open files
	FILE *fi = fopen(argFile, "rb");
	if (fi == NULL) {
		printf("Unable to open %s for reading.\n", argFile);
		wait();
		return -1;
	}
	FILE *fo = fopen(file, "wt");
	if (fo == NULL) {
		printf("Unable to open %s for writing.\n", file);
		wait();
		fclose(fi);
		return -1;
	}

	//Write output
	fprintf(fo, "#ifndef %s_H_\n", nameUpper);
	fprintf(fo, "#define %s_H_\n", nameUpper);
	fprintf(fo, "\n");
	fprintf(fo, "static const unsigned char %s[] = {\n", nameLower);
	int c, count = 0;
	while ((c = fgetc(fi)) != EOF) {
		char ch = (unsigned char)c;
		if (count == 12) {
			fprintf(fo, ",\n");
			count = 0;
		}
		fprintf(fo, (count > 0) ? ", " : "\t");
		fprintf(fo, "0x%.2X", ch & 0xFF);
		count++;
	}
	fprintf(fo, "\n");
	fprintf(fo, "};\n");
	fprintf(fo, "\n");
	fprintf(fo, "#endif\n");
	fclose(fi);
	fclose(fo);
	
	//printf("Done.\n");
	//wait();
	
	return 0;
}
