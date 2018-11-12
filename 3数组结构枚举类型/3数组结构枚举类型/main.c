#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//------------------------基本的数组声明-------------------------
int main1(){
	char A[12] = {0}; //由12个char元素组成
	char *B[8] = {0}; //包含8个指向char类型的指针数组
	int C[6] = {0}; //由6个int元素组成
	double *D[5] = {0};//包含5个指向double类型的指针数组
	return 0;
}
//Tips:内存引用指令可以用来简化数组的访问，假设E是一个int型的数组，而我们想计算E[i],在此，E的地址存放在寄存器rdx中，而i存放在rcx中，然后指令movl (%rdx,%rcx,4),%eax会执行地址计算 E+ 4i,并将结果存放到寄存器eax中

//------------------------指针运算-------------------------
int main2(){
	int a = 10;
	int *p; //声明一个指针类型，指向一个int类型
	p = &a; // &符号的作用是产生一个指针，将a变量的地址赋值给P指针
	*p = 30; //*符号的作用是间接的引用指针，将30赋值给P指针指向的内存空间
	char buf[20] = { 0 };
	char *p2 = buf; //将数组的地址赋值给一个p2指针
	p2[0] = 20; //等同于*(p + 0) = 20
	p2[1] = 30; //等同于*(p + 1) = 30 ,这里的p + 1 = p的地址 + L数据类型的大小 * 1
	return 0;
}

//--------------------------嵌套数组---------------------------------
int main3(){
	char buf[2][3] = {0}; //二维数组，由一个2 x 3大小的数据组成
	char (*p)[3] = buf; //指向二维数组的指针
	//char **p = buf;//会提醒类型不匹配
	//printf("%x", p);//打印不出来值
	printf("buf_address = %x,p_address = %x", buf, p);
	buf[2][3] = 10; //相当于 *(*(buf + 2) + 1) = 10
	p[2][3] = 30; //P也指向了数组的初始地址，所以，改变的同样是buf数组，结果打印出来了.
	//但是会提醒，可能会引起栈越界.
	printf("%d", buf[2][3]);
}

//-----------------------变长数组---------------------------------
int main4(){
	return 0;
}

//------------------结构-----------------------
//创建一个结构
struct rect {
	long llx;
	long lly;
	unsigned long width;
	unsigned long height;
	unsigned color;
};
//声明一个struct rect类型的变量r,并将它的字段值设置为如下:
//struct rect r;
//r.llx = r.lly = 0;
//r.color = 0xFF00FF;
//r.width = 10;
//r.height = 20;
//可以简写为
struct rect r = { 0, 0, 10, 20, 0xFF00FF };
long area(struct rect *rp){
	return rp->width * rp->height;//等同于 (*rp).width * (*rp).height
}
int main5(){
	//将结构作为一个函数参数传递给另外一个函数是很常见的
	unsigned long result = area(&r);
	printf("%ld", result);
}

//---------------------联合------------------------------
union U3 {
	char c;
	int i[2];
	double v;
};
int main6(){

}


//---------------------函数指针--------------------
void hello(){
	printf("hello world");
}
int main(){
	void(*fp)();//创建一个指向函数的指针
	fp = hello;
	hello();
	return 0;
}