/* tree.c */
#include "tree.h"

Tree root = { .n = {
    .tag = (TagRoot | TagNode),     // root and node at same time
    .north = (Node *)&root,         // points to itself
    .west = 0,
    .east = 0,
    .path = "/"
}};

void zero(int8 *str ,int16 size){
    int8 *p;
    int16 n;

    for(n = 0,p=str;n<size;p++,n++)
        *p = 0;
    return;
}

Node *create_node(Node *parent, int8 *path){
    Node *n;
    int16 size;


    errno = NoError;
    assert(parent);
    size = sizeof(struct s_node);
    n = (Node *)malloc((int)size);
    zero((int8 *)n, size);

    parent->west = n;
    n->tag = TagNode;
    n->north = parent;

    strncpy((char *)n->path,(char *)path,255);

    return n;
}

Leaf *find_last_linear(Node *parent){
    Leaf *l;

    errno = NoError;
    assert(parent);

    if(!parent->east)
        reterr(NoError);

    for(l = parent->east; l->east;l = l->east)
    assert(l);
    return l;


}

Leaf *create_leaf(Node *parent,int8 *key,int8 *value,int16 count){
    Leaf *l,*new_leaf;
    int16 size;

    assert(parent);
    l = find_last(parent);

    size = sizeof(struct s_leaf);
    new_leaf = (Leaf *)malloc(size);
    assert(new_leaf);
    if(!l)
        parent->east = new_leaf;
    else
        l->east = new_leaf;
    
    zero((int8 *)new_leaf,size);
    new_leaf->tag = TagLeaf;
    new_leaf->west = (!l) ? 
        (Tree *)parent : 
        (Tree *)l;
    
    strncpy((char *)new_leaf->key,(char *)key,127);
    new_leaf->value = (int8 *)malloc(count);
    zero(new_leaf->value,count);
    assert(new_leaf->value);
    strncpy((char *)new_leaf->value,(char *)value,count);
    new_leaf->size = count;

    return new_leaf;
}

int main(){
    Node *n,*n2;
    Leaf *l1,*l2;
    int8 *key,*value;
    int16 size;

    n = create_node((Node*) &root, (int8 *)"/Users");
    assert(n);
    n2 = create_node(n,(int8 *)"/Users/login");
    assert(n2);

    key = (int8 *)"sumit";
    value = (int8 *)"abc12322aa";
    size = (int16)strlen((char *)value);
    l1 = create_leaf(n2,key,value,size);
    assert(l1);

    printf("%s\n",l1->value);

    key = (int8 *)"kumar";
    value = (int8 *)"123ee3s";
    size = (int16)strlen((char*)value);
    l2 = create_leaf(n2,key,value,size);
    assert(l2);

    printf("%s\n",l2->key);

    printf("%p %p\n",n,n2);
    free(n2);
    free(n);

    return 0;
}
