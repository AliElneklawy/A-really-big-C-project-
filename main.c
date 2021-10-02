#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <assert.h>
//#include <graphics.h>
#include <wchar.h>
#include <ctype.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#define MAX 1000

//FSOUND_SAMPLE* handle;

//char* song = "Creepy-background-music.wav";

int set_password(char []);
int numofbooks(FILE *);
int searchauthor(FILE *);
int searchtitle(FILE *);
char * reset(char pass_reset[]);
int savepassword(char []);
int edit(FILE *);
int add();
void start();
int del(FILE *);
int abstract(FILE *, int *);
int game();
void startgame();
int theme();
int quraan();

struct books{
    char bname[150];
    char bauthor[100];
    char *abstract;
    unsigned bpages,
             price,
             numavail;
} info[MAX];


void colour()
{
    FILE *th = fopen("themes.thm", "r");
    char them;
    them = fgetc(th);

    if (them == 'd') {
        system("color 07");
        fclose(th);
    }
    else if (them == 'l') {
        system("color F0");
        fclose(th);
    }
}


char *strcasestr(const char *str, const char *pattern) {
    size_t i;

    if (!*pattern)
        return (char*)str;

    for (; *str; str++) {
        if (toupper((unsigned char)*str) == toupper((unsigned char)*pattern)) {
            for (i = 1;; i++) {
                if (!pattern[i])
                    return (char*)str;
                if (toupper((unsigned char)str[i]) != toupper((unsigned char)pattern[i]))
                    break;
            }
        }
    }
    return NULL;
}


int readbooks (void) {
    FILE *ptr = fopen("books info.dtt", "r");
    if ( ! ptr) {
        perror ( "books info.dtt");
        return 0;
    }
    int book = 0;
    int field = -1;
    int each = 0;
    int parse = 0;
    int ch = 0;

    info[0].bname[0] = 0;
    info[0].bauthor[0] = 0;
    info[0].bpages = 0;
    info[0].price = 0;
    info[0].numavail = 0;

    while ( EOF != ( ch = fgetc ( ptr))) {
       // printf("%c", ch);

        if ( '\n' == ch) {
            parse = 0;//end of line. no parsing
        }
        if ( parse) {
            if ( ! each && ( ' ' == ch || '\t' == ch)) {
                continue;//skip leading spaces
            }
            if ( 0 == field) {
                if ( each + 1 < 150) {
                    info[book].bname[each] = ch;
                    ++each;
                    info[book].bname[each] = 0;
                }
               // printf ( "name %s  ", info[book].bname);
            }
            if ( 1 == field) {
                if ( each + 1 < 100) {
                    info[book].bauthor[each] = ch;
                    ++each;
                    info[book].bauthor[each] = 0;
                }
               // printf ( "author %s  ", info[book].bauthor);
            }
            if ( 2 == field) {
                info[book].bpages *= 10;
                info[book].bpages += ch - '0';
            }
            if ( 3 == field) {
                info[book].price *= 10;
                info[book].price += ch - '0';
            }
            if ( 4 == field) {
                info[book].numavail *= 10;
                info[book].numavail += ch - '0';
            }
        }
        if ( ':' == ch) {
            ++field;
            if ( 5 == field) {
                field = 0;
                if ( book + 1 < MAX) {
                    ++book;
                    info[book].bname[0] = 0;
                    info[book].bauthor[0] = 0;
                    info[book].bpages = 0;
                    info[book].price = 0;
                    info[book].numavail = 0;
                }
            }
            each = 0;
            parse = 1;//resume parsing
        }
    }
    fclose ( ptr);
    if (4 == field) {
        ++book;
    }
    return book;
}

/*void clock()
{
    int h = 2, m = 41, s = 12;
    int d = 1000;


    while(1){
        s++;
        if (s > 59){
            m++;
            s = 0;
        }
        if (m > 59){
            h++;
            m = 0;
        }
        if(h>12){
            h = 1;
        }

        printf("%02d : %02d : %02d", h, m, s);
        Sleep(d);
        system("cls");
        //menu();

    }
    printf("\n\n");

}*/

void startgame()
{
    //system("color 04");
    char start[11] = " GOOD LUCK";

    printf("\n\n\n\n\n\n\n                 ");
    for (int i = 1; i < 20; i++) {
        printf("*");
        Sleep(50);
    }
    for (int i = 0; i < 11; i++) {
        printf("%c", start[i]);
        Sleep(50);
    }
    for (int i = 1; i < 20; i++) {
        printf("*");
        Sleep(50);
    }

    Sleep(1000);
    system("cls");
}

void start()
{

         //system("color 04");
         char start[8] = "WELCOME";

         printf("\n\n\n\n\n\n\n                 ");
         Sleep(500);
         for (int as = 1; as < 20; as++) {
            Sleep(50);
            printf("-");
         }
         printf(">");
         printf(" ");

         for (int as = 0; as < 9; as++) {
            Sleep(50);
            printf("%c", start[as]);
         }
         printf("\b");

         printf("<");
         for (int as = 1; as < 20; as++) {
            Sleep(50);
            printf("-");
         }
         Sleep(1000);
         system("cls");

         return;
}

int wmain(void) {

    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    int m;
    printf(" %d ", tm.tm_mday);
    m = tm.tm_mon+1;
    switch(m)
    {
        case 1:
            printf("Jan, ");
            break;
        case 2:
            printf("Feb, ");
            break;
        case 3:
            printf("Mar, ");
            break;
        case 4:
            printf("Apr, ");
            break;
        case 5:
            printf("May, ");
            break;
        case 6:
            printf("June, ");
            break;
        case 7:
            printf("July, ");
            break;
        case 8:
            printf("Aug, ");
            break;
        case 9:
            printf("Sep, ");
            break;
        case 10:
            printf("Oct, ");
            break;
        case 11:
            printf("Nov, ");
            break;
        case 12:
            printf("Dec, ");
            break;
    }
    printf("%d", tm.tm_year+1900);
    printf("\n ");
    if(tm.tm_hour>=12)
    {
        if(tm.tm_hour==12)
            printf("12");
        else
            printf("%d", tm.tm_hour-12);
        printf(":%d PM\n", tm.tm_min);
    }
    else
        printf("%d:%d AM", tm.tm_hour, tm.tm_min);
    //getch();
    return 0;
}

void gotoxy(int x, int y)
{
    COORD coord = {0, 0};
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void draw_box()
{
    unsigned i, xc = 5, yc = 20;

    gotoxy(20, 4);
    printf("%c", 201);

    for (i = 1; i < 37; i++) {
        printf("%c", 205);
    }
    printf("%c", 187);

    for (int l = 1; l < 14; l++) {
        gotoxy(yc, xc++);
        printf("%c", 186);
        for (i = 1; i < 37; i++) {
            printf("%c", 32);
        }
        printf("%c", 186);
    }

    gotoxy(20, 17);
    printf("%c", 200);
    for (i = 1; i < 37; i++) {
        printf("%c", 205);
    }
    printf("%c", 188);
}

void ShowConsoleCursor(int showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorlnfo;

    GetConsoleCursorInfo(out, &cursorlnfo);
    cursorlnfo.bVisible = showFlag;

    SetConsoleCursorInfo(out, &cursorlnfo);
}

int menu()
{

    system("color 07");

    int n, pos = 1;
    char ch;

    wmain();
    draw_box();

    ShowConsoleCursor(0);

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    do {
        SetConsoleTextAttribute(console, 15);

        gotoxy(21, 5);   printf(" Add a book.                        ");
        gotoxy(21, 6);   printf(" Display books available.           ");
        gotoxy(21, 7);   printf(" Search by author.                  ");
        gotoxy(21, 8);   printf(" Search by book title.              ");
        gotoxy(21, 9);   printf(" Show number of books we have.      ");
        gotoxy(21, 10);   printf(" Set password                       ");
        gotoxy(21, 11);   printf(" Edit the library.                  ");
        gotoxy(21, 12);   printf(" Delete a book                      ");
        gotoxy(21, 13);   printf(" Theme mode.                        ");
        gotoxy(21, 14);   printf(" Golden millionaire game.           ");
        gotoxy(21, 15);   printf(" MP3 QURA'AN                        ");
        gotoxy(21, 16);   printf(" Exit.                              ");

        switch(pos){

        case 1:
            SetConsoleTextAttribute(console, 6);
            gotoxy(21, 5);   printf(" Add a book.                        ");
            break;

        case 2:
            SetConsoleTextAttribute(console, 6);
            gotoxy(21, 6);   printf(" Display books available.           ");
            break;

        case 3:
            SetConsoleTextAttribute(console, 6);
            gotoxy(21, 7);   printf(" Search by author.                  ");
            break;

        case 4:
            SetConsoleTextAttribute(console, 6);
            gotoxy(21, 8);   printf(" Search by book title.              ");
            break;

        case 5:
            SetConsoleTextAttribute(console, 6);
            gotoxy(21, 9);   printf(" Show number of books we have.      ");
            break;

        case 6:
            SetConsoleTextAttribute(console, 6);
            gotoxy(21, 10);   printf(" Set password.                      ");
            break;

        case 7:
            SetConsoleTextAttribute(console, 6);
            gotoxy(21, 11);   printf(" Edit the library.                  ");
            break;

        case 8:
            SetConsoleTextAttribute(console, 6);
            gotoxy(21, 12);   printf(" Delete a book.                     ");
            break;

        case 9:
            SetConsoleTextAttribute(console, 6);
            gotoxy(21, 13);   printf(" Theme mode.                        ");
            break;

        case 10:
            SetConsoleTextAttribute(console, 6);
            gotoxy(21, 14);   printf(" Golden millionaire game.           ");
            break;

        case 11:
            SetConsoleTextAttribute(console, 6);
            gotoxy(21, 15);   printf(" MP3 QURA'AN.                       ");
            break;

        case 12:
            SetConsoleTextAttribute(console, 6);
            gotoxy(21, 16);   printf(" Exit.                              ");
            break;
        }

        ch = getch();
        if (ch == -32) {
            ch = getch();
        }

        if (ch == 72) {
            pos--;

            if (pos == 0) {
                pos = 12;
            }

        }

        if (ch == 80) {
            pos++;

            if (pos == 13) {
                pos = 1;
            }
        }

    } while(ch != 13);

    //printf("\n              Welcome to our book store.... \n\n\n");
    //printf(" [1]. Add a book.\n [2]. Display books available.\n [3]. Search by author.\n [4]. Search by book title.\n [5]. Show number of books we have.\n [6]. Set password\n [7]. Edit the library\n [8]. Delete a book.\n [9]. Theme mode.\n [10]. Golden millionare game.\n [11]. MP3 QURA'AN.\n [12]. Exit\n\n");

    //printf("Your choice: ");      scanf("%d", &n);

    colour();

    return pos;
}

void check_files()
{
    char ch;

    FILE *ptr = fopen("books info.dtt", "r");
    FILE *temp = fopen("backup.datt", "r");

    if (ptr == NULL || temp == NULL) {
        fclose(temp);
        fclose(ptr);

        ptr = fopen("books info.dtt", "w");
        temp = fopen("backup.datt", "w");

        return;
    }

    fseek(ptr, 0, SEEK_END);
    fseek(temp, 0, SEEK_END);

    unsigned long size = (unsigned long)ftell(ptr);
    unsigned long size_temp = (unsigned long)ftell(temp);

    if ( (size == 0) && (size_temp == 0) ) {
        fclose(temp);
        fclose(ptr);
        return;
    }
    else if ( (size == 0) && (size_temp != 0) ) {
        freopen("books info.dtt", "w", ptr);
        fseek(ptr, 0, SEEK_END);
        rewind(temp);

        ch = fgetc(temp);

        while (!feof(temp)) {
            fputc(ch, ptr);
            ch = fgetc(temp);
        }
    }

    fclose(temp);
    fclose(ptr);

    return;
}

int main()
{
    //start();
    check_files();
    ShowConsoleCursor(0);
    //colour();
    //sndPlaySound(song, SND_ASYNC);
    //Sleep(3000);
    /*FSOUND_Init (44100, 32, 0);

   // load and play mp3
   handle=FSOUND_Sample_Load (0,"Saad Lamjarred & Zouhair Bahaoui - Lewjah Tani   2021   ÓÚÏ áãÌÑÏ æ ÒåíÑ ÈåÇæí -  áæÌå ÇáÊÇäí.mp3",0, 0, 0);
   FSOUND_PlaySound (0,handle);

   // wait until the users hits a key to end the app
   while (!_kbhit())
   {
   }

   // clean up
   FSOUND_Sample_Free (handle);
   FSOUND_Close();*/

    unsigned n,
             trials = 0,
             btrials = 3;
    int i = 0,
        re;

    FILE *ptr,
         *pw,
         *first;

    char ch,
         decide,
         de,
         de2,
         fi,
         pass_set [MAX],
         pass_set2[MAX],
         pass_in [MAX];     //used to store the password from the user

    first = fopen("d.dat", "r");
    fi = fgetc(first);
    if (fi == 'b') {
        goto start;
    }
    else {
        label:

            printf("\n\n\n\n\n\n                                 Enter the password: ");
            pw = fopen("a.rlb", "rb");
            fread (pass_set2, sizeof (pass_set2), 1, pw);

            pass_in[i] = getch();
            while ( pass_in[i] != '\r') {

                if( pass_in[i] == 27 ) {
                     system("cls");
                     exit(EXIT_SUCCESS);
                     }

                else if (pass_in[i] == '\b')
                {
                   if (i > 0) {
                        --i;
                        printf("\b");
                        printf(" ");
                        printf("\b");
                        pass_in[i] = getch();
                        /*if (i <= 0) {
                            pass_in[i] = getch();
                        }*/
                   } else if (i <= 0) {
                        pass_in[i] = getch();
                    }
                } else {
                    printf("*");
                    i++;
                    pass_in[i] = getch();
                  }
                //pass_in[i] = ch2;
                //printf("*");
                //i++;
            }
            pass_in[i] = '\0';
            i = 0;
            if(strcmp(pass_in, pass_set2) == 0){
                system("cls");
                printf("\n\n\n\n\n\n\n\n\n                                      CHECKING");
                for(i = 0; i <= 5; i++){
                    Sleep(20);
                    printf(".");
                }
                system("cls");
                printf("\n\n\n\n\n\n\n\n\n                                      WELCOME");
                for(i = 0; i <= 5; i++){
                    Sleep(20);
                    printf(".");
                }
                system("cls");
                goto start;  //line 111
            }
            else {
                fflush(stdin);
                printf("\n\n                      Invalid password.");
                trials++;
                printf("\n\n                      You have %u trials left.", btrials--);

                if (trials == 4) {
                    system("cls");
                    btrials = 3;
                    trials = 0;
                    for (int d = 30; d > -1; d--) {
                        printf("\n\n                      Retry in %d seconds.", d);
                        Sleep(1000);
                        system("cls");
                    }
                }

                label3:
                    printf("\n\n                      Press 't' to try again or 'e' to exit.\n\n");
                    de = getch();
                    //scanf("%c", &answer);
                    if ((de == 't') || (de == 'T')){
                        system("cls");
                        goto label;  //line 53
                    }

                    else if ( (de == 'e') || (de == 'E'))     { exit(0); }

                    else {
                        system("cls");
                        printf("\n\n                      Please, enter a valid value");
                        goto label3;  //line 93
                        }
                    }
    }

    start:

      n = menu();
      switch(n){

        case 1:

            re = add();
            if (re == 2) {
               goto start;
            }
            break;

       case 2:
           system("cls");
           ptr = fopen("books info.dtt", "r");

           printf("\n\n                     Here are all the books we have in the library.....\n\n\n");
           printf(" Total (%d) books are available:-\n\n", numofbooks(ptr));

           ptr = freopen("books info.dtt", "r", ptr);
           ch = fgetc(ptr);

           while (ch != EOF){
                printf("%c", ch);
                ch = fgetc(ptr);
           }

           label2:
                fflush(stdin);
                printf("\n\n  press 'm' to go to main menu or 'e' to exit. \n\n\n");
                decide = getch();
                //scanf("%c", &ans);
                if (decide == 'm' || decide == 'M'){
                    system("cls");
                    goto start;
                }
                else if(decide == 'e' || decide == 'E'){
                    system("cls");
                    printf("\n\n        See you soon");
                    for(i = 1; i <= 7; i++){
                        Sleep(200);
                        printf(".");
                    }
                    printf("\n\n\n\n");
                    exit(0);
                }
                else {
                    system("cls");
                    printf("\n\n  Please, enter a valid value.");
                    goto label2;    //line 164
                }

           break;

       case 3:
           system("cls");
        research:
           re = searchauthor(ptr);
           if (re == 1) {
                goto start;
           }

           else if (re == 2) {
                goto research;
           }

           break;

       case 4:
        system("cls");
      research2:
        re = searchtitle(ptr);
        if (re == 1) {
                goto start;
           }

           else if (re == 2) {
                goto research2;
           }
        break;

       case 5:
           system("cls");
           ptr = fopen("books info.dtt", "r");
           if (ptr == NULL)    { printf("Couldn't open the file....");     exit(1); }
           int numberofbooks = numofbooks(ptr);
           printf("\n\n     Total (%d) books are available in the library. ", numberofbooks);
           label4:
               printf("\n\n\n\nPress 'm' to go to main menu or 'e' to exit. ");
               de2 = getch();
               if(de2 == 'm' || de2 == 'M'){
                    system("cls");
                    goto start;
               }
               else if(de2 == 'e' || de2 == 'E'){
                    system("cls");
                    printf("GOODBYE");
                    for (i = 1; i <= 6; i++){
                        Sleep(200);
                        printf(".");
                    }
                    printf("\n\n\n");
                    exit(1);
               }
               else{
                printf("\n\nPlease, enter a valid value.\n");
                goto label4;    //line 200
               }
           i = 0;
           break;

       case 6:
           system("cls");

         retry:
           re = set_password(pass_set);

           if (re == 5) {
              system("cls");
              goto start;
              break;
           }
           else if (re == 1) {
              goto retry;
           }
           else {
              /* for (i=0; i < 100; i++){
                printf("%c", pass_set[i]);
               }
               i = 0;*/
               for (i = 0; i < 90; i++){
                pass_set2[i] = pass_set[i];
               }
              // i = 0;

               /*for (i=0; i < 100; i++){
                printf("%c", pass_set2[i]);
               }
               i = 0;*/


               //FILE *pw;
             label12:
               pw = fopen("a.rlb", "wb");
               if(pw == NULL) {
                    printf("Can't open the file. Try again.");
                    goto label12;
               }
               else{
                fwrite(pass_set2, sizeof(char), sizeof(pass_set2), pw);
               }
               fclose(pw);
               pw = freopen("a.rlb", "rb", pw);
               fgets(pass_set2, i, pw);
               /*for(j = 0; j < i; j++){
                printf("%c", pass_set2[j]);
               }*/
               fclose(pw);

               printf("\n   You will be asked to enter your new password again\n\n");
               for(i = 0; i <= 5; i++){
                    Sleep(500);
                    printf(".");
               }
               system("cls");
               main();
               //goto label;
               break;
           }

       case 7:
           system("cls");
      research3:
        re = edit(ptr);
        if (re == 1) {
                goto start;
           }

           else if (re == 2) {
                goto research3;
           }
           break;

       case 8:
            system("cls");
        del2:
            //fclose(ptr);
            re = del(ptr);
            if (re == 1) {
                goto del2;
            }

            else if (re == 2) {
                goto start;
            }
            break;

       case 9:
           system("cls");

         go:
           re = theme();

           if (re == 1) {
            goto go;
           }
           else if (re == 2) {
            goto start;
           }

           break;

       case 10:
           system("cls");
         again:
           re = game();
           if (re == 1) {
            goto again;
           }
           else if (re == 2) {
            goto start;
           }
           break;

       case 11:
           system("cls");
           re = quraan();

           if (re == 1) {
             //system("pause");
             system("cls");
             goto start;
           }
           else if (re == 2) {
             //system("pause");

             sndPlaySound(NULL, SND_ASYNC);

             system("cls");
             goto start;
           }

           break;

       case 12:
           system("cls");
           printf("\n\n\n\n\n\n\n\n\n                  GOODBYE");
           for (i = 1; i <= 6; i++){
              Sleep(100);
              printf(".");
           }
           printf("\n\n\n");
           break;
        }
}

int draw_quraan_box()
{
    unsigned i, xc = 5, yc = 20;

    gotoxy(20, 4);
    printf("%c", 201);

    for (i = 1; i < 39; i++) {
        printf("%c", 205);
    }
    printf("%c", 187);

    for (int l = 1; l < 4; l++) {
        gotoxy(yc, xc++);
        printf("%c", 186);
        for (i = 1; i < 39; i++) {
            printf("%c", 32);
        }
        printf("%c", 186);
    }

    gotoxy(20, 8);
    printf("%c", 200);
    for (i = 1; i < 39; i++) {
        printf("%c", 205);
    }
    printf("%c", 188);
}

int quraan_main_menu()
{
    system("color 07");

    char ch;
    int pos = 1;

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    do {

        SetConsoleTextAttribute(console, 15);

        gotoxy(21, 5);   printf(" Khalid Al-Jalil                     ");
        gotoxy(21, 6);   printf(" Yasser Al-Dossary                   ");
        gotoxy(21, 7);   printf(" Turn off the sound in the background");

        switch(pos){
        case 1:
            SetConsoleTextAttribute(console, 6);
            gotoxy(21, 5);   printf(" Khalid Al-Jalil                     ");
            break;

        case 2:
            SetConsoleTextAttribute(console, 6);
            gotoxy(21, 6);   printf(" Yasser Al-Dossary                   ");
            break;

        case 3:
            SetConsoleTextAttribute(console, 6);
            gotoxy(21, 7);   printf(" Turn off the sound in the background");
            break;
        }


        ch = getch();
        if (ch == -32) {
            ch = getch();
        }

        if (ch == 72) {
            pos--;

            if (pos == 0) {
                pos = 3;
            }

        }

        if (ch == 80) {
            pos++;

            if (pos == 4) {
                pos = 1;
            }
        }

    } while (ch != 13);


    return pos;
}

int quraan()
{
    draw_quraan_box();

    int pos = quraan_main_menu();

    colour();

    int cho, su, ma;

    if (pos == 3) {
        return 2;
    }

    if (pos == 1) {
        system("cls");

        printf("\n\n [1]. Yusuf\n [2]. Al-Kahf\n [3]. Ghafir\n [4]. Maryam\n\n   Your choice: ");
        scanf("%d", &su);

        if (su == 1) {
            system("cls");

            char *play = "C:\\Users\\M E T R O\\Desktop\\library book management\\Library book management\\Sounds\\Khalid Al-Jalil\\Yusuf.wav";
            sndPlaySound(play, SND_ASYNC);

            printf("\n\n\n      Now playing: Yusuf\n\n  ");
        }
        else if (su == 2) {
            system("cls");

            char *play = "C:\\Users\\M E T R O\\Desktop\\library book management\\Library book management\\Sounds\\Khalid Al-Jalil\\Al-Kahf.wav";
            sndPlaySound(play, SND_ASYNC);

            printf("\n\n\n      Now playing: Al-Kahf\n\n  ");
        }
        else if (su == 3) {
            system("cls");

            char *play = "C:\\Users\\M E T R O\\Desktop\\library book management\\Library book management\\Sounds\\Khalid Al-Jalil\\Ghafir.wav";
            sndPlaySound(play, SND_ASYNC);

            printf("\n\n\n      Now playing: Ghafir\n\n  ");
        }
        else if (su == 4) {
            system("cls");

            char *play = "C:\\Users\\M E T R O\\Desktop\\library book management\\Library book management\\Sounds\\Khalid Al-Jalil\\Maryam.wav";
            sndPlaySound(play, SND_ASYNC);

            printf("\n\n\n      Now playing: Maryam\n\n  ");
        }
    }
    else if (pos == 2) {
        system("cls");
        printf("\n\n  [1]. Ar-Rahman\n\n    Your choice: ");
        scanf("%d", &su);

        if (su == 1) {
            system("cls");

            char *play = "C:\\Users\\M E T R O\\Desktop\\library book management\\Library book management\\Sounds\\Yasser Al-Dossary\\Ar-Rahman.wav";
            sndPlaySound(play, SND_ASYNC);
            printf("\n\n\n      Now playing: Ar-Rahman - Yasser Al-Dossary\n\n  ");
        }
    }

    printf("\n\n  [1]. Go to main menu while playing Qura'an.\n\n  [2]. Turn off and go to main menu.\n\n   Your choice: ");
    scanf("%d", &ma);

    if (ma == 1) {
        return 1;       //continue playing
    }
    else if (ma == 2) {
        return 2;       //turn off
    }
}

int add()
{
    system("cls");

    int ans = 1;
    char line[100] = "";
    int p, re;
    char ch;

    //printf("%d", p);
    FILE *ptr = fopen("books info.dtt", "a");
    p = readbooks();
    if ( ! ptr) {
        perror ( "books info.dtt");
        return 0;
    }
    while(ans == 1) {

        fflush(stdin);
        printf("\nEnter The name of the book: ");
        fgets(info[p].bname, 150, stdin);
        info[p].bname[strcspn ( info[p].bname, "\n")] = 0;
        fprintf(ptr, "Book name: %s\n", info[p].bname);
        fflush(stdin);

        printf("Enter The author of this book: ");
        fgets(info[p].bauthor, 100, stdin);
        info[p].bauthor[strcspn ( info[p].bauthor, "\n")] = 0;
        fprintf(ptr, "Book author: %s\n", info[p].bauthor);

        printf("Enter The number of pages of this book: ");
        fgets ( line, 100, stdin);
        sscanf(line, "%u", &info[p].bpages);
        fprintf(ptr, "Number of pages: %u\n", info[p].bpages);

        printf("What is the price of the book (in EGP)? ");
        fgets ( line, 100, stdin);
        sscanf( line, "%u", &info[p].price);
        fprintf(ptr, "Price (in EGP): %u\n", info[p].price);

        printf("Number of books available: ");
        fgets ( line, 100, stdin);
        sscanf( line, "%u", &info[p].numavail);
        fprintf(ptr, "Number of books available: %u", info[p].numavail);

        /*printf("\nAdd an abstract:-\n   ");
        fgets ( line, 600, stdin);
        sscanf( line, "%s", &info[p].abstract);
        fprintf(ptr, "\nAbstract: %s", info[p].abstract);*/
        ++p;

        fprintf(ptr, "\n---------------------------------------------------------\n");
        printf("\nBook information saved successfully....\n");

      label:
        printf("\nEnter    (1) to add another book\nor       (2) for main menu. ");
        fgets ( line, 100, stdin);
        sscanf( line, "%d", &ans);
        if (ans == 2)       {
            system("cls");
            fclose(ptr);
            return 2;
        }
        else if (ans == 1) {
            continue;
        }
        else {
            printf("\n Please enter a valid value.");
            goto label;
        }
    }

    return p;
}

int theme()
{
    int choice;
    FILE *th;

    printf("\n\n  [1]. Dark mode\n  [2]. Light mode\n\n   Your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        system("color 07");

        th = fopen("themes.thm", "w");
        fprintf(th, "d");
        fclose(th);
    }
    else if (choice == 2) {
        system("color F0");

        th = fopen("themes.thm", "w");
        fprintf(th, "l");
        fclose(th);
    }

    printf("\n\n  Press any key to continue. ");
    getch();
    system("cls");

    return 2;
}


int numofbooks(FILE *ptr)
{
    int ch;
    int num = 0, keep;
    ch = fgetc(ptr);
    while(ch != EOF){
       if(ch == ':'){
            num++;
        }
    ch = fgetc(ptr);
    }

    return num / 5;
}

int searchauthor(FILE *ptr)
{
    int save;
    char de;
    char in_name[30];
    int flag = 1;

    save = readbooks();
    ptr = fopen("books info.dtt", "r");
    fflush(stdin);
    printf("\n Enter the name of the author: ");
    gets(in_name);
    printf("-------------------------------------------------");

    for(int i = 0; i < save; i++){
        if(strcasestr(info[i].bauthor, in_name) != NULL){
            printf("\n Book name: %s\n Book author: %s\n Price: %u\n Number of books available: %u\n Number of pages: %u\n-------------------------------------------------", info[i].bname, info[i].bauthor, info[i].price, info[i].numavail, info[i].bpages);
            flag = 0;
        }
    }

    if (flag == 1){
        printf("\n Not found.\n Do you want to try another search [Y/N]? ");
        scanf("%c", &de);
        if(de == 'y' || de == 'Y'){
            system("cls");
            in_name[MAX] = reset(in_name);
            fclose(ptr);
            return 2;
        }
        else if(de == 'n' || de == 'N'){
            printf("\n You will be redirected to main menu");
            for(int k = 1; k <= 5; k++){
                Sleep(300);
                printf(".");
            }
            system("cls");
            return 1;
        }
    }


    printf("\n\n Do you want to try another search [Y/N]? ");
    de = getch();

    if (de == 'y' || de == 'Y') {
        system("cls");
        in_name[MAX] = reset(in_name);
        return 2;       //return 2 to case 3 to search again
    }
    else if (de == 'n' || de == 'N') {
        system("cls");
        printf("\n You will be redirected to main menu");
        for(int k = 1; k <= 5; k++){
            Sleep(300);
            printf(".");
        }
        system("cls");
        return 1;
    }

  /*back:
    printf("\n\n");
    printf("\n      ---------------------");
    printf("\n     |Press 'q' to go back | \n");
    printf("      ---------------------");
    de = getch();
    if (de == 'q' || de == 'Q') {
        system("cls");
        return 1;
    }
    else {
        printf("\n     Please, enter a valid value.");
        goto back;
    }*/

    printf("\n\n");
}


int searchtitle(FILE *ptr)
{
    int save;
    char de;
    char in_title[40];
    int flag = 1;

    save = readbooks();
    ptr = fopen("books info.dtt", "r");
    fflush(stdin);
    printf("\n Enter the name of the book: ");
    gets(in_title);
    printf("-------------------------------------------------");

    for(int i = 0; i < save; i++){
        if(strcasestr(info[i].bname, in_title) != 0){
            printf("\n Book name: %s\n Books author: %s\n Price:  %u\n Number of books available: %u\n Number of pages: %u\n-------------------------------------------------", info[i].bname, info[i].bauthor, info[i].price, info[i].numavail, info[i].bpages);
            flag = 0;
        }
    }

    if (flag == 1) {
        printf("\n Not found.\n Do you want to try another search [Y/N]? ");
        scanf("%c", &de);
        if(de == 'y' || de == 'Y') {
            system("cls");
            in_title[40] = reset(in_title);
            fclose(ptr);
            return 2;
        }
        else if(de == 'n' || de == 'N') {
            printf("\n You will be redirected to main menu");
            for(int k = 1; k <= 5; k++){
                Sleep(300);
                printf(".");
            }
            system("cls");
            return 1;
        }
    }

    printf("\n\n Do you want to try another search [Y/N]? ");
    scanf("%c", &de);

    if (de == 'y' || de == 'Y') {
        system("cls");
        in_title[MAX] = reset(in_title);
        return 2;       //return 2 to case 4 to search title again
    }
    else if (de == 'n' || de == 'N') {
        system("cls");
        printf("\n You will be redirected to main menu");
        for(int k = 1; k <= 5; k++){
            Sleep(300);
            printf(".");
        }
        system("cls");
        return 1;
    }

    printf("\n\n");
}


int set_password(char pass_set[])
{
    int chh;

    printf("\n\n [1]. Edit password\n [2]. Delete password");
    printf("\n\n Your choice: ");
    scanf("%d", &chh);

    if (chh == 2) {
        FILE *first = fopen("d.dat", "w");
        fprintf(first, "b");
        fclose(first);
        printf("\n Password is deleted successfuly");
        for (int i = 1; i < 5; i++) {
            printf(".");
            Sleep(500);
        }
        return 5;
    }
    else {
        system("cls");

        char pass_set2[MAX],
             ch,
             //ch2,
             pass_set3[MAX],
             pass_set1[MAX];

        int i = 0,
            i2 = 0,
            len;

        printf("\n\n    Please, enter a new password:  ");

        pass_set[i] = getch();

        while ( pass_set[i] != '\r') {

            if( pass_set[i] == 27 ) {
                system("cls");
                return 5;
            }

            else if (pass_set[i] == '\b')
            {
                if (i > 0) {
                    --i;
                    printf("\b");
                    printf(" ");
                    printf("\b");
                    pass_set[i] = getch();
                        /*if (i <= 0) {
                            pass_in[i] = getch();
                        }*/
                } else if (i <= 0) {
                    pass_set[i] = getch();
                  }
                } else {
                    printf("*");
                    i++;
                    pass_set[i] = getch();
                  }
            }

        pass_set[i] = '\0';     //password input ends here

        len = strlen(pass_set);

        if (len < 6) {

            system("cls");
            printf("\n     Password is too short. Enter at least 7 characters");

            for (int count = 1; count <= 5; count ++) {
                printf(".");
                Sleep(300);
            }

            system("cls");

            pass_set[MAX] = reset(pass_set);

            return 1;
        }

        i = 0;
        printf("\n\n    Please, confirm your password: ");

        pass_set3[i] = getch();
        while ( pass_set3[i] != '\r') {

            if ( pass_set3[i] == 27 ) {
                system("cls");
                exit(EXIT_SUCCESS);
            }

            else if (pass_set3[i] == '\b')
            {
                if (i > 0) {
                    --i;
                    printf("\b");
                    printf(" ");
                    printf("\b");
                    pass_set3[i] = getch();
                        /*if (i <= 0) {
                            pass_in[i] = getch();
                        }*/
                } else if (i <= 0) {
                    pass_set3[i] = getch();
                  }
                } else {
                    printf("*");
                    i++;
                    pass_set3[i] = getch();
                  }
            }

        pass_set3[i] = '\0';
        system("cls");                  //password confirmation ends here

        if (strcmp(pass_set, pass_set3)  != 0) {
            system("cls");
            printf("\n    Passwords don't match. Please, try again.");
            pass_set[MAX] = reset(pass_set);
            pass_set3[MAX] = reset(pass_set3);
            set_password(pass_set);
        }
        else {
            printf("\n\n    Your new passord is: ");
            for(int j2 = 0; j2 < i; j2++){
                printf("%c",  pass_set[j2]);
            }
                printf("\n    Please, memorize it.\n\n\n\n");
        }

           FILE *first = fopen("d.dat", "w");
           fprintf(first, "a");
           fclose(first);
           return pass_set;
           savepassword(pass_set);
        }
}

char * reset(char pass_reset[])
{
    memset(pass_reset, 0, sizeof(pass_reset)/sizeof(pass_reset[0]));

    return pass_reset;
}

int savepassword(char pass_save[])         //pass_save = pass_set3 from main
{

       return pass_save;
}

void draw_edit_box()
{
    unsigned i, xc = 5, yc = 55;

    gotoxy(55, 4);
    printf("%c", 201);

    for (i = 1; i < 38; i++) {
        printf("%c", 205);
    }
    printf("%c", 187);

    for (int l = 1; l < 8; l++) {
        gotoxy(yc, xc++);
        printf("%c", 186);
        for (i = 1; i < 38; i++) {
            printf("%c", 32);
        }
        printf("%c", 186);
    }

    gotoxy(55, 11);
    printf("%c", 200);
    for (i = 1; i < 38; i++) {
        printf("%c", 205);
    }
    printf("%c", 188);
}

draw_edit_menu()
{
    system("color 07");

    char ch;
    int pos = 1;

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    do {

        SetConsoleTextAttribute(console, 15);

        gotoxy(56, 5);   printf(" Edit the name of the book ");
        gotoxy(56, 6);   printf(" Edit the name of the author ");
        gotoxy(56, 7);   printf(" Edit price ");
        gotoxy(56, 8);   printf(" Edit the number of pages ");
        gotoxy(56, 9);   printf(" Edit the number of avialable books ");
        gotoxy(56, 10);  printf(" Edit all ");

        switch(pos){
        case 1:
            SetConsoleTextAttribute(console, 6);
            gotoxy(56, 5);   printf("  Edit the name of the book ");
            break;

        case 2:
            SetConsoleTextAttribute(console, 6);
            gotoxy(56, 6);   printf("  Edit the name of the author ");
            break;

        case 3:
            SetConsoleTextAttribute(console, 6);
            gotoxy(56, 7);   printf("  Edit price ");
            break;

        case 4:
            SetConsoleTextAttribute(console, 6);
            gotoxy(56, 8);   printf("  Edit the number of pages ");
            break;

        case 5:
            SetConsoleTextAttribute(console, 6);
            gotoxy(56, 9);   printf("  Edit the number of avialable books ");
            break;

        case 6:
            SetConsoleTextAttribute(console, 6);
            gotoxy(56, 10);   printf("  Edit all ");
            break;
        }


        ch = getch();
        if (ch == -32) {
            ch = getch();
        }

        if (ch == 72) {
            pos--;

            if (pos == 0) {
                pos = 6;
            }

        }

        if (ch == 80) {
            pos++;

            if (pos == 7) {
                pos = 1;
            }
        }

    } while (ch != 13);


    return pos;
}

int edit(FILE *ptr)
{
    system("cls");

    ptr = fopen("books info.dtt", "r");

    char edbook[40],
         de,
         ch,
         newname[40],
         newauthor[30];
    int save,
        flag = 1,
        i,
        bookindex,
        newprice,
        newnumavail,
        check,
        newpages,
        pos;

    save = readbooks();
    fflush(stdin);

    //printf("\n      BE AWARE THAT IF YOU DO NOT COMPLETE EDITING THE BOOK YOU\n      SEARCHED, ALL THE BOOKS SAVED WILL BE DELETED...!");
    printf("\n\n Enter The name of the book to edit: ");
    gets(edbook);

    for (i = 0; i < save; i++){
        if(strcasestr(info[i].bname, edbook) != NULL){
            printf("\n Here is the book you want to edit: ");
            printf("\n-------------------------------------------------");
            printf("\n Book name: %s\n Books author: %s\n Price:  %u\n Number of books available: %u\n Number of pages: %u\n-------------------------------------------------", info[i].bname, info[i].bauthor, info[i].price, info[i].numavail, info[i].bpages);
            //fprintf(temp, " Book name: %s\n Books author: %s\n Price:  %u\n Number of books available: %u\n Number of pages: %u", info[i].bname, info[i].bauthor, info[i].price, info[i].numavail, info[i].bpages);
            flag = 0;
            //printf("%d", i);
            bookindex = i;
        }
    }
    //fclose(ptr);

    if (flag == 1) {
        printf("\n Not found.\n Do you want to try another search [Y/N]? ");
        scanf("%c", &de);
        if(de == 'y' || de == 'Y') {
            system("cls");
            edbook[40] = reset(edbook);
            fclose(ptr);
            return 2;
        }
        else if (de == 'n' || de == 'N') {
            printf("\n You will be redirected to main menu");
            for(int k = 1; k <= 5; k++){
                Sleep(300);
                printf(".");
            }
            system("cls");
            return 1;
        }
    }
    printf("\n\n");

    FILE *temp = fopen("backup.datt", "w");
    freopen("backup.datt", "a", temp);
    char chb;

    chb = fgetc(ptr);
    while (!feof(ptr)) {
        fputc(chb, temp);
        chb = fgetc(ptr);
    }
    fclose(temp);

    draw_edit_box();
    pos = draw_edit_menu();
    system("cls");

    freopen("books info.dtt", "w", ptr);

    switch(pos) {

        case 1:

            //system("cls");

            //freopen("books info.dtt", "w", ptr);
            printf("\n Enter the new name of the book: ");
            gets(info[bookindex].bname);
            fprintf(ptr, " Book name: %s", info[bookindex].bname);

            int k = bookindex;

            fprintf(ptr, "\n Books author: %s\n Price:  %u\n Number of books available: %u\n Number of pages: %u\n-------------------------------------------------\n", info[k].bauthor, info[k].price, info[k].numavail, info[k].bpages);

            for (i = 0; i < save; i++) {
                if (i == bookindex) {
                    continue;
                }
                else {
                    fprintf(ptr, " Book name: %s\n Book author: %s\n Number of pages: %u\n Price: %u\n Number of books available: %u\n-------------------------------------------------\n", info[i].bname, info[i].bauthor, info[i].bpages, info[i].price, info[i].numavail);
                }
            }

            break;

        case 2:

            printf("\n Enter the new author of the book: ");
            gets(info[bookindex].bauthor);
            //fprintf(ptr, " Book author: %s", info[bookindex].bauthor);

           //int l = bookindex;

            fprintf(ptr, " Book name: %s\n Book author: %s\n Number of pages: %u\n Price: %u\n Number of books available: %u\n-------------------------------------------------\n", info[bookindex].bname, info[bookindex].bauthor, info[bookindex].bpages, info[bookindex].price, info[bookindex].numavail);

            for (i = 0; i < save; i++) {

                if (i == bookindex) {
                    continue;
                }
                else {
                    fprintf(ptr, " Book name: %s\n Book author: %s\n Number of pages: %u\n Price: %u\n Number of books available: %u\n-------------------------------------------------\n", info[i].bname, info[i].bauthor, info[i].bpages, info[i].price, info[i].numavail);
                }
            }

            break;

        case 3:

            printf("\n Enter the new price: ");
            scanf("%u", &info[bookindex].price);
            //fprintf(ptr, "Price: %u\n", info[bookindex].price);

            fprintf(ptr, " Book name: %s\n Book author: %s\n Number of pages: %u\n Price: %u\n Number of books available: %u\n-------------------------------------------------\n", info[bookindex].bname, info[bookindex].bauthor, info[bookindex].bpages, info[bookindex].price, info[bookindex].numavail);

            for (i = 0; i < save; i++) {

                if (i == bookindex) {
                    continue;
                }
                else {
                    fprintf(ptr, " Book name: %s\n Book author: %s\n Number of pages: %u\n Price: %u\n Number of books available: %u\n-------------------------------------------------\n", info[i].bname, info[i].bauthor, info[i].bpages, info[i].price, info[i].numavail);
                }
            }

            break;

        case 4:

            printf("\n Enter the new number of pages: ");
            scanf("%u", &info[bookindex].bpages);
            //fprintf(ptr, "Number of pages: %u\n", info[bookindex].bpages);

            fprintf(ptr, " Book name: %s\n Book author: %s\n Number of pages: %u\n Price: %u\n Number of books available: %u\n-------------------------------------------------\n", info[bookindex].bname, info[bookindex].bauthor, info[bookindex].bpages, info[bookindex].price, info[bookindex].numavail);

            for (i = 0; i < save; i++) {

                if (i == bookindex) {
                    continue;
                }
                else {
                    fprintf(ptr, " Book name: %s\n Book author: %s\n Number of pages: %u\n Price: %u\n Number of books available: %u\n-------------------------------------------------\n", info[i].bname, info[i].bauthor, info[i].bpages, info[i].price, info[i].numavail);
                }
            }

            break;

        case 5:

            printf("\n Enter the number of the available books: ");
            scanf("%u", &info[bookindex].numavail);
           // fprintf(ptr, "Number of books available: %u", info[bookindex].numavail);
           // fprintf(ptr, "\n---------------------------------------------------------\n");

            fprintf(ptr, " Book name: %s\n Book author: %s\n Number of pages: %u\n Price: %u\n Number of books available: %u\n-------------------------------------------------\n", info[bookindex].bname, info[bookindex].bauthor, info[bookindex].bpages, info[bookindex].price, info[bookindex].numavail);

            for (i = 0; i < save; i++) {

                if (i == bookindex) {
                    continue;
                }
                else {
                    fprintf(ptr, " Book name: %s\n Book author: %s\n Number of pages: %u\n Price: %u\n Number of books available: %u\n-------------------------------------------------\n", info[i].bname, info[i].bauthor, info[i].bpages, info[i].price, info[i].numavail);
                }
            }

            break;

        case 6:

            printf("\n Enter the new name of the book: ");
            gets(info[bookindex].bname);
            fprintf(ptr, "Book name: %s", info[bookindex].bname);

            printf("\n Enter the new author of the book: ");
            gets(info[bookindex].bauthor);
            fprintf(ptr, "\nBook author: %s\n", info[bookindex].bauthor);

            printf("\n Enter the new number of pages: ");
            scanf("%u", &info[bookindex].bpages);
            fprintf(ptr, "Number of pages: %u\n", info[bookindex].bpages);

            printf("\n Enter the new price: ");
            scanf("%u", &info[bookindex].price);
            fprintf(ptr, "Price: %u\n", info[bookindex].price);

            printf("\n Enter the number of the available books: ");
            scanf("%u", &info[bookindex].numavail);
            fprintf(ptr, "Number of books available: %u", info[bookindex].numavail);
            fprintf(ptr, "\n---------------------------------------------------------\n");

            freopen("books info.dtt", "a", ptr);
            for (i = 0; i < save; i++) {
                if (i == bookindex) {
                    continue;
                }
                else {
                    fprintf(ptr, "Book name: %s\nBook author: %s\nNumber of pages: %u\nPrice: %u\nNumber of books available: %u\n---------------------------------------------------------\n", info[i].bname, info[i].bauthor, info[i].bpages, info[i].price, info[i].numavail);
                }
            }

    }

    fclose(ptr);

  retry:
    printf("\n Do you want to edit another book [Y/N]? ");
    de = getch();

    if (de == 'y' || de == 'Y') {
        system("cls");
        edbook[40] = reset(edbook);
        return 2;
    }
    else if (de == 'n' || de == 'N') {
        system("cls");
        printf("\n You will be redirected to main menu");
        for (int j = 1; j < 4; j++) {
            Sleep(200);
            printf(".");
        }
        system("cls");
        return 1;
    }
    else {
        printf("\n Please enter a valid value.\n");
        goto retry;
    }
}

int del(FILE *ptr)
{
    char delbook[41],
         de,
         de1;
    unsigned save,
        bookindex,
        flag = 1;
    FILE *temp;

    save = readbooks();
    ptr = fopen("books info.dtt", "r");

    fflush(stdin);

    printf("\n Enter the name of the book to delete: ");
    gets(delbook);

    for (int i = 0; i < save; i++) {
        if (strcasestr(info[i].bname, delbook) != NULL) {
            printf("\n Here is the book you want to delete\n ---------------------------------------------------------");
            printf("\n Book name: %s\n Books author: %s\n Price:  %u\n Number of books available: %u\n Number of pages: %u\n -------------------------------------------------", info[i].bname, info[i].bauthor, info[i].price, info[i].numavail, info[i].bpages);
            bookindex = i;
            flag = 0;
        }
    }

    if (flag == 0) {
        printf("\n Are you sure you want to delete this book (Press (y) for yes, (n) for no)? ");
        de1 = getch();

        if (de1 == 'y' || de1 == 'Y') {
            fclose(ptr);
            ptr = fopen("books info.dtt", "w");
            ptr = freopen("books info.dtt", "a", ptr);
            for (int cpy = 0; cpy < save; cpy++) {
                if (cpy == bookindex) {
                    continue;
                }
                else {
                    fprintf(ptr, "Book name: %s\nBook author: %s\nNumber of pages: %u\nPrice: %u\nNumber of books available: %u\n---------------------------------------------------------\n", info[cpy].bname, info[cpy].bauthor, info[cpy].bpages, info[cpy].price, info[cpy].numavail);
                }

            }

            fclose(ptr);

            printf("\n\n Book deleted successfully!\n");
        }
    }


    else if (flag == 1) {
        printf(" Not found.");
      retry1:
        printf("\n Do you want to try another search [Y/N]? ");
        de1 = getch();
        if (de1 == 'Y' || de1 == 'y') {
            system("cls");
            delbook[41] = reset(delbook);
            return 1;
        }
        else if (de1 == 'n' || de1 == 'N') {
            system("cls");
            return 2;
        }

        else {
            printf("\n Please, enter a valid value.");
            system("cls");
            goto retry1;  //line 1119
        }
    }

  retry:
    printf("\n\n Do you want to delete another book [Y/N]? ");
    scanf("%c", &de);

    if (de == 'y' || de == 'Y') {
        system("cls");
        return 1;
    }

    else if (de == 'n' || de == 'N') {
        system("cls");
        return 2;
    }

    else {
        printf("\n Please, enter a valid value.");
        system("cls");
        goto retry;  //line 1119
    }
}


int game()
{
    char *song = "C:\\Users\\M E T R O\\Desktop\\library book management\\Library book management\\Sounds\\golden millionaire.wav";
    sndPlaySound(song, SND_ASYNC);
    //Sleep(12000);
    //sndPlaySound(NULL, SND_ASYNC);

    startgame();
    //system("color 07");

    char q[1000],
         answers_cap[20] = {'C', 'A', 'A', 'B', 'C', 'D', 'B', 'A', 'B', 'D', 'A', 'D', 'C', 'A'},
         answers_cap2[20]= {'D', 'B', 'C', 'A', 'A', 'C', 'B', 'D', 'C', 'B', 'A', 'A', 'D', 'A'},
         ch,
         ans,
         ex,
         de,
         ranch;

    unsigned crr = 0,
             wrng = 0,
             i = 0,
             score = 0;

    FILE *game;
    game = fopen("game.dat", "r");

    FILE *randomf,
         *game2;

    game2 = fopen("game2.dat", "r");
    randomf = fopen("ranq.dar", "r");

    if (game == NULL) {
        perror("game.dat");
    }

    if (randomf == NULL) {
        perror("ranq.dar");
    }

    if (game2 == NULL) {
        perror("game2.dat");
    }

    ranch = fgetc(randomf);
    fclose(randomf);

    if (ranch == 'a') {

        fopen("ranq.dar", "w");
        fprintf(randomf, "b");
        fclose(randomf);

        printf("\n [Tip: press (esc) to exit the game...]");

       cont:
        printf("\n\n");

        fgets(q, 120, game);
        printf("    %s", q);
        printf("\n");
        fgets(q, 120, game);
        printf("    %s", q);
        fgets(q, 120, game);
        printf("    %s", q);

        fflush(stdin);

        printf("\n\n      ANSWER: ");
        ans = getche();
        Sleep(300);
        ans = toupper(ans);

        if (ans == answers_cap[i]) {
            crr++;
            i++;
        }
        else {
            wrng++;
            i++;
        }

        if (ans == 27) {
            system("cls");
            printf("\n\n You have scored %d correct answers and %d wrong answers.\n", crr, --wrng);
            printf("\n\n Press any key to continue.");

            ex = getch();
            system("cls");

            return 2;       //2 to get back to main menu
        }

        while (!feof(game)) {
            system("cls");
            goto cont;
        }
        Sleep(12000);
    sndPlaySound(NULL, SND_ASYNC);

        Sleep(500);
        system("cls");
        printf("\n\n\n CHECKING");
        for (int l = 1; l < 5; l++) {
            Sleep(300);
            printf(".");
        }

        system("cls");
        fclose(game);

        printf("\n\n You have scored %d correct answers and %d wrong answers.\n", crr, wrng);

       re:
        printf("\n\n Press 'a' to play again or 'm' for main menu\n");
        de = getch();

        if (de == 'a') {
            system("cls");
            return 1;
        }
        else if (de == 'm') {
            system("cls");
            return 2;
        }
        else {
            system("cls");
            printf("\n Enter a valid value.\n\n");
            goto re;
        }
    }
    else if (ranch == 'b') {

        fopen("ranq.dar", "w");
        fprintf(randomf, "a");
        fclose(randomf);

        printf("\n\n [Tip: press (esc) to exit the game...]");

       cont2:
        printf("\n\n");

        fgets(q, 120, game2);
        printf("    %s", q);
        printf("\n");
        fgets(q, 120, game2);
        printf("    %s", q);
        fgets(q, 120, game2);
        printf("    %s", q);

        fflush(stdin);

        printf("\n\n      ANSWER: ");
        ans = getche();
        Sleep(300);
        ans = toupper(ans);

        if (ans == answers_cap2[i]) {
            crr++;
            i++;
        }
        else {
            wrng++;
            i++;
        }

        if (ans == 27) {
            system("cls");
            printf("\n\n You have scored %d correct answers and %d wrong answers.\n", crr, --wrng);
            printf("\n\n Press any key to continue.");

            ex = getch();
            system("cls");

            return 2;       //2 to get back to main menu
        }

        while (!feof(game2)) {
            system("cls");
            goto cont2;
        }

        Sleep(500);
        system("cls");
        printf("\n\n\n CHECKING");
        for (int l = 1; l < 5; l++) {
            Sleep(300);
            printf(".");
        }

        system("cls");

        fclose(game2);
        printf("\n\n You have scored %d correct answers and %d wrong answers.\n", crr, wrng);

       re2:
        printf("\n\n Press 'a' to play again or 'm' for main menu\n");
        de = getch();
        de = toupper(de);

        if (de == 'A') {
            system("cls");
            return 1;
        }
        else if (de == 'M') {
            system("cls");
            return 2;
        }
        else {
            system("cls");
            printf("\n Enter a valid value.\n\n");
            goto re2;
        }
    }
}

