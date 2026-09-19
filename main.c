


#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

int main()
{
    printf("====================================\n");
    printf("     SMART HOSPITAL SYSTEM\n");
    printf("====================================\n");

    const char *specialtyName[] = {
    "",
    "General Practice (OPD)",
    "Paediatrics",
    "Cardiology",
    "Neurology"
};

const float specialtyFee[] = {
    0,
    1500.00,
    2500.00,
    4500.00,
    5000.00
};

const int consultationTime[] = {
    0,
    15,
    20,
    30,
    30
};

const int dailyPatientCap[] = {
    0,
    30,
    20,
    12,
    10
};

const char *wardName[] = {
    "",
    "General Ward",
    "Paediatric Ward",
    "Surgical Ward",
    "ICU"
};

const float wardRate[] = {
    0,
    3000.00,
    6000.00,
    12000.00,
    25000.00
};

const int wardCapacity[] = {
    0,
    20,
    10,
    10,
    5
};
int bedOccupancy[4][20];
int i, j;

for(i = 0; i < 4; i++)
{
    for(j = 0; j < 20; j++)
    {
        bedOccupancy[i][j] = 0;
    }
}
int patientId[MAX_PATIENTS];
char patientName[MAX_PATIENTS][50];
int patientAge[MAX_PATIENTS];
int urgencyLevel[MAX_PATIENTS];

int selectedSpecialty[MAX_PATIENTS];

int admitted[MAX_PATIENTS];
int selectedWard[MAX_PATIENTS];
int admissionDays[MAX_PATIENTS];

float baseFee[MAX_PATIENTS];
float surcharge[MAX_PATIENTS];
float wardCost[MAX_PATIENTS];
float grossTotal[MAX_PATIENTS];
float discount[MAX_PATIENTS];
float finalAmount[MAX_PATIENTS];

float waitingTime[MAX_PATIENTS];

int assignedBed[MAX_PATIENTS];

printf("Enter Patient Name: ");
scanf(" %[^\n]", patientName[count]);

printf("Enter Age: ");
scanf("%d", &patientAge[count]);

printf("Enter Urgency Level (1-Normal, 2-Urgent, 3-Critical): ");
scanf("%d", &urgencyLevel[count]);

printf("Enter Specialty ID (1-4): ");
scanf("%d", &selectedSpecialty[count]);

printf("Admitted to Ward? (1-Yes, 0-No): ");
scanf("%d", &admitted[count]);

    return 0;
}

