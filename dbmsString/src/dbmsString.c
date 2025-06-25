#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SQL_LEN		1000
#define	SUBSTR		"SUBSTR"
#define	SUBSTRING	"SUBSTRING"
#define	SBSTR		"SBSTR"
#define DBMS1		"DBMS1"
#define DBMS2		"DBMS2"
#define DBMS3		"DBMS3"

// This function replaces an oldString with a newString
void replaceSubString(char *str, const char *oldString, const char *newString) {
    char result[SQL_LEN];
    char *pos, temp[SQL_LEN];
    int index = 0;
    int oldStringLen = strlen(oldString);

    // Copy original string to temp
    strcpy(temp, str);

    while ((pos = strstr(temp, oldString)) != NULL) {
        // Copy characters before the oldString
        int lenBefore = pos - temp;
        strncpy(result + index, temp, lenBefore);
        index += lenBefore;

        // Copy the newString
        strcpy(result + index, newString);
        index += strlen(newString);

        // Move past the oldString in temp
        strcpy(temp, pos + oldStringLen);
    }

    // Copy the remaining part of temp
    strcpy(result + index, temp);

    // Copy result back to original string
    strcpy(str, result);
}

// Rebuild query with substring for given DBMS
// This function assumes that the 3 variants(SUBSTRING,SUBSTR,SBSTR) are the only substring commands that are possible.
// It will replace whichever any of these with the appropriate substring command.
void rebuildQuery(char *str, const char *dbms){
	// Check which DBMS query is needed for
	if (strcmp(dbms,DBMS1) == 0) {
		// Only call if given subString exists in query
		if (strstr(str, SUBSTRING) != NULL) {
			replaceSubString(str, SUBSTRING, SUBSTR);
		}
		if (strstr(str, SBSTR) != NULL) {
			replaceSubString(str, SBSTR, SUBSTR);
		}
	}
	else if (strcmp(dbms,DBMS2) == 0) {
		if (strstr(str, SUBSTR) != NULL) {
			replaceSubString(str, SUBSTR, SUBSTRING);
		}
		if (strstr(str, SBSTR) != NULL) {
			replaceSubString(str, SBSTR, SUBSTRING);
		}
	}
	else if (strcmp(dbms,DBMS3) == 0) {
		if (strstr(str, SUBSTRING) != NULL) {
			replaceSubString(str, SUBSTRING, SBSTR);
		}
		if (strstr(str, SUBSTR) != NULL) {
			replaceSubString(str, SUBSTR, SBSTR);
		}
	}
	else {
		printf("DBMS %s not found!",dbms);
	}

}

int main() {
    char str1[SQL_LEN] = "SELECT SUBSTRING(COL1,1,3),SBSTR(COL2,1,3) FROM MYTABLE";
    char str2[SQL_LEN] = "SELECT SUBSTR(COL1,1,3),SBSTR(COL2,1,3) FROM MYTABLE";
    char str3[SQL_LEN] = "SELECT SUBSTRING(COL1,1,3),SUBSTR(COL2,1,3) FROM MYTABLE";

    printf("Test Function for DBMS1.  Original Query:%s\n", str1);
    rebuildQuery(str1,DBMS1);
    printf("New Query:%s\n", str1);
    printf("Test Function for DBMS2.  Original Query:%s\n", str2);
    rebuildQuery(str2,DBMS2);
    printf("New Query:%s\n", str2);
    printf("Test Function for DBMS3.  Original Query:%s\n", str3);
    rebuildQuery(str3,DBMS3);
    printf("New Query:%s\n", str3);
    return EXIT_SUCCESS;
}
