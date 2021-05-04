#include "list.h"

node_t *createnode(int data, int height)
{
    node_t *node = malloc(sizeof(node_t));
    if (node)
    {
        node->data = data;
        node->height = height;
        node->right = NULL;
        node->left = NULL;
    }
    else
    {
        node = NULL;
    }

    return node;    
}

node_t *find(node_t *head, int key)
{
    node_t *cur = NULL;
    if (head != NULL)
    {
        if (key == head->data)
        {
            return head;
        }
        else if (key < head->data)
        {
            cur = find(head->left, key);
        }
        else if (key > head->data)
        {
            cur = find(head->right, key);
        }
    }
    return cur;
}

node_t *insert(node_t *head, node_t *node, int *rc)
{
    (*rc)++;
    if (head == NULL)
    {
        return node;
    }
    else
    {
        if (node->data < head->data)
        {
            head->left = insert(head->left, node, rc);
        }
        else if (node->data > head->data)
        {
            head->right = insert(head->right, node, rc);
        }
        else if (node->data == head->data)
        {
            free(node);
            return head;
        }
    }

    return head;    
}

int whatheight(node_t *head)
{
    return head ? head->height : 0;
}

void newheight(node_t *head)
{
    int hl = whatheight(head->left);
    int hr = whatheight(head->right);
    head->height = ((hl > hr) ? hl : hr) + 1;
}

int factorlr(node_t *head)
{
    return whatheight(head->right) - whatheight(head->left);
}

node_t *returnright(node_t *head)
{
    node_t *buf = head->left;
    head->left = buf->right;
    buf->right = head;
    newheight(head);
    newheight(buf);

    return buf;
}

node_t *returnleft(node_t *head)
{
    node_t *buf = head->right;
    head->right = buf->left;
    buf->left = head;

    newheight(head);
    newheight(buf);

    return buf;
}

node_t *balancenode(node_t *head)
{
    newheight(head);
    if (factorlr(head) == 2)
    {
        if (factorlr(head->right) < 0)
        {
            head->right = returnright(head->right);
        }
        return returnleft(head);
    }
    if (factorlr(head) == -2)
    {
        if (factorlr(head->left) > 0)
        {
            head->left = returnleft(head->left);
        }
        return returnright(head);
    }

    return head;

}
node_t *insertbalance(node_t *head, node_t *node, int *rc)
{
    (*rc)++;
    if (head == NULL)
    {
        return node;
    }
    
    if (node->data < head->data)
    {
        head->left = insertbalance(head->left, node, rc);
    }
    else if (node->data > head->data)
    {
        head->right = insertbalance(head->right, node, rc);
    }
    else if (node->data == head->data)
    {
        return head;
    }

    return balancenode(head);
}

void printtree(node_t *head, int down, int strelochka)
{
    if (head)
    {
        printtree(head->right, down + 1, 2);
        for (int i = 0; i < down; i++)
        {
            printf("       ");
        }
        if (strelochka == 1)
        {
            printf(" ➘ ");
        }
        else if (strelochka == 2)
        {
            printf(" ➚ ");
        }
        else if (strelochka == 0)
        {
            printf("   ");
        }

        printf(" %d\n", head->data);
        
        printtree(head->left, down + 1, 1);
    }
}

void freetreenode(node_t *head, void *p)
{
    if (head)
    {
        free(head);
    }
    head = NULL;
}

void freetree(node_t *head)
{
    if (head)
    {
        apply_po(head, freetreenode, NULL);
    }
}

void exporttodot(FILE *f, node_t *head)
{
    fprintf(f, "digraph %s {\n", "my_graph");
    apply_pre(head, todot, f);
    fprintf(f, "}\n");
}

void todot(node_t *head, void *p)
{
    FILE *f = p;

    if (head->left)
    {
        fprintf(f, "%d -> %d;\n", head->data, head->left->data);
    }

    if (head->right)
    {
        fprintf(f, "%d -> %d;\n", head->data, head->right->data);
    }
}

void apply_pre(node_t *head, void (*f)(node_t *, void *), void *arg)
{
    if (head == NULL)
    {
        return;
    }
    
    f(head, arg);
    apply_pre(head->right, f, arg);
    apply_pre(head->left, f, arg);
}

void apply_po(node_t *head, void (*f)(node_t *, void *), void *arg)
{
    if (head == NULL)
    {
        return;
    }
    
    apply_po(head->right, f, arg);
    apply_po(head->left, f, arg);
    f(head, arg);
}

