#include "stdio.h"

static void HandleError(cudaError_t err,
                        const char *file,
                        int line)
                        {
                            if(err != cudaSuccess)
                            {
                                printf("%s in %s at line %d\n",
                                cudaGetErrorString(err),
                                file, line);
                                exit(EXIT_FAILURE);
                            }
                        }
#define HANDLE_ERROR(err) (HandleError(err, __FILE__, __LINE__))

// 查找线程
int getThreadNum()
{
    cudaDeviceProp prop;
    int count;//计算gpu

    HANDLE_ERROR(cudaGetDeviceCount(&count));
    printf("gpu num %d\n", count);
    HANDLE_ERROR(cudaGetDeviceProperties(&prop, 0));
    printf("max thread num: %d\n", prop.maxThreadsPerBlock);
    //block 由grid划分
    printf("max grid dimensions: %d, %d, %d)\n",
     prop.maxGridSize[0], prop.maxGridSize[1], prop.maxGridSize[2]);
    return prop.maxThreadsPerBlock;
}

//设备上的 + global
__global__ void conv(float *img, float *kernel, float *result, 
    int width, int height, int kernelSize)
    {
        // 每一次处理一个点
        int ti = threadIdx.x;
        int bi = blockIdx.x;
        int id = (bi * blockDim.x + ti); //图上的第几个点
        if(id >= width * height)
        {
            return;
        }
        int row = id / width;
        int col = id % width;
        for(int i = 0; i < kernelSize; ++i)
        {
            for(int j = 0; j < kernelSize; ++j)
            {
                float imgValue = 0;
                //中心点为row，col，kernalSize奇数
                int curRow = row - kernelSize / 2 + i;//在图上的坐标是第几位
                int curCol = col - kernelSize / 2 + j;
                if(curRow < 0 || curCol < 0 || curRow >= height || curCol >= width)
                {}
                else
                {
                    imgValue = img[curRow * width + curCol];
                }
                //kernel[i * kernelSize + j] 是kernal对应的点
                result[id] += kernel[i * kernelSize + j] * imgValue;
            }

        }
    }

int main()
{
    //定义图
    int width = 1920;
    int height = 1080;
    float *img = new float[width * height]; //img float指针对象
    //给graph赋值
    for(int row = 0; row < height; ++row)
    {
        for(int col = 0; col < width; ++col)
        {
            img[col + row * width] = (col + row) % 256;
        }
    }

    int kernelSize = 3;
    float *kernel = new float[kernelSize * kernelSize];
    for(int i = 0; i < kernelSize * kernelSize; ++i)
    {
        //检测竖着的纹路
        //++i性能更高，i++有一步复制操作，java自动优化
        // -1, 0, 1, -1, 0, 1
        kernel[i] = i % kernelSize - 1;
    }

    float *imgGpu;
    float *kernelGpu;
    float *resultGpu;

    //二重指针：c的malloc返回的是地址，cuda有可能错误（显卡驱动和cuda版本不对称：不能分配，一个指针返回的是错误信息-》再加一个指针）
    HANDLE_ERROR(cudaMalloc((void**)&imgGpu, width * height * sizeof(float)));
    HANDLE_ERROR(cudaMalloc((void**)&kernelGpu, kernelSize * kernelSize * sizeof(float)));
    HANDLE_ERROR(cudaMalloc((void**)&resultGpu, width * height * sizeof(float)));

    HANDLE_ERROR(cudaMemcpy(imgGpu, img,
     width * height * sizeof(float), cudaMemcpyHostToDevice));
    HANDLE_ERROR(cudaMemcpy(kernelGpu, kernel,
     kernelSize * kernelSize * sizeof(float), cudaMemcpyHostToDevice));
    
    int threadNum = getThreadNum();
    int blockNum = (width * height - 0.5) / threadNum + 1; //-0。5 防止整除

    conv<<<blockNum, threadNum>> >
        (imgGpu, kernelGpu, resultGpu, width, height, kernelSize);

    float *result = new float[width * height];
    HANDLE_ERROR(cudaMemcpy(result, resultGpu,
     width * height * sizeof(float), cudaMemcpyDeviceToHost));

    // visualization
    printf("img\n");
    for(int row = 0; row < 10; ++row)
    {
        for(int col = 0; col < 10; ++col)
        {
            printf("%2.0f ", img[col + row * width]);
        }
        printf("\n");
    }
    printf("kernel\n");
    for(int row = 0; row < kernelSize; ++row)
    {
        for(int col = 0; col < kernelSize; ++col)
        {
            printf("%2.0f ", kernel[col + row * kernelSize]);
        }
        printf("\n");
    }

    printf("result\n");
    for(int row = 0; row < 10; ++row)
    {
        for(int col = 0; col < 10; ++col)
        {
            printf("%2.0f ", result[col + row * width]);
        }
        printf("\n");
    }


    return 0;
}