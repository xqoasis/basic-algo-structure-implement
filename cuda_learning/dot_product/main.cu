#include <stdio.h>

#define LENGTH 16
#define BLOCKNUM 2
#define THREADNUM 4
__global__ void dot_product(float *a, float *b, float* r)
{
	int tid = threadIdx.x;
	int bid = blockIdx.x;
	int total_thread_num = THREADNUM * BLOCKNUM;

	__shared__ float sData[THREADNUM]; //sData[0] = a[0] * b[0] + a[8] * b[8] ...
	int global_id = tid + bid * THREADNUM; //总的第几位(从block0开始数)
	sData[tid] = 0;//初始值
	while(global_id < LENGTH)
	{
		sData[tid] += a[global_id] * b[global_id];
		global_id += total_thread_num;//0， 8， 。。。
	}
	__syncthreads();
	for(int i = THREADNUM/2; i > 0; i /= 2)
	{
		if(tid < i)
		{
			//内存连续，s[0] = s[0] + s[4] -> s[0] = s[0] + s[2]
			sData[tid] = sData[tid] + sData[tid + i];
		}
		__syncthreads();
	}
	if(tid == 0)
	{
		//多个block
		r[bid] = sData[0];
	}
}

int main()
{
	float a[LENGTH];
	float b[LENGTH];
	for(int i = 0; i < LENGTH; i++)
	{
		a[i] = i*(i+1);
		b[i] = i*(i-2);
	}
	float *aGpu;
	cudaMalloc((void**)&aGpu, LENGTH * sizeof(float));
	cudaMemcpy(aGpu, a, LENGTH * sizeof(float), cudaMemcpyHostToDevice);

	float *bGpu;
	cudaMalloc((void**)&bGpu, LENGTH * sizeof(float));
	cudaMemcpy(bGpu, b, LENGTH * sizeof(float), cudaMemcpyHostToDevice);

	float *rGpu;
	cudaMalloc((void**)&rGpu, BLOCKNUM * sizeof(float));
	dot_product<<<BLOCKNUM, LENGTH>> >(aGpu, bGpu, rGpu);

	float r[BLOCKNUM];
	cudaMemcpy(r, rGpu, BLOCKNUM * sizeof(float), cudaMemcpyDeviceToHost);

	float result = 0;
	for(int i = 0; i < BLOCKNUM; i++)
	{
		result += r[i];
	}
	printf("result: %f\n",result);
	return 0;
}