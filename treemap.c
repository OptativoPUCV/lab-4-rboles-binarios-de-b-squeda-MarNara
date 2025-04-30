#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * map = (TreeMap *)malloc(sizeof(TreeMap));
    if (map == NULL) return NULL;
    map->root = NULL;
    map->current = NULL;
    map->lower_than = lower_than;
    return map;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {

}

TreeNode * minimum(TreeNode * x){
    //hacer lo que hice en la tarea en casa pero en este caso solo buscamos el menor
    while(x && x->left){
        x = x->left;
    }
    return x;

    //return NULL;
}

/*5.- Implemente la función void removeNode(TreeMap * tree, TreeNode* node). Esta función elimina el nodo *node* del árbol 
*tree*. Recuerde que para eliminar un node existen 3 casos:
**Nodo sin hijos:** Se anula el puntero del padre que apuntaba al nodo
**Nodo con un hijo:** El padre del nodo pasa a ser padre de su hijo
**Nodo con dos hijos:** Descienda al hijo derecho y obtenga el menor nodo del subárbol 
(con la función minimum). Reemplace los datos (key,value) de *node* con los del nodo "minimum". 
Elimine el nodo minimum (para hacerlo puede usar la misma función *removeNode*).*/
void removeNode(TreeMap * tree, TreeNode* node) {
    //nodo sin hijos, primero debo preguntar si no estan y que hacer en cada caso.
    if(node->left == NULL && node->right == NULL){
        if(node->parent == NULL){
            tree->root = node;//como tampoco hay raiz transformo el nodo en raiz.
        }
        else if(node->parent->left == NULL){
            node->left = NULL;//para desconectar el nodo
        }
        else{
            node->parent->right = NULL;
        }

        //free(node);
    }

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    //necesito el nodo de la raiz arbol
    TreeNode* node = tree->root;

    //mientras el nodo exista;
    while(node != NULL){
        //si es menor la clave a la clave actual, como no mtengo key debo usar pair, ya que pair tiene key y value
        if(tree->lower_than(key, node->pair->key)){
            node = node->left;
        }
        //ahora en el caso de que sea mayor
        else if(tree->lower_than(node->pair->key, key)){
            node = node->right;
        }
        //cuando son iguales
        else{
            tree->current = node;
            return node->pair;
        }


    }

    //int resultado = map->lower_than(key1,key2);

    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
