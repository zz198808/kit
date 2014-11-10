/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file bb.c
 * @author zhangzhao01(com@baidu.com)
 * @date 2014/11/09 14:46:16
 * @brief 
 *  
 **/
#include<stdio.h>
#include<stdlib.h>

struct Info
{
    int age;
    //char* name;//由于*name指向的内容是别的地方，因此info写二进制的时候只写了name的地址，而不是值
    char name[1024];//所有最好用连续分配内存的char name[]
};

int main()
{
    FILE *fwRun = fopen("testFile","wb");
    struct Info* info= (struct Info*)malloc(sizeof(struct Info));
    //info->name = (char*)malloc(100);
    int index=0;
    const char* z_name="zhangsan";
    for(;index<1000;index++)
    {
        char buffer[100]="";
        info->age=index;
        sprintf(buffer,"%s%d",z_name,index);
       //sprintf(info->name,"%s%d",z_name,index);//这样是可以的
        //printf("%s",buffer);
        strcpy(info->name,buffer);//数组的话不能直接赋值，必须采用拷贝的方式
        //info->name = buffer ; //这样打印出来都是zhangsan999，因为name始终是存的buffer的地址，buffer内容最后一次被修改为zhangsan999
        fwrite(info,sizeof(struct Info),1,fwRun);
        fflush(fwRun);
    }
    //close(fwRun);
    index=0;
    //struct Info* read_info= (struct Info*)malloc(sizeof(struct Info));
    //FILE *frRun = fopen("testFile","rb");
    fwRun = fopen("testFile","rb");
    for(;index<10;index++)
    {
        fread(info,sizeof(struct Info),1,fwRun);
        printf("age is %d\n",info->age);
        printf("name is %s\n",info->name);
    }
    close(fwRun);
    return 0;
}



/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
