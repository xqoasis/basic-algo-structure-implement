#include <stdio.h>

__global__ void sum(float *a, float *b)
{
	//thread id
	//all元素求值，放到新的共享列表里面
	//每个block有共享内存
	int tid = threadIdx.x;

	//变量写在share里面
	__shared__ float sData[16];
	sData[tid] = a[tid];//一个线程管的一位数字
	__syncthreads();//一个block的线程等待同步
	for(int i = 8; i > 0; i /= 2)
	{
		if(tid < i)
		{
			sData[tid] = sData[tid] + sData[tid + i];
		}
		__syncthreads();
	}
	if(tid == 0)
	{
		b[0] = sData[0];
	}
}

int main()
{
	//数组求和
	float a[16];
	//define value
	for(int i = 0; i < 16; i++)
	{
		a[i] = i*(i+1);
	}
	float *aGpu;
	cudaMalloc((void**)&aGpu, 16 * sizeof(float));
	cudaMemcpy(aGpu, a, 16 * sizeof(float), cudaMemcpyHostToDevice);

	float *bGpu;
	cudaMalloc((void**)&bGpu, 1 * sizeof(float));
	//一个block 16 thread
	sum<<<1, 16>> >(aGpu, bGpu);

	float b[1];
	cudaMemcpy(b, bGpu, 1 * sizeof(float), cudaMemcpyDeviceToHost);
	printf("b: %f\n",b[0]);
	return 0;
}