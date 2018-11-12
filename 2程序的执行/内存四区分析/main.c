#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char * getStr1(){
	char *p1 = "abcdefg2";
	return p1;
}
char *getStr2(){
	char *p2 = "abcdefg2";
	return p2;
}
void main(){
	char *p1 = NULL; //第一步：思考下为什么必须放入栈中，而不是寄存器中
	char *p2 = NULL; //第二步：思考下为什么必须放入栈中，而不是寄存器中
	//第三步：main函数执行完毕，进入getStr1函数内部执行，这时候栈中main函数的过程是被暂时挂起的
	//当getStr1函数运行时候，它只需要为局部变量分配新的存储空间，或者设置到另一个过程的调用即可。
	//当控制从main函数转移到函数getStr1的时候，只需要将PC指向getStr1的起始位置即可，为了返回的时候继续执行
	//main函数，main函数必须把返回的地址（下一条main指令）压入main的栈帧中
	p1 = getStr1();
	//第四步：当getStr1函数返回的时候，任何它分配的局部存储空间都可以被释放。
	//栈从返回地址中得到下一条指令，开始执行对getStr2的调用，调用过程与getStr1相同.
	p2 = getStr2();
	//返回main函数，继续执行
	printf("p1:%s,p2:%s\n", p1, p2);
	printf("p1:%d,p2:%d\n", p1, p2);//p1 = p2 ?
	printf("hello....\n");
	system("pause");
	return;
}

//---------------------------有数据传送的例子----------------------
int sum(int a, int b,int c,int d,int e,int f,int g){
	return a + b + c + d + e + f;//分别从六个寄存器和main的栈帧中取出对应的值,最后返回结果交给rax寄存器
}
int main2(){
	int a = 10; //rdi寄存器
	int b = 20;//rsi寄存器
	int c = 30; //edx寄存器
	int d = 40;//rcx寄存器
	int e = 50;//r8w寄存器
	int f = 60;//r9寄存器
	int g = 70;//入栈70 ,main函数将70放入自己的参数构造区
	int result = sum(a, b,c,d,e,f,g);//a,b,c,d,e,f这六个参数放入对应的6个寄存器中保存，剩余的g变量从main的参数构造区访问
	//下一条指令地址入栈，进入sum的栈帧
	printf("result=%d\n", result);//main函数通过访问%rax寄存器得到计算结果.
	return 0;
}

//---------------------栈中的局部存储的例子------------------------------
//1.寄存器不足以存放所有的本地数据
//2.对一个局部变量使用了地址运算符 &,因此必须为它产生一个地址，这时候必须放到内存中
//3.某些局部变量是数组或结构，因此必须能够通过数组或结构引用

long swap_add(long *xp, long*yp){
	long x = *xp;//从rdi寄存器获得xp指针的数据
	long y = *yp;//从rsi寄存器获得yp指针的数据
	*xp = y;//将yp指针的数据赋值给*xp指向的地址
	*yp = x;//将xp指针的数据赋值给*yp指向的地址
	return x + y;//返回两个数据的和
}
long main3(){
	long arg1 = 534;//在main的栈帧-16，arg1的地址在栈顶
	long arg2 = 1057;//arg2在栈顶 + 8的位置
	long sum = swap_add(&arg1, &arg2);//这两个参数用到了指针，所以，必须放入main的栈帧中
	//重点来了，他们都在栈中，但要传递给swap_add函数使用，所以，必须从栈------->rdi,rsi寄存器中去
	long diff = arg1 - arg2;
	//diff结果保存在寄存器中
	return sum * diff;
}

//--------------------寄存器的局部存储空间-------------------------
//寄存器rbx,rbp和r12-r15被划分为被调用者保存寄存器
//当过程p调用过程Q时候，Q必须保存这些寄存器的值，保证他们的值在Q返回到P时与被调用时候是一样的，过程Q保存一个寄存器的值不变，要么就是根本不去改变它，要么就是把原始的值压入栈中，改变寄存器的值，然后在返回前从栈中弹出旧值。压入寄存器的值会在栈帧中创建标号为“保存的寄存器”的一部分。
long q(long dec){
	return dec + 1;
}
long p(long x, long y){ //p在这里使用了rdi,rsi两个寄存器保存x,y的值
	long u = q(y);//p在这个时候调用q,需要使用rdi寄存器传递y的值，这时候rdi中放着x的值
	//rax保存着q(y)的返回值
	long v = q(x);//p在这时候调用q,需要使用寄存器rdi传递x的值，这时候rdi 中放着y的值
	//这时候需要使用rax保存q(x)的返回值，但是这时候，rax里面放着q(y)的返回值
	return u + v; //将两个返回值相加
}
int main4(){
	p(10,20);
	return 0;
}
//x in rdi,y in rsi,先让rbx.rbp两个寄存器入栈(也就是它们原始的值)，第一次调用q之前，把参数x复制到rbp,第二次调用之前，把q(y)的结果复制到rbx,最后在函数的结尾，把他们从栈中弹出，恢复他们原始的值。


