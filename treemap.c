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
    /*El nombre de la función es *lower_than*, recibe dos parámetros (las claves) y 
    retorna un entero (1 si key1<key2 y 0 si no).*/
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

/*3.- Implemente la función void insertTreeMap(TreeMap * tree, void* key, void * value). Esta función inserta un nuevo 
dato (key,value) en el árbol y hace que el current apunte al nuevo nodo.
Para insertar un dato, primero debe realizar una búsqueda para encontrar donde debería ubicarse. 
Luego crear el nuevo nodo y enlazarlo. Si la clave del dato ya existe retorne sin hacer nada 
(recuerde que el mapa no permite claves repetidas).
   */
void insertTreeMap(TreeMap * tree, void* key, void * value) {
    //usar search
    TreeNode* nodoEsta = searchTreeMap(tree, key);
    if(nodoEsta != NULL) return;//Si la clave del dato ya existe retorne sin hacer nada
    //crear el nodo para que voy a insertar
    TreeNode* nodoAinsertar = createTreeNode(key, value);
    TreeNode* currentParaInsertar = tree->root; //para recorrer desde el inicio
    TreeNode* padreDeInsertar = NULL;

    //recorrer el arbol
    while(currentParaInsertar != NULL){
        padreDeInsertar = currentParaInsertar;
        if(tree->lower_than(key, currentParaInsertar->pair->key)){//(1 si key1<key2 y 0 si no)
            currentParaInsertar = currentParaInsertar->left;
        }
        else{
            currentParaInsertar = currentParaInsertar->right;
        }

    }

    nodoAinsertar->parent  = padreDeInsertar;
    
    
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
    if(node == NULL){
        return;
    }
    //nodo sin hijos, primero debo preguntar si no estan y que hacer en cada caso.
    if(node->left == NULL && node->right == NULL){
        if(node->parent == NULL){
            tree->root = NULL;//como tampoco hay raiz transformo el nodo en raiz.
        }
        else if(node->parent->left == node){
            node->parent->left = NULL;//para desconectar el nodo
        }
        else{
            node->parent->right = NULL;
        }
        

        free(node);
    }
    else if(node->left == NULL || node->right == NULL){
        //necesito el nodo hijo, ya que tiene uno, puede ser izquierdo o derecho
        TreeNode* nino;
        if(node->parent->left != NULL){
            nino = node->left;
        }
        else{
            nino = node->right;
        }
        //evaluar

        if(node->parent == NULL){
            tree->root = nino;
        }
        else if(node->parent->left == node){
            node->parent->left = nino;
        }
        else{
            node->parent->right = nino;
        }

        //falta actualizar el padre
        
        nino->parent = node->parent;
        
        free(node);
        return;
    }
    else{
        /*como debo usar la funcion minimum es decir el menor de los mayores sera reemplazado como el el proximo nodo
        que estaba en esa posicion cambiando las claves por las del dato que acabo de elegir para que lo reemplace */
        TreeNode* nodoMenor = minimum(node->right);
        node->pair->key = nodoMenor->pair->key;
        node->pair->value = nodoMenor->pair->value;
        //eliminar el nodo como en la tarea en casa
        removeNode(tree, nodoMenor);

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
