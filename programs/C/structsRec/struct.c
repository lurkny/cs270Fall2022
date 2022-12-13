/* CS270 
 *
 * Author: Your name here
 * Date:   2/12/2020
 */

#include "struct.h"
#include<stdio.h>
#include<stdlib.h>
/********** FUNCTION DEFINITIONS **********************************************/

void readStudentAndEnroll(Student **slot)
{
Student* stu = malloc(sizeof(Student));
scanf("%s", stu->firstName);
scanf("%f", &stu->qualityPoints);
scanf("%d", &stu->numCredits);
*slot = stu;
}

void displayStudent(Student s)
{
float gpa = s.qualityPoints / s.numCredits;
printf("%s, %.2f\n", s.firstName, gpa);

}
