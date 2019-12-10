#include <stdlib.h>
#include <stdio.h>

static void __attribute__((constructor)) before_main(void){
    printf("在main之前\n");

}
int main(){
    printf("main\n");
    return 0;
}