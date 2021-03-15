#include "stdio.h"
#include "string.h"
#include "DesCODE.h"
#include "stdlib.h"
//#include "crtdbg.h"
#include "math.h"
#include "stdafx.h"
//#include "bigcaculator.h"

int Caesar(char *in, char *out, char key, int length, char type){ // 凯撒密码的ASCII变式

	if (type == 'E' or type == 'e')
	{
		for (int i = 0; i < length; i++)
		{
			*(out + i) = (*(in + i) + key) % 256;
		}
	}
	else if (type == 'D' or type == 'd')
	{
		for (int i = 0; i < length; i++)
		{
			*(out + i) = (*(in + i) - key) % 256;
		}
	}
	else
	{
		printf("Enc or Dec?\n");
		return 1;
	}

	return 0;
}

int triple_DES() {



	return 0;
}

int RC4(char *in, char *out, char *key, int length, char type) {
	int S_box[256]; // 1kB
	int T_box[256];
	memset(T_box, 0, sizeof(int) * 256);
	memset(S_box, 0, sizeof(int) * 256);
	int keylen = strlen(key); // 典型的密钥长度为 40-256比特 即 keylen = range[5, 32];
	for (int i = 0; i < 256; i++)
	{
		S_box[i] = i; // 初始化S盒
		T_box[i] = *(key + i % keylen);
	}
	int index = 0;
	int buffer = 0;
	for (int i = 0; i < 256; i++) // KSA the Key-Scheduling algorithm
	{
		index = (index + S_box[i] + *(key + i % keylen)) % 256;
		buffer = S_box[i];
		S_box[i] = S_box[index];
		S_box[index] = buffer;
	}
	int t = 0;
	int buffer2 = 0;
	for (int i = 0; i < length; i++)
	{
		index = (index + 1) % 256;
		buffer = (buffer + S_box[index]) % 256;
		t = (S_box[index] + S_box[buffer]) % 256;
		buffer2 = index;
		index = buffer;
		buffer = buffer2;
		*(out + i) = *(in + i) ^ S_box[t];
	}

	
	if (type == 'E' or type == 'e')
	{
		
	}
	else if (type == 'D' or type == 'd')
	{
		
	}
	else
	{
		printf("Enc or Dec? You have an implicitly usage\n");
		
	}
	return 1;
}


int AES() {


	return 0;
}

int SEAL(){
    
	
	return 0;
}

int IDEA() {


	return 0;
}

int argu_checker() { // 根据情况，有必要进行解耦合时再摘出单独处理


	return 0;
}

/*
参数说明：程序自身名称，源文件名，目标文件名，密码算法名，密钥
如果有空余时间可以考虑套一层代码自加密
*/
int main(int argc, char **argv) {
	//char str0[] = "Lucy";
	//char str2[] = "THVjeQ==";
	//char* str1 = (char *)malloc(100);
	//int zero = base64_parser(str2, str1, strlen(str2), 0);
	printf("%s\n%s\n%s\n%s\n%s\n%s\n", *(argv), *(argv + 1), *(argv+ 2) , *(argv + 3), *(argv + 4), *(argv + 5));
	// C:\Users\Administrator\source\repos\Cryptology\Debug\Cryptology.exe D:\postGraduate\Cryptology\source_files\... D:\postGraduate\Cryptology\dest_files\...
	// RC4 12345678 enc/dec
	// D:\postGraduate\Cryptology\source_files\... D:\postGraduate\Cryptology\dest_files\...
	// D:\postGraduate\Cryptology\dest_files\001.txt D:\postGraduate\Cryptology\source_files\001_.txt -CAESAR 10 d

	// D:\postGraduate\Cryptology\source_files\001.txt D:\postGraduate\Cryptology\dest_files\001_rc4.txt -RC4 12345678 e
	// D:\postGraduate\Cryptology\dest_files\001_rc4.txt  C:\Users\Administrator\Desktop\rc4.txt -RC4 12345678 d
	// D:\postGraduate\Cryptology\source_files\result_my2_model.avi D:\postGraduate\Cryptology\dest_files\001_rc4.txt -RC4 12345678 e
	// D:\postGraduate\Cryptology\dest_files\001_rc4.txt C:\Users\Administrator\Desktop\result_my2_mocel.avi -RC4 12345678 d

	// D:\postGraduate\Cryptology\source_files\002.txt D:\postGraduate\Cryptology\dest_files\002_des.txt -DES 12345678 e
	// D:\postGraduate\Cryptology\dest_files\002_des.txt  C:\Users\Administrator\Desktop\des.txt -DES 12345678 d
	// 打开文件流并计算文件大小，若文件过大则不一次性载入内存，分块调用并传回参数，在主函数中进行写入等，该功能计划于密码算法编写完成后再添加。

	//int _b = tester();
//	int _b = long_data_caculate("D:\\testCases\\big_int_cacu\\1.txt", "D:\\testCases\\big_int_cacu\\2.txt", NULL, '+');
//	int _c = long_int_plus("D:\\testCases\\big_int_cacu\\1.txt", "D:\\testCases\\big_int_cacu\\2.txt");
	FILE *fp1, *fp2;
	fp1 = fopen(*(argv + 1), "rb");
	fp2 = fopen(*(argv + 2), "wb");
//	int fp_eor_1 = fopen_s(&fp1, *(argv + 1), "rb");
//	int fp_eor_2 = fopen_s(&fp2, *(argv + 2), "wb"); 
/*	if (fp_eor_1 != 0)
	{
		printf("Source File open error, error code == %d, please check your arguments or if the source file really exists\n", fp_eor_1);
		return 0; 
		// 如果有被上层其他程序调用的需要，则考虑返回非零值（不要覆盖系统已经定义的
	}
	if (fp_eor_2 != 0)
	{
		printf("Destination file open error, error code == %d\n", fp_eor_2);
		return 0;
	}
*/
	if (NULL == fp1)
	{
		printf("Source File open error, error code == %d, please check your arguments or if the source file really exists\n", -0);
                return 0; 

	}
	if (NULL == fp2)
	{
		printf("Destination file open error, error code == %d\n", -0);
                return 0;

	}
	int length = 0;
	fseek(fp1, 0, SEEK_END);
	length = ftell(fp1) + 1;
	rewind(fp1);
	char *plaintext = (char *)malloc(sizeof(char) * length);
	char *cipher = (char *)malloc(sizeof(char) * length);
	char *plaintext2 = (char *)malloc(sizeof(char) * length - 1);
	int arguments_eor = 0;

	if (NULL == plaintext || NULL == (plaintext2) || NULL == cipher)
	{
		printf("Memory allocation error\n");
		return 0;
	}
	else
	{

	}
	// 至于使用ASCII还是base64编码，视算法的特点再决定
	memset(plaintext, 0, length);
	memset(cipher, 0, length);
	
	if (length <= 1) 
	{
		arguments_eor = -1;
		printf("Source File open error, please check your arguments or if the source file really exists\n");
		return 0;
	}
	else
	{

	}

	fread(plaintext, sizeof(char), length - 1, fp1);
	fclose(fp1);
	if (NULL != fp1)
	{
		//free(fp1);
		fp1 = NULL;
	}
	//free(fp1); 
	// 此处释放fp1 会出现 “处理的句柄不可用”这样的异常，在函数之前定义许多数组的时候同样出现了这个问题
	// An invalid handle was specified
	if (NULL == *(argv + 1) || NULL == *(argv + 2) || NULL == *(argv + 3) || NULL == *(argv + 4) || NULL == *(argv + 5))
	{
		arguments_eor = -2;
		printf("There are some empty arguments, please check your arguments\n");
		return 0;
	}
	else
	{

	}

	if (cipher == 0 || plaintext == 0)
	{
		printf("Memory allocation error\n");
		return 0;
	}
	else
	{

	}
	// -----------------------------------------------------------------------------------------------------

	// 密钥长度判定留在具体算法当中
	if (strcmp(*(argv + 3), "-CAESAR") == 0)
	{
		int algo_eor_caesar = Caesar(plaintext, cipher, *(*(argv + 4)), length - 1, *(*(argv + 5)));
		if (algo_eor_caesar == 0)
		{
			if (NULL == fp2)
			{
				printf("fp2 is a null pointer\n");
				return 0;
			}
			else
			{
				fwrite(cipher, 1, length - 1, fp2);
				fclose(fp2);
			}
		}
		else
		{
			printf("Error when executing the function 'Caesar'\n");
		}
	}
	else if (strcmp(*(argv + 3), "-RC4") == 0)
	{
		
		int algo_eor_rc4 = RC4(plaintext, cipher, *(argv + 4), length - 1, *(*(argv +5)));
		int algo_eor_rc4_2 = RC4(cipher, plaintext2, *(argv + 4), length - 1, *(*(argv + 5)));
		if (algo_eor_rc4 == 1)
		{
			if (NULL == fp2)
			{
				printf("fp2 is a null pointer\n");
				return 0;
			}
			else
			{
				fwrite(cipher, 1, (length - 1), fp2);
				fclose(fp2);
				//free(fp2);
				fp2 = NULL;
				return 0;
			}
			
		}
		else
		{
			printf("Error when executing the function 'RC4'\n");

		}
		
	}
	else if (strcmp(*(argv + 3), "-DES") == 0)
	{
		//return 0;
		if (length - 1 < 8)
		{
			printf("Plaintext is too short \n");
			return 0; 
			// 默认Nopadding 时，退出。
		}

		int algo_eor_des = DES(plaintext, cipher, *(argv + 4), length - 1, *(*(argv + 5))); 
		// 为便于排除问题，DES()的调用方式是逐块调用，接下来修改一下文件的写入方式

		char *plaintext1 = (char *)malloc(9);
		if (plaintext1 == NULL)
		{
			printf("Memory allocation error\n");
			return 0;
		}
		memset(plaintext1, 0, 9);
		
		int algo_eor_des2 = DES(cipher, plaintext1, *(argv + 4), length - 1, 'd');
		
		if ((algo_eor_des == 0))
		{
			if (fp2 != NULL)
			{
				fwrite(cipher, 1, length - 1, fp2);
				fclose(fp2);
				//free(fp2);
				fp2 = NULL;
			}
			else
			{
				printf("fp2 is null pointer\n");
				return 0;
			}
			free(plaintext1);
		}
		else
		{
			printf("Error when executing the function 'DES'\n");
			printf("error code == %d\n", algo_eor_des);
			return 0;
		}	
	}
	else if (strcmp(*(argv + 3), "-3DES"))
	{

	}
	else
	{
		printf("Using Uppercase when choosing algorithm, or check your expecting algorithm supported or not\n");
		printf("------------------- \n -CAESAR\n -DES\n -AES\n -3DES\n -IDEA\n -RC4\n -SEAL\n --------------------------");
		
	}
	//--------------------------------------------------------------------------------------------------------------------------------------
	free(plaintext); // 不要free fp ，置零即可
	free(cipher); // free()最好留一个空白结束符
	

	return 0; //

}
