#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
double getInput(const char *prompt);
bool isScientificNotation(const char *input);
float findRoot(float (*fpr)(float, float), float a1, float a2, float eps, float y);
float func1(float x, float y);
float func2(float x, float y);
void getInitialGuesses(float y, float a1, float a2, float (*fpr)(float, float));
int main()
{
    int choice;
    float y, a1, a2, eps;
    float res;
    while (1)
    {
        printf("Choose equation: \n\t1:  cos(y/x)-2sin(1/x)+1/x = 0 \n\t2:  sin(lnx)-cos(lnx)+y*lnx = 0\n");
        choice = getInput("Enter your answer(\"1\" or \"2\"): ");
        if ((choice != 1) && (choice != 2))
        {
            printf("Please, choose equation again.\n");
        }
        else
        {
            break;
        }
    }
    y = getInput("Enter y: ");
    getInitialGuesses(y, a1, a2, choice == 1 ? func1 : func2);

    eps = getInput("Enter accuracy: ");

    res = choice == 1 ? findRoot(func1, a1, a2, eps, y) : findRoot(func2, a1, a2, eps, y);

    printf("\tx = %f\n", res);
}
double getInput(const char *prompt)
{
    const int SIZE = 100;
    char input[SIZE];
    double number;

    do
    {
        printf("%s", prompt);
        scanf("%s", input);

        int invalidInput = 0;
        for (int i = 0; input[i]; i++)
        {
            if (isdigit(input[i]) == 0 && input[i] != '.' && input[i] != '-' && !isScientificNotation(input))
            {
                printf("\nYour input is invalid\n");
                invalidInput = 1;
                break;
            }
        }

        if (!invalidInput)
        {
            number = atof(input);
            break;
        }
    } while (1);

    return number;
}
bool isScientificNotation(const char *input)
{
    int len = strlen(input);
    int eCount = 0;
    int digitsBeforeE = 0;
    int digitsAfterE = 0;

    for (int i = 0; i < len; i++)
    {
        char c = input[i];
        if (c == 'e' || c == 'E')
        {
            eCount++;
        }
        else if (isdigit(c) && eCount == 0)
        {
            digitsBeforeE++;
        }
        else if (isdigit(c) && eCount == 1)
        {
            digitsAfterE++;
        }
    }

    return (eCount == 1) && (digitsBeforeE > 0) && (digitsAfterE > 0);
}
float findRoot(float (*fpr)(float, float), float a1, float a2, float eps, float y)
{
    float x;
    while (fabs(a1 - a2) > eps)
    {
        x = (a1 + a2) / 2.0;
        ((*fpr)(a1, y) * (*fpr)(x, y) > 0) ? (a1 = x) : (a2 = x);
    }

    return x;
}

float func1(float x, float y)
{
    return (cos(y / x) - 2 * sin(1.0 / x) + 1.0 / x);
}
float func2(float x, float y)
{
    return (sin(log(x)) - cos(log(x)) + y * log(x));
}

void getInitialGuesses(float y, float a1, float a2, float (*fpr)(float, float))
{
    do
    {
        a1 = getInput("Enter a1: ");
        a2 = getInput("Enter a2: ");
    } while (((*fpr)(a1, y) * (*fpr)(a2, y)) >= 0);
}
