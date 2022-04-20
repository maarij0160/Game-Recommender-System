#include<iostream>
#include<vector>
#include<queue>

using namespace std;

template<class t>
class BTnode{
    public:
        t data;
        BTnode<t> * left;
        BTnode<t> * right;

        BTnode(){left = right = 0;}
        BTnode(t d){data = d; left = right = 0;}
        BTnode(t d, BTnode<t>*l, BTnode<t>*r){data = d; left = l; right = r;}
};

template<class t>
class BST{
    public:
        BTnode<t> * root;

        void deletetree(BTnode<t> * r){
            if(r == 0) return;

            deletetree(r->left);
            deletetree(r->right);
            delete r;
        }

        BTnode<t>* copytree(BTnode<t> * root){
            if(root == 0) return NULL;

            BTnode<t> *l;
            BTnode<t> *r;

            if(root->left != 0) l = copytree(root->left);
            else l = NULL;

            if(root->right != 0) r = copytree(root->right);
            else r = NULL;
            
            return new BTnode<t>(root->data, l, r);
        }

        BST<t>(){root = NULL;}

        ~BST<t>(){
            deletetree(root);
        }

        BST<t> operator=(BST<t> tree){
            if(*this != tree){
                deletetree(this->root);
                this->root = copytree(tree->root);
            }

            return *this;
        }

        void insert(t d){
            BTnode<t> *node = new BTnode<t>(d);

            if(root == 0){
                root = node;
                return;
            }

            BTnode<t>* par = root;
            BTnode<t>* cur = root;

            while(cur != NULL){
                par = cur;

                if(d < cur->data) cur = cur->left;
                else cur = cur->right;
            }

            if(d < par->data) par->left = node;
            else par->right = node;
        }

        bool check(t d){
            if(root == 0){
                return false;
            }

            BTnode<t>* tmp = root;

            while(tmp->data != d){
                if(d < tmp->data) tmp = tmp->left;
                else tmp = tmp->right;

                if(tmp == NULL){
                    return false;
                }
            }

            return true;
        }

        void inorder(BTnode<t> * r){
            if(r != 0){
                inorder(r->left);
                cout<<" "<<r->data;
                inorder(r->right);
            }
        }
};
