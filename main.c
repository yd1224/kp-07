#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
double getInput(const char *prompt);
bool isScientificNotation(const char *input);
float findBisectionRoot(float (*fpr)(float, float), float a1, float a2, float eps, float y);
float findNewtonRoot(float (*fpr)(float, float), float a1, float a2, float eps, float y);
float func1(float x, float y);
float func2(float x, float y);
int main()
{
    int choice, method;
    float x, y, a1, a2, eps;
    float res;
    float (*funcs[])(float x, float y) = {func1, func2};
    int result_ans = 0;
    char ans[] = "yes";
    char ans1[4];
    while (result_ans == 0)
    {
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
        while (1)
        {
            method = getInput("\nWhich method do you want to use: \n\t 1:  Bisection \n\t 2:  Newton\nEnter your answer(\"1\" or \"2\"): ");
            if ((method != 1) && (method != 2))
            {
                printf("Please, choose method again.");
            }
            else
            {
                break;
            }
        }
        y = getInput("Enter y: ");
        if (method == 1)
        {
            do
            {
                a1 = getInput("Enter a1: ");
                a2 = getInput("Enter a2: ");
            } while ((funcs[choice - 1](a1, y) * funcs[choice - 1](a2, y)) >= 0);

            eps = getInput("Enter accuracy: ");

            res = findBisectionRoot(funcs[choice - 1], a1, a2, eps, y);
            printf("*********************\n");
            printf(" Bisection Method \n");
            printf("*********************\n");
            printf("Root is: %f\n", res);
        }
        else
        {
            a1 = getInput("Enter a1: ");
            a2 = getInput("Enter a2: ");
            eps = getInput("Enter accuracy: ");
            res = findNewtonRoot(funcs[choice - 1], a1, a2, eps, y);
            printf("*********************\n");
            printf(" Newton's Method \n");
            printf("*********************\n");
            printf("Root is: %f\n", res);
        }
        while (1)
        {
            printf("If you want to continue, please type \"yes\", if you do not - type \"no\":\n");
            scanf("%3s", ans1);
            int c;
            while ((c = getchar()) != '\n')
                ;
            if (strcmp(ans1, "yes") == 0 || strcmp(ans1, "no") == 0)
            {
                break;
            }
            else
            {
                printf("Invalid input.\n");
            }
        }

        result_ans = strcmp(ans, ans1);
        if (result_ans != 0)
        {
            break;
        }
    }
    return 0;
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
float findBisectionRoot(float (*fpr)(float, float), float a1, float a2, float eps, float y)
{
    float x;
    while (fabs(a1 - a2) > eps)
    {
        x = (a1 + a2) / 2.0;
        ((*fpr)(a1, y) * (*fpr)(x, y) > 0) ? (a1 = x) : (a2 = x);
    }

    return x;
}
float findNewtonRoot(float (*fpr)(float, float), float a, float b, float eps, float y)
{
    float x1 = (*fpr)(b, y);
    float delta = 1.0;
    do
    {
        float derivative = ((*fpr)(x1 + eps, y) - (*fpr)(x1, y)) / eps;
        if (derivative == 0)
        {
            printf("*********************\n");
            printf(" Mathematical Error \n");
            printf("*********************\n");
            return -1;
        }
        delta = (*fpr)(x1, y) / derivative;
        x1 = x1 - delta;
    } while (fabs(delta) > eps);
    return x1;
}
float func1(float x, float y)
{
    return (cos(y / x) - 2 * sin(1.0 / x) + 1.0 / x);
}
float func2(float x, float y)
{
    return (sin(log(x)) - cos(log(x)) + y * log(x));
}
