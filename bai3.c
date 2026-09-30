#include <stdio.h>

struct UserAccount {
    int account_id;
    int plan_type;
    int monthly_fee;
    int remaining_days;
    int active_devices;
};

int main() {
    struct UserAccount a[100], temp;
    int n, i, j;
    int mrr_before = 0, mrr_after = 0;

    do {
        printf("Nhap N: ");
        scanf("%d", &n);
    } while (n < 1 || n > 100);

    for (i = 0; i < n; i++) {
        printf("\nTai khoan %d\n", i + 1);

        printf("Account ID: ");
        scanf("%d", &a[i].account_id);

        do {
            printf("Plan (0-Free, 1-Standard, 2-Premium): ");
            scanf("%d", &a[i].plan_type);
        } while (a[i].plan_type < 0 || a[i].plan_type > 2);

        printf("Monthly fee: ");
        scanf("%d", &a[i].monthly_fee);

        printf("Remaining days: ");
        scanf("%d", &a[i].remaining_days);

        printf("Active devices: ");
        scanf("%d", &a[i].active_devices);

        if (a[i].active_devices <= 0)
            a[i].active_devices = 1;

        if (a[i].plan_type > 0)
            mrr_before += a[i].monthly_fee;

        if (a[i].remaining_days <= 0) {
            a[i].plan_type = 0;
            a[i].monthly_fee = 0;
        } else {
            if (a[i].plan_type == 0) {
                a[i].monthly_fee = 0;
                if (a[i].active_devices > 1)
                    a[i].active_devices = 1;
            } else if (a[i].plan_type == 1) {
                a[i].monthly_fee = 120000;
                if (a[i].active_devices > 2)
                    a[i].active_devices = 2;
            } else {
                a[i].monthly_fee = 300000;
                if (a[i].active_devices > 5)
                    a[i].active_devices = 5;
            }
        }

        if (a[i].plan_type > 0)
            mrr_after += a[i].monthly_fee;
    }

    for (i = 1; i < n; i++) {
        temp = a[i];
        j = i - 1;

        while (j >= 0 &&
              (a[j].plan_type == 0 ||
              (a[j].monthly_fee < temp.monthly_fee &&
               temp.plan_type > 0))) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = temp;
    }

    printf("\n%-10s %-10s %-12s %-15s %-15s\n",
           "Account", "Plan", "Monthly Fee", "Remaining", "Devices");


    for (i = 0; i < n; i++) {
        printf("%-10d %-10d %-12d %-15d %-15d\n",
               a[i].account_id,
               a[i].plan_type,
               a[i].monthly_fee,
               a[i].remaining_days,
               a[i].active_devices);
    }

    printf("\nMRR truoc kiem toan: %d VND\n", mrr_before);
    printf("MRR sau kiem toan:   %d VND\n", mrr_after);
    printf("Chenh lech MRR:      %d VND\n", mrr_before - mrr_after);

    return 0;
}