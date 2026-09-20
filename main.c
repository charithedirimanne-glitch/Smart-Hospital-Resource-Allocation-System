
#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

const char *specialtyName[] = {
    "",
    "General Practice (OPD)",
    "Paediatrics",
    "Cardiology",
    "Neurology"
};

const float specialtyFee[] = {0, 1500.00, 2500.00, 4500.00, 5000.00};
const int consultationTime[] = {0, 15, 20, 30, 30};
const int dailyPatientCap[] = {0, 30, 20, 12, 10};

const char *wardName[] = {
    "",
    "General Ward",
    "Paediatric Ward",
    "Surgical Ward",
    "ICU"
};

const float wardRate[] = {0, 3000.00, 6000.00, 12000.00, 25000.00};
const int wardCapacity[] = {0, 20, 10, 10, 5};

int count = 0;
int queueCount[5] = {0};
int bedOccupancy[4][20];

int patientId[MAX_PATIENTS];
char patientName[MAX_PATIENTS][50];
int patientAge[MAX_PATIENTS];
int urgencyLevel[MAX_PATIENTS];
int selectedSpecialty[MAX_PATIENTS];
int admitted[MAX_PATIENTS];
int selectedWard[MAX_PATIENTS];
int admissionDays[MAX_PATIENTS];
int assignedBed[MAX_PATIENTS];

float baseFee[MAX_PATIENTS];
float surcharge[MAX_PATIENTS];
float wardCost[MAX_PATIENTS];
float grossTotal[MAX_PATIENTS];
float discount[MAX_PATIENTS];
float finalAmount[MAX_PATIENTS];
float waitingTime[MAX_PATIENTS];

float calculateWaitingTime(int specialty) {
    return queueCount[specialty] * consultationTime[specialty];
}

float calculateSurcharge(float fee, int urgency) {
    if (urgency == 2) return fee * 0.20;
    if (urgency == 3) return fee * 0.50;
    return 0.0;
}

float calculateWardCost(int ward, int days) {
    if (ward == 0) return 0.0;
    return wardRate[ward] * days;
}

float calculateDiscount(float gross, int age) {
    if (age < 5 || age > 65) return gross * 0.15;
    return 0.0;
}

int allocateBed(int ward) {
    if (ward < 1 || ward > 4) return 0;
    for (int j = 0; j < wardCapacity[ward]; j++) {
        if (bedOccupancy[ward - 1][j] == 0) {
            bedOccupancy[ward - 1][j] = 1;
            return j + 1;
        }
    }
    return -1;
}

void savePatientRecord(int i) {
    FILE *fp = fopen("patient_records.txt", "a");
    if (fp == NULL) return;
    fprintf(fp, "%s,%s,%d,%.2f\n",
            patientName[i], specialtyName[selectedSpecialty[i]], patientAge[i], finalAmount[i]);
    fclose(fp);
}

void displayBill(int i) {
    printf("\n============================================\n");
    printf("       SMART HOSPITAL ADMISSION & BILL\n");
    printf("============================================\n");
    printf("Patient ID       : PAT-%04d\n", patientId[i]);
    printf("Patient Name     : %s\n", patientName[i]);
    printf("Age              : %d\n", patientAge[i]);
    printf("Specialty        : %s\n", specialtyName[selectedSpecialty[i]]);

    if (admitted[i] == 1 && assignedBed[i] > 0) {
        printf("Assigned Ward    : %s\n", wardName[selectedWard[i]]);
        printf("Bed Number       : %d\n", assignedBed[i]);
    } else {
        printf("Assigned Ward    : OPD\n");
    }

    printf("Urgency Level    : Level %d\n", urgencyLevel[i]);
    printf("--------------------------------------------\n");
    printf("Base Consultation Fee : LKR %.2f\n", baseFee[i]);
    printf("Emergency Surcharge   : LKR %.2f\n", surcharge[i]);
    printf("Ward Stay Cost        : LKR %.2f\n", wardCost[i]);
    printf("--------------------------------------------\n");
    printf("Gross Total Bill      : LKR %.2f\n", grossTotal[i]);
    printf("Age Subsidy Discount  : LKR %.2f\n", discount[i]);
    printf("--------------------------------------------\n");
    printf("Final Payable Amount  : LKR %.2f\n", finalAmount[i]);
    printf("Estimated Waiting Time: %.2f mins\n", waitingTime[i]);
    printf("============================================\n");
}

void registerPatient() {
    if (count >= MAX_PATIENTS) {
        printf("Patient limit reached!\n");
        return;
    }

    patientId[count] = 1001 + count;

    printf("\nEnter Patient Name: ");
    scanf(" %[^\n]", patientName[count]);

    printf("Enter Age: ");
    scanf("%d", &patientAge[count]);

    printf("Enter Urgency Level (1-Normal, 2-Urgent, 3-Critical): ");
    scanf("%d", &urgencyLevel[count]);

    printf("Enter Specialty ID (1-4): ");
    scanf("%d", &selectedSpecialty[count]);

    printf("Admitted to Ward? (1-Yes, 0-No): ");
    scanf("%d", &admitted[count]);

    if (admitted[count] == 1) {
        printf("Enter Ward ID (1-4): ");
        scanf("%d", &selectedWard[count]);

        printf("Enter Number of Days: ");
        scanf("%d", &admissionDays[count]);

        assignedBed[count] = allocateBed(selectedWard[count]);
    } else {
        selectedWard[count] = 0;
        admissionDays[count] = 0;
        assignedBed[count] = 0;
    }

    waitingTime[count] = calculateWaitingTime(selectedSpecialty[count]);
    queueCount[selectedSpecialty[count]]++;

    baseFee[count] = specialtyFee[selectedSpecialty[count]];
    surcharge[count] = calculateSurcharge(baseFee[count], urgencyLevel[count]);
    wardCost[count] = calculateWardCost(selectedWard[count], admissionDays[count]);

    grossTotal[count] = baseFee[count] + surcharge[count] + wardCost[count];
    discount[count] = calculateDiscount(grossTotal[count], patientAge[count]);
    finalAmount[count] = grossTotal[count] - discount[count];

    displayBill(count);
    savePatientRecord(count);
    count++;
}

void sortPatients(int n, int order[]) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (urgencyLevel[order[j]] > urgencyLevel[order[i]]) {
                temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }
}

void displayPriorityList(int n) {
    if (n == 0) {
        printf("No patients registered.\n");
        return;
    }

    int order[MAX_PATIENTS];
    for (int i = 0; i < n; i++) order[i] = i;

    sortPatients(n, order);

    printf("\n===== PATIENT PRIORITY LIST =====\n");
    for (int i = 0; i < n; i++) {
        printf("%s - Level %d\n", patientName[order[i]], urgencyLevel[order[i]]);
    }
}

void generateReports() {
    if (count == 0) {
        printf("No records available.\n");
        return;
    }

    int normal = 0, urgent = 0, critical = 0;
    float revenue = 0, totalDiscount = 0;
    int highest = 0;

    for (int i = 0; i < count; i++) {
        if (urgencyLevel[i] == 1) normal++;
        else if (urgencyLevel[i] == 2) urgent++;
        else if (urgencyLevel[i] == 3) critical++;

        revenue += finalAmount[i];
        totalDiscount += discount[i];

        if (finalAmount[i] > finalAmount[highest]) {
            highest = i;
        }
    }

    printf("\nHighest Paying Patient: %s\n", patientName[highest]);
    printf("Bill: LKR %.2f\n", finalAmount[highest]);
}

void displayBedStatus() {
    for (int i = 0; i < 4; i++) {
        int occupied = 0;
        for (int j = 0; j < wardCapacity[i + 1]; j++) {
            if (bedOccupancy[i][j] == 1) occupied++;
        }
        printf("%s : %.2f%%\n", wardName[i + 1], ((float)occupied / wardCapacity[i + 1]) * 100);
    }
}

void saveBeds() {
    FILE *fp = fopen("beds_status.txt", "w");
    if (fp == NULL) return;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < wardCapacity[i + 1]; j++) {
            fprintf(fp, "%d ", bedOccupancy[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

int main() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 20; j++) {
            bedOccupancy[i][j] = 0;
        }
    }

    int choice;
    do {
        printf("\n==============================\n");
        printf("      SMART HOSPITAL\n");
        printf("==============================\n");
        printf("1. Register Patient\n");
        printf("2. Display Patient Bill\n");
        printf("3. Display Priority Patients\n");
        printf("4. Generate Reports\n");
        printf("5. Display Bed Status\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerPatient();
                break;
            case 2:
                if (count > 0) displayBill(count - 1);
                else printf("No patients registered.\n");
                break;
            case 3:
                displayPriorityList(count);
                break;
            case 4:
                generateReports();
                break;
            case 5:
                displayBedStatus();
                break;
            case 6:
                saveBeds();
                printf("Thank you!\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 6);

    return 0;
}


