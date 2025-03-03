#include <stdio.h>
#include <stdlib.h>


typedef struct s_list
{
	struct s_list	*next;
	int				data;
}	t_list;

t_list	*lst_new(int data)
{
	t_list *node;

	node = malloc(sizeof(t_list));
	node->data = data;
	node->next = NULL;
	return (node);
}

void	add_back(t_list **head, int data)
{	
	if (!head)
		return;
	t_list *current = *head;
	t_list *new_node = lst_new(data);
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	new_node->next = NULL;
	return ;
}

void	lst_print(t_list *head)
{
	if (head == NULL)
		return ;
	while (head != NULL)
	{
		printf("%d->", head->data);
		head = head->next;
	}
	printf("NULL");
}

int main()
{
	t_list *head;
	head = NULL;
	add_back(&head, 10);
	add_back(&head, 50);
	add_back(&head, 30);
	lst_print(head);
}