#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_mylist
{
    int             value;
    int             index;
    int             pos;
    int             cost_a;
    int             cost_b;
    struct s_mylist *next;
}                   t_mylist;

/* ==================== LIBFT FUNCTIONS ==================== */
size_t ft_strlen(const char *s)
{
    size_t len = 0;
    while (s[len])
        len++;
    return len;
}

char *ft_strdup(const char *s1)
{
    char *copy;
    size_t len = ft_strlen(s1) + 1;

    copy = malloc(len);
    if (!copy)
        return NULL;
    for (size_t i = 0; i < len; i++)
        copy[i] = s1[i];
    return copy;
}

int ft_count_words(char const *s, char c)
{
    int count = 0;
    int in_word = 0;

    while (*s)
    {
        if (*s != c && !in_word)
        {
            in_word = 1;
            count++;
        }
        else if (*s == c)
            in_word = 0;
        s++;
    }
    return count;
}

char *ft_get_word(char const *s, char c, int *i)
{
    char *word;
    int start = *i;
    int len = 0;

    while (s[*i] && s[*i] != c)
    {
        (*i)++;
        len++;
    }
    word = malloc(len + 1);
    if (!word)
        return NULL;
    for (int j = 0; j < len; j++)
        word[j] = s[start + j];
    word[len] = '\0';
    return word;
}

char **ft_split(char const *s, char c)
{
    int word_count = ft_count_words(s, c);
    char **result = malloc(sizeof(char *) * (word_count + 1));
    int i = 0;
    int word_index = 0;

    if (!s || !result)
        return NULL;
        
    while (word_index < word_count)
    {
        while (s[i] && s[i] == c)
            i++;
        if (s[i])
        {
            result[word_index] = ft_get_word(s, c, &i);
            if (!result[word_index])
            {
                while (word_index > 0)
                    free(result[--word_index]);
                free(result);
                return NULL;
            }
            word_index++;
        }
    }
    result[word_count] = NULL;
    return result;
}

/* ==================== LIST UTILS ==================== */
void free_list(t_mylist **lst)
{
    t_mylist *current = *lst;
    t_mylist *next;

    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *lst = NULL;
}

t_mylist *createnode(int value, int index_count)
{
    t_mylist *node = malloc(sizeof(t_mylist));
    if (!node)
        return NULL;
    node->value = value;
    node->index = index_count;
    node->next = NULL;
    return node;
}

void addback(t_mylist **List, int value)
{
    t_mylist *node = createnode(value, 0);
    t_mylist *current;

    if (!*List)
    {
        *List = node;
        return;
    }
    current = *List;
    while (current->next)
        current = current->next;
    current->next = node;
}

void add_front(t_mylist **lst, t_mylist *new)
{
    new->next = *lst;
    *lst = new;
}

int countlist(t_mylist *head)
{
    int count = 0;
    t_mylist *current = head;

    while (current)
    {
        count++;
        current = current->next;
    }
    return count;
}

/* ==================== MEMORY UTILS ==================== */
void free_tableau(char **tab)
{
    int i = 0;
    if (!tab)
        return;
    while (tab[i])
        free(tab[i++]);
    free(tab);
}

char **get_args(int ac, char **av)
{
    char **args;
    int i = 0;

    if (ac == 1)
        return NULL;
    if (ac == 2)
        return ft_split(av[1], ' ');
    
    args = malloc(sizeof(char *) * ac);
    if (!args)
        return NULL;
    while (i < ac - 1)
    {
        args[i] = ft_strdup(av[i + 1]);
        if (!args[i])
        {
            free_tableau(args);
            return NULL;
        }
        i++;
    }
    args[ac - 1] = NULL;
    return args;
}

/* ==================== INPUT VALIDATION ==================== */
int is_space(char c)
{
    return (c == 32 || (c >= 9 && c <= 13));
}

long ft_atoi_modif(char *str)
{
    long res = 0;
    int minus = 1;

    if (!str || !*str)
        return 99999999999999;
    
    while (is_space(*str))
        str++;
    
    if (*str == '-' || *str == '+')
        if (*str++ == '-')
            minus *= -1;
    
    while (*str >= '0' && *str <= '9')
    {
        res = res * 10 + (*str - '0');
        str++;
        if ((minus == -1 && res > (long)INT_MAX + 1) || 
            (minus == 1 && res > INT_MAX))
            return 99999999999999;
    }
    return (*str ? 99999999999999 : res * minus);
}

int check_duplicates(t_mylist *stack)
{
    t_mylist *cur;
    t_mylist *runner;

    cur = stack;
    while (cur)
    {
        runner = cur->next;
        while (runner)
        {
            if (cur->value == runner->value)
                return 1;
            runner = runner->next;
        }
        cur = cur->next;
    }
    return 0;
}

int sorted_list(t_mylist *stack)
{
    t_mylist *cur = stack;

    while (cur && cur->next)
    {
        if (cur->value > cur->next->value)
            return 0;
        cur = cur->next;
    }
    return 1;
}

int put_in_struct(t_mylist **List, char **av)
{
    long num;

    if (!av || !*av)
        return 1;
        
    for (int i = 0; av[i]; i++)
    {
        num = ft_atoi_modif(av[i]);
        if (num == 99999999999999 || num > INT_MAX || num < INT_MIN)
            return 1;
        addback(List, (int)num);
    }
    return 0;
}

/* ==================== STACK OPERATIONS ==================== */
void swap(t_mylist **stack, char *name)
{
    int temp;
    if (!stack || !*stack || !(*stack)->next)
        return;
    
    temp = (*stack)->value;
    (*stack)->value = (*stack)->next->value;
    (*stack)->next->value = temp;
    
    if (name)
    {
        write(1, name, ft_strlen(name));
        write(1, "\n", 1);
    }
}

void push(t_mylist **src, t_mylist **dst, char *name)
{
    t_mylist *top;
    
    if (!src || !*src)
        return;
    
    top = *src;
    *src = top->next;
    top->next = *dst;
    *dst = top;
    
    if (name)
    {
        write(1, name, ft_strlen(name));
        write(1, "\n", 1);
    }
}

void rotate(t_mylist **stack, char *name)
{
    t_mylist *first;
    t_mylist *last;
    
    if (!stack || !*stack || !(*stack)->next)
        return;
    
    first = *stack;
    *stack = first->next;
    first->next = NULL;
    
    last = *stack;
    while (last->next)
        last = last->next;
    last->next = first;
    
    if (name)
    {
        write(1, name, ft_strlen(name));
        write(1, "\n", 1);
    }
}

void reverse_rotate(t_mylist **stack, char *name)
{
    t_mylist *last;
    t_mylist *prev;
    
    if (!stack || !*stack || !(*stack)->next)
        return;
    
    prev = NULL;
    last = *stack;
    while (last->next)
    {
        prev = last;
        last = last->next;
    }
    
    prev->next = NULL;
    last->next = *stack;
    *stack = last;
    
    if (name)
    {
        write(1, name, ft_strlen(name));
        write(1, "\n", 1);
    }
}

/* ==================== STACK OPERATIONS 2 ==================== */
void rr(t_mylist **a, t_mylist **b)
{
    rotate(a, NULL);
    rotate(b, NULL);
    write(1, "rr\n", 3);
}

void rrr(t_mylist **a, t_mylist **b)
{
    reverse_rotate(a, NULL);
    reverse_rotate(b, NULL);
    write(1, "rrr\n", 4);
}

void rotate_times(t_mylist **stack, int *cost, char *rot_name, char *rev_name)
{
    while (*cost > 0)
    {
        rotate(stack, rot_name);
        (*cost)--;
    }
    while (*cost < 0)
    {
        reverse_rotate(stack, rev_name);
        (*cost)++;
    }
}

/* ==================== QUICKSORT UTILS ==================== */
void ft_swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int *tab, int start, int end)
{
    int pivot = tab[end];
    int i = start;
    
    for (int j = start; j < end; j++)
    {
        if (tab[j] < pivot)
            ft_swap(&tab[i++], &tab[j]);
    }
    ft_swap(&tab[i], &tab[end]);
    return i;
}

void quicksort(int *tab, int start, int end)
{
    if (start >= end)
        return;
    
    int pivot = partition(tab, start, end);
    quicksort(tab, start, pivot - 1);
    quicksort(tab, pivot + 1, end);
}

int *get_sorted_array(t_mylist *a, int size)
{
    int *tab = malloc(size * sizeof(int));
    if (!tab)
        return NULL;
    
    for (int i = 0; i < size; i++)
    {
        tab[i] = a->value;
        a = a->next;
    }
    quicksort(tab, 0, size - 1);
    return tab;
}

int get_position(t_mylist *stack, int index_to_find)
{
    int pos = 0;
    while (stack)
    {
        if (stack->index == index_to_find)
            return pos;
        pos++;
        stack = stack->next;
    }
    return -1;
}

/* ==================== SORT OPERATIONS ==================== */
void sort_two(t_mylist **stack)
{
    if ((*stack)->value > (*stack)->next->value)
        swap(stack, "sa");
}

void sort_three(t_mylist **stack)
{
    int a = (*stack)->value;
    int b = (*stack)->next->value;
    int c = (*stack)->next->next->value;

    if (a > b && b < c && a < c) swap(stack, "sa");
    else if (a > b && b < c && a > c) rotate(stack, "ra");
    else if (a > b && b > c) { rotate(stack, "ra"); swap(stack, "sa"); }
    else if (a < b && b > c && a < c) { reverse_rotate(stack, "rra"); swap(stack, "sa"); }
    else if (a < b && b > c) reverse_rotate(stack, "rra");
}

int find_smallest(t_mylist **stack_a)
{
    t_mylist *cur = *stack_a;
    int min = cur->value;
    int pos = 0;
    int i = 0;

    while (cur)
    {
        if (cur->value < min)
        {
            min = cur->value;
            pos = i;
        }
        i++;
        cur = cur->next;
    }
    return pos;
}

void push_to_b(t_mylist **a, t_mylist **b)
{
    int size = countlist(*a);
    int pos = find_smallest(a);
    int rotations;

    if (pos <= size / 2)
        while (pos--) rotate(a, "ra");
    else
    {
        rotations = size - pos;
        while (rotations--) reverse_rotate(a, "rra");
    }
    push(a, b, "pb");
}

void sort_five(t_mylist **a, t_mylist **b)
{
    push_to_b(a, b);
    push_to_b(a, b);
    if (countlist(*a) == 3) sort_three(a);
    else if (countlist(*a) == 2) sort_two(a);
    push(b, a, "pa");
    push(b, a, "pa");
}

void small_sort(t_mylist **a, t_mylist **b)
{
    int size = countlist(*a);
    if (size == 2) sort_two(a);
    else if (size == 3) sort_three(a);
    else if (size <= 5) sort_five(a, b);
}

/* ==================== MAIN ALGO ==================== */
void get_index_for_list(int *tab, t_mylist *head, int size)
{
    t_mylist *cur;
    for (int i = 0; i < size; i++)
    {
        cur = head;
        while (cur)
        {
            if (cur->value == tab[i])
            {
                cur->index = i;
                break;
            }
            cur = cur->next;
        }
    }
}

int get_position_of_min(t_mylist *a)
{
    int min_index = a->index;
    int min_pos = 0;
    int i = 0;
    t_mylist *cur = a;

    while (cur)
    {
        if (cur->index < min_index)
        {
            min_index = cur->index;
            min_pos = i;
        }
        i++;
        cur = cur->next;
    }
    return min_pos;
}

int get_insert_position(t_mylist *a, int index_b)
{
    int i = 0;
    t_mylist *cur = a;

    while (cur->next)
    {
        if (cur->index < index_b && cur->next->index > index_b)
            return i + 1;
        i++;
        cur = cur->next;
    }
    if (index_b < a->index) return 0;
    return i + 1;
}

int get_target_position_in_a(t_mylist *a, int index_b)
{
    int pos = get_insert_position(a, index_b);
    if (pos != -1) return pos;
    return get_position_of_min(a);
}

void calculate_move_cost(t_mylist *a, t_mylist *b)
{
    int size_a = countlist(a);
    int size_b = countlist(b);
    t_mylist *cur = b;
    int pos_b, target_a;

    while (cur)
    {
        pos_b = get_position(b, cur->index);
        target_a = get_target_position_in_a(a, cur->index);
        
        cur->cost_b = (pos_b <= size_b / 2) ? pos_b : pos_b - size_b;
        cur->cost_a = (target_a <= size_a / 2) ? target_a : target_a - size_a;
        
        cur = cur->next;
    }
}

/* ==================== MAIN ALGO 2 ==================== */
int ft_abs(int n) { return (n < 0) ? -n : n; }

t_mylist *find_cheapest_move(t_mylist *b)
{
    t_mylist *best = b;
    int best_cost = ft_abs(b->cost_a) + ft_abs(b->cost_b);
    t_mylist *cur = b->next;

    while (cur)
    {
        int cost = ft_abs(cur->cost_a) + ft_abs(cur->cost_b);
        if (cost < best_cost)
        {
            best_cost = cost;
            best = cur;
        }
        cur = cur->next;
    }
    return best;
}

void execute_move(t_mylist **a, t_mylist **b, t_mylist *move)
{
    int cost_a = move->cost_a;
    int cost_b = move->cost_b;

    while (cost_a > 0 && cost_b > 0 && rr(a, b), cost_a--, cost_b--) {}
    while (cost_a < 0 && cost_b < 0 && rrr(a, b), cost_a++, cost_b++) {}
    rotate_times(a, &cost_a, "ra", "rra");
    rotate_times(b, &cost_b, "rb", "rrb");
    push(b, a, "pa");
}

void align_stack_a(t_mylist **a)
{
    int size = countlist(*a);
    int pos = 0;
    t_mylist *cur = *a;

    while (cur && cur->index != 0)
    {
        pos++;
        cur = cur->next;
    }

    if (pos <= size / 2)
        while (pos--) rotate(a, "ra");
    else
        while (pos++ < size) reverse_rotate(a, "rra");
}

/* ==================== OPTIMIZED ==================== */
int calculate_chunk_size(int size)
{
    return (size <= 100) ? 15 : 30;
}

void push_to_b_fast(t_mylist **a, t_mylist **b)
{
    int size = countlist(*a);
    int index = 0;
    int pos;

    while (countlist(*a) > 3)
    {
        pos = get_position(*a, index);
        if (pos <= size / 2)
            while (pos--) rotate(a, "ra");
        else
            while (pos++ < size) reverse_rotate(a, "rra");
        push(a, b, "pb");
        index++;
    }
}

/* ==================== PUSH_SWAP MAIN ALGO ==================== */
void push_swap(t_mylist **a, t_mylist **b)
{
    int size = countlist(*a);
    int *sorted;

    if (size <= 1 || sorted_list(*a))
        return;

    sorted = get_sorted_array(*a, size);
    if (!sorted)
        return;
    
    get_index_for_list(sorted, *a, size);
    free(sorted);

    if (size <= 5)
        return small_sort(a, b);
    
    while (countlist(*a) > 3)
        push_to_b(a, b);
    sort_three(a);
    
    while (*b)
    {
        calculate_move_cost(*a, *b);
        t_mylist *move = find_cheapest_move(*b);
        execute_move(a, b, move);
    }
    align_stack_a(a);
}

/* ==================== MAIN FUNCTION ==================== */
int main(int ac, char **av)
{
    t_mylist *stack_a = NULL;
    t_mylist *stack_b = NULL;
    char **args = get_args(ac, av);

    if (ac < 2 || !args || put_in_struct(&stack_a, args) != 0)
    {
        write(2, "Error\n", 6);
        free_tableau(args);
        return 1;
    }
    free_tableau(args);

    if (check_duplicates(stack_a))
    {
        write(2, "Error\n", 6);
        free_list(&stack_a);
        return 1;
    }

    push_swap(&stack_a, &stack_b);
    free_list(&stack_a);
    free_list(&stack_b);
    return 0;
}