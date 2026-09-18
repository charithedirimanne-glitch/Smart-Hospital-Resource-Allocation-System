


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

    return 0;
}

