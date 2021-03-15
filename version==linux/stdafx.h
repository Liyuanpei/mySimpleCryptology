#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#include "stdafx_data.h"
#pragma once



/*
���ַ������ȣ�ÿ�����ַ���24bits��Ϊһ�飬ʹ���ĸ��ַ���ʾ��
ת��ASCIIΪ�����ƣ�����24Ϊ�ĸ������أ���λ������㡣
���ĸ��ֽ�ת��Ϊʮ���ƣ��õ�������ַ�

���볤�Ȳ���3�ı���ʱ������0�������������á�=����ʶ

��׼�����������Ĵ洢�ռ䣬��ִ�к���

			L           u           c           y
ASCII:      76          117         99          121
8bit�ֽ�:   01001100    01110101    01100011    01111001      00000000    00000000
6bit�ֽ�:     010011      000111      010101      100011      011110  010000  000000  000000
ʮ����:     19          7           21          35             30      16      (�쳣) (�쳣)
��Ӧ����:   T           H           V           j               e       Q       =       =

*/
int base64_parser(char *in, char *out, int length_in, int type) {
	// 1. �����������

	if (length_in != strlen(in))
	{
		printf("Memory error, maybe string ending is missing\n");
		return 1;
	}
	if (1 == type)
	{
		int blocks1 = (int)(ceil(double(strlen(in) / 3.0)));
		int length = blocks1 * 3 * 8;
		char *buffer_in = (char *)malloc(length + 1);
		char *buffer_out = (char *)malloc(length + 1);

		if (NULL == buffer_in || NULL == buffer_out)
		{
			printf("Memory allocation error\n");
			return 1;
		}

		memset(buffer_in, 0, length + 1);
		memset(buffer_out, 0, length + 1);

		for (unsigned int i = 0; i < strlen(in); i++)
		{
			int buf = 0x80;
			for (int j = 0; j < 8; j++)
			{
				char _a = *(in + i) & buf;
				if (_a != 0)
				{
					*(buffer_in + i * 8 + j) = 1; // ��Ҫ������ܣ����� >> (7 - j)
				}
				else
				{
					*(buffer_in + i * 8 + j) = 0;
				}
				buf = buf >> 1;
			}
		}

		int cnt = (int)(length / 6.0);
		for (int i = 0; i < cnt; i++)
		{
			int buf = 0;
			for (int j = 0; j < 6; j++)
			{
				buf += *(buffer_in + i * 6 + j) * (int)pow(2, (int)((double)5 - (double)j));
			}
			if (0 != buf)
			{
				*(buffer_out + i) = base64_alphabet[buf];
			}
			else
			{
				*(buffer_out + i) = '=';
			}

		}
		int _1 = -1;
	}
	else
	{
		int ending_cnt = 0;
		for (int i = 0; i < strlen(in); i++)
		{
			if (*(in + i) == '=')
			{
				ending_cnt += 1;
			}
		}
		if (ending_cnt >= 3 || strlen(in) <= 3)
		{
			printf("Please check input \n");
			return 1;
		}
		int str_length = strlen(in);
		int length = strlen(in) * 8;
		char *buffer_in = (char *)malloc(length + 1);
		int blocks = (int)(strlen(in) / 4) * 3;
		char *buffer_out = (char *)malloc(blocks * 8 + 1);

		if (NULL == buffer_in || NULL == buffer_out)
		{
			printf("Memory allocate error \n");
			return 1;
		}

		memset(buffer_in, 0, length + 1);
		memset(buffer_out, 0, blocks * 8 + 1);
		// λ��תΪʮ����
		for (int i = 0; i < str_length; i++)
		{
			for (int j = 0; j < 64; j++)
			{
				if (base64_alphabet[j] == *(in + i))
				{
					*(in + i) = j;
				}
			}
		}
		for (int i = 0; i < str_length; i++)
		{
			if ('=' == *(in + i))
			{
				*(in + i) = 0; // ֱ���޸��Ƿ�������쳣
			}
		}

		// ʮ����ת������
		for (int i = 0; i < str_length; i++)
		{
			int buf = 0x80;
			for (int j = 0; j < 8; j++)
			{
				char _a = *(in + i) & buf;
				if (_a != 0)
				{
					*(buffer_in + i * 8 + j) = 1; // ��Ҫ������ܣ����� >> (7 - j)
				}
				else
				{
					*(buffer_in + i * 8 + j) = 0;
				}
				buf = buf >> 1;
			}
		}

		//ȥ��ǰ��λ0
		for (int i = 0, cnt = 0; i < str_length; i++)
		{

			for (int j = 2; j < 8; j++, cnt++)
			{
				*(buffer_out + cnt) = *(buffer_in + i * 8 + j);
			}

		}
		for (int i = 0; i < blocks; i++)
		{
			int buf = 0;
			for (int j = 0; j < 8; j++)
			{
				buf += *(buffer_out + i * 8 + j) * (int)pow(2, (int)((double)7 - (double)j));
			}
			*(out + i) = buf;

		}


		int _1 = -1;
	}
	return 0;
}


int bytes_2_bits(char *in, char *out) { // 8 bytes parse to 64 bits

	for (int i = 0; i < 8; i++)
	{
		int buf = 0x80;
		for (int j = 0; j < 8; j++)
		{
			char _a = *(in + i) & buf;
			if (_a != 0)
			{
				*(out + i * 8 + j) = 1; // ��Ҫ������ܣ����� >> (7 - j)
			}
			else
			{
				*(out + i * 8 + j) = 0;
			}
			buf = buf >> 1;
		}
	}

	return 0;
}

int bits_2_bytes(char *in, char *out) { // 64 bits parse to 8 bytes

	for (int i = 0; i < 8; i++)
	{
		int buf = 0;
		for (int j = 0; j < 8; j++)
		{
			buf += *(in + i * 8 + j) * (int)pow(2, (int)((double)7 - (double)j));
		}
		*(out + i) = buf;

	}
	return 0;
}

char byte_XOR(char a, char b) {
	if (a == b)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}


