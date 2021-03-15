#pragma once
#include "stdlib.h"
#include "stdafx.h"
#include "math.h"
#include "string.h"
#include "stdio.h"
// #include "windows.h"


/*
	直接执行两个大整数的加法
	params:
	  @1 : char * : longer
	  @2 : char * : shorter
	  @3 : char * : destnation
	  事实上调用前需保证两个in参数空间相等，并且较小的长度填入了较大的空间中
*/
int long_int_plus_1(char *in1, char *in2, int length1, int length2, char *out) {

	int f_len_1 = length1;
	int f_len_2 = length2;
	int carry = 0;
	
	char *str_in_3 = (char *)malloc(sizeof(char) * (1 + f_len_1)); // dest buffer
	char *str_in_4 = (char *)malloc(sizeof(char) * (1 + f_len_1)); // long src buffer
	char *big_caculator_result = (char *)malloc(sizeof(char) * (2 + f_len_1)); // dest
	// 结果可能产生进位，所以结果的位数预保留为较长串位数加一

	if (NULL == str_in_3 || NULL == str_in_4 || NULL == big_caculator_result)
	{
		printf("Memory allocation error\n");
		return 1;
	}
	else
	{
		memset(str_in_3, 0, f_len_1 + 1);
		memset(str_in_4, 0, f_len_1 + 1); // 仍使用较长的空间以对齐
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
	// 1. 总长度可能产生进位 2. 对齐，这两行需要格外注意

	printf("\n");
	for (int i = 0; i < f_len_1 + 1; i++)
	{
		printf("%c", (*(big_caculator_result + i) + '0'));
	}
	printf("\n"); // 做了几组测试，目前结果和时间都还行

	memcpy(out, big_caculator_result, 2 + f_len_1);
	return 0;
}

/*
大数/大整数的加 减 乘 取余
加法的代码需要重构，写成大函数，这样好一次性使用文件并且方便参数传递
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

	// 使得f_len_3 >= f_len_4 找出较长的串
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
	// 判定字符串长度，使得3 4一样长，但将较短的填充在4中，较长的填充在3中
	char *str_in_1 = (char *)malloc(sizeof(char) * (1 + f_len_1)); // src1
	char *str_in_2 = (char *)malloc(sizeof(char) * (1 + f_len_2)); // src2
	char *str_in_3 = (char *)malloc(sizeof(char) * (1 + f_len_3)); // dest buffer
	char *str_in_4 = (char *)malloc(sizeof(char) * (1 + f_len_3)); // long src buffer
	// 创建一个矩阵，f_len_4 行  f_len_3 + f_len_4 + 1 列，列末尾放入字符结尾

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
		memset(str_in_4, 0, f_len_3 + 1); // 仍使用较长的空间以对齐
	
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

	// 将小的填充到大的里面
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
		// 结果可能产生进位，所以结果的位数预保留为较长串位数加一

		if (NULL == big_caculator_result)
		{
			printf("Memory allocation error\n");
			return 1;
		}
		else
		{
			memset(big_caculator_result, 0, f_len_3 + 2);
		}

		// 在此需要用户输入检查，完成基本功能后添加
	

		int plus_eor = long_int_plus_1(str_in_3, str_in_4, f_len_3, f_len_3, big_caculator_result);
	
	}
	else if ('*' == mode)
	{
		// 进行多次加法时，会每一次都扩大数组，若要解决这个问题可以提前计算结果空间
	}
	else
	{
		printf("Mode error\n");
		return 1;
	}
	return 0;

}


/*
从两个文件中分别接受字符串形式的大整数，并求和

D:\\testCases\\big_int_cacu\\1.txt
D:\\testCases\\big_int_cacu\\2.txt

TODO 求和结果是临时变量，写成第三个文件
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
	// 判定字符串长度，使得3 4一样长，但将较短的填充在4中，较长的填充在3中
	char *str_in_1 = (char *)malloc(sizeof(char) * (1 + f_len_1)); // src1
	char *str_in_2 = (char *)malloc(sizeof(char) * (1 + f_len_2)); // src2
	char *str_in_3 = (char *)malloc(sizeof(char) * (1 + f_len_3)); // dest buffer
	char *str_in_4 = (char *)malloc(sizeof(char) * (1 + f_len_3)); // long src buffer
	char *big_caculator_result = (char *)malloc(sizeof(char) * (2 + f_len_3)); // dest
	// 结果可能产生进位，所以结果的位数预保留为较长串位数加一

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
		memset(str_in_4, 0, f_len_3 + 1); // 仍使用较长的空间以对齐
		memset(big_caculator_result, 0, f_len_3 + 2);
	}
	fread(str_in_1, sizeof(char), f_len_1, fp1);
	fread(str_in_2, sizeof(char), f_len_2, fp2);
	printf("%s\n    +\n%s\n    ||\n     V\n", str_in_1, str_in_2);
	fclose(fp1);
	fclose(fp2);

	// 在此需要用户输入检查，完成基本功能后添加
	for (int i = 0; i < f_len_1; i++)
	{
		*(str_in_1 + i) -= '0';
	}
	for (int i = 0; i < f_len_2; i++)
	{
		*(str_in_2 + i) -= '0';
	}

	// 将小的填充到大的里面 4 in bigger
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
	// 1. 总长度可能产生进位 2. 对齐，这两行需要格外注意
	printf("\n");
	for (int i = 0; i < f_len_3 + 1; i++)
	{
		printf("%c", (*(big_caculator_result + i) + '0'));
	}
	printf("\n"); // 做了几组测试，目前结果和时间都还行
	return 0;
}

/*
从两个文件中分别接受字符串形式的大整数，并求积。其结果写入第三个文件中
params:
	@1 input_1
	@2 input_2
	@3 input_3
D:\\testCases\\big_int_cacu\\1.txt
D:\\testCases\\big_int_cacu\\2.txt
实现方法：
将两个数转为二进制（先不介意空间消耗，每一位占一个char）
再使用一个数作为参照，如下方式进行
1110001 * 101101
使用1110001作为参照，创建6个大小不同的存储空间，存储空间大小依据参照数移位之后的结果而定（直接后面补零即可）
101101 = 10000 + 1000 + 100 + 1
即 左移五位的结果 * 1 + 左移四位的结果 * 0 + 左移三位的结果 * 1 + 左移二位的结果 * 1 + 左移一位的结果 * 0 + 自身 * 1；
可以事先准备六个空的缓冲区，大小为原始长度分别+5，4，3，2，1（这里注意一下加法产生的进位）
同样的道理，这里使用十进制也可以
*/
int long_int_mul(char *filename1, char *filename2, char *filename3) {
	

	return 0;
}
