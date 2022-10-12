
char* fn_name(int num){
    switch (num){
        case 1:
            return "add";
            break;
        default:
            return "NULL";
            break;
    }
}

int add(int a, int b){
    return a + b;
}