#include "bfg_internal.h"

bfg_status bfgInitStack(bfg_stack stack)
{
    BFG_CHECK_NULL(stack);

    ((bfg_stack_t*)stack)->capacity = 0;
    ((bfg_stack_t*)stack)->page = 1;
    return bfgAddStackPage(stack);
}

bfg_status bfgAddStackPage(bfg_stack stack)
{
    BFG_CHECK_NULL(stack);

    bfg_status status = BFG_SUCCESS;
    if(((bfg_stack_t*)stack)->capacity >= STACK_MAX_PAGES)
    {
        status = BFG_FULLSTACK;
        BFG_PRINT("Stack is full!\n");
    }
    else
    {
        ((bfg_stack_t*)stack)->pages[((bfg_stack_t*)stack)->capacity] = (bfg_page_t*)malloc(sizeof(bfg_page_t));
        ((bfg_stack_t*)stack)->pages[((bfg_stack_t*)stack)->capacity]->field = 0;
        memset(((bfg_stack_t*)stack)->pages[((bfg_stack_t*)stack)->capacity]->mem, 0, sizeof(bfg_data_t) * STACK_PAGE_SIZE);
        ((bfg_stack_t*)stack)->capacity++;
    }
    return status;
}

bfg_bool bfgStackIsEmpty(bfg_stack stack)
{
    BFG_CHECK_NULL(stack);
    bfg_bool res = bfg_false;
    if(((bfg_stack_t*)stack)->page <= 1)
    {
        bfg_page_t* page = ((bfg_stack_t*)stack)->pages[((bfg_stack_t*)stack)->page - 1];
        if(page->field == 0)
            res = bfg_true;
    }
    return res;
}

bfg_status bfgPushStack(bfg_stack stack, bfg_data_t* data)
{
    BFG_CHECK_NULL(stack);
    BFG_CHECK_NULL(data);
    BFG_CHECK_NULL(data->mem);

    bfg_status status;
    bfg_bool mem_size_check = bfg_false;
    switch(data->type)
    {
    case BFG_DATA_SIMPLE:
        if(data->data_size == sizeof(bfg_int))
            mem_size_check = bfg_true;
        break;
    case BFG_DATA_USER:
        if(data->data_size > 0)
            mem_size_check = bfg_true;
        break;
    default:
        BFG_PRINT("Unsupported stack data type(%d)!\n", data->type);
        return BFG_UNSUPPORTED_TYPE;
    }
    if(mem_size_check == bfg_true)
    {
        bfg_page_t* page = ((bfg_stack_t*)stack)->pages[((bfg_stack_t*)stack)->page - 1];
        if(page->field >= STACK_PAGE_SIZE)
        {
            if(((bfg_stack_t*)stack)->page >= ((bfg_stack_t*)stack)->capacity)
            {
                status = bfgAddStackPage(stack);
                if(status != BFG_SUCCESS)
                    return status;
            }
            ((bfg_stack_t*)stack)->page++;
            page = ((bfg_stack_t*)stack)->pages[((bfg_stack_t*)stack)->page - 1];
        }
        page->field++;
        bfg_data_t* stack_mem = &page->mem[page->field - 1];
        stack_mem->type = data->type;
        stack_mem->data_size = data->data_size;
        stack_mem->mem = malloc(data->data_size);
        memcpy(stack_mem->mem, data->mem, data->data_size);
    }
    else
    {
        return BFG_WRONG_MEM_SIZE;
    }
    return BFG_SUCCESS;
}

bfg_status bfgPopStack(bfg_stack stack, bfg_data_t* data)
{
    BFG_CHECK_NULL(stack);

    if(bfgStackIsEmpty(stack) == bfg_true)
    {
        return BFG_STACK_IS_EMPTY;
    }

    bfg_page_t* page = ((bfg_stack_t*)stack)->pages[((bfg_stack_t*)stack)->page - 1];
    bfg_data_t* stack_mem = &page->mem[page->field - 1];
    if(data != NULL)
    {
        BFG_CHECK_NULL(data->mem);
        if(stack_mem->type != data->type)
            return BFG_WRONG_DATA_TYPE;

        if(stack_mem->data_size != data->data_size)
            return BFG_WRONG_MEM_SIZE;

        memcpy(data->mem, stack_mem->mem, stack_mem->data_size);
    }
    free(stack_mem->mem);
    stack_mem->mem = NULL;
    if(page->field == 1)
    {
        page->field = 0;
        if(((bfg_stack_t*)stack)->page > 1)
            ((bfg_stack_t*)stack)->page--;
    }
    else
    {
        page->field--;
    }
    return BFG_SUCCESS;
}

bfg_status bfgReleaseStack(bfg_stack stack)
{
    BFG_CHECK_NULL(stack);

    int p, f;
    for(p = 0; p < ((bfg_stack_t*)stack)->page; p++)
    {
        for(f = 0; f < ((bfg_stack_t*)stack)->pages[p]->field; f++)
        {
            free(((bfg_stack_t*)stack)->pages[p]->mem[f].mem);
        }
    }
    for(p = 0; p < ((bfg_stack_t*)stack)->capacity; p++)
    {
        free(((bfg_stack_t*)stack)->pages[p]);
    }
    return BFG_SUCCESS;
}
