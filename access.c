#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

void login(){

    printf("<div class=\"wave\">\
                <h1 class=\"label\">Login</h1><br>\
                <form action=\"http://localhost/cgi-bin/access.cgi\" method=\"get\">\
                    <input type=\"text\" placeholder=\"Username\" name=\"username\" class=\"entry1\"><br>\
                    <input type=\"password\" placeholder=\"Password\" name=\"password\" class=\"entry2\"><br>\
                    <input type=\"submit\" value=\"Log in\" class=\"log\"><br>\
                </form>\
                <form action=\"http://localhost/cgi-bin/access.cgi\" method=\"get\">\
                    <button class=\"pseudo-link\" name=\"create\" >Don't have an account?</button>\
                </form>\
            </div>\
    ");

}

void startSession(){

    printf("<form action=\"http://localhost/cgi-bin/access.cgi \" method=\"get\">\
                <button class=\"open-session\" name=\"start\">Click here to continue</button>\
            </form>\
    ");

}



void loadcss(){

    //le fichier css se trouve à l'exterieur du serveur
    FILE* file=fopen("/home/iantso/site-Manager/login.css","r");

    char tmp[256];

    printf("<style>");

    for(int i=0;fgets(tmp,sizeof(tmp),file);i++){
        printf("%s\n",tmp);
    }

    printf("</style>");

    fclose(file);
}

bool verify(char usr[],char passwd[]){

    FILE* file=fopen("/home/iantso/C/access.txt","r");

    char tmp[256];
    char entry1[250];
    char entry2[250];

    for(int i=0;fgets(tmp,sizeof(tmp),file);i++){
        sscanf(tmp,"%[^ ] %[^ ] ",entry1,entry2);

        if (strcmp(usr,entry1)==0 && strcmp(passwd,entry2)==0){
            return true;
        }

    }
    return false;

    fclose(file);
}
void createAccount(){

    printf("<div class=\"sign-up\">\
                <form action=\"http://localhost/cgi-bin/access.cgi\" method=\"get\">\
                    <p>Create account</p>\
                    <input type=\"text\" placeholder=\"username\" name=\"usr\" class=\"entry1\"><br>\
                    <input type=\"password\" placeholder=\"password\" name=\"pwd\" class=\"entry1\"><br>\
                    <input type=\"text\" placeholder=\"e-mail\" name=\"usrid\" class=\"entry2\"><br>\
                    <input type=\"submit\" value=\"Sign up\" class=\"log\"><br>\
                </form<\
            </div>\
    ");
}

void displayBtn(int len){
    int nbrBtn=ceil(len/10.0);
		    printf("<form action=\"http://localhost/cgi-bin/access.cgi\" method=\"get\" style=\"margin-left:300px;\">");
		    for(int i=0;i<nbrBtn;i++){
			    printf("<button name=\"btn\" value=\"%d\">%d</button>",i+1,i+1);
		    }
		    printf("</form>");
}
int getlen(){
        int len=0;
        char tmp[256];
        char ip[256];
        FILE* file=fopen("/var/log/apache2/access.log.1","r");
        FILE* file1=fopen("/home/iantso/data.txt","w");

        for(int i=0;fgets(tmp,sizeof(tmp),file);i++){
            sscanf(tmp,"%[^ ] - - [%*[^ ] +0300] \"%*[^\"]\" %*[^ ] %*[^ ] \"%*[^\"]\" ",ip);
            if(strcmp(ip,"127.0.0.1")==0){
                fprintf(file1,"%s",tmp);
                len++;
            }
        }
        fclose(file1);
        fclose(file);
        return len;
}

int main(){
    printf("content-type:text/html\n\n");
    puts("<html><head><title>Access</title></head>");
    loadcss();
    puts("<body style=\"display:flex;justify-content:center;align-items:center\">");
    
    char* data=getenv("QUERY_STRING");
    char entry1[256];
    char value1[256];
    char entry2[256];
    char value2[256];
    char entry3[256];
    char value3[256];


        char tmp[200];
        char ip[200];
        char date[200];
        char url[200];

        int len=getlen();
        int cpt=1;

    if (data!=NULL){
        sscanf(data,"%[^=]=%[^&]&%[^=]=%[^&]&%[^=]=%s",entry1,value1,entry2,value2,entry3,value3);
        if(strcmp(entry1,"btn")==0){

        FILE* fichier=fopen("/home/iantso/data.txt","r");
        puts("<div style=\"display-flex;justify-content:center;align-items:center;\">");

        displayBtn(len);

        puts("<table style=\"border:10px solid black;display:flex;justify-content:center;\">");
        puts("<tr><td class=\"primary\">Adresse ip</td><td class=\"primary\">Date de visite</td><td class=\"primary\">url</td></tr>");
        while(fgets(tmp,200,fichier)){
            sscanf(tmp,"%[^ ] - - [%[^ ] +0300] \"%*[^\"]\" %*[^ ] %*[^ ] \"%[^\"]\" ",ip,date,url);
            int c=atoi(value1);
            if (cpt>((c*10)-10) && cpt<((c*10)+1)){
                printf("<tr><td>%s</Std><td>%s</td><td>%s</td></tr>",ip,date,url);
            }
            cpt++;

        }
        puts("</table>");
        puts("</div>");
        fclose(fichier);

        }
        else if(strcmp(entry1,"username")==0 && strcmp(entry2,"password")==0){
            bool status=verify(value1,value2);

            if(status){
                printf("<h1 class=\"centered-label\">Login successfully!</h1>");
                displayBtn(len);
            }
            else{
                printf("<h1 class=\"centered-label\">Login failed!</h1>");
                login();
            }

        }

        else if(strcmp(entry1,"create")==0){
            createAccount();
        }
         else if((strcmp(entry1,"usr")==0 && strcmp(entry2,"pwd")==0) && strcmp(entry3,"usrid")==0){
            FILE* file3=fopen("/home/iantso/C/access.txt","a");

            if (strstr(value3,"gmail.com")){
                fprintf(file3,"%s %s %s\n",value1,value2,value3);
                printf("<h1>Sign up successfully,try login now</h1>");
                login();
            }
            else{
                printf("<h1>Try again</h1>");
                createAccount();
            }
            fclose(file3);

        }
        else{
            login();
        }
    }
    printf("</body></html>");
    return 0;
}
