 #include<stdio.h>
 #include<stdlib.h>
 #include <string.h>
 #include <unistd.h>
 void list_port(){
 	FILE *fp = popen("netstat -ano","r");
 	if(fp==NULL){
 		perror("Failed to run neststat -an");
 		return ;	
	 }
	 
	 char line[400];
	 printf("Open Ports:\n");
     while(fgets(line, sizeof(line),fp)){
     	printf("%s",line);
	 } 
	 pclose(fp);	
 }
 
 
 // used to find port number 
 void find_app_using_port_number(int port){
 	char command[256];
 	char line[256];
 	snprintf(command,sizeof(command),"netstat -ano | findstr :%d",port);
 	FILE *fp = popen(command,"r");
 	if(fp==NULL){
 		printf("\n \a Failed to run This command");
	 }
	 // read out put for 
	
	 char processName[100];
	 int pid = -1;
	 while(fgets(line, sizeof(line), fp)){
	 	if(sscanf(line , "%*s %*s %*s %*s %d", &pid)==1){
	 		printf("\n||\t\tPID: %d\t\t||\n ",pid);
	 		break;
		 }
	 	
	 }
	 pclose(fp);
	 
	 if(pid == -1){
	 	printf("\n No Application is using this port:%d.\n\a",port);
	 }
	 
	 snprintf(command , sizeof(command), "tasklist | findstr %d",pid);
	 fp = popen(command ,"r");
	 if(fp == NULL ){
	 	printf("\n \a faild to run tasklist");
	 }
	 
	 
	 // to print  the process name 
	 int found = 0 ;
	 while(fgets(line , sizeof(line),fp)){
	 	if(strstr(line , "Image Name")) continue; // skip header file 
	 	
	 	if(sscanf(line ,"%99s",processName)==1){
	 		printf("\n||------Application:%s (PID: %d)" , processName , pid );
	 		found = 1;
	 		break ;
		 }
	 	
	 }  
	 pclose(fp);
	 
	   if (!found) {
        printf("\nNo application found for PID: %d\n", pid);
    }
	 

}


// loading section 

void progeressLoading(){
	int total = 40 ;
	printf("\nLoading.....\n[");
	
	for(int i = 0 ; i < total ; i++){
		printf("#");
		fflush(stdout);
		usleep(200000); // wait (0.2)
		
		
	}
	printf("] \nDone!!!!!\n ");
}


 
int main(){
	char name[20] ;
	int portnum ;
	printf("||Hellow User !!!!!! \n");
	printf("||please Enter your name Here::");
	scanf("%s",&name);
	printf("||I'm Exctiry To Meet with you::\'%s\'",name);
	printf("\n||OK let precced ");
	printf("\n||Enter the Port number::");
	scanf("%d",&portnum);
	progeressLoading();
	find_app_using_port_number(portnum);
	printf("\n+-----------------------------------------+\n");
	list_port();
	
	return 0 ;
}
