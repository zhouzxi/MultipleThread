/**********************************************************************
* 版权所有 (C)2015, Zhou Zhaoxiong。
*
* 文件名称：MultipleThread_3.c
* 文件标识：无
* 内容摘要：多线程中的变量值问题
* 其它说明：无
* 当前版本：V1.0
* 作    者：Zhou Zhaoxiong
* 完成日期：20151117
*
**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// 重定义数据类型
typedef signed   int    INT32;
typedef unsigned int    UINT32;

// 宏定义
#define THREAD_NUM     100              // 线程个数

// 全局变量
UINT32 g_iTestInteger = 0;

// 函数声明
void ProcessTask(void *pParam);
void Sleep(UINT32 iCountMs);


/**********************************************************************
* 功能描述：主函数
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：无
* 修改日期        版本号     修改人            修改内容
* -------------------------------------------------------------------
* 20151117        V1.0     Zhou Zhaoxiong        创建
***********************************************************************/
INT32 main()
{
    pthread_t MultiHandle  = 0;      // 多线程句柄
    pthread_t SingleHandle = 0;     // 单线程句柄
    UINT32    iLoopFlag    = 0;
    INT32     iRetVal      = 0;  // 创建线程函数的返回值

    // 循环创建线程
    for (iLoopFlag = 0; iLoopFlag < THREAD_NUM; iLoopFlag ++)
    {
        iRetVal = pthread_create(&MultiHandle, NULL, (void * (*)(void *))(&ProcessTask), (void *)iLoopFlag);
        if (0 != iRetVal)
        {
            printf("Create ProcessTask %d failed!\n", iLoopFlag);
            return -1;
        }
    }
	
    Sleep(1000);   // 休息1s
	
    // 打印全局变量的值
    printf("In main, TestInteger = %d\n", g_iTestInteger);

    return 0;   
}


/**********************************************************************
 * 功能描述： 处理线程
 * 输入参数： pParam-线程编号
 * 输出参数： 无
 * 返 回 值： 无
 * 其它说明： 无
 * 修改日期            版本号            修改人           修改内容
 * ----------------------------------------------------------------------
*  20151117            V1.0          Zhou Zhaoxiong        创建
 ************************************************************************/
void ProcessTask(void *pParam)
{
    g_iTestInteger ++;
}


/**********************************************************************
* 功能描述： 程序休眠
* 输入参数： iCountMs-休眠时间(单位:ms)
* 输出参数： 无
* 返 回 值： 无
* 其它说明： 无
* 修改日期          版本号       修改人              修改内容
* ------------------------------------------------------------------
* 20151117          V1.0     Zhou Zhaoxiong           创建
********************************************************************/
void Sleep(UINT32 iCountMs)
{
    struct timeval t_timeout = {0};
 
    if (iCountMs < 1000)
    {
        t_timeout.tv_sec = 0;
        t_timeout.tv_usec = iCountMs * 1000;
    }
    else
    {
        t_timeout.tv_sec = iCountMs / 1000;
        t_timeout.tv_usec = (iCountMs % 1000) * 1000;
    }
    select(0, NULL, NULL, NULL, &t_timeout);   // 调用select函数阻塞程序
}
