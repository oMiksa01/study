
char* fn_name(int num){
    switch (num){
        case 1:
            return "sub";
            break;
        default:
            return "NULL";
            break;
    }
}

int sub(int a, int b){
    return a - b;
}