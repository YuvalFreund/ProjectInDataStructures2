
#ifndef WET1_AVLTREE_H
#define WET1_AVLTREE_H

#include <iostream>
#include <cstdio>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <math.h>
using namespace std;
namespace oasis{

    template <class T>
    class AVLTree {

        /**
    * Node definition
    */
        class avl_Node {
        public:
            T data;
            avl_Node *left;
            avl_Node *right;
            avl_Node *parent;
            int height;
            avl_Node(T data) :  data(data), left(NULL), right(NULL), height(0) {}

            ~avl_Node(){}
        };

        ///base of tree
        avl_Node *root;
        int size;

        /**
        * BF - Balance Factor
        * return balance factor of a specific node
        */
        int BF(avl_Node *node) {
            if (node == NULL) {
                return 0;
            }
            int right = node->right ? node->right->height + 1 : 0;
            int left = node->left ? node->left->height + 1 : 0;
            return (left - right);
        }

        int height(avl_Node *node) {
            return (node == NULL) ? -1 : node->height;
        }


        /**
       * RR_Rotation - rotate a node to maintain BF
       * return the upper most node of the operation
       */
        avl_Node *RR_Rotation(avl_Node *node) {
            if (node == NULL) {
                return NULL;
            }
            avl_Node *temp = node->right;
            node->right = temp->left;
            if (temp->left != NULL) {
                temp->left->parent = node;
            }
            temp->parent = node->parent;
            temp->left = node;
            node->parent = temp;
            node->height = std::max(height(node->left), height(node->right)) + 1;
            temp->height = std::max(height(temp->left), node->height) + 1;
            if(node == root) root = temp;
            return temp;
        }

        /**
      * LL_Rotation - rotate a node to maintain BF
      * return the upper most node of the operation
      */
        avl_Node *LL_Rotation(avl_Node *node) {
            if (node == NULL) {
                return NULL;
            };
            avl_Node *temp = node->left;
            node->left = temp->right;
            if (temp->right != NULL) {
                temp->right->parent = node;
            }
            temp->parent = node->parent;
            temp->right = node;
            node->parent = temp;
            node->height = std::max(height(node->left), height(node->right)) + 1;
            temp->height = std::max(height(node->right), node->height) + 1;
            if(node == root) root = temp;
            return temp;
        }

        /**
          * RL_Rotation - rotate a node to maintain BF
         * return the upper most node of the operation
         */
        avl_Node *RL_Rotation(avl_Node *node) {
            if (node == NULL) {
                return NULL;
            }
            node->right = LL_Rotation(node->right);
            return RR_Rotation(node);
        }

        /**
          * LR_Rotation - rotate a node to maintain BF
         * return the upper most node of the operation
         */
        avl_Node *LR_Rotation(avl_Node *node) {
            if (node == NULL) {
                return NULL;
            }
            node->left = RR_Rotation(node->left);
            return LL_Rotation(node);
        }

        /**
          * make_balanced - balance tree according to BF
         * return the upper most node of the operation
         */
        avl_Node *make_balanced(avl_Node *node) {
            if (node == NULL) {
                return NULL;
            }
            avl_Node *temp = node->parent;
            /////////!!!!!!!!!!!!!////////////////this is the addition
            int whereToShift=1; /// 1 means insert to right, 2 means left
            if(temp!=NULL && temp->left == node ){
                whereToShift = 2;
            }
            if (BF(node) == 2) {///Rotate according to BF and sons value
                if (BF(node->left) == -1) {
                    node = LR_Rotation(node);
                    if (temp != NULL && whereToShift ==1) {
                        temp->right = node;
                    }
                    if (temp != NULL && whereToShift ==2) {
                        temp->left = node;
                    }
                } else if (BF(node->left) >= 0) {
                    node = LL_Rotation(node);
                    if (temp != NULL && whereToShift ==1) {
                        temp->right = node;
                    }
                    if (temp != NULL && whereToShift ==2) {
                        temp->left = node;
                    }
                }
            }
            if (BF(node) == -2) {
                if (BF(node->right) == 1) {
                    node = RL_Rotation(node);
                    if (temp != NULL && whereToShift ==1) {
                        temp->right = node;
                    }
                    if (temp != NULL && whereToShift ==2) {
                        temp->left = node;
                    }
                } else if (BF(node->right) <= 0) {
                    node = RR_Rotation(node);
                    if (temp != NULL && whereToShift ==1) {
                        temp->right = node;
                    }
                    if (temp != NULL && whereToShift ==2) {
                        temp->left = node;
                    }
                }
            }
            return node;
        }

        template<typename Compare>
        avl_Node *Where_to_insert(avl_Node *node, T data, Compare f) {
            avl_Node *temp = node;///will save father's node of future inserted value
            while (node != NULL) {
                if (f(node->data, data) == 2) {
                    temp = node;///saving father
                    node = node->right;
                } else if(f(node->data, data) == 1){
                    temp = node;///saving father
                    node = node->left;
                }
                else{
                    throw AVLTreeAlreadyExist();
                }
            }
            return temp;///returning father
        }

        template<typename Compare>
        avl_Node *find(avl_Node *node, T data, Compare f) {
            while (node != NULL) {
                if(f(node->data, data) == 0){
                    return node;
                }
                if (f(node->data, data) == 2) {
                    node = node->right;
                } else if (f(node->data, data) == 1) {
                    node = node->left;
                }
            }
            return NULL;
        }

        /**
         * insert - insert a new node to the tree
        * return the upper most node of the operation
        */
        template<typename Compare>
        avl_Node *insert(avl_Node *node, T data, Compare f) {
            avl_Node *temp = Where_to_insert(node, data, f);///temp is the father of the inserted node
            size++;
            ///if passed this point value is not in tree
            avl_Node *inserted = new avl_Node(data);
            inserted->data = (data);
            inserted->parent = inserted->left = inserted->right = NULL;
            inserted->height = 0;
            if (temp == NULL) {
                root = inserted;
                return inserted;///if tree is empty
            }

            ///insert new value according to fathers value (left/right)
            if (f(temp->data, data) == 2) {
                temp->right = inserted;
            } else if(f(temp->data, data) == 1){
                temp->left = inserted;
            }
            inserted->parent = temp;

            avl_Node *iterate = inserted;
            int counter = 0;
            while (iterate != root) {///calculate new height of nodes and rotate accordingly if needed
                iterate = iterate->parent;
                iterate->height = ++counter;
                if (std::abs(BF(iterate)) > 1) {
                    if (iterate == root)root = make_balanced(iterate);
                    else {
                        make_balanced(iterate);
                    }
                    break;
                }
            }
            return inserted;
        }

        ///finds the min value in right sub tree
        avl_Node *findMinRight(avl_Node *node) {
            while (node->left != NULL) {
                node = node->left;
            }
            return node;
        }

        /**
         * Sons0_1 - changes the tree when a node with 0/1 sons is being removed
        */
        int Sons0_1(avl_Node* &found){
            if(found == root && found->right == NULL && found->left==NULL){
                root = NULL;
                delete found;
                return 0;
            }
            avl_Node *temp = found;
            if (found->left == NULL) {
                found = found->right;
            } else if (found->right == NULL) {
                found = found->left;
            }
            if (temp->parent != NULL && temp->parent->right == temp) {
                temp->parent->right = found;
                if(found!=NULL)found->parent = temp->parent;
            } else if (temp->parent != NULL && temp->parent->left == temp) {
                temp->parent->left = found;
                if(found!=NULL)found->parent = temp->parent;
            }

            if(temp==root){
                root->data = found->data;
                root->right = root->left = NULL;
                delete (found);
                return 0;
            }
            delete (temp);
            if(found!=NULL)
                return 1;///need to deduct 1 from every node
            return 0;
        }

        bool check_height_status(avl_Node* node, int actual_height){
            if(node->height > actual_height &&
               ((node->right!=NULL && node->right->height == actual_height-1) &&
                (node->left!=NULL && node->left->height == actual_height-1)))
                return true;
            if(node->height > actual_height && node->right==NULL &&
                node->left==NULL)  return true;
            return false;
        }
        /**
         * remove - remove a certain node from the tree
         * if needed, the tree is re-balanced
        */
        template<typename Compare>
        void remove(avl_Node *node, T data, Compare f) {
            if (node == NULL) {
                return;
            }
            avl_Node *iterate;
            avl_Node *found = find(node, data, f);///found is the node with data value
            if (!found) throw AVLTreeDoesntExist();
            size--;
            int start_of_count;
            ///if has 2 sons
            if (found->right && found->left) {
                avl_Node *temp = findMinRight(found->right);///find min in right sub tree
                T saver = found->data;
                found->data = temp->data;
                temp->data = saver;
                iterate = temp->parent;
                start_of_count = Sons0_1(temp);
            }
                ///if has 0/1 sons
            else {
                iterate = found->parent;
                start_of_count = Sons0_1(found);
            }

            int counter = start_of_count;
            ///re-balance tree - go through every node from where deleted and up
            while (iterate != NULL) {
               // cout << "iter data: " << iterate->data<<" iter high: "<<iterate->height;
              //  cout<<" counter: "<<counter<<endl;
                if(check_height_status(iterate,counter)) {
                    iterate->height = counter++;
                } else{
                    counter++;
                }
                if (std::abs(BF(iterate)) > 1) {
                    make_balanced(iterate);
                }
                iterate = iterate->parent;
            }
        }

        /**
         * display - display tree
        */
        void display(avl_Node *ptr,int level) {
            int i;
            if (ptr!=NULL)
            {
                display(ptr->right, level + 1);
                printf("\n");
                if (ptr == root)
                    std::cout<<"Root -> ";
                for (i = 0; i < level && ptr != root; i++) {
                    std::cout << "        ";
                    if (i == 0)std::cout << "        ";
                }
                std::cout<<ptr->data<<","<<ptr->height;
                display(ptr->left, level + 1);
            }
        }

        /**
         * inorder - inorder through tree
         * returns an array - vals that contains all the nodes
        */
        template <typename Pred,typename dosomething>
        void inorder(avl_Node *node,T* vals,int &counter,Pred ifclng, dosomething setToNull){
            if(node == NULL){
                return;
            }
            if(!ifclng(node->data)) {
               setToNull(node->data);
            }
            inorder(node->left,vals,counter,ifclng,setToNull);
            vals[counter++] = node->data;
            inorder(node->right,vals,counter,ifclng,setToNull);
        }
        void Cleaninorder(avl_Node *node,T* vals,int &counter){
            if(node == NULL){
                return;
            }
            Cleaninorder(node->left,vals,counter);
            vals[counter++] = node->data;
            Cleaninorder(node->right,vals,counter);
        }
    //    T* preorder(avl_Node *node);
    //    T* postorder(avl_Node *node);

        static avl_Node* copyTree(avl_Node* node){
            if(node == NULL){
                return NULL;
            }
            avl_Node* new_node = new avl_Node(node->data);
            new_node->height = node->height;
            new_node->parent = node->parent;
            new_node->data = node->data;
            new_node->left = copyTree(node->left);
            new_node->right = copyTree(node->right);
            return new_node;
        }

    public:

        /**
       * Constructor
       * set an empty tree pointing to NULL
       */
        AVLTree(){
            size = 0;
            root = NULL;
        }

        AVLTree<T>& operator=(const AVLTree<T>& toCopy){
            destroyTree(root);
            root = copyTree(toCopy.root);
            return *this;
        }

        template <typename Compare>
        avl_Node *insert(T data, Compare f){
            return insert(root,data,f);
        }

        template <typename Compare>
        void remove(T data,Compare f){
            remove(root,data,f);
        }

        template <typename Compare>
        T* find(T data,Compare f){
            avl_Node *temp = find(root,data,f);
            return &temp->data;
        }

        void display(){
            display(root,0);
        }
        template <typename Pred,typename dosomething>
        void inorder(T* vals,Pred g, dosomething d){
            int count = 0;
            if(root == NULL){
                vals = NULL;
                return;
            }
            inorder(root,vals,count,g,d);
        }
        void Cleaninorder(T* vals){
            int count = 0;
            if(root == NULL){
                vals = NULL;
                return;
            }
            Cleaninorder(root,vals,count);
        }
      //  T* preorder();
      //  T* postorder();

        void destroyTree(avl_Node* node){
            if(node == NULL)return;
            destroyTree(node->right);
            destroyTree(node->left);
            delete node;
        }
        int getTreeSize()const{
            return size;
        }
        void setRoot(avl_Node* newRoot){
            this->root= newRoot;
        }
        avl_Node* getRoot()const{
            return this->root;
        }

        ///merging two arrays into one O(n) time
        template <typename Compare,typename Pred, typename addOn>
        int merge( T* array1, int size1,  T* array2, int size2,
                   T* result, Compare f, Pred ifclng, addOn k){
            int ia = 0,ib = 0,ic = 0, counter = 0;
            for(;ia<size1 && ib<size2;ic++){
                if(!ifclng(array1[ia])){///if value doesn't qualify condition
                    --ic;ia++;
                    continue;
                }
                if(!ifclng(array2[ib])){///if value doesn't qualify condition
                    --ic;ib++;
                    continue;
                }
                if(f(array1[ia],array2[ib])==2){
                    k(array1[ia]);
                    result[ic] = array1[ia];
                    ia++;
                    counter++;
                }
                else {
                    k(array2[ib]);
                    result[ic] = array2[ib];
                    ib++;
                    counter++;
                }
            }
            for(;ia<size1;ia++,ic++){
                if(!ifclng(array1[ia])){///if value doesn't qulify condition
                    --ic;
                    continue;
                }
                k(array1[ia]);
                result[ic] = array1[ia];
                counter++;
            }
            for(;ib<size2;ib++,ic++){
                if(!ifclng(array2[ib])){///if value doesn't qulify condition
                    --ic;
                    continue;
                }
                k(array2[ib]);
                result[ic] = array2[ib];
                counter++;
            }
            return counter;
        }
        /* A function that constructs Balanced Binary Search Tree from a sorted array */
        avl_Node* sortedArrayToAVL(T *arr, int start, int end, int height, avl_Node *father)
        {
            /* Base Case */
            if (start > end)
                return NULL;

            /* Get the middle element and make it root */
            int mid = (start + end)/2;
            avl_Node *node= new avl_Node(arr[mid]);
            node->left = node->right = NULL;
            node->parent = father;
            node->height = height;

            ///Recursively make left side of tree
            node->left =  sortedArrayToAVL(arr, start, mid-1, height-1, node);

            ///Recursively make right side of tree
            node->right = sortedArrayToAVL(arr, mid+1, end, height-1, node);

            return node;
        }
        /**
         * mergeTrees - merge two trees into one
         * inroder through every tree, and merge both arrays into one. then build a new tree
         * from the sorted array
       */
        template <typename Compare,typename Pred, typename doSomething,typename addOn>
        int mergeTrees(AVLTree& tree,Compare f,Pred g,doSomething d,addOn a){
            int values = this->size+tree.size;
            T* array = new T[values];
            T* temp1 = new T[this->size];
            T* temp2 = new T[tree.size];
            this->inorder(temp1,g,d);
            tree.inorder(temp2,g,d);
            int real_size = merge(temp1,this->size,temp2,tree.size,array,f,g,a);
            double height = floor(log(real_size))+1;
            this->destroyTree(this->root);
            this->root = sortedArrayToAVL(array,0,real_size-1,height,NULL);
            this->size = real_size;
            delete[] temp1;
            delete[] temp2;
            delete[] array;
            return real_size;
        }
        ~AVLTree(){
            destroyTree(root);
        }
        ///exceptions
        class AVLTreeAlreadyExist : public std::exception{};
        class AVLTreeDoesntExist : public std::exception{};

    };
}



#endif //WET1_AVLTREE_H
