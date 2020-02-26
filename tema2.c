#include <stdio.h>
#include <string.h>
#include<stdlib.h>
//urmatoarea functie va alinia la stanga textul
void align_left(char original[1000][1000], int begin, int end, int original_line_count)
{
char s[1000]; //vector auxiliar pentru aliniere
int nr, j, i;
for(i = begin; i <= end; i++){
	strcpy(s, original[i]); 
	nr = 0;
	j = 0;
	//vom contoriza numarul de spatii de la inceputul randului
	while(original[i][j] == 32){
		nr++;
		j++;
	}
	strcpy(s, original[i] + nr); //se aliniaza textul
	strcpy(original[i], s); 
}

//urmatoarea secenta de cod elimina trailing whitespaces
if(original[original_line_count - 1][strlen(original[original_line_count -1]) - 2] == 32){
	original[original_line_count - 1][strlen(original[original_line_count -1]) - 2] = 10;
	original[original_line_count - 1][strlen(original[original_line_count -1]) - 1] = '\0';
}
}
void align_right(char original[1000][1000], int begin, int end, int original_line_count)
{
	int lung_max;
	int i, j;
	lung_max = 0;
	int nr_spatii;
	char s1[1000];
	//se cauta linia de lungime maxima si se retine lungimea maxima
	for (i = 0; i <= original_line_count; i++){
	    if(strlen(original[i]) > lung_max){
	        lung_max = strlen(original[i]);
	      }
	}

	if(begin == end){
		//in nr se retine nr de spatii cu care trebuie mutat textul la dreapta
	    nr_spatii = lung_max - strlen(original[begin]); 
	    for( j = 0; j < nr_spatii; j++)
	        s1[j] = 32;
	    strcpy(s1 + nr_spatii, original[begin]);
	    strcpy(original[begin], s1);

	  }
	else{
	   	for(i = begin; i <= end; i++){
	    	//s1[100] =NULL;
	    	if(strlen(original[i]) > 1){
	    		//printf("%d\n", nr_spatii );
		      	nr_spatii = lung_max - strlen(original[i]);
		     	for( j = 0; j < nr_spatii; j++)
		        	s1[j] = 32;
			    strcpy(s1 + nr_spatii, original[i]);// se muta linia la dreapta
			    strcpy(original[i], s1);//se copiaza linia alniata in original
		    }
	   }
	}
}
void center(char original[1000][1000], int begin, int end, int original_line_count){
	int i, max_length = 0, max_line, j;
	char s2[1000];
	int nr_spatii_center;
	for (i = 0;i <= original_line_count; i++){
		//se retin linia de lungime maxima si lungimea maxima
		if(strlen(original[i]) > max_length){
		    max_line = i;
		    max_length = strlen(original[i]);
		}
	}
	for(i = begin;i <= end; i++){
		//s2[100] =NULL;
		if((strlen(original[i]) > 1) && (i != max_line)){
			//se calculeaza numarul de spatii cu care 
			//trebuie mutata lnia la dreapta
		    if((max_length - strlen(original[i])) % 2 == 0) 
		        nr_spatii_center = ((max_length - strlen(original[i])) / 2);
		    else
		        nr_spatii_center = ((max_length - strlen(original[i])) / 2) + 1;
		    //se adauga spatii goale la inceputul vectorului 
		    for( j =0; j < nr_spatii_center; j++)
		        s2[j] = 32;
		    //se copiaza linia i in vector
		    strcpy(s2 + nr_spatii_center, original[i]);
		    strcpy(original[i], s2); //se copiaza pe linia i vectorul
		    }


	}

}
void paragraphs(char original[1000][1000], int begin, int end, int indent_length){
char s3[1000];
int k, i;
if(begin == end){
	//se adauga spatii goale la inceputul vectorului auxiliar
	for(k = 0; k < indent_length; k++){
		s3[k] = 32;
	}
    //se copiaza linia din original in vector
	strcpy(s3 + indent_length, original[begin]); 
    strcpy(original[begin], s3); //se copiaza linia din vector in original
}
else{ 
	for(i = begin - 1;i <= end; i++){
		//prima linie din fisier este paragraf
		if( i == 0){
		    for(k = 0; k < indent_length; k++){
		        s3[k] = 32;
		    }
		strcpy(s3 + indent_length, original[i]);
		strcpy(original[i], s3);
		}

		if(strcmp(original[i], "\n") == 0) {
			i = i + 1;
			for(k = 0; k < indent_length; k++){
			    s3[k] = 32;
			}
			strcpy(s3 + indent_length, original[i]);
			strcpy(original[i], s3);
		}	

	}

}	
}
void lists(char original[1000][1000], int begin, int end, char list_type[20], char special_character[20])
{
char s3[1000], s5[1000];
int listcount, i;
char string;
//se verifica tipul listei
if(strcmp(list_type, "n") == 0 ){
	listcount = 1;
	for(i = begin; i <= end; i++){
		//se scriu in s3 contorul si caracterul special
		sprintf(s3,"%d%s ", listcount, special_character);
		//se concateneaza in s3 linia i
		if(listcount < 10)
		    strcpy(s3 + 3, original[i]);
		else
		    strcpy(s3 + 4, original[i]);
		listcount ++;
		strcpy(original[i], s3);

	}
}
if(strcmp(list_type, "b") == 0 ){
	for(i = begin; i <= end; i++){
		if(strcmp(original[i], "\n") == 0)
		    i++;
		//se scrie in s3 caracterul special
		sprintf(s3,"%s", special_character);
		s3[1] = 32;
		strcpy(s3 + 2, original[i]);
		strcpy(original[i], s3);
	}

}
if(strcmp(list_type, "a") == 0 ){
	string = 'a';
	for(i = begin; i <= end; i++){
		if(strcmp(original[i], "\n") == 0)
		    i++;
		s5[0] = string;
		string = string + 1;
		strcpy(s5 + 1, special_character);
		strcpy(s5 + 2, " ");
		strcpy(s5 + 3, original[i]);
		strcpy(original[i], s5);
	}

}
if(strcmp(list_type, "A") == 0 ){
	string = 'A';
	for(i = begin; i <= end; i++){
		if(strcmp(original[i], "\n") == 0)
			i++;
		s5[0] = string;
		string = string + 1;
		strcpy(s5 + 1, special_character);
		strcpy(s5 + 2, " ");
		strcpy(s5 + 3, original[i]);
		strcpy(original[i], s5);
	}

		  
}	

}
void ordered_lists(char original[1000][1000], int begin, int end, 
	char list_type[20], char special_character[20], char ordering[10],
	int original_line_count)
{
int i, ok;
char ordonare[1000];
if(strcmp(ordering, "a") == 0){
	if(begin == 0 && end == original_line_count){
	//se ordoneaza alfabetic lista
	do{
		ok = 0; //ok va fi 0 atunci cand lista este ordonata
	    	for(i = begin; i < end - 1; i++){
	    		//se compara lexicografic fiecare linie cu urmatoarea
	      		if(strcmp(original[i], original[i + 1]) > 0){
	        	strcpy(ordonare, original[i]);
	        	strcpy(original[i], original[i + 1]);
	        	strcpy(original[i + 1], ordonare);
	        	ok = 1;
	      	}

	    }
	}while(ok);
	}
	else{
		//se ordoneaza alfabetic lista
	  	do{
	    	ok = 0;
	    	for(i = begin; i <= end - 1; i++){
	      		if(strcmp(original[i], original[i + 1]) > 0){
			        strcpy(ordonare, original[i]);
			        strcpy(original[i], original[i + 1]);
			        strcpy(original[i + 1], ordonare);
			        ok = 1;
			    }
			}
	    }while(ok);

	}
	}
	if(strcmp(ordering, "z") == 0){
		//se sorteaza lista in ordine invers alfabetica
	  	do{
	    	ok = 0;
	   		for(i = begin; i <= end - 1; i++){
	      		if(strcmp(original[i], original[i + 1]) < 0){
		        strcpy(ordonare, original[i]);
		        strcpy(original[i], original[i + 1]);
		        strcpy(original[i + 1], ordonare);
		        ok = 1;
	      		}

	    	}
	  	}while(ok);
	}
	//se aliniaza lista
	align_left(original, begin, end, original_line_count);
	//se construieste lista
	lists(original, begin, end, list_type, special_character);
 }
	
int main(int argc, char *argv[]){

char buf[1000],  //folosit pentru citirea din fisier             
      original[1000][1000], //textul original 
      result[1000][1000]; //textul obtinut dupa efectuarea operatiilor
char copie[1000][1000] ;      
int original_line_count = 0, //numarul initial de linii ale textului
      result_line_count = 0, //numarul de linii din textul rezultat  
      i, j, k;
char operation_string[100], //vector in care se retin toate operatiile
 commands[100][100]; //matrice care va avea pe fiecare linie cate o operatie
char name_of_command[20];
char *pch, *pch2;
int icount = 0, nr_cmd;
int l;
char *aux;
int begin, end; //intervalul in care se vor efectua operatiile
int nr = 0;
char s[100];
int indent_length;
char list_type[20], special_character[20];
char ordering[20];
int max_length1; //nr maxim de cuvinte pe linie (wrap)
int temp;
int lung_max;
int nr_spatii;
char s1[1000], cuv_max = 0;


if (argc != 4) {  // invalid number of arguments
    fprintf(stderr,
            "Usage: %s operations_string input_file output_file\n",
            argv[0]);
    return -1;
}

  // Open input file for reading
FILE *input_file = fopen(argv[2], "r");

if (input_file == NULL) {
	fprintf(stderr, "File \"%s\" not found\n", argv[2]);
    return -2;
}

  // Read data in file line by line
while (fgets(buf, 1000, input_file)) {
    strcpy(original[original_line_count], buf);
    original_line_count++;
}
fclose(input_file);

//copierea operatiilor in vector
strcpy(operation_string, argv[1]);
icount = 0; 
//se construieste o matrice care are pe linie cate o operatie si argumentele ei   
pch =  strtok(operation_string, ",");
while(pch != NULL){
    strcpy(commands[icount], pch);
    icount++;
    pch = strtok(NULL, ",");

}
nr_cmd  = icount;
//printf("%d\n", nr_cmd );
if(nr_cmd > 10){
  	printf("Too many operations! Only the first 10 will be applied.\n");
  	nr_cmd = 10;
}
//se parcurge matricea de comenzi si se verifica tipul comenzii
for (l = 0; l < nr_cmd; l++){
   
	pch2 = strtok(commands[l]," ");
    strcpy(name_of_command, pch2);
    
    if((strcmp(name_of_command, "l") == 0) || (strcmp(name_of_command,"L") == 0)){
    	begin = 0;
        end = original_line_count;
        //se verifica intervalul in care se va aplica operatia
        pch2 = strtok(NULL, " ");
	    if(pch2 != NULL){
	    	aux = pch2;
	        begin = atoi(aux);
	    }
      	pch2 = strtok(NULL, " ");
      	if(pch2 != NULL){
	        aux = pch2;
	        end = atoi(aux);

      	}
      	if (begin > end || begin < 0){
      		printf("Invalid operation!\n");
      	}
      	else{
	    	if(end > original_line_count)
	      	 	end = original_line_count;
	      	if(begin <= original_line_count){
	      		align_left(original, begin, end, original_line_count);
	      
			}

		}
		
	}
	
	if((strcmp(name_of_command, "r") == 0) || (strcmp(name_of_command,"R") == 0)){
     	begin = 0;
      	end = original_line_count;
      	//se verifica intervalul in care se va aplica operatia
      	pch2 = strtok(NULL, " ");
      	if(pch2 != NULL){
        	aux = pch2;
        	begin = atoi(aux);
      	}
      	pch2 = strtok(NULL, " ");
      	if(pch2 != NULL){
	        aux = pch2;
	        end = atoi(aux);

      	}
      	pch2 = strtok(NULL, " ");
      	if(pch2 != NULL){
      		printf("Invalid operation\n");
      	}
      	else{
			if(end > original_line_count){
			    end = original_line_count;
			}
			if(begin <= original_line_count){
			    align_right(original, begin, end, original_line_count);
			}
		}	
		    
	}
	if((strcmp(name_of_command, "c") == 0) || (strcmp(name_of_command,"C") == 0)){
    	begin = 0;
      	end = original_line_count;
      	pch2 = strtok(NULL, " ");
      	if(pch2 != NULL){
        	aux = pch2;
        	begin = atoi(aux);
      	}
      	pch2 = strtok(NULL, " ");
      	if(pch2 != NULL){
        	aux = pch2;
        	end = atoi(aux);

      	} 
    	if (begin > end || begin < 0){
      		printf("Invalid operation!\n");
      	}
    	else{
	    	if(end > original_line_count){
	      	  	end = original_line_count;
	    	}
	   		if(begin <= original_line_count){
	   			center(original, begin, end, original_line_count);
	   		}

		}
	}
	if((strcmp(name_of_command, "p") == 0) || (strcmp(name_of_command,"P") == 0)){
      	begin = 0;
      	end = original_line_count;
      	pch2 = strtok(NULL, " ");
      	//se verifica nr de caractere cu care trebuie indentat paragraful
      	if(pch2 != NULL){
        	aux = pch2;
        	indent_length = atoi(aux);
     	}
     	//se verifica 
      	pch2 = strtok(NULL, " ");
      	if(pch2 != NULL){
        	aux = pch2;
        	begin = atoi(aux);
      	}
      	pch2 = strtok(NULL, " ");
      	if(pch2 != NULL){
        	aux = pch2;
        	end = atoi(aux);

      	}
  		if (begin > end || begin < 0){
      		printf("Invalid operation!\n");
      	}
   		else{
		 	if(end > original_line_count)
		      	  end = original_line_count;
		  	if(begin <= original_line_count)
		  		paragraphs(original, begin, end, indent_length);
		}
	}

	if((strcmp(name_of_command, "i") == 0) || (strcmp(name_of_command,"I") == 0)){
 		begin = 0;
 		end = original_line_count;
 		//se verifica tipul listei
 		pch2 = strtok(NULL, " ");
  		if(pch2 != NULL){
    		strcpy(list_type, pch2);
  		}
  		//se verifica caracterul special
  		pch2 = strtok(NULL, " ");
  		if(pch2 != NULL){
   			 strcpy(special_character, pch2);
 		}
 		//se verifica intervalul in care se vor efectua operatile
 		pch2 = strtok(NULL, " ");
  		if(pch2 != NULL){
    		aux = pch2;
    		begin = atoi(aux);
  		}
  		pch2 = strtok(NULL, " ");
  		if(pch2 != NULL){
    		aux = pch2;
    		end = atoi(aux);
   		}
  		if (begin > end || begin < 0){
      		printf("Invalid operation!\n");
      	}
  		else{
  			if(end > original_line_count)
		    	end = original_line_count;
		  	if(begin <= original_line_count){
		  		lists(original, begin, end, list_type, special_character);
		  	}
		}

}
if((strcmp(name_of_command, "o") == 0) || (strcmp(name_of_command,"O") == 0)){
  	begin = 0;
  	end = original_line_count;
  	pch2 = strtok(NULL, " ");
  	if(pch2 != NULL){
    	strcpy(list_type, pch2);
  	}
  	pch2 = strtok(NULL, " ");
  	if(pch2 != NULL){
    	strcpy(special_character, pch2);
  	}
  	pch2 = strtok(NULL, " ");
  	if(pch2 != NULL){
    	strcpy(ordering, pch2);
  	}
  	pch2 = strtok(NULL, " ");
  	if(pch2 != NULL){
    	aux = pch2;
    	begin = atoi(aux);
  	}
  	pch2 = strtok(NULL, " ");
  	if(pch2 != NULL){
    	aux = pch2;
    	end = atoi(aux);
 	}
  	if (begin > end || begin < 0){
      	printf("Invalid operation!\n");
    }
   else{
	  	if(end > original_line_count)
	      	end = original_line_count;
	  	if(begin <=  original_line_count){
	  		ordered_lists(original, begin, end, list_type, special_character, 
	  			ordering, original_line_count);
		}
	}
}
if((strcmp(name_of_command, "w") == 0) || (strcmp(name_of_command,"W") == 0)){
  begin = 0;
  end = original_line_count;
  pch2 = strtok(NULL, " ");
  //se verifica numarul maxim de caractere de pe o linie
  if(pch2 != NULL){
    aux = pch2;
    max_length1 = atoi(aux);
  }
//voi forma o noua matrice(copie care va avea 
//pe linie maxim max_lenght1 elemente)
pch2 = strtok(NULL, " ");
if(pch2 != NULL)
	printf("Invalid operation!\n");
else{
for(i = 0; i <= original_line_count; i++){
	strcpy(s1, original[i]);
	pch = strtok(s1, " ");
	while(pch != NULL){
		if (strlen(pch) > cuv_max)
			cuv_max = strlen(pch);
		pch = strtok(NULL, " ");
	}

}
if(max_length1 < cuv_max)
	printf("Cannot wrap!\n");
else{

temp = 0; //retine numar de caractere de pe linie
j = 0; 
for(i = 0;i <= original_line_count;i++){
	//daca randul este gol, se va copia in matricea copie
  	if(strcmp(original[i], "\n") == 0){
  		temp = 0;
  		//se va pune pe ultima pozitie din randul nou "\n"
  		copie[j][strlen(copie[j]) - 1] = 10;
  		strcpy(copie[j + 1], "\n");
  		j ++; //se trece la o noua linie
  	}
  	else{
  	//se retin pe rand cuvintele din linie in pch
  	pch = strtok(original[i], " \n");
  	while(pch != NULL){
  		//se adauga in temp lungimea cuvantului si se verifica
  		//daca acesta incape sau nu pe linia j
  		temp = temp + strlen(pch);
  		//daca incape, se adauga cuvantul pe linia j si se pune spatiu dupa acesta
  		if(temp <= max_length1){
  			strcat(copie[j], pch);
  			strcat(copie[j], " ");
  			temp ++; //se numara si spatiul pe care l-am adaugat
  		}
  		else{
  			//in sens contrar, se adauga "\n" pe linia curenta a matricei
  			copie[j][strlen(copie[j]) - 1] = 10;
  			//se trece la o noua linie si se adauga cuvantul pe aceasta linie
  			j = j + 1;
  			temp = strlen(pch);
  			strcat(copie[j],pch);
  			strcat(copie[j]," ");
  			temp++;
  		}
  	pch = strtok(NULL, " \n");
  	}

  }
}

//se marcheaza sfarsitul textului 
copie[j][strlen(copie[j]) -1] = 10;
copie[j][strlen(copie[j])] = '\0';
//se copiaza noua matrice in cea initiala si se actualizeaza numarul de linii
original_line_count = j + 1;
for( i = 0; i <= original_line_count; i++)
     strcpy(original[i], copie[i]);
}
}
 
}
if((strcmp(name_of_command, "j") == 0) || (strcmp(name_of_command,"J") == 0)){
    begin = 0;
    end = original_line_count;
    pch2 = strtok(NULL, " ");
    if(pch2 != NULL){
       	aux = pch2;
        begin = atoi(aux);
    }
    pch2 = strtok(NULL, " ");
    if(pch2 != NULL){
       	aux = pch2;
        end= atoi(aux);
    }
    if( end > original_line_count)
		end = original_line_count;
	//daca textul contine tab-uri la inceputul liniei acestea se elimina
    nr = 0;
    for(i = begin; i <= end; i++){
		strcpy(s, original[i]); 
		nr = 0;
		j = 0;
		while(original[i][j] == 9){
			nr++;
			j++;
		}
		strcpy(s, original[i] + nr); 
		strcpy(original[i], s); 
	}
	//se aliniaza la stanga textul
    align_left(original, begin, end, original_line_count); 
    //se cauta linia de lungime maxima din text si se retine lungimea maxima
    lung_max = 0;
    for(i = 0; i < original_line_count; i++){
    	if(strlen(original[i]) > lung_max){
    		lung_max = strlen(original[i]);
		}
	}
	
	
	for(i = begin; i <= end - 1; i++){
		//daca randul este gol, acesta va ramane neschimbat
		if(strcmp(original[i + 1], "\n") == 0)
			i = i + 1;
		else{
			//vom retine linia din matrice in vectorul s
			strcpy(s, original[i]);
			//se calculeaza nr de spatii care se vor adauga
			nr_spatii = lung_max - strlen(original[i]);
			temp = strlen(original[i]);
			k = 0;
			while(nr_spatii > 0){
				//se parcurge vectorul s pana la primul spatiu
				while(s[k] != 32){
					if(s[k] == 10)
						k= 0;
					k++;
					
				}
				//se parcurge vectorul pana la ultimul spatiu
				while(s[k] != 10){
					if(s[k] == 32)
						k++;
					else
						break;
				}
				//se insereaza un spatiu pe pozitia k
				for(j = temp + 1; j >= k; j--)
					s[j] = s[j - 1];
				s[k] = 32;
				temp = temp + 1;
				nr_spatii --;
				k = k + 1;

			}
		//se actualizeaza linia matricei
		strcpy(original[i], s);
		}
	}
	

	
}	

}


for (i = 0; i <= original_line_count; i++){
	strcpy(result[i], original[i]);
}
result_line_count = original_line_count;

  // Open output file for writing
FILE *output_file = fopen(argv[3], "w");

if (output_file == NULL) {
    fprintf(stderr, "Could not open or create file \"%s\"\n", argv[3]);
    return -2;
}
 
  // Write result in output file
for (i = 0; i < result_line_count; i++) {
    fputs(result[i], output_file);
}

  fclose(output_file); 

}