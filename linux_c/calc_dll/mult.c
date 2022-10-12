
char* fn_name(int num){
    switch (num){
        case 1:
            return "mult";
            break;
        default:
            return "NULL";
            break;
    }
}

int mult(int a, int b){
    return a * b;
}