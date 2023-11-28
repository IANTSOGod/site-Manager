#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


void login(){
    
    printf("<div class=\"wave\">\
                <h1 class=\"label\">Login</h1><br>\
                <form action=\"http://localhost/cgi-bin/login.cgi\" method=\"get\">\
                    <input type=\"text\" placeholder=\"Username\" name=\"username\" class=\"entry1\"><br>\
                    <input type=\"password\" placeholder=\"Password\" name=\"password\" class=\"entry2\"><br>\
                    <input type=\"submit\" value=\"Log in\" class=\"log\"><br>\
                </form>\
                <form action=\"http://localhost/cgi-bin/login.cgi\" method=\"get\">\
                    <button class=\"pseudo-link\" name=\"btn\" >Don't have an account?</button>\
                </form>\
            </div>\
    ");

}

void startSession(){
    
    printf("<form action=\"http://localhost/cgi-bin/login.cgi \" method=\"get\">\
                <button class=\"open-session\" name=\"start\">Click here to continue</button>\
            </form>\
    ");

}



void loadcss(){

    //le fichier css se trouve à l'exterieur du serveur
    FILE* file=fopen("/home/mit/login.css","r");

    char tmp[256];

    printf("<style>");

    for(int i=0;fgets(tmp,sizeof(tmp),file);i++){
        printf("%s\n",tmp);
    }

    printf("</style>");

    fclose(file);
}

bool verify(char usr[],char passwd[]){

    FILE* file=fopen("/home/mit/C/data.txt","r");

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
void sendForm(){

    printf("<form action=\"http://localhost/cgi-bin/login.cgi\" method=\"get\">\
                <h1>Label</h1>\
                <input type=\"text\" name=\"sitename\" placeholder=\"Write your sitename\"><br>\
                <input type=\"text\" name=\"ipadress\" placeholder=\"Write your ipadress\"><br>\
                <input type=\"text\" name=\"webmaster\" placeholder=\"Webmaster@localhost\"><br>\
                <input type=\"text\" name=\"documentroot\" placeholder=\"DocumentRoot\"><br>\
                <h3>Activate site</h1><br>\
                <input type=\"checkbox\" name=\"checkbox\" value=\"active\">Yes<br>\
                <input type=\"checkbox\" name=\"checkbox\" value=\"non-active\">No<br>\
                <h3>Activate CGI</h1><br>\
                <input type=\"checkbox\" name=\"cgi\" value=\"active\">Yes<br>\
                <input type=\"checkbox\" name=\"cgi\" value=\"non-active\">No<br>\
                <input type=\"submit\" value=\"Confirm\">\
            </form>\
    ");
}

void createAccount(){

    printf("<div class=\"sign-up\">\
                <form action=\"http://localhost/cgi-bin/login.cgi\" method=\"get\">\
                    <p>Create account</p>\
                    <input type=\"text\" placeholder=\"username\" name=\"usr\" class=\"entry1\"><br>\
                    <input type=\"password\" placeholder=\"password\" name=\"pwd\" class=\"entry1\"><br>\
                    <input type=\"text\" placeholder=\"e-mail\" name=\"usrid\" class=\"entry2\"><br>\
                    <input type=\"submit\" value=\"Sign up\" class=\"log\"><br>\
                </form<\
            </div>\
    ");
}


int main(){
    
    printf("Content-Type: text/html\n\n");
    
    printf("<html>\
        <head>\
            <title>Manager</title>\
        </head>\
        ");
    
    loadcss();
    
    printf("<body>");
    
    char* data=getenv("QUERY_STRING");
    char entry1[256];
    char sitename[256];
    char entry2[256];
    char ipadress[256];
    char entry3[256];
    char webmaster[256];
    char entry4[256];
    char documentroot[256];
    char entry5[256];
    char value[256];
    char entry6[256];
    char cgi[256];

    char command[500];
if(data!=NULL){
        
       sscanf(data,"%[^=]=%[^&]&%[^=]=%[^&]&%[^=]=%[^&]&%[^=]=%[^&]&%[^=]=%[^&]&%[^=]=%s",entry1,sitename,entry2,ipadress,entry3,webmaster,entry4,documentroot,entry5,value,entry6,cgi);
        
        if((strcmp(entry1,"sitename")==0 && strcmp(entry2,"ipadress")==0)){
           

            snprintf(command,sizeof(command),"/home/mit/C/%s.conf",sitename);
            FILE* file=fopen(command,"w");
            FILE* file1=fopen("/etc/apache2/sites-available/000-default.conf","r");
            char tmp[256];
            for(int i=0;fgets(tmp,sizeof(tmp),file1);i++){
                if(strcmp(cgi,"active")==0){
                    if(strstr(tmp,"#ServerName www")){
                        if(strcmp(value,"active")==0){
                            fprintf(file,"\tServerName www.%s.com\n",sitename);
                        }
                        else{
                            fprintf(file,"\t#ServerName www.%s.com\n",sitename);
                        }
                    }
                    else if(strstr(tmp,"<Directory /usr/lib/cgi-bin/>")){
                        fprintf(file,"\t<Directory /home/mit/%s/>\n",documentroot);
                    }
                    else if(strstr(tmp,"Script")){

                    }
                    else if(strstr(tmp,"DocumentRoot")){
                        fprintf(file,"\tDocumentRoot /home/mit/%s/",documentroot);
                    }
                    else if(strstr(tmp,"ServerAdmin")){
                        fprintf(file,"\tServerAdmin %s@localhost\n",webmaster);
                    }
                    else{
                        fprintf(file,"%s",tmp);
                    }
                }
                else{
                    if(i<14 || i>=19){
                        if(strstr(tmp,"#ServerName www")){
                        if(strcmp(value,"active")==0){
                            fprintf(file,"\tServerName www.%s.com\n",sitename);
                        }
                        else{
                            fprintf(file,"\t#ServerName www.%s.com\n",sitename);
                        }
                        }
                        else if(strstr(tmp,"Script")){

                        }
                        else if(strstr(tmp,"DocumentRoot")){
                            fprintf(file,"\tDocumentRoot /home/iantso/%s/",documentroot);
                        }
                        else if(strstr(tmp,"ServerAdmin")){
                            fprintf(file,"\tServerAdmin %s@localhost\n",webmaster);
                        }
                        else{
                            fprintf(file,"%s",tmp);
                        }
                    }
                }
            }
            fclose(file1);
            fclose(file);

            FILE* file2=fopen("/home/mit/C/hosts","w");
            FILE* file3=fopen("/etc/hosts","r");
            fprintf(file2,"%s\twww.%s.com\n",ipadress,sitename);
            for(int i=0;fgets(tmp,sizeof(tmp),file3);i++){
                fprintf(file2,"%s",tmp);
            }
            fclose(file3);
            fclose(file2);

            char cmd[256];
            sscanf(cmd,"sudo mv /home/mit/C/%s.conf /etc/apache2/sites-available/",sitename);
            system(cmd);
            system("sudo mv /home/mit/C/hosts /etc/hosts");
            sscanf(cmd,"a2ensite %s",sitename);
            system(cmd);
        }

        else if(strcmp(entry1,"username")==0 && strcmp(entry2,"password")==0){
            bool status=verify(sitename,ipadress);

            if(status){
                printf("<h1 class=\"centered-label\">Login successfully!</h1>");
                startSession();
            }
            else{
                printf("<h1 class=\"centered-label\">Login failed!</h1>");
                login();
            }

        }
        
        else if(strcmp(entry1,"btn")==0){
            createAccount();                        
        }
        
        //avec trois cond séparer 2 par 2
        else if((strcmp(entry1,"usr")==0 && strcmp(entry2,"pwd")==0) && strcmp(entry3,"usrid")==0){
            FILE* file=fopen("/home/mit/C/data.txt","a");

            if (strstr(webmaster,"gmail.com")){
                fprintf(file,"%s %s %s\n",sitename,ipadress,webmaster);
                printf("<h1>Sign up successfully,try login now</h1>");
                login();
            }
            else{
                printf("<h1>Try again</h1>");
                createAccount();
            }
            fclose(file);

        }

        else if(strcmp(entry1,"start")==0){
            sendForm();
        }

        else{
            login();
        }
    }
    printf("</body></html>");
    return 0;    
}
