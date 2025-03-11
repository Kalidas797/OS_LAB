//Optimal
#include <stdio.h>
#include <limits.h>

int fr[10], n, m; // Maximum of 10 frames

void display();

int main() {
    int i, j, page[100], index, k;
    int max, found, lg[10], flag1, flag2, pf = 0;
    float pr;

    printf("Enter length of the reference string: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &page[i]);

    printf("Enter number of frames: ");
    scanf("%d", &m);

    for (i = 0; i < m; i++)
        fr[i] = -1;

    for (j = 0; j < n; j++) {
        flag1 = 0;
        flag2 = 0;

       
        for (i = 0; i < m; i++) {
            if (fr[i] == page[j]) {
                flag1 = 1; 
                flag2 = 1;
                break;
            }
        }

        // If the page is not in a frame, check for an empty frame
        if (flag1 == 0) {
            for (i = 0; i < m; i++) {
                if (fr[i] == -1) { // Empty frame found
                    fr[i] = page[j];
                    flag2 = 1;
                    pf++; // Page fault
                    break;
                }
            }
        }

        // If no empty frame, replace a page using the OPT algorithm
        if (flag2 == 0) {
            // Initialize look-ahead distances to a large number (no future use)
            for (i = 0; i < m; i++)
                lg[i] = INT_MAX;

            // Find the future usage distance for each page in the frame
            for (i = 0; i < m; i++) {
                for (k = j + 1; k < n; k++) {
                    if (fr[i] == page[k]) {
                        lg[i] = k; // Store the index of the next occurrence
                        break;
                    }
                }
            }

            // Select the page that will be used **farthest in the future** (or never used again)
            max = -1;
            index = -1;
            for (i = 0; i < m; i++) {
                if (lg[i] > max) {
                    max = lg[i];
                    index = i;
                }
            }

            fr[index] = page[j];
            pf++;
        }

        display();
    }

   
    printf("Number of page faults: %d\n", pf);
    pr = ((float)pf / n) * 100;
    printf("Page fault rate = %.2f%%\n", pr);

    return 0;
}

void display() {
    for (int i = 0; i < m; i++) {
        if (fr[i] == -1)
            printf("-\t");
        else
            printf("%d\t", fr[i]);
    }
    printf("\n");
}
