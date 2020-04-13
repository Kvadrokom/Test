#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct                s_list
{
  struct  s_list              *next;
  void                      *data;
}                             t_list;

t_list  *ft_create_element(void *data)
{

  t_list *tmp;
  tmp = (t_list*)malloc(sizeof(t_list));
  if(tmp)
  {
    tmp->next = 0;
    tmp->data = data;
  }
  return tmp;
}

void  ft_push_back(t_list **begin_list, void *data)
{
  t_list *list;

  list = ft_create_element(data);
  if(*begin_list == 0)
      *begin_list = list;
  else
  {
      list->next = *begin_list;
      *begin_list = list;
  }
}

char *make_str_from_int(int num)
{
    char c[20];
    int i;
    int k;
    char *tmp;

    i = 0;
    k = 0;
    while (num > 0)
    {
        c[i] = num % 10 + 48;
        num = num / 10;
        i++;
    }
    tmp = malloc(sizeof(char) * (i + 1));
    while (i > 0)
    {
        tmp[k] = c[i - 1];
        k++;
        i--;
    }
    tmp[k] = '\0';
    return (tmp);
}

void    ft_pop(t_list **begin_list)
{
    t_list *tmp;
    tmp = *begin_list;
    tmp = tmp->next;
    free(*begin_list);
    *begin_list = tmp;
}

int     last_op(t_list * list_int, t_list *list_op)
{
    int     num1;
    int     num2;
   // char    op;
    //char     *c;
    char    *a;

    //c = list_op->data;
    //op = c[0];
    while (list_op)
    {
        num2 = atoi(list_int->data);
        ft_pop(&list_int);
        num1 = atoi(list_int->data);
        ft_pop(&list_int);
        a = make_str_from_int(num1 + num2);
        ft_push_back(&list_int, a);
        ft_pop(&list_op);       
    }
    return (atoi(list_int->data));
}


void  print_list(t_list  *head)
{
  t_list  *tmp;

  tmp = head;
  while (tmp)
  {
   printf("%s\n", (char*)tmp->data);
    tmp = tmp->next;
  }
  printf("\n");
}

int main() 
{
  t_list *list_int;
  t_list *list_op;
  
  list_int = 0;
  list_op = 0;
  char    *c = "3 + (42 * 2 - 34) % 51 + 2";
  //char* a = make_str_from_int(76);
  ft_push_back(&list_int, &c[5]);
  ft_push_back(&list_int, &c[14]);
  ft_push_back(&list_op, &c[2]);
  int a =  last_op(list_int, list_op);
  printf("%d\n", a);
  print_list(list_int);
  return 0;
}