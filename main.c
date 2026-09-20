


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

if(admitted[count] == 1)
{
    printf("Enter Ward ID (1-4): ");
    scanf("%d", &selectedWard[count]);

    printf("Enter Number of Days: ");
    scanf("%d", &admissionDays[count]);
}
else
{
    selectedWard[count] = 0;
    admissionDays[count] = 0;
}
int queueCount[5] = {0};
float calculateWaitingTime(int specialty, int queueCount[])
{
    return queueCount[specialty] * consultationTime[specialty];
    waitingTime[count] =
    calculateWaitingTime(selectedSpecialty[count], queueCount);

queueCount[selectedSpecialty[count]]++;
}
float calculateSurcharge(float fee, int urgency)
{
    if(urgency == 1)
        return 0;

    else if(urgency == 2)
        return fee * 0.20;

    else if(urgency == 3)
        return fee * 0.50;

    return 0;

    float calculateWardCost(int ward, int days)
{
    if(ward == 0)
        return 0;

    return wardRate[ward] * days;
    grossTotal[count] =
    baseFee[count]
    + surcharge[count]
    + wardCost[count];
}
}
float calculateDiscount(float gross, int age)
{
    if(age < 5 || age > 65)
        return gross * 0.15;

    return 0;
}
finalAmount[count] =
    grossTotal[count] - discount[count];

    int allocateBed(int ward, int bedOccupancy[][20])
{
    int j;

    for(j = 0; j < wardCapacity[ward]; j++)
    {
        if(bedOccupancy[ward - 1][j] == 0)
        {
            bedOccupancy[ward - 1][j] = 1;
            return j + 1;
        }
    }

    return -1;
}

void displayBill(int i)
{
    printf("\n============================================\n");
    printf("       SMART HOSPITAL ADMISSION & BILL\n");
    printf("============================================\n");

    printf("Patient ID       : PAT-%04d\n", patientId[i]);
    printf("Patient Name     : %s\n", patientName[i]);
    printf("Age              : %d\n", patientAge[i]);

    printf("Specialty        : %s\n",
           specialtyName[selectedSpecialty[i]]);

    if(admitted[i] == 1)
    {
        printf("Assigned Ward    : %s\n",
               wardName[selectedWard[i]]);

        printf("Bed Number       : %d\n",
               assignedBed[i]);
    }
    else
    {
        printf("Assigned Ward    : OPD\n");
    }

    printf("Urgency Level    : Level %d\n",
           urgencyLevel[i]);

    printf("--------------------------------------------\n");

    printf("Base Consultation Fee : LKR %.2f\n",
           baseFee[i]);

    printf("Emergency Surcharge   : LKR %.2f\n",
           surcharge[i]);

    printf("Ward Stay Cost        : LKR %.2f\n",
           wardCost[i]);

    printf("--------------------------------------------\n");

    printf("Gross Total Bill      : LKR %.2f\n",
           grossTotal[i]);

    printf("Age Subsidy Discount  : LKR %.2f\n",
           discount[i]);

    printf("--------------------------------------------\n");

    printf("Final Payable Amount  : LKR %.2f\n",
           finalAmount[i]);

    printf("Estimated Waiting Time: %.2f mins\n",
           waitingTime[i]);

    printf("============================================\n");
}
void sortPatients(int n, int order[])
{
    int i, j, temp;

    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(urgencyLevel[order[j]] >
               urgencyLevel[order[i]])
            {
                temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }
}
void displayPriorityList(int n)
{
    int order[MAX_PATIENTS];
    int i;

    for(i = 0; i < n; i++)
        order[i] = i;

    sortPatients(n, order);

    printf("\n===== PATIENT PRIORITY LIST =====\n");

    for(i = 0; i < n; i++)
    {
        printf("%s - Level %d\n",
               patientName[order[i]],
               urgencyLevel[order[i]]);
    }
}
int normal = 0;
int urgent = 0;
int critical = 0;

for(i = 0; i < count; i++)
{
    if(urgencyLevel[i] == 1)
        normal++;

    else if(urgencyLevel[i] == 2)
        urgent++;

    else if(urgencyLevel[i] == 3)
        critical++;
}
float revenue = 0;
float totalDiscount = 0;

for(i = 0; i < count; i++)
{
    revenue += finalAmount[i];
    totalDiscount += discount[i];
}
int highest = 0;

for(i = 1; i < count; i++)
{
    if(finalAmount[i] > finalAmount[highest])
        highest = i;
}
printf("Highest Paying Patient: %s\n",
       patientName[highest]);

printf("Bill: LKR %.2f\n",
       finalAmount[highest]);


    return 0;
}

