/******************
Name: Aviv Sayer
ID: 326552304
Assignment: ex2
*******************/

#include <stdio.h>
#define TRUE 1

int main() {
    // pre-declare all vars to avoid redefs
    int option, num, size, reversed, cheer, smile;
    char eyes, nose, mouth;

    while (TRUE) {
        // get option
        printf("Choose an option:\n"
               "\t1. Happy Face\n"
               "\t2. Balanced Number\n"
               "\t3. Generous Number\n"
               "\t4. Circle Of Joy\n"
               "\t5. Happy Numbers\n"
               "\t6. Festival Of Laughter\n"
               "\t7. Exit\n");
        scanf(" %d", &option);

        switch (option) {
            // Case 1: Draw Happy Face with given symbols for eyes, nose and mouse
            /* Example:
             * n = 3:
             * 0   0
             *   o
             * \___/
             */
            case 1:
                // get the eyes, nose, mouth symbols
                printf("Enter symbols for the eyes, nose, and mouth:\n");
                scanf(" %c %c %c", &eyes, &nose, &mouth);

                // get the face's size
                printf("Enter face size:\n");
                scanf(" %d", &size);

                // if the face's size is illegal (even or non-positive) get it again
                while (!(size > 0 && size % 2)) {
                    printf("The face's size must be an odd and positive number, please try again:\n");
                    scanf(" %d", &size);
                }

                // print the face
                printf("%c", eyes); // eyes
                for (int i = 0; i < size; ++i)
                    printf(" ");
                printf("%c\n", eyes);
                for (int i = 0; i < size / 2 + 1; ++i) // nose
                    printf(" ");
                printf("%c\n", nose);
                printf("\\"); // mouth
                for (int i = 0; i < size; ++i)
                    printf("%c", mouth);
                printf("/\n");
                break;

            // Case 2: determine whether the sum of all digits to the left of the middle digit(s)
            // and the sum of all digits to the right of the middle digit(s) are equal
            /* Examples:
             * Balanced: 1533, 450810, 99
             * Not blanced: 1552, 34
             * Please notice: the number has to be bigger than 0.
             */
            case 2:
                // get the number
                printf("Enter a number:\n");
                scanf(" %d", &num);

                // if the number is illegal (non-positive) get it again
                while (num <= 0) {
                    printf("Only positive number is allowed, please try again:\n");
                    scanf(" %d", &num);
                }

                // check if number is balanced
                int sum = 0, len = 0;
                for (int tmp = num; // get the number of digits in num and the sum of all digits
                     tmp != 0; tmp /= 10, ++len);
                for (int i = 0; i < len / 2; sum += num % 10, num /= 10, ++i); // get the sum of the first half
                if (len % 2) // skip the middle digit (if exists)
                    num /= 10;
                for (; num != 0; sum -= num % // subtract the second half's sum to the first half's sum
                                        10, num /= 10);

                // print output
                printf(sum // if sum = firstHalf-secondHalf = 0, number is balanced
                       ? "This number isn't balanced and destroys harmony.\n"
                       : "This number is balanced and brings harmony!\n");
                break;

            // Case 3: determine whether the sum of the proper divisors (odd and integer) is greater than the number itself
            /* Examples:
             * Abundant: 12, 20, 24
             * Not Abundant: 3, 7, 10
             * Please notice: the number has to be bigger than 0.
             */
            case 3:
                // get the number
                printf("Enter a number:\n");
                scanf(" %d", &num);

                // if the number is illegal (non-positive) get it again
                while (num <= 0) {
                    printf("Only positive number is allowed, please try again:\n");
                    scanf(" %d", &num);
                }

                // check if number is abundant
                sum = num != 1; // skips checking 1 because it is a divisor of all numbers
                for (int i = 2; i < num; ++i) // sum up all divisors
                    if (!(num % i))
                        sum += i;

                // print output
                printf(sum > num // sum > num <==> number is abundant
                       ? "This number is generous!\n"
                       : "This number does not share.\n");
                break;

            // Case 4: determine whether a number is a prime.
            /* Examples:
             * This one brings joy: 3, 5, 11
             * This one does not bring joy: 15, 8, 99
             * Please notice: the number has to be bigger than 0.
             */
            case 4:
                // get the number
                printf("Enter a number:\n");
                scanf(" %d", &num);

                // if the number is illegal (non-positive) get it again
                while (num <= 0) {
                    printf("Only positive number is allowed, please try again:\n");
                    scanf(" %d", &num);
                }

                // generating the reversed number of num
                reversed = 0;
                for (int tmp = num; tmp != 0; reversed *= 10, reversed += tmp % 10, tmp /= 10);

                // checking if prime
                /* some math:
                 * you dont need to check above the sqrt of num.
                 * let n > sqrt(num) natural number and divisor of num
                 * n is a divisor of num some natural number m exists so n*m=num
                 * num = n*m > sqrt(num)*m => num > sqrt(num)*m
                 * num/sqrt(num) > m => sqrt(num) > m
                 *
                 * so we have checked the number m before checking n,
                 * meaning the loop has been stopped before checking n,
                 * because we knew before that num is not prime.
                 * Q.E.D ■
                 *
                 * further more, every even number is dividable by 2,
                 * so instead of checking every even number we can check if
                 * the number is divided by 2 and then check just odd numbers
                 */
                if (!(num % 2) || num == 1)
                    num = 0; // 0 -> num is not prime. breaks loop because 3 * 3 > 0
                for (int i = 3; i * i <= num; i += 2)
                    if (!(num % i))
                        num = 0; // 0 -> num is not prime. breaks loop because i * i > 0 (i >= 3)
                if (!(reversed % 2) || reversed == 1)
                    reversed = 0; // 0 -> num is not prime. breaks loop because 3 * 3 > 0
                for (int i = 3; i * i <= reversed; i += 2)
                    if (!(reversed % i))
                        reversed = 0; // 0 -> num is not prime. breaks loop because i * i > 0 (i >= 3)

                // print output: reversed != 0 && num != 0 => number and reversed are prime (changed to 0 if not prime)
                printf(num && reversed
                       ? "This number completes the circle of joy!\n"
                       : "The circle remains incomplete.\n");
                break;

            // Happy numbers: Print all the happy numbers between 1 to the given number.
            // Happy number is a number which eventually reaches 1 when replaced by the sum of the square of each digit
            /* Examples:
             * Happy :) : 7, 10
             * Not Happy :( : 5, 9
             * Please notice: the number has to be bigger than 0.
             */
            case 5:
                // get the number
                printf("Enter a number:\n");
                scanf(" %d", &num);

                // if the number is illegal (non-positive) get it again
                while (num <= 0) {
                    printf("Only positive number is allowed, please try again:\n");
                    scanf(" %d", &num);
                }

                // check if every number(1 <= number <= num) is happy and print them
                /* some math:
                 * let F(n) be the function that sums up the 2nd power of every digit in a natural number n.
                 * let Fi(n) be the ith iteration of F over n
                 * we know that if n is happy exists a number i so Fi(n) = 1
                 * we know that if n is unhappy nexists a number i so Fi(n) = 1
                 * by induction it can be proved that for every number n greater or equal to 100 F(n)<n,
                 * meaning that foreach n from infinity to 100 the sequence a_i = Fi(n) is descending until Fi(n)<100.
                 * with all of this knowledge we can say that if n is happy Fi(n) --> 1,
                 * and if n is unhappy when n --> infinity there is a closed constant size circuit of Fi(n)
                 * such as exists j natural so Fi(n)=F(i+j)(n)
                 * we can find this circuit, and it is:
                 * 4, 16, 37, 58, 89, 145, 42, 20, 4, ...
                 * so simply we can check if n had come to 1 or 4 and determent if the number is happy or unhappy
                 */
                printf("Between 1 and %d only these numbers bring happiness:", num);
                for (int i = 1; i <= num; ++i) {
                    sum = i;
                    while (sum != 1 && sum != 4) {
                        int tmp = sum;
                        sum = 0;
                        for (; tmp != 0; sum += (tmp % 10) * (tmp % 10), tmp /= 10);
                    }
                    if (sum == 1)
                        printf(" %d", i); // print if happy
                }

                printf("\n"); // endl linebreak

                break;

            // Festival of Laughter: Prints all the numbers between 1 the given number:
            // and replace with "Smile!" every number that divided by the given smile number
            // and replace with "Cheer!" every number that divided by the given cheer number
            // and replace with "Festival!" every number that divided by both of them
            /* Example:
             * 6, smile: 2, cheer: 3 : 1, Smile!, Cheer!, Smile!, 5, Festival!
             */
            case 6:
                // get the festival numbers
                printf("Enter a smile and cheer number:\n");
                int success = scanf(" smile: %d , cheer: %d", &smile, &cheer);
                scanf("%*[^\n]"); // clear stdin

                // if the numbers are illegal (non-positive or equal) get it again
                while (smile == cheer || smile <= 0 || cheer <= 0 || success != 2) {
                    printf("Only 2 different positive numbers in the given "
                           "format are allowed for the festival, please try again:\n");
                    success = scanf(" smile: %d , cheer: %d", &smile, &cheer);
                    scanf("%*[^\n]"); // clear stdin
                }

                // get the maximum number
                printf("Enter maximum number for the festival:\n");
                scanf(" %d", &num);

                // if the number is illegal (non-positive) get it again
                while (num <= 0) {
                    printf("Only positive maximum number is allowed, please try again:\n");
                    scanf(" %d", &num);
                    scanf("%*[^\n]"); // clear stdin
                }

                // print output
                for (int i = 1; i <= num; ++i) {
                    if (!(i % cheer || i % smile))
                        printf("Festival!");
                    else if (!(i % cheer))
                        printf("Cheer!");
                    else if (!(i % smile))
                        printf("Smile!");
                    else printf("%d", i);
                    printf("\n");
                }

                break;

            case 7:
                printf("Thank you for your journey through Numeria!\n");
                return 0;

            default:
                printf("This option is not available, please try again.\n");
        }
    }
}
