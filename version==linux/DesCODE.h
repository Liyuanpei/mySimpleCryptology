#pragma once
#include "stdafx.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "stdafx_data.h"
/*
分部分测试中间结果，通过大量的测试用例以排除潜在的或难以发现的编程错误
输入参数：函数名，该函数的输入，函数预期输出
输出参数：状态码

状态码：0（正常），1（输出格式正确，结果错误），-1（数据格式错误或遇到预料外的输出）

随后可以借助python增强其功能和可扩展程度

*/
int tester() {
	char in[64];
	char out[64];
	char LK[28];
	char RK[28];
	char type = 'e';
	char plaintext[9] = "ABCDEFGH";
	char key[9] = "12345678";
	char *buffer = (char *)malloc(8);
	char *Hex_p = (char *)malloc(64);
	char *Hex_k = (char *)malloc(64);
	if (NULL == Hex_k || NULL == Hex_p || NULL == buffer)
	{
		printf("Memory allocation error\n");
		return -1;
	}
	memset(Hex_p, 0, 64);
	memset(Hex_k, 0, 64);
	memset(LK, 0, 28);
	memset(RK, 0, 28);
	bytes_2_bits(plaintext, Hex_p);

	printf("----------- Testing bytes_2_bits ----------------\n");
	printf("%s\n", plaintext);
	for (int i = 0; i < 64; i++)
	{
		printf("%2d ", *(Hex_p + i));
		if ((i + 1) % 8 == 0)
		{
			printf("\n");
		}
	}
	printf("\n ");
	bits_2_bytes(Hex_p, buffer);
	for (int i = 0; i < 8; i++)
	{
		printf("%c  ", *(buffer + i));
	}
	printf("\n");
	printf("----------- Testing IP and IP_reverse-----------\n");
	for (int i = 0; i < 64; i++)
	{
		in[i] = i;
		out[i] = 0;
	}
	for (int i = 0; i < 64; i++)
	{
		out[i] = in[IP_box[i] - 1];
		printf("%2d ", out[i]);
		if ((i + 1) % 8 == 0)
		{
			printf("\n");
		}
	}
	printf("\n");
	for (int i = 0; i < 64; i++)
	{
		in[i] = out[IP_reverse[i] - 1];
		printf("%2d ", in[i]);
		if ((i + 1) % 8 == 0)
		{
			printf("\n");
		}
	}
	// 正常
	printf("------------ Testing key rotator --------- \n");
	char key_rotate_buffer_l[28];
	char key_rotate_buffer_r[28];
	char key_buffer[56];
	for (int i = 0; i < 28; i++)
	{
		LK[i] = i;
		RK[i] = i;
	}
	for (int round = 0; round < 16; round++)
	{

		memcpy(key_rotate_buffer_l, LK + key_Rotate_enc[round], 28 - key_Rotate_enc[round]);
		memcpy(key_rotate_buffer_l + 28 - key_Rotate_enc[round], LK, key_Rotate_enc[round]);
		memcpy(LK, key_rotate_buffer_l, 28);
		memset(key_rotate_buffer_l, 0, 28);

		memcpy(key_rotate_buffer_r, RK + key_Rotate_enc[round], 28 - key_Rotate_enc[round]);
		memcpy(key_rotate_buffer_r + 28 - key_Rotate_enc[round], RK, key_Rotate_enc[round]);
		memcpy(RK, key_rotate_buffer_r, 28);
		memset(key_rotate_buffer_r, 0, 28); // 密钥分别循环左移
		memcpy(key_buffer, LK, 28);
		memcpy(key_buffer + 28, RK, 28);
		for (int i = 0; i < 56; i++)
		{
			printf("%2d ", key_buffer[i]);
			if (i == 27)
			{
				printf("\n\n");
			}
		}
		printf("\n----------round == %2d rotatation step == %2d  ENC \n", round, key_Rotate_enc[round]);

	}

	printf("\n******************************\n\n");
	for (int round = 0; round < 16; round++)
	{
		// 密钥分别循环右移
		memcpy(key_rotate_buffer_l + key_Rotate_dec[round], LK, 28 - key_Rotate_dec[round]);
		memcpy(key_rotate_buffer_l, LK + 28 - key_Rotate_dec[round], key_Rotate_dec[round]);
		memcpy(LK, key_rotate_buffer_l, 28);
		memset(key_rotate_buffer_l, 0, 28);

		memcpy(key_rotate_buffer_r + key_Rotate_dec[round], RK, 28 - key_Rotate_dec[round]);
		memcpy(key_rotate_buffer_r, RK + 28 - key_Rotate_dec[round], key_Rotate_dec[round]);
		memcpy(RK, key_rotate_buffer_r, 28);
		memset(key_rotate_buffer_r, 0, 28);

		memcpy(key_buffer, LK, 28);
		memcpy(key_buffer + 28, RK, 28);
		for (int i = 0; i < 56; i++)
		{
			printf("%2d ", key_buffer[i]);
			if (i == 27)
			{
				printf("\n\n");
			}
		}
		printf("\n----------round == %2d rotatation step == %2d  DEC\n", round, key_Rotate_dec[round]);
	}


	return 0;
}


int DES(char *in, char *out, char *key, int length, char type) {
	// 1. 文件不是8字节的整数倍 ：指定填充模式，Nopadding表示最后一块不进行加密，PKCS5表示，使用n个n填充，例如
	// (XX) (FF FF 05 05 05 05 05 05)
	// 解密时，看最后，若符合，即可
	// 2. 输入密钥长度不为64bits ： 缺失则提示异常然后退出，多余则询问是否截断，若否，则退出
	// 3. 密钥下一步可以由文件中的十六进制整数指定（键盘中的字符表达空间有限）
	char block[8];
	memcpy(block, in, 8);
	// ECB CBC 目前使用的是 ECB 模式
	int checker = length % 8;
	int cnt = (int)(length / 8);
	char K[8];
	char Hex_key[64]; // 空间数量没有 +1 不能用作字符串
	char block_bits[64];
	memset(block_bits, 0, 64);
	memset(K, 0, 8);

	int text_parse_eor = bytes_2_bits(block, block_bits);

	if (strlen(key) == 8)
	{
		memcpy(K, key, 8);
		// Change bytes into bits
		memset(Hex_key, 0, 64);
		int key_parse_eor = bytes_2_bits(K, Hex_key);
		if (key_parse_eor != 0)
		{
			return -1;
		}
	}
	else if (strlen(key) == 18)
	{
		if (*(key + 0) != '0' || *(key + 1) != 'x')
		{
			printf("Please begin with '0x' when using hex\n");
			return -1;
		}
		char *key_buf = (char *)malloc(16);
		for (int i = 0; i < 16; i++)
		{
			*(key_buf + i) = *(key + i + 2);
		}
		for (int i = 0; i < 16; i++)
		{
			if (*(key_buf + i) >= '0' && *(key_buf + i) <= '9')
			{

			}
			else if (*(key_buf + i) >= 'A' && *(key_buf + i) <= 'F')
			{

			}
			else
			{
				printf("Only upper-case supported when using hex\n");
				return -1;
			}


		}
	}
	else
	{
		printf("Error in checking key length, using 8 bytes chars or 16 bytes hex to present it\n");
		printf("Such as abcdefgh or 0xFF00FF00FF00FF00\n");
		return -2;
	}

	char L[32];
	char R[32];
	char block_swapping_buffer[32];
	char buffer[48];
	char key_buffer[56];
	char LK[28];
	char RK[28];
	char key_rotate_buffer_l[28];
	char key_rotate_buffer_r[28];
	char block_bits_1[64];
	char key_buffer_2[48];
	char buffer2[48];
	char buffer3[32];
	char buffer4[32];
	char buffer5[32];

	memset(buffer5, 0, 32);
	memset(buffer4, 0, 32);
	memset(buffer3, 0, 32);
	memset(buffer2, 0, 48);
	memset(key_buffer_2, 0, 48);
	memset(block_swapping_buffer, 0, 32);
	memset(key_buffer, 0, 56);
	memset(LK, 0, 28);
	memset(RK, 0, 28);
	memset(L, 0, 32);
	memset(R, 0, 32);
	memset(buffer, 0, 48);
	memset(block_bits_1, 0, 64);
	memset(key_rotate_buffer_l, 0, 28);
	memset(key_rotate_buffer_r, 0, 28);

	for (int i = 0; i < 64; i++)
	{
		*(block_bits_1 + i) = *(block_bits + IP_box[i] - 1); // IP swapping
	}

	memcpy(L, block_bits_1, 32);
	memcpy(R, block_bits_1 + 32, 32);

	for (int i = 0; i < 56; i++)
	{
		*(key_buffer + i) = *(Hex_key + key_switching[i] - 1);
	}

	memcpy(LK, key_buffer, 28);
	memcpy(RK, key_buffer + 28, 28);
	int round = 0;

	for (round = 0; round < 16; round++)
	{
		// 右半部分进行扩展变换
		// 密钥循环左移生成子密钥 Kn
		// 对子密钥压缩（56 -> 48）压缩结果是一次性使用的，也就是说每次移位后都进行压缩，但结果跳不出
		// Rn 与 Kn 异或
		memcpy(block_swapping_buffer, R, 32); // Rn = L(n-1)

		for (int i = 0; i < 48; i++)
		{
			*(buffer + i) = *(R + Expand[i] - 1); // 扩展置换右半

		}

		if (type == 'E' || type == 'e')
		{
			memcpy(key_rotate_buffer_l, LK + key_Rotate_enc[round], 28 - key_Rotate_enc[round]);
			memcpy(key_rotate_buffer_l + 28 - key_Rotate_enc[round], LK, key_Rotate_enc[round]);
			memcpy(LK, key_rotate_buffer_l, 28);
			memset(key_rotate_buffer_l, 0, 28);

			memcpy(key_rotate_buffer_r, RK + key_Rotate_enc[round], 28 - key_Rotate_enc[round]);
			memcpy(key_rotate_buffer_r + 28 - key_Rotate_enc[round], RK, key_Rotate_enc[round]);
			memcpy(RK, key_rotate_buffer_r, 28);
			memset(key_rotate_buffer_r, 0, 28); // 密钥分别循环左移

		}
		else if (type == 'D' || type == 'd')
		{
			// 密钥分别循环右移
			memcpy(key_rotate_buffer_l + key_Rotate_dec[round], LK, 28 - key_Rotate_dec[round]);
			memcpy(key_rotate_buffer_l, LK + 28 - key_Rotate_dec[round], key_Rotate_dec[round]);
			memcpy(LK, key_rotate_buffer_l, 28);
			memset(key_rotate_buffer_l, 0, 28);

			memcpy(key_rotate_buffer_r + key_Rotate_dec[round], RK, 28 - key_Rotate_dec[round]);
			memcpy(key_rotate_buffer_r, RK + 28 - key_Rotate_dec[round], key_Rotate_dec[round]);
			memcpy(RK, key_rotate_buffer_r, 28);
			memset(key_rotate_buffer_r, 0, 28);

		}
		else
		{
			printf("Enc or Dec? \n");
			return 1;

		}

		memcpy(key_buffer, LK, 28);
		memcpy(key_buffer + 28, RK, 28); // 合并至缓冲区

		for (int i = 0; i < 48; i++)
		{

			*(key_buffer_2 + i) = *(key_buffer + key_switching_2[i] - 1); // 子密钥压缩

		}
		memset(key_buffer, 0, 28);
		for (int i = 0; i < 48; i++)
		{
			// 注意，这里每个字节中只有 0 1 
			*(buffer2 + i) = byte_XOR(*(buffer + i), *(key_buffer_2 + i));

		}
		memset(buffer, 0, 48);
		memset(key_buffer, 0, 48);
		for (int i = 0; i < 8; i++)
		{
			int row = *(buffer2 + i * 6 + 0) * 2 + *(buffer2 + i * 6 + 5);
			int col = *(buffer2 + i * 6 + 1) * 8 + *(buffer2 + i * 6 + 2) * 4 + *(buffer2 + i * 6 + 3) * 2 + *(buffer2 + i * 6 + 4);
			int index = S_box[i * 64 + row * 16 + col];

			*(buffer3 + i * 4 + 0) = (index & 0x8) >> 3;
			*(buffer3 + i * 4 + 1) = (index & 0x4) >> 2;
			*(buffer3 + i * 4 + 2) = (index & 0x2) >> 1;
			*(buffer3 + i * 4 + 3) = index & 0x1;
			// S盒的输出

		}
		memset(buffer2, 0, 48);

		for (int i = 0; i < 32; i++)
		{
			*(buffer4 + i) = *(buffer3 + P_box[i] - 1);
			// P盒置换

		}
		memset(buffer3, 0, 32);

		for (int i = 0; i < 32; i++)
		{
			*(buffer5 + i) = byte_XOR(*(buffer4 + i), *(L + i));

		}
		memset(buffer4, 0, 32);
		memcpy(R, buffer5, 32);
		memset(buffer5, 0, 32);
		memcpy(L, block_swapping_buffer, 32);
		memset(block_swapping_buffer, 0, 32);
		printf("\nL:  ");
		for (int i = 0; i < 32; i++)
		{
			printf(" %d", L[i]);
		}
		printf("\nR:  ");
		for (int i = 0; i < 32; i++)
		{
			printf(" %d", R[i]);
		}
		printf("---\n");
	}

	memcpy(block_bits_1, R, 32);  // 
	memcpy(block_bits_1 + 32, L, 32); // 十六轮结束之后再交换一次

	for (int i = 0; i < 64; i++)
	{
		*(block_bits + i) = *(block_bits_1 + IP_reverse[i] - 1); // 末置换（逆IP置换）
	}
	// 初步推测是循环导致的错误，例如赋值时被覆盖或者赋值目标错误
	int test_parse_eor2 = bits_2_bytes(block_bits, block);
	memcpy(out, block, 8);

	return 0;
}