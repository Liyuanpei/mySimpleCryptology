#pragma once
#include "stdlib.h"
#include "stdafx.h"
#include "math.h"
#include "string.h"
#include "stdio.h"
// #include "windows.h"


/*
	ֱ��ִ�������������ļӷ�
	params:
	  @1 : char * : longer
	  @2 : char * : shorter
	  @3 : char * : destnation
	  ��ʵ�ϵ���ǰ�豣֤����in�����ռ���ȣ����ҽ�С�ĳ��������˽ϴ�Ŀռ���
*/
int long_int_plus_1(char *in1, char *in2, int length1, int length2, char *out) {

	int f_len_1 = length1;
	int f_len_2 = length2;
	int carry = 0;
	
	char *str_in_3 = (char *)malloc(sizeof(char) * (1 + f_len_1)); // dest buffer
	char *str_in_4 = (char *)malloc(sizeof(char) * (1 + f_len_1)); // long src buffer
	char *big_caculator_result = (char *)malloc(sizeof(char) * (2 + f_len_1)); // dest
	// ������ܲ�����λ�����Խ����λ��Ԥ����Ϊ�ϳ���λ����һ

	if (NULL == str_in_3 || NULL == str_in_4 || NULL == big_caculator_result)
	{
		printf("Memory allocation error\n");
		return 1;
	}
	else
	{
		memset(str_in_3, 0, f_len_1 + 1);
		memset(str_in_4, 0, f_len_1 + 1); // ��ʹ�ýϳ��Ŀռ��Զ���
		memset(big_caculator_result, 0, f_len_1 + 2);
	}

	memcpy(str_in_3, in1, f_len_1);
	memcpy(str_in_4, in2, f_len_2);

	for (int i = f_len_1 - 1; i >= 0; i--)
	{
		*(big_caculator_result + 1 + i) = (carry + (*(str_in_3 + i) + *(str_in_4 + i))) % 10;
		carry = (int)(carry + (*(str_in_3 + i) + *(str_in_4 + i))) / 10;
	}
	*(big_caculator_result) = carry;
	// 1. �ܳ��ȿ��ܲ�����λ 2. ���룬��������Ҫ����ע��

	printf("\n");
	for (int i = 0; i < f_len_1 + 1; i++)
	{
		printf("%c", (*(big_caculator_result + i) + '0'));
	}
	printf("\n"); // ���˼�����ԣ�Ŀǰ�����ʱ�䶼����

	memcpy(out, big_caculator_result, 2 + f_len_1);
	return 0;
}

/*
����/�������ļ� �� �� ȡ��
�ӷ��Ĵ�����Ҫ�ع���д�ɴ�����������һ����ʹ���ļ����ҷ����������
    params:
	  @1: in 1
	  @2: in 2
	  @3: out
*/
int long_data_caculate(const char *filename1, const char *filename2, char *filename3, char mode) {
	FILE *fp1, *fp2;// , *fp3;
	int f_eor_1 = fopen_s(&fp1, filename1, "rb");
	int f_eor_2 = fopen_s(&fp2, filename2, "rb");
	//int f_eor_3 = fopen_s(&fp3, filename3, "rb");
	
	if (f_eor_1 != 0 || f_eor_2 != 0 )//|| f_eor_3 != 0)
	{
		printf("file open error\n");
		return 1;
	}
	else
	{
		// Nothing to do
	}

	int f_len_1 = 0;
	int f_len_2 = 0;
	int f_len_3 = 0;
	int f_len_4 = 0;
	int upmost = 1024 * 1024;
	int carry = 0;

	fseek(fp1, 0, SEEK_END);
	f_len_1 = ftell(fp1);
	rewind(fp1);
	fseek(fp2, 0, SEEK_END);
	f_len_2 = ftell(fp2);
	rewind(fp2);

	if (f_len_1 > upmost || f_len_2 > upmost)
	{
		printf("Maximum of the file is 1MB\n");
		return 1;
	}
	else
	{

	}

	// ʹ��f_len_3 >= f_len_4 �ҳ��ϳ��Ĵ�
	if (f_len_1 > f_len_2)
	{
		f_len_3 = f_len_1;
		f_len_4 = f_len_2;
	}
	else
	{
		f_len_3 = f_len_2;
		f_len_4 = f_len_1;
	}
	// �ж��ַ������ȣ�ʹ��3 4һ�����������϶̵������4�У��ϳ��������3��
	char *str_in_1 = (char *)malloc(sizeof(char) * (1 + f_len_1)); // src1
	char *str_in_2 = (char *)malloc(sizeof(char) * (1 + f_len_2)); // src2
	char *str_in_3 = (char *)malloc(sizeof(char) * (1 + f_len_3)); // dest buffer
	char *str_in_4 = (char *)malloc(sizeof(char) * (1 + f_len_3)); // long src buffer
	// ����һ������f_len_4 ��  f_len_3 + f_len_4 + 1 �У���ĩβ�����ַ���β

	if (NULL == str_in_1 || NULL == str_in_2)
	{
		printf("Memory allocation error\n");
		return 1;
	}
	else
	{
		memset(str_in_1, 0, 1 + f_len_1);
		memset(str_in_2, 0, 1 + f_len_2);
		memset(str_in_3, 0, f_len_3 + 1);
		memset(str_in_4, 0, f_len_3 + 1); // ��ʹ�ýϳ��Ŀռ��Զ���
	
	}
	fread(str_in_1, sizeof(char), f_len_1, fp1);
	fread(str_in_2, sizeof(char), f_len_2, fp2);
	fclose(fp1);
	fclose(fp2);
	printf("%s\n    +\n%s\n    ||\n     V\n", str_in_1, str_in_2);
	for (int i = 0; i < f_len_1; i++)
	{
		*(str_in_1 + i) -= '0';
	}
	for (int i = 0; i < f_len_2; i++)
	{
		*(str_in_2 + i) -= '0';
	}

	// ��С����䵽�������
	if (f_len_1 == f_len_3 && f_len_3 >= f_len_2)
	{
		memcpy(str_in_3 + (f_len_3 - f_len_2), str_in_2, f_len_3);
		memcpy(str_in_4, str_in_1, f_len_1);

	}
	else if (f_len_2 == f_len_3 && f_len_3 >= f_len_1)
	{
		memcpy(str_in_3 + (f_len_3 - f_len_1), str_in_1, f_len_3);
		memcpy(str_in_4, str_in_2, f_len_2);
	}
	else
	{
		printf("Error please check f_len_3\n");
		return 1;
	}

	free(str_in_1);
	free(str_in_2);
	if ('+' == mode)
	{
		
		char *big_caculator_result = (char *)malloc(sizeof(char) * (2 + f_len_3)); // dest
		// ������ܲ�����λ�����Խ����λ��Ԥ����Ϊ�ϳ���λ����һ

		if (NULL == big_caculator_result)
		{
			printf("Memory allocation error\n");
			return 1;
		}
		else
		{
			memset(big_caculator_result, 0, f_len_3 + 2);
		}

		// �ڴ���Ҫ�û������飬��ɻ������ܺ����
	

		int plus_eor = long_int_plus_1(str_in_3, str_in_4, f_len_3, f_len_3, big_caculator_result);
	
	}
	else if ('*' == mode)
	{
		// ���ж�μӷ�ʱ����ÿһ�ζ��������飬��Ҫ���������������ǰ�������ռ�
	}
	else
	{
		printf("Mode error\n");
		return 1;
	}
	return 0;

}


/*
�������ļ��зֱ�����ַ�����ʽ�Ĵ������������

D:\\testCases\\big_int_cacu\\1.txt
D:\\testCases\\big_int_cacu\\2.txt

TODO ��ͽ������ʱ������д�ɵ������ļ�
*/
int long_int_plus(const char *filename1, const char *filename2) {
	FILE *fp1, *fp2;
	int f_eor_1 = fopen_s(&fp1, filename1, "rb");
	int f_eor_2 = fopen_s(&fp2, filename2, "rb");

	int f_len_1 = 0;
	int f_len_2 = 0;
	int f_len_3 = 0;
	int f_len_4 = 0;
	int upmost = 1024 * 1024;
	int carry = 0;

	fseek(fp1, 0, SEEK_END);
	f_len_1 = ftell(fp1);
	rewind(fp1);
	fseek(fp2, 0, SEEK_END);
	f_len_2 = ftell(fp2);
	rewind(fp2);

	if (f_len_1 > upmost || f_len_2 > upmost)
	{
		printf("Maximum of the file is 1MB\n");
		return 1;
	}
	else
	{

	}
	if (f_len_1 > f_len_2)
	{
		f_len_3 = f_len_1;
		f_len_4 = f_len_2;
	}
	else
	{
		f_len_3 = f_len_2;
		f_len_4 = f_len_1;
	}
	// �ж��ַ������ȣ�ʹ��3 4һ�����������϶̵������4�У��ϳ��������3��
	char *str_in_1 = (char *)malloc(sizeof(char) * (1 + f_len_1)); // src1
	char *str_in_2 = (char *)malloc(sizeof(char) * (1 + f_len_2)); // src2
	char *str_in_3 = (char *)malloc(sizeof(char) * (1 + f_len_3)); // dest buffer
	char *str_in_4 = (char *)malloc(sizeof(char) * (1 + f_len_3)); // long src buffer
	char *big_caculator_result = (char *)malloc(sizeof(char) * (2 + f_len_3)); // dest
	// ������ܲ�����λ�����Խ����λ��Ԥ����Ϊ�ϳ���λ����һ

	if (NULL == str_in_1 || NULL == str_in_2 || NULL == str_in_3 || NULL == str_in_4 || NULL == big_caculator_result)
	{
		printf("Memory allocation error\n");
		return 1;
	}
	else 
	{
		memset(str_in_1, 0, (f_len_1 + 1) % upmost);
		memset(str_in_2, 0, f_len_2 + 1);
		memset(str_in_3, 0, f_len_3 + 1);
		memset(str_in_4, 0, f_len_3 + 1); // ��ʹ�ýϳ��Ŀռ��Զ���
		memset(big_caculator_result, 0, f_len_3 + 2);
	}
	fread(str_in_1, sizeof(char), f_len_1, fp1);
	fread(str_in_2, sizeof(char), f_len_2, fp2);
	printf("%s\n    +\n%s\n    ||\n     V\n", str_in_1, str_in_2);
	fclose(fp1);
	fclose(fp2);

	// �ڴ���Ҫ�û������飬��ɻ������ܺ����
	for (int i = 0; i < f_len_1; i++)
	{
		*(str_in_1 + i) -= '0';
	}
	for (int i = 0; i < f_len_2; i++)
	{
		*(str_in_2 + i) -= '0';
	}

	// ��С����䵽������� 4 in bigger
	if (f_len_1 == f_len_3 && f_len_3 >= f_len_2)
	{
		memcpy(str_in_3 + (f_len_3 - f_len_2), str_in_2 , f_len_3);
		memcpy(str_in_4, str_in_1, f_len_1);
		
	}
	else if (f_len_2 == f_len_3 && f_len_3 >= f_len_1)
	{
		memcpy(str_in_3 + (f_len_3 - f_len_1), str_in_1, f_len_3);
		memcpy(str_in_4, str_in_2, f_len_2);
	}
	else
	{
		printf("Error please check f_len_3\n");
		return 1;
	}

	for (int i = f_len_3 - 1; i >= 0; i--)
	{
		*(big_caculator_result + 1 + i) = (carry + (*(str_in_3 + i) + *(str_in_4 + i))) % 10;
		carry = (int)(carry + (*(str_in_3 + i) + *(str_in_4 + i))) / 10;
	}
	*(big_caculator_result) = carry;
	// 1. �ܳ��ȿ��ܲ�����λ 2. ���룬��������Ҫ����ע��
	printf("\n");
	for (int i = 0; i < f_len_3 + 1; i++)
	{
		printf("%c", (*(big_caculator_result + i) + '0'));
	}
	printf("\n"); // ���˼�����ԣ�Ŀǰ�����ʱ�䶼����
	return 0;
}

/*
�������ļ��зֱ�����ַ�����ʽ�Ĵ������������������д��������ļ���
params:
	@1 input_1
	@2 input_2
	@3 input_3
D:\\testCases\\big_int_cacu\\1.txt
D:\\testCases\\big_int_cacu\\2.txt
ʵ�ַ�����
��������תΪ�����ƣ��Ȳ�����ռ����ģ�ÿһλռһ��char��
��ʹ��һ������Ϊ���գ����·�ʽ����
1110001 * 101101
ʹ��1110001��Ϊ���գ�����6����С��ͬ�Ĵ洢�ռ䣬�洢�ռ��С���ݲ�������λ֮��Ľ��������ֱ�Ӻ��油�㼴�ɣ�
101101 = 10000 + 1000 + 100 + 1
�� ������λ�Ľ�� * 1 + ������λ�Ľ�� * 0 + ������λ�Ľ�� * 1 + ���ƶ�λ�Ľ�� * 1 + ����һλ�Ľ�� * 0 + ���� * 1��
��������׼�������յĻ���������СΪԭʼ���ȷֱ�+5��4��3��2��1������ע��һ�¼ӷ������Ľ�λ��
ͬ���ĵ�������ʹ��ʮ����Ҳ����
*/
int long_int_mul(char *filename1, char *filename2, char *filename3) {
	

	return 0;
}
