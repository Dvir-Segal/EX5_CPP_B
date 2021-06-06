#pragma once 
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <climits>
#include <unordered_map>
#include <map>
#include <set>
#include <bits/stdc++.h>
#include <utility>
using namespace std;

namespace ariel{
    template<typename T>
    class BinaryTree{
        class Node{
            T value;
            Node* father;
            Node* sonLeft;
            Node* sonRight;
            public:
                Node(T v, Node* parent):father(parent), sonLeft(nullptr), sonRight(nullptr), value(v){};
                ~Node(){
                    if (this->soLeft != nullptr){
                        delete this->sonLeft;
                    }
                    if (this->sonRight != nullptr){
                        delete this->sonRight;
                    }
                    if (this->father != nullptr){
                        delete this->father;
                    }

                }
                Node &operator=(const Node &other){
                if (this != &other)
                {

                    this = new Node(other);
                }
                return *this;
                }
                
                void setValue(const T& v){value=v;}
                T& getValue(){return value;}
                Node* getLeft(){return sonLeft;}
                Node* getRight(){return sonRight;}
                Node* getParent(){return father;}
                void setLeft(Node* node){sonLeft=node;}
                void setRight(Node* node){sonRight=node;}
        };

        Node* head;

        public:
        
            BinaryTree():head(nullptr){};
            BinaryTree& add_root(const T& root){
                if (head!=nullptr){
                    head->setValue(root);
                    return *this;
                }
                head=new Node(root, nullptr);
                return *this;
            }
            BinaryTree& add_left(const T& f, const T& l){
                if (head==nullptr){
                    throw out_of_range("Invalid input\n");
                }
                Node* node = nullptr;
                for (itIn it=this->begin_inorder(); it!=this->end_inorder(); ++it){
                    if((*it)==f){
                        node=it.getPtr();
                        break;
                    }
                }
                if (node==nullptr){
                    throw out_of_range("Invalid input\n");
                }
                else{
                    if (node->getLeft()!=nullptr){
                        node->getLeft()->setValue(l);
                    }
                    else{
                        Node* ptr=new Node(l, node);
                        node->setLeft(ptr);
                    }
                    return *this;
                }
            }
            BinaryTree& add_right(const T& f, const T& r){
                if (head==nullptr){
                    throw out_of_range("Invalid input\n");
                }
                Node* node = nullptr;
                for (itIn it=this->begin_inorder(); it!=this->end_inorder(); ++it){
                    if((*it)==f){
                        node=it.getPtr();
                        break;
                    }
                }
                if (node==nullptr){
                    throw out_of_range("Invalid input\n");
                }
                else{
                    if (node->getRight()!=nullptr){
                        node->getRight()->setValue(r);
                    }
                    else{
                        Node* ptr=new Node(r, node);
                        node->setRight(ptr);
                    }
                    return *this;
                }
            }
            friend ostream& operator<<(ostream& os, BinaryTree& input){
                return os;
            }

            BinaryTree* operator=(const BinaryTree* other){
                for (auto it=other->begin_inorder(); it!=other->end_inorder(); ++it){
                    Node* p = it.getPtr()->getParent();
                    delete (it.getPtr());
                    it.setPtr(p);
                }
                this=BinaryTree(other);
                return *this;
            }

            class itPre{
                protected:
                    Node* p;

                public:
                    itPre(Node *ptr): p(ptr){};

                    Node* preorderSuccessor(Node* n){
                        if (n->getLeft()!=nullptr){
                            return n->getLeft();
                        }
                        else if(n->getRight()!=nullptr){
                            return n->getRight();
                        }
                        else{
                            while (n->getParent() != nullptr && n->getParent()->getRight() == nullptr && n->getParent()->getLeft()==n){
                                n=n->getParent();
                            }
                            while (n->getParent() != nullptr && n->getParent()->getRight() == n){
                                n=n->getParent();
                            }
                            if(n->getParent()==nullptr){
                                n=nullptr;
                            }
                            else{
                                n=n->getParent()->getRight();
                            }
                        }
                        return n;
                    }

                    bool operator!=(const itPre& other){
                        return p != other.p;
                    }
            
                    T& operator*(){
                        return this->p->getValue();
                    }

                    itPre operator++(int){
                        itPre tmp= *this;
                        p=preorderSuccessor(p);
                        return tmp;
                    }

                    itPre& operator++(){
                        p=preorderSuccessor(p);
                        return *this;
                    }

                    T *operator->(){
                        return &(p->getValue());
                    }

                    bool operator==(const itPre& other){
                        return p==other.p;
                    }

                    Node* getPtr(){return this->p;}
            };

            class itIn{
                protected:
                    Node* p;

                public:
                    itIn(Node *ptr): p(ptr){};

                    Node* inorderSuccessor(Node* n){
                        if (n->getRight()!=nullptr){
                            Node* curr = n->getRight();
                            while (curr->getLeft() != nullptr) {
                                curr = curr->getLeft();
                            }
                            return curr;
                        }
                        Node* p = n->getParent();
                        while (p != nullptr && n == p->getRight()) {
                            n = p;
                            p = p->getParent();
                        }
                        return p;
                    }

                    bool operator!=(const itIn& other){
                        return p != other.p;
                    }
            
                    T& operator*(){
                        return this->p->getValue();
                    }

                    itIn operator++(int){
                        itIn tmp= *this;
                        p=inorderSuccessor(p);
                        return tmp;
                    }

                    itIn& operator++(){
                        p=inorderSuccessor(p);
                        return *this;
                    }

                    T *operator->(){
                        return &(p->getValue());
                    }
                    
                    bool operator==(const itIn& other){
                        return p==other.p;
                    }

                    Node* getPtr(){return this->p;}
                    void setPtr(Node* ptr){this->p=ptr;}
            };

            class itPost{
                protected:
                    Node* p;

                public:
                    itPost(Node *ptr): p(ptr){};

                    Node* postorderSuccessor(Node* n){
                        if (n->getParent()==nullptr){
                            return nullptr;
                        }
                        Node* parent = n->getParent();
                        if (parent->getLeft()==n){
                            if (parent->getRight() == nullptr){
                                return parent;
                            }
                            n=parent->getRight();
                            while (n->getLeft()!=nullptr || n->getRight()!=nullptr){
                                if(n->getLeft()!=nullptr){
                                    n=n->getLeft();
                                }
                                else{
                                    n=n->getRight();
                                } 
                            }
                            return n;   
                        }
                        return n->getParent();
                    }

                    bool operator!=(const itPost& other){
                        return p != other.p;
                    }
            
                    T& operator*(){
                        return this->p->getValue();
                    }

                    itPost operator++(int){
                        itPost tmp= *this;
                        p=postorderSuccessor(p);
                        return tmp;
                    }

                    itPost& operator++(){
                        p=postorderSuccessor(p);
                        return *this;
                    }

                    T *operator->(){
                        return &(p->getValue());
                    }

                    bool operator==(const itPost& other){
                        return p==other.p;
                    }
            };


            itPre begin_preorder(){
                if (head==nullptr){
                    return itPre(nullptr);
                }
                return itPre(head);
            }
            
            itPre end_preorder(){
                return itPre(nullptr);
            }
                
            itIn begin_inorder(){
                if (head==nullptr){
                    return itIn(nullptr);
                }
                if (head->getLeft()==nullptr){
                    return head;
                }
                Node *p=head;
                while (p->getLeft()!=nullptr){
                    p=p->getLeft();
                }
                return itIn(p);
            }
            
            itIn end_inorder(){
                return itIn(nullptr);
            }

            itIn begin(){
                if (head==nullptr){
                    return itIn(nullptr);
                }
                if (head->getLeft()==nullptr){
                    return head;
                }
                Node *p=head;
                while (p->getLeft()!=nullptr){
                    p=p->getLeft();
                }
                return itIn(p);
            }
            
            itIn end(){
                return itIn(nullptr);
            }
            
            itPost begin_postorder(){
                if (head==nullptr){
                    return itPost(nullptr);
                }
                Node *p=head;
                while (p->getLeft()!=nullptr || p->getRight()!=nullptr){
                    if(p->getLeft()!=nullptr){
                        p=p->getLeft();
                    }
                    else{
                       p=p->getRight();
                    } 
                }
                return itPost(p);
            }
            
            itPost end_postorder(){
               return itPost(nullptr);
            }   
        
    };
    
    
}