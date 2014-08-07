#include "base64.h"

int main(int argc,char **argv)
{
	char s[512] = "标准Base64编码C语言版本";
	char *en, *de;
	
	printf("\n原始内容：\n%s\n\n",s);
	
	#if 0
	en = base64_encode(s);
	printf("编码结果：\n%s\n\n",en);
	
	de = base64_decode(en);
	printf("解码结果：\n%s\n\n",de);
	
	free(en);
	free(de);
	#endif
	
	#if 1
	base64_encode(s);
	printf("编码结果：\n%s\n\n",s);
	
	base64_decode(s);
	printf("解码结果：\n%s\n\n",s);
	#endif
	
	return 0;
}
