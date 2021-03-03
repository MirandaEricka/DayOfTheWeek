#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct {
    int year;
    int month;
    int day;
} date;
int isLeapYear (int y){
    if(y%4 == 0 && y%100 != 0 || y%400 == 0) return 1;
    else return 0;
}
int daysPerMonth (int m){
    if (m > 7 && m%2 == 0 || m <= 7 && m%2 == 1) return 31;
    else if (m == 2) return 28;
    else return 30;
}
int scan(int min, int max, char str[5]){
    char *ch, s[100];
    int n;
    if (str == "month") printf("Enter a month as a number (example: use 02 for February): ");
    else printf("Enter the %s: ", str);
    while (fgets(s, sizeof(s), stdin)) {
        n = strtol(s, &ch, 10);
        if (n < min || n > max || ch == s || *ch != '\n') {
            if(str == "year") printf("Invalid input. Year must be a positive integer. Enter another number: ");
            else printf("Invalid input. %s must be from %d to %d. Enter another number: ", str, min, max);
        } else break;
    }
    return n;
}
int dayNumber (int y, int m, int d){
    int iter, dNum = d;
    for(iter = 1; iter < m; iter++){
        dNum += daysPerMonth(iter);
    }
    if(isLeapYear(y) && m > 2) return dNum + 1;
    else return dNum;
}
int R(int y, int m){
    return y%m;
}
int GaussMethod(int A){
    return R(1 + 5*R(A - 1, 4) + 4*R(A - 1, 100) + 6*R(A - 1,400), 7);
}
void suffix (int n){
    if (n%10 == 1) printf("st day of the year");
    else if (n%10 == 2) printf("nd day of the year");
    else if (n%10 == 3) printf("rd day of the year");
    else printf("th day of the year");

}
void GaussDay(int y, int m, int d){
    char day_arr[7][9] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    int dN = dayNumber(y, m, d), r;
    r = (GaussMethod(y) + dN - 1)%7;
    printf("%s, %d", day_arr + r, dN);
    suffix(dN);
}
int main(){
    date date;
    int ans, days_MAX;
    char *ch;

    printf("Determine what day of the week a date is. ");
    date.year = scan(1, INT_MAX, "year");
    date.month = scan(1, 12, "month");
    days_MAX = daysPerMonth(date.month);
    if(date.month == 2 && isLeapYear(date.year)) days_MAX++;
    date.day = scan(1, days_MAX, "day");
    GaussDay(date.year, date.month, date.day);

    return 0;
}
