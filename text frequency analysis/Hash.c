#include <stdio.h>
#include <string.h>
#define HASH_SIZE 100

typedef struct hash_word{
    char* value;
    int quantity;
}hash_word;
typedef struct doubly_linked_list{
    hash_word word;
    struct My_List* left_element;
    struct My_List* right_element;
}hash_element;
void init_hash_element(hash_element* element){
    element->word.value="head";
    element->word.quantity=0;
    element->left_element=NULL;
    element->right_element=NULL;
}
void set_element(hash_element* head,char* value){
    hash_element* i_element=head;
    int flag_word_in_tabl=0;
    hash_element* new_element;
    while (i_element->right_element!=NULL){
        i_element=i_element->right_element;
        if (*i_element->word.value==*value){
            i_element->word.quantity++;
            flag_word_in_tabl=1;
        }
    }
    if (flag_word_in_tabl==0){
        new_element=malloc(sizeof(hash_element));
        i_element->right_element=new_element;
        new_element->word.value=malloc(sizeof(char)*(strlen(value)+1));
        strcpy(new_element->word.value,value);
        new_element->word.quantity=1;
        new_element->left_element=i_element;
        new_element->right_element=NULL;
    }
}
void clear_element(hash_element* head){
    hash_element* i_element=head;
    while (i_element->right_element!=NULL){
        i_element=i_element->right_element;
    }
    if (i_element->left_element!=NULL){
        while (i_element->left_element!=NULL){
            i_element->word.value="";
            free(i_element->word.value);
            i_element->word.quantity=0;
            i_element=i_element->left_element;
            free(i_element->right_element);
        }
    }
}
void print_element(hash_element* head){
    hash_element* i_element=head;
    while (i_element->right_element!=NULL){
        i_element=i_element->right_element;
        printf("%s(%d)\n",i_element->word.value,i_element->word.quantity);
    }
}
int Hash_function(char* new_word){
    int i,hash_value=0;
    for(i=0;new_word[i]!='\0';i++){
        hash_value+=((int)(new_word[i]))*i;
    }
    hash_value%=HASH_SIZE;
    return hash_value;
}
void Hash_Tabl_init(hash_element* Hash_Tabl){
    int i;
    for (i=0;i<HASH_SIZE;i++){
        init_hash_element(&Hash_Tabl[i]);
    }
}
void Hash_Tabl_add(hash_element* Hash_Tabl, char* new_word){
    set_element(&Hash_Tabl[Hash_function(new_word)],new_word);
}
void Hash_Tabl_print(hash_element* Hash_Tabl){
    int i;
    for(i=0;i<HASH_SIZE;i++){
        print_element(&Hash_Tabl[i]);
    }
}
void Hash_Tabl_free(hash_element* Hash_Tabl){
    int i;
    for (i=0;i<HASH_SIZE;i++){
        clear_element(&Hash_Tabl[i]);
    }
}
int max_word_len(char* filename){
    int i=0,ch=0,max=0;
    FILE* pfile=fopen(filename,"r");
    while ((ch = fgetc(pfile)) != EOF){
        if (((ch>=65)&&(ch<=90))||((ch>=97)&&(ch<=122))){
            i++;
        }
        else{
            if (i>max){
                max=i;
            }
            i=0;
        }
    }
    fclose(pfile);
    return max;
}
int read_file(char* filename,hash_element* Hash_Tabl){
    FILE *pfile;
    int i=0,ch=0;
    pfile=fopen(filename,"r");
    if (pfile==NULL){
        return 1;
    }
    char* read_word=malloc(sizeof(char)*max_word_len(filename));
    read_word[0]='\0';
    while ((ch = fgetc(pfile)) != EOF){
        if (((ch>=65)&&(ch<=90))||((ch>=97)&&(ch<=122))){
            if (ch<=90){
                ch+=32;
            }
            read_word[i]=(char)(ch);
            i++;
            read_word[i]='\0';
        }
        else{
            if (read_word[0]!='\0'){
                Hash_Tabl_add(Hash_Tabl,read_word);
            }
            read_word[0]='\0';
            i=0;
        }
    }
    free(read_word);
    fclose(pfile);
    return 0;
}
int main(int argc, char* argv[]){
    int i;
    hash_element Hash_Tabl[HASH_SIZE];
    Hash_Tabl_init(Hash_Tabl);
    if ((read_file(argv[0],Hash_Tabl))!=0){
        printf("incorrect filename\n");
        return 0;
    }
    else{
        Hash_Tabl_print(Hash_Tabl);
        Hash_Tabl_free(Hash_Tabl);
    }
    return 0;
}
