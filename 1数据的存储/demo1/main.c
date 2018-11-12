#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//可以对数据类型进行重命名，使用struct
struct teacher {
	int name;
	char buf[10];
} t1;
//-------------------数据类型----------------------------
int main1(){
	//数据类型可以理解为创建变量的模子：是固定内存大小的别名
	//数据类型的作用：编译器预算对象分配的内存空间大小
	printf("%d\n", sizeof(int));
	printf("%d\n", sizeof(char));//sizeof返回数据类型所占的字节数
	t1.name = "李志远";
	printf("%s\n", t1);
	char  *p2 = (char *)malloc(sizeof(char) * 20); //手动创建内存空间，并强制进行类型转化.
	int *p1 = NULL;//空指针
	//void可以指向任何数据类型，如果事先不知道数据的类型，可以使用void
	return 0;
}
//--------------------------变量------------------------------------
int main2(){
	int a = 10; //变量是一段连续内存空间的别名（是一个门牌号）
	int b = 20;
	//修改变量的方式
	//1.直接修改方法
	a = 100;
	//2.间接修改法
	int *p = &a;
	*p = 250;
	printf("%d\n", a);
}
//----------------------内存四区-------------------------------
static int globalc = 30; //全局区
#define MAX 10000  //常量区
void func(){
	printf("hello world\n"); //代码区
}
int main3(){
	int a; //入栈
	static int b;//全局区
	char *p = (char *)malloc(sizeof(char) * 20);//堆区
	func(); 
	printf("program is over !!!!!"); //代码区
}
//--------------------------------操作数----------------------------
int main4(){
	char str[] = "this is a word";//左边是一个数组，右边是一个立即数，可以理解为是一个常量字符串
	int a = 10;//开辟一块4字节内存空间，起了一个别名方便操作，并将10的值写入到内存地址对应的存储中
	register int reg = 100;//将reg存放到寄存器中
	int b = 20;
	int sum;
	sum = a + b; //操作数从内存中读取出来，交给寄存器完成运算，相加后的结果再写入sum所代表的内存地址.
	a = b;//将b的值赋给a,需要使用寄存器来完成.
	printf("%d\n", sum);
	return 0;
}
//总结：源操作数可以以常数形式给出，或是从寄存器、内存中读出,结果一般是传递给内存(sum),很少会给到寄存器(reg)
//Tips:一般赋值操作，在汇编中都是以move指令操作的，将数据从源位置复制到目的位置，不做任何变化。而一个值从一个地方
//到另外一个地方分两个步骤：1.将源值加载到寄存器 2.由寄存器放入指定目的,其实，只要是运算，都需要两步操作。

//-------------------有符号数和无符号数之间的转化----------------------------
int main5(){
	short int v = -12345;
	unsigned short uv = (unsigned short)v; //-12345 + 65536 = 53191
	printf("v=%d,uv=%u\n", v, uv);
	unsigned short int v1 = 53191; 
	short int uv1 = (signed short)v1; // 53191 - 65536 = -12345
	printf("v1=%u,uv1=%d\n", v1, uv1);
	short int v2 = 12345;
	unsigned short  uv2 = (unsigned short)v2; //这个有符号和无符号都是一样的
	printf("v2=%d,uv2=%u\n", v2, uv2);
	return 0;
}
//数值可能会变，但是位模式不变，有符号转无符号，就是在这个数的基础上+模（最高位的权重变成了一个更大的正数），无符号转有符号就是-模（最高位舍弃，变成了一个比较小的正数）
//Tips:小于2w-1的无符号数，不变，大于2w-1的无符号数改变；有符号大于0的不变，小于0的改变


//---------------------将较小的操作数赋值给较大的操作数----------------------
int main6(){
	short sx = -12345;
	unsigned short usx = sx; //53191
	int x = sx;
	unsigned ux = usx;
	printf("sx=%d:\t", sx); //cf c7
	printf("usx=%u:\t", usx); // cf c7
	printf("x=%d:\t", x); // ff ff cf c7
	printf("ux=%u:\t", ux); // 00 00 cf c7
}
//有符号数的扩展是补齐最高有效位，无符号的扩展是补齐0

//--------------将较大的操作数赋值给较小的操作数-------------------------
int main7(){
	int a = 12345678;
	int b = -300;
	unsigned char c = a;
    char d = b;
	printf("%d\n", a);
	printf("%d\n", b);
	printf("%d\n", c);
	printf("%d\n", d); //截取的结果就是这个-44
	return 0;
}
//先将数据转化为无符号数，然后实现截取,负数会将这个无符号数再转化为补码形式

//------------------------无符号的加法------------------
int main8(){
	unsigned char a = 255;
	unsigned char sum = a + 1;
	printf("%d + 1 = %d", a,sum);
	return 0;
}
//255+1的结果为0,发生了正溢出的情况 255 + 1 -256 = 0的结果,高位被简单的舍弃了
//Tips:sum高位如果是0，那么舍弃不会改变数的大小，也就是说和小于2w


//---------------补码的加法--------------------
int main9(){
	char big = -128;
	char small = 127;
	printf("big=%d\n", big);
	printf("small=%d\n", small);

	char sum1 = small + 1;  // 127- 256 + 1  = -128
	printf("正溢出的结果:%d", sum1);
	char sum2 = big - 1; // -128 + 256 - 1  = 127
	printf("负溢出的结果:%d", sum2);
	return 0;
}
//正常范围内的数值是不会产生溢出的,计算补码加法，先将有符号数的补码转化为无符号数，计算完毕之后，再转化为补码


//---------------------无符号的乘法-----------------------------
int main10(){
	unsigned char a = 100;
	unsigned char b = 200;
	unsigned int sum = a * b; // 100 * 200 = 20000
	unsigned char sum1 = a * b; 
	printf("long sum=%x\n", sum);
	printf("short sum=%x\n", sum1); //截取即可
	return 0;
}

//-----------------有符号的乘法 ---------------------
int main11(){
	int a = -10;
	int b = -30;
	int sum = a * b;
	printf("sum=%d", sum);
	return 0;
}
//先用无符号计算，最后再转化为补码形式即可.

//---------------乘以一个常数/除以一个常数-------------------------
int main(){
	int a = 10;
	int sum = a * 4; //乘以2的次幂，相当于将这个数右进行移位
	int sum1 = a / 4;//除以2的次幂，相当于将这个数左进行移位
	return 0;
}
//Tips:除以的数如果是一个负数，那么用的就不再是逻辑左右移了，而是算数右移了，移动多少位，补足的是符号位


















