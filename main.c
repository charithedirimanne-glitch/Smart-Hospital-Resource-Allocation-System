


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

    return 0;
}

