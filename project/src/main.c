#include "utils.h"

int main(void) {
    int choice = 0;
    FILE *Ptr, *Ptr_2 , *black;
    Data client_data;
    Data transfer;
    printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
    while (scanf("%d", &choice) !=  -1) {
        switch (choice) {
            case 1:
                Ptr = fopen("record.dat", "r+");
                if (Ptr == NULL) {
                    puts("Not acess");
                } else {
                    masterWrite(Ptr, &client_data);
                    fclose(Ptr);
                }
                break;
            case 2:
                Ptr = fopen("record.dat", "r+");
                if (Ptr == NULL) {
                    puts("Not acess");
                } else {
                    transactionWrite(Ptr, &transfer);
                    fclose(Ptr);
                }
                break;
            case 3:
                Ptr = fopen("record.dat", "r");
                Ptr_2 = fopen("transaction.dat", "r");
                black = fopen("blackrecord.dat", "w");
                if (Ptr == NULL || Ptr_2 == NULL || black == NULL) {
                    puts("exit");
                } else {
                    blackRecord(Ptr, Ptr_2, black, &client_data, &transfer);
                    fclose(Ptr);
                    fclose(Ptr_2);
                    fclose(black);
                }
                break;
            default:
                puts("error");
                break;
            }
        printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
    }
    return 0;
}
