#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
double getInput(const char *prompt);
bool isScientificNotation(const char *input);
float findRoot(float (*fpr)(float), float l, float h, float eps);
float funcCos(float x);
float funcSin(float x);
int main()
{
    int choice;
    float y, a1, a2, eps;
    while (1)
    {
        printf("Choose equation: \n\t1:  cos(t/x)-2sin(1/x)+1/x = 0 \n\t2:  sin(lnx)-cos(lnx)+t*lnx = 0\n");
        choice = getInput("Enter your answer(\"1\" or \"2\"): ");
        if ((choice != 1) && (choice != 2))
        {
            printf("Please, choose equation again.\n");
        }
        else
        {
            break;
        }
        y = getInput("Enter y: ");
        a1 = getInput("Enter a1: ");
        a2 = getInput("Enter a2: ");
        eps = getInput("Enter accuracy: ");
    }

    findRoot(float (*fpr)(float), a1, a2, eps);
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
float findRoot(float (*fpr)(float), float l, float h, float eps)
{
    float x;
    while (fabs(h - l) > eps)
    {
        x = (l + h) / 2.0;
        ((*fpr)(l) * (*fpr)(x) > 0) ? (l = x) : (h = x);
    }
    return x;
}
float funcCos(float x)
{
    return (cos(2.0 / x) - 2 * sin(1.0 / x) + 1.0 / x);
}
float funcSin(float x)
{
    return (sin(log(x)) - cos(log(x)) + 2 * log(x));
}