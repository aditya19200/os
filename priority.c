CODE: 
#include<stdio.h> 
struct Process {
    int pid, bt, priority, wt, tat;
};
void sortProcesses(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].priority > p[j + 1].priority) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}
void calculateTimes(struct Process p[], int n) {
    p[0].wt = 0;
    p[0].tat = p[0].bt;
    for (int i = 1; i < n; i++) {
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
        p[i].tat = p[i].wt + p[i].bt;
    }
}
void displayResults(struct Process p[], int n) {
    float total_wt = 0, total_tat = 0;
    printf("\nPID  Priority  BT   WT   TAT\n");
    for (int i = 0; i < n; i++) {
        total_wt += p[i].wt;
        total_tat += p[i].tat;
        printf("%d      %d       %d    %d    %d\n", p[i].pid, p[i].priority, p[i].bt, p[i].wt, p[i].tat);
    }
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    printf("Enter Burst Time and Priority for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process %d (BT Priority): ", i + 1);
        scanf("%d %d", &p[i].bt, &p[i].priority);
    }
     sortProcesses(p, n);
    calculateTimes(p, n);
    displayResults(p, n);
    return 0;
}
