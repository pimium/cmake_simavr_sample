/*****************************************************************************
 *                                                                           *
 *  uCUnit - A unit testing framework for microcontrollers                   *
 *                                                                           *
 *  (C) 2007 - 2008 Sven Stefan Krauss                                       *
 *                  https://www.ucunit.org                                   *
 *                                                                           *
 *  File        : Testsuite.h                                                *
 *  Description : Sample testsuite                                           *
 *  Author      : Sven Stefan Krauss                                         *
 *  Contact     : www.ucunit.org                                             *
 *                                                                           *
 *****************************************************************************/

/*
 * This file is part of ucUnit.
 *
 * You can redistribute and/or modify it under the terms of the
 * Common Public License as published by IBM Corporation; either
 * version 1.0 of the License, or (at your option) any later version.
 *
 * uCUnit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Common Public License for more details.
 *
 * You should have received a copy of the Common Public License
 * along with uCUnit.
 *
 * It may also be available at the following URL:
 *       http://www.opensource.org/licenses/cpl1.0.txt
 *
 * If you cannot obtain a copy of the License, please contact the
 * author.
 */

#include "second_testsuite.h"
#include "System.h"
#include "uCUnit-v1.0.h"
// #include "ProductionCode.h"

static void Test_ChecklistDemo(void) {
  int a = 0;
  int b = 0;
  int c = 0;

  UCUNIT_TestcaseBegin("DEMO:Checklists");

  /* Check if calculation works */
  a = 10;
  b = -20;
  c = a + b;

  UCUNIT_ChecklistBegin(UCUNIT_ACTION_WARNING);
  UCUNIT_CheckIsEqual(-10, c);        /* Pass */
  UCUNIT_CheckIsInRange(a, 0, 10);    /* Pass */
  UCUNIT_CheckIsInRange(a, 10, 20);   /* Pass */
  UCUNIT_CheckIsInRange(a - 2, 0, 9); /* Fail */
  UCUNIT_ChecklistEnd();

  UCUNIT_TestcaseEnd(); /* Fail */
}

void test_tick_init(void) {
  tick_init();
  /* All of these should pass */
  // UCUNIT_CheckIsEqual(0, FindFunction_WhichIsBroken(78));
  // UCUNIT_CheckIsEqual(1, FindFunction_WhichIsBroken(2));
  // UCUNIT_CheckIsEqual(0, FindFunction_WhichIsBroken(33));
  // UCUNIT_CheckIsEqual(1, FindFunction_WhichIsBroken(999));
  // UCUNIT_CheckIsEqual(0, FindFunction_WhichIsBroken(-1));
  UCUNIT_TestcaseEnd(); /* Fail */
}

void Testsuite_RunTests2(void) {
  Test_ChecklistDemo();
  // test_FindFunction_WhichIsBroken_ShouldReturnZeroIfItemIsNotInList_WhichWorksEvenInOurBrokenCode();

  UCUNIT_WriteSummary();
}

void Testsuite_RunTests(void) {
  // Test_ChecklistDemo();
  test_tick_init();

  UCUNIT_WriteSummary();
}

int main(void) {
  UCUNIT_Init();
  UCUNIT_WriteString("\n**************************************");
  UCUNIT_WriteString("\nName:     ");
  UCUNIT_WriteString("uCUnit demo application");
  UCUNIT_WriteString("\nCompiled: ");
  UCUNIT_WriteString(__DATE__);
  UCUNIT_WriteString("\nTime:     ");
  UCUNIT_WriteString(__TIME__);
  UCUNIT_WriteString("\nVersion:  ");
  UCUNIT_WriteString(UCUNIT_VERSION);
  UCUNIT_WriteString("\n**************************************");
  Testsuite_RunTests();
  // Testsuite_RunTests2();
  UCUNIT_Shutdown();

  return 0;
}
