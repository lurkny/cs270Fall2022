 /** @mainpage 
   *  \htmlinclude "STRUCTS.html"
   */
/* CS270 
 *
 * Author: Your name here
 * Date:   2/12/2020
 */
#include<stdio.h>
#include <stdlib.h>
#include "struct.h"




int main(int argc, const char **argv)
{
  ClassRoster roster;
  int numS = 0;
  scanf("%d", &numS);
  roster.numStudents = numS;
  roster.students = (Student**) calloc(numS,sizeof(Student*));
  for(int i = 0; i < numS; i++){
	readStudentAndEnroll(&roster.students[i]);
}

  for(int j = 0; j < numS; j++){
	displayStudent(*roster.students[j]);
	free(roster.students[j]);
}
free(roster.students);
  return 0;
}
