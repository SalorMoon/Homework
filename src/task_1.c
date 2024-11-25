#include <stdio.h>
#include <string.h>

int main(){
    char str_report[100];
    while(1){
        scanf("%s", str_report);
        if(str_report[0] == '\0'){
            break;
        } else {
            for(int i = 0; str_report[i] != '\0'; ++i){
                if(str_report[i] == '#' || str_report[i] == '@'){
                    continue;   
                }
            }
            printf("%c", str_report[i]); 
        }
        
    }
}