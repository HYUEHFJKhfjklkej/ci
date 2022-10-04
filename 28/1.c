#include <stdio.h>
void read_file();
int main() {
    int mode = 0;
    while (mode != -1) {
        scanf("%d", &mode);
        if (mode ==1) {
            read_file();
        }  
    }
    
}

void read_file() {
    FILE *mf;
    char file_name[200], ch;
    scanf("%s", file_name);
    mf = fopen(file_name, "r");
    if (mf == NULL) {
        printf("n/a");
    } else {
        ch = fgetc(mf);
        if (ch != EOF)
        {
            while (ch != EOF)
            {
                putchar(ch);
            }
            
        } else {
            printf("n/a");
        }
        fclose(mf);  
    }
}