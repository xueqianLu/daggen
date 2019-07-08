// Last Update:2018-05-25 15:26:32
/**
 * @file gen_dag.c
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2018-05-25
 */


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "ethash.h"

int ethash_callback(unsigned p)
{
    printf("[%d]progress %03d%%\n", (int32_t)time(NULL), p);
    return 0;
}

int dag_general(int argc, char *argv[])
{
    uint64_t block_number = 0;
    char *dir_name = NULL;
    if(argc < 3)
    {
        printf("usage: %s block_number dirname\n", argv[0]);
    }
    block_number = atol(argv[1]);
    dir_name = argv[2];
    ethash_light_t light = ethash_light_new(block_number);
    if(light == NULL)
    {
        printf("create light node failed.\n");
        return -1;
    }
    ethash_full_t full = ethash_full_new_dir(dir_name, light, ethash_callback);
    if(full == NULL)
    {
        printf("dag general failed.\n");
        return -2;
    }
    ethash_full_dag_file(full);
    printf("dag general successful at %s.\n", dir_name);
    ethash_full_delete(full);
    ethash_light_delete(light);
    return 0;
}

int main(int argc, char *argv[])
{
    dag_general(argc, argv);
    return 0;
}
