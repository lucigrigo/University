int main(){
    char str[] = "\tExamen\0de\0\nprogramare";
    printf("%d %d %d",strlen(str),sizeof(str),strlen(str+12));
    getch();
    return 0;
}


