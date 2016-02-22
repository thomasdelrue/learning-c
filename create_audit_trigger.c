/* Automate creation of audit triggers.
   
   input: 2 arguments: name table, alias name
   output: trigger file
*/
#include <stdio.h>

int create_trigger(char *table, char *alias) 
{
	char *filename;
	sprintf(filename, "t_%s_ad.trg", alias);
	
	printf("creating file: %s\n", filename);
	FILE *out_file = fopen(filename, "w");
	
	fprintf(out_file, "PROMPT CREATE OR REPLACE TRIGGER T_%s_AD\n", alias);
	fprintf(out_file, "CREATE OR REPLACE TRIGGER \"T_%s_AD\"\n", alias);
	fprintf(out_file, "BEFORE INSERT OR UPDATE\n");
	fprintf(out_file, "ON %s\n", table);
	fprintf(out_file, "FOR EACH ROW\n");
	fprintf(out_file, "BEGIN\n");
	fprintf(out_file, "/* CVS information :\n");
	fprintf(out_file, " *\n");
	fprintf(out_file, " * $Id: $\n");
	fprintf(out_file, " *\n");
	fprintf(out_file, " */\n");
	fprintf(out_file, "  If Inserting Then\n");
    fprintf(out_file, "    :new.DTCREATIE := Sysdate;\n");
    fprintf(out_file, "    :new.USERCREATIE := sys_context('P4_GGR_CTX','USER');\n");
	fprintf(out_file, "  Elsif Updating Then\n");
	fprintf(out_file, "    :new.DTWIJZIGING := Sysdate;\n");
    fprintf(out_file, "   :new.USERWIJZIGING := sys_context('P4_GGR_CTX','USER');\n");
	fprintf(out_file, "  End If;\n");
	fprintf(out_file, "End;\n");
	fprintf(out_file, "/\n");
	fprintf(out_file, "SHOW ERROR\n");
	
	fclose(out_file);
	
	return 0;
}

int main(int argc, char* argv[])
{
	char *tablename, *alias;
	int retval;
	
	if (argc == 3) {
		retval = create_trigger(argv[1], argv[2]);
	} else if (argc == 1) {
		while (scanf("%s,%6[^\n]", tablename, alias) == 2) {
			printf("output: %s %s\n", tablename, alias);
			retval = create_trigger(tablename, alias);			
		}
	} else {
		fprintf(stderr, "Usage: either 2 arguments or ");
		return 1;
	}

	
	return retval;
}