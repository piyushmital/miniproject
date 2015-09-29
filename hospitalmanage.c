#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
struct Doctor{ 
	int id;
	char name[25];
	int age;
	char specialty[100];
}Doctor;
void append info(char *name){
	int i = 0, fp, m = 0, x;
	Doctor b[100];
 	double go;
	fp = open(name, O_APPEND | O_WRONLY);
	printf("Enter id, name, age, speciality\n");
	while(scanf("%d%s%d%s", b[i].id, &b[i].name, &b[i].age, &b[i]speciality) != EOF) {
		printf("Enter id, name, age, speciality\n");	
		i++;
	} 	
	write(fp, a, sizeof(Doctor)*i);  	
	rewind(fp);
	x = read(fp, &m, sizeof(int));
	rewind(fp);
	i = i + m;
	write(fp, &i, sizeof(int));
	close(fp);
	return 0;
}
void deleteinfo(char *name){
		int i, fp, m ,x, k = 0, fc, g = 0;
	Doctor a[100];
 	int go;
	fp = open(name, O_RDONLY);
	fc = open("copy.c", O_WRONLY);	
	go = atof(argv[2]);
	if(fp == -1) {
		printf("open failed\n");
		return 0;
	}
	x = read(fp, &m, sizeof(int));
	for( i = 0; i < m; i++) {
		x = read(fp, a, sizeof(Doctor));
		if(go == a[i].id){
			g = 1;		
		}
	}
	if(g == 1){
		printf("Id to be deleted exists in the file\n");
		g = m;
		g = g - 1;
		write(fc, &g, sizeof(int)); 
	}else{ 
		printf("Error Id\n");
	}
	rewind(fp);
	for(i = 0; i < m; i++){
		x = read(fp,  a, sizeof(Doctor));
		if(go != a[i].id)
			write(fc, a, sizeof(Doctor));
	}
	rename("copy.c", name);
	close(fp);
	close(fc);
	return 0;
}
void readinfo(char *name, char *id){
	int i, fp, m ,x, k = 0;
	Doctor a[100];
 	int go;
	fp = open(name, O_RDONLY);
	go = atof(id);
	if(fp == -1) {
		printf("open failed\n");
		return 0;
	}
	x = read(fp, &m, sizeof(int));
	for( i = 0; i < m; i++) {
		x = read(fp, a, sizeof(Doctor));
		if(go == a[i].id){
			k = 1;
			printf("Id = %d\n Name = %s\n Age = %d\n Speciality = %s\n", a[i].id, a[i].name, a[i].age, a[i]speciality );
		}
	}
	close(fp);
	return 0;
}
int main(){
	int a = 0, b = 0; c = 0;
	char *id;
	printf("Select doctor options\n1. read doctor info\n2. append doctor info\n3. delete doctor info\n");
	while(scanf("%d",&a) != EOF){
		switch(a){
			case 1: printf("enter id\n");
				scanf("%s",id);
				readinfo( doctor.txt, id);
				break;
			case 2: appendinfo(doctor.txt);
				break;
			case 3: deleteinfo(doctor.txt);
				break;
			default:
				printf("error input\n");
				break;
		}
	}
}

