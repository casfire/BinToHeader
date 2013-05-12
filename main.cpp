#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

void wait(){
	fflush(stdin);
	fgetc(stdin);
}

int main(int argc, char *argv[]){
	char *tmp;

	if(argc < 2){
		printf("No input files.\n");
		wait();
		return -1;
	}

	char *argFile = argv[1];

	//Output file
	char file[1024];
	sprintf(file,"%s.h",argFile);

	//Get input file name
	char *name = argFile;
	for(tmp = argFile; *tmp != 0; tmp++){
		if((*tmp == '\\')||(*tmp == '/'))name = tmp+1;
	}

	//Input file name to upper case
	char nameUpper[256];
	strcpy(nameUpper, name);
	for(tmp = nameUpper; *tmp != 0; tmp++){
		if(*tmp == '.')*tmp = '_';
		else *tmp = toupper(*tmp);
	}

	//Input file name to lower case
	char nameLower[256];
	strcpy(nameLower, name);
	for(tmp = nameLower; *tmp != 0; tmp++){
		if(*tmp == '.')*tmp = '_';
		else *tmp = tolower(*tmp);
	}

	FILE *fi = fopen(argFile,"rb");
	if(fi == NULL){
		printf("Unable to open %s for reading.\n", argFile);
		wait();
		return -1;
	}
	FILE *fo = fopen(file,"wt");
	if(fo == NULL){
		printf("Unable to open %s for writing.\n", file);
		wait();
		fclose(fi);
		return -1;
	}

	fprintf(fo, "#ifndef %s_H_\n", nameUpper);
	fprintf(fo, "#define %s_H_\n", nameUpper);
	fprintf(fo, "\n");
	fprintf(fo, "static const unsigned char %s[] = {\n", nameLower);
	int c, count = 0;
	while((c = fgetc(fi)) != EOF){
		char ch = (unsigned char)c;
		if(count == 11){
			fprintf(fo, ",\n");
			count = 0;
		}
		if(count > 0)fprintf(fo, ", ");
		else fprintf(fo, "\t");
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
