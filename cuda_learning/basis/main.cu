#include <stdio.h>
#include <time.h>

__global__ void add(int* a, int* b, int* c, int num)
{
	//一个线程干的事情
	//当前线程的id，可以换成block的id
	int i = threadIdx.x;
	if(i < num)//防止溢出
	{
		c[i] = a[i] + b[i];
	}
}

int main(void)
{
	// init data
	int num = 10;
	int a[num], b[num], c[num];
	int *a_gpu, *b_gpu, *c_gpu;

	for(int i = 0; i < num; i++)
	{
		a[i] = i;
		b[i] = i * i;
	}

	cudaMalloc((void **)&a_gpu, num * sizeof(int)); //分配gpu的空间，不能直接分配，需要给指针的指针
	cudaMalloc((void **)&b_gpu, num * sizeof(int));
	cudaMalloc((void **)&c_gpu, num * sizeof(int));

	// copy data
	cudaMemcpy(a_gpu, a, num * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(b_gpu, b, num * sizeof(int), cudaMemcpyHostToDevice);//gpu的指针，原始数据，size， 状态

	// do
	//一块，十个线程（小项目）
	add<<1, num>>(a_gpu, b_gpu, c_gpu, num);

	// get data
	cudaMemcpy(c, c_gpu, num * sizeof(int), cudaMemcpyDeviceToHost);

	// visualization
	for(int i = 0; i < num; i++)
	{
		printf("%d + %d = %d\n", a[i], b[i], c[i]);
	}

	return 0;
}