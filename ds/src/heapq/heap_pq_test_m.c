/*OL76 dlist
developer name: Matan Albilia
reviewer: Shachar
date: 20/10
status: sent
*/

#include <stdio.h> /*printf*/
#include "pq.h"

#define UNUSED (void)

#define TITLE(X) (printf("\033[1;34m%s\n\033[0m",X))

#define TEST_INT(res,exp) (*(int *)res == *(int*)exp ? 0 : printf("ERROR, LINE:%d\nres = %d,exp = %d\n",__LINE__,*(int *)res, *(int *)exp))



void TestCreate();
void TestEnque();
void TestDeque();
void TestSize();
void TestIsEmpty();
void TestAppend();
void TestErase();

int main()
{
	TestCreate();
	TestEnque();
	TestDeque();
	TestIsEmpty();
	TestSize();
	TestAppend();
	TestErase();

	return 0;
}

int IsBeforeInt(void *data1, void *data2, void *param)
{
	UNUSED param;
	return *(int *)data1 > *(int *)data2;
}

int IsMatchInt(void *data, void *param)
{
	return *(int *)data == *(int *)param;
}

void TestCreate()
{
	pq_t *pque = PQCreate(IsBeforeInt, NULL);
	PQDestroy(pque);
}

void TestEnque()
{
	pq_t *pque = PQCreate(IsBeforeInt, NULL);
	int data0 = 0;
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;

	TITLE("TestEnque");

	/*enque to empty list*/
	PQEnqueue(pque, &data2);
	TEST_INT(PQPeek(pque), &data2);

	/*enque data with bigger priority*/
	PQEnqueue(pque, &data1);
	TEST_INT(PQPeek(pque), &data1);

	/*enque data with smaller priority*/
	PQEnqueue(pque, &data3);
	TEST_INT(PQPeek(pque), &data1);
	PQEnqueue(pque, &data4);
	TEST_INT(PQPeek(pque), &data1);

	/*enque data with bigger priority*/
	PQEnqueue(pque, &data0);
	TEST_INT(PQPeek(pque), &data0);

	PQDestroy(pque);
}

void TestDeque()
{
	pq_t *pque = PQCreate(IsBeforeInt, NULL);
	int data0 = 0;
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;

	TITLE("TestDeque");

	PQEnqueue(pque, &data2);
	PQEnqueue(pque, &data1);
	PQEnqueue(pque, &data4);
	PQEnqueue(pque, &data3);
	/*exp list 1 - 2 - 3 - 4*/

	PQDequeue(pque);
	/*exp list 2 - 3 - 4*/
	TEST_INT(PQPeek(pque), &data2);

	PQDequeue(pque);
	PQDequeue(pque);

	/*exp list 4*/
	
	TEST_INT(PQPeek(pque), &data4);

	PQEnqueue(pque, &data0);
	PQDequeue(pque);
	TEST_INT(PQPeek(pque), &data4);

	PQDestroy(pque);
}

void TestIsEmpty()
{
	pq_t *pque = PQCreate(IsBeforeInt, NULL);
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;

	int res = 0;
	int exp = 0;

	TITLE("TestIsEmpty");
	res = PQIsEmpty(pque);
	exp = 1;

	TEST_INT(&res,&exp);

	PQEnqueue(pque, &data2);

	res = PQIsEmpty(pque);
	exp = 0;

	TEST_INT(&res,&exp);

	PQEnqueue(pque, &data1);
	PQEnqueue(pque, &data4);
	PQEnqueue(pque, &data3);

	res = PQIsEmpty(pque);
	exp = 0;

	TEST_INT(&res,&exp);

	PQDequeue(pque);
	PQDequeue(pque);
	PQDequeue(pque);
	PQDequeue(pque);

	res = PQIsEmpty(pque);
	exp = 1;

	TEST_INT(&res,&exp);

	PQDestroy(pque);

}

void TestSize()
{
	pq_t *pque = PQCreate(IsBeforeInt, NULL);
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;

	size_t res = 0;
	size_t exp = 0;

	TITLE("TestSize");

	res = PQCount(pque);

	TEST_INT(&res,&exp);

	PQEnqueue(pque, &data2);
	res = PQCount(pque);
	exp = 1;

	TEST_INT(&res,&exp);

	PQEnqueue(pque, &data1);
	PQEnqueue(pque, &data4);
	PQEnqueue(pque, &data3);

	res = PQCount(pque);
	exp = 4;

	TEST_INT(&res,&exp);

	PQDequeue(pque);
	PQDequeue(pque);
	PQDequeue(pque);
	PQDequeue(pque);

	res = PQCount(pque);
	exp = 0;

	TEST_INT(&res,&exp);

	PQDestroy(pque);
}

void TestAppend()
{
	/*case 1*/
	pq_t *pque1 = PQCreate(IsBeforeInt, NULL);
	pq_t *pque2 = PQCreate(IsBeforeInt, NULL);

	int pq1_data1 = 1;
	int pq1_data2 = 2;
	int pq1_data3 = 3;
	int pq2_data1 = 4;
	int pq2_data2 = 5;
	int pq2_data3 = 6;
	int exp1[] = {1, 2, 3, 4, 5, 6};

	/*case 2*/
	pq_t *pque3 = PQCreate(IsBeforeInt, NULL);
	pq_t *pque4 = PQCreate(IsBeforeInt, NULL);

	int pq3_data1 = 1;
	int pq3_data2 = 5;
	int pq3_data3 = 6;
	int pq4_data1 = 2;
	int pq4_data2 = 3;
	int pq4_data3 = 4;
	int exp2[] = {1, 2, 3, 4, 5, 6};

	/*case 3*/
	pq_t *pque5 = PQCreate(IsBeforeInt, NULL);
	pq_t *pque6 = PQCreate(IsBeforeInt, NULL);

	int pq5_data1 = 4;
	int pq5_data2 = 5;
	int pq5_data3 = 6;
	int pq6_data1 = 1;
	int pq6_data2 = 2;
	int pq6_data3 = 3;
	int exp3[] = {1, 2, 3, 4, 5, 6};

	/*case 4*/
	pq_t *pque7 = PQCreate(IsBeforeInt, NULL);
	pq_t *pque8 = PQCreate(IsBeforeInt, NULL);

	int pq7_data1 = 1;
	int pq7_data2 = 1;
	int pq7_data3 = 1;
	int pq7_data4 = 3;
	int pq7_data5 = 3;
	int pq7_data6 = 3;
	int pq8_data1 = 2;
	int pq8_data2 = 2;
	int pq8_data3 = 2;
	int exp4[] = {1, 1, 1, 2, 2, 2, 3, 3, 3};

	/*case 5 dest empty*/
	pq_t *pque9 = PQCreate(IsBeforeInt, NULL);
	pq_t *pque10 = PQCreate(IsBeforeInt, NULL);


	int pq10_data1 = 1;
	int pq10_data2 = 2;
	int pq10_data3 = 3;
	int exp5[] = {1, 2, 3};

	/*case 6 src empty*/
	pq_t *pque11 = PQCreate(IsBeforeInt, NULL);
	pq_t *pque12 = PQCreate(IsBeforeInt, NULL);

	int pq11_data1 = 1;
	int pq11_data2 = 2;
	int pq11_data3 = 3;

	int exp6[] = {1, 2, 3};

	size_t i = 0;

	TITLE("TestAppend");

	/*case 1*/
	PQEnqueue(pque1, &pq1_data1);
	PQEnqueue(pque1, &pq1_data2);
	PQEnqueue(pque1, &pq1_data3);
	/*1 - 2 - 3*/

	PQEnqueue(pque2, &pq2_data1);
	PQEnqueue(pque2, &pq2_data2);
	PQEnqueue(pque2, &pq2_data3);
	/*4 - 5 - 6*/

	/* PQAppend(pque1, pque2); */

	/* 1 - 2 - 3 - 4 - 5 - 6 */

	puts("test1");

	for (i = 0 ; i < sizeof(exp1)/sizeof(int) ; ++i)
	{
		TEST_INT(PQPeek(pque1), &exp1[i]);
		PQDequeue(pque1);
	}

	/*end case 1*/

	/*case 2*/
	PQEnqueue(pque3, &pq3_data1);
	PQEnqueue(pque3, &pq3_data2);
	PQEnqueue(pque3, &pq3_data3);
	/*1 - 5 - 6*/

	PQEnqueue(pque4, &pq4_data1);
	PQEnqueue(pque4, &pq4_data2);
	PQEnqueue(pque4, &pq4_data3);
	/*2 - 3 - 4*/

	puts("test2");

	/* PQAppend(pque3, pque4);
 */
	for (i = 0 ; i < sizeof(exp2)/sizeof(int) ; ++i)
	{
		TEST_INT(PQPeek(pque3), &exp2[i]);
		PQDequeue(pque3);
	}


	/*case 3*/
	PQEnqueue(pque5, &pq5_data1);
	PQEnqueue(pque5, &pq5_data2);
	PQEnqueue(pque5, &pq5_data3);
	/*1 - 5 - 6*/

	PQEnqueue(pque6, &pq6_data1);
	PQEnqueue(pque6, &pq6_data2);
	PQEnqueue(pque6, &pq6_data3);
	/*2 - 3 - 4*/

	/* PQAppend(pque5, pque6);
 */
	puts("test3");

	for (i = 0 ; i < sizeof(exp3)/sizeof(int) ; ++i)
	{
		TEST_INT(PQPeek(pque5), &exp3[i]);
		PQDequeue(pque5);
	}

	/*case 4*/
	PQEnqueue(pque7, &pq7_data1);
	PQEnqueue(pque7, &pq7_data2);
	PQEnqueue(pque7, &pq7_data3);
	PQEnqueue(pque7, &pq7_data4);
	PQEnqueue(pque7, &pq7_data5);
	PQEnqueue(pque7, &pq7_data6);
	/*1 - 1 - 1 - 3 - 3 - 3*/

	PQEnqueue(pque8, &pq8_data1);
	PQEnqueue(pque8, &pq8_data2);
	PQEnqueue(pque8, &pq8_data3);
	/*2 - 2 - 2 */

	/* PQAppend(pque7, pque8); */

	/*1 - 1 - 1 -2 - 2 - 2 - 3 - 3 - 3*/

	puts("test4");

	for (i = 0 ; i < sizeof(exp4)/sizeof(int) ; ++i)
	{
		TEST_INT(PQPeek(pque7), &exp4[i]);
		PQDequeue(pque7);
	}

	/*case 5*/
	/*dest empty*/

	PQEnqueue(pque10, &pq10_data1);
	PQEnqueue(pque10, &pq10_data2);
	PQEnqueue(pque10, &pq10_data3);


	/* PQAppend(pque9, pque10); */
	/*1 - 2 - 3 */

	puts("test5");

	for (i = 0 ; i < sizeof(exp5)/sizeof(int) ; ++i)
	{
		TEST_INT(PQPeek(pque9), &exp5[i]);
		PQDequeue(pque9);
	}

	/*case 6*/
	/*src empty*/

	PQEnqueue(pque11, &pq11_data1);
	PQEnqueue(pque11, &pq11_data2);
	PQEnqueue(pque11, &pq11_data3);

	/* PQAppend(pque11, pque12); */
	/*1 - 2 - 3 */

	puts("test6");

	for (i = 0 ; i < sizeof(exp6)/sizeof(int) ; ++i)
	{
		TEST_INT(PQPeek(pque11), &exp6[i]);
		PQDequeue(pque11);
	}

	PQDestroy(pque1);
	PQDestroy(pque2);
	PQDestroy(pque3);
	PQDestroy(pque4);
	PQDestroy(pque5);
	PQDestroy(pque6);
	PQDestroy(pque7);
	PQDestroy(pque8);
	PQDestroy(pque9);
	PQDestroy(pque10);
	PQDestroy(pque11);
	PQDestroy(pque12);
}

void TestErase()
{
	/*test 1*/
	pq_t *pque1 = PQCreate(IsBeforeInt, NULL);

	int pq1_data1 = 1;
	int pq1_data2 = 2;
	int pq1_data3 = 3;
	int pq1_data4 = 4;

	int to_erase1 = 1;
	int exp1[] = {2, 3, 4};

	/*******************************************/

	/*test 2*/
	pq_t *pque2 = PQCreate(IsBeforeInt, NULL);

	int pq2_data1 = 1;
	int pq2_data2 = 2;
	int pq2_data3 = 3;
	int pq2_data4 = 4;

	int to_erase2 = 3;
	int exp2[] = {1, 2, 4};

	/*******************************************/

	/*test 3*/
	pq_t *pque3 = PQCreate(IsBeforeInt, NULL);

	int pq3_data1 = 1;
	int pq3_data2 = 2;
	int pq3_data3 = 3;
	int pq3_data4 = 4;

	int to_erase3 = 4;
	int exp3[] = {1, 2, 3};

	/*******************************************/

	/*test 4*/
	pq_t *pque4 = PQCreate(IsBeforeInt, NULL);

	int pq4_data1 = 1;
	int pq4_data2 = 2;
	int pq4_data3 = 3;
	int pq4_data4 = 4;

	int to_erase4 = 10;
	int exp4[] = {1, 2, 3, 4};

	/*******************************************/

	size_t i = 0;

	TITLE("TestErase");

	puts("test1");

	PQEnqueue(pque1, &pq1_data1);
	PQEnqueue(pque1, &pq1_data2);
	PQEnqueue(pque1, &pq1_data3);
	PQEnqueue(pque1, &pq1_data4);

	PQErase(pque1, IsMatchInt, &to_erase1);

	for (i = 0 ; i < sizeof(exp1)/sizeof(int) ; ++i)
	{
		TEST_INT(PQPeek(pque1), &exp1[i]);
		PQDequeue(pque1);
	}

	puts("test2");
	PQEnqueue(pque2, &pq2_data1);
	PQEnqueue(pque2, &pq2_data2);
	PQEnqueue(pque2, &pq2_data3);
	PQEnqueue(pque2, &pq2_data4);

	PQErase(pque2, IsMatchInt, &to_erase2);

	for (i = 0 ; i < sizeof(exp2)/sizeof(int) ; ++i)
	{
		TEST_INT(PQPeek(pque2), &exp2[i]);
		PQDequeue(pque2);
	}

	puts("test3");

	PQEnqueue(pque3, &pq3_data1);
	PQEnqueue(pque3, &pq3_data2);
	PQEnqueue(pque3, &pq3_data3);
	PQEnqueue(pque3, &pq3_data4);

	PQErase(pque3, IsMatchInt, &to_erase3);

	for (i = 0 ; i < sizeof(exp3)/sizeof(int) ; ++i)
	{
		TEST_INT(PQPeek(pque3), &exp3[i]);
		PQDequeue(pque3);
	}

	puts("test4");

	PQEnqueue(pque4, &pq4_data1);
	PQEnqueue(pque4, &pq4_data2);
	PQEnqueue(pque4, &pq4_data3);
	PQEnqueue(pque4, &pq4_data4);

	PQErase(pque4, IsMatchInt, &to_erase4);

	for (i = 0 ; i < sizeof(exp4)/sizeof(int) ; ++i)
	{
		TEST_INT(PQPeek(pque4), &exp4[i]);
		PQDequeue(pque4);
	}

	PQDestroy(pque1);
	PQDestroy(pque2);
	PQDestroy(pque3);
	PQDestroy(pque4);
}


