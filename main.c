#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char* data;
    struct node* left;
    struct node* right;
}node;
node* newNode(char* val)
{
    node* n=malloc(sizeof(node));
    n->data=malloc(strlen(val)+1);
    strcpy(n->data,val);
    n->right=NULL;
    n->left=NULL;
    return n;
}
node* insert(node* root,char* key)
{
    if(root==NULL)
        return newNode(key);
    else if(strcasecmp(root->data,key)>0)
        root->left=insert(root->left,key);
    else if(strcasecmp(root->data,key)<0)
        root->right=insert(root->right,key);
}
node* search(node* root,char* key)
{
    if(root==NULL)
        return NULL;
    else if(strcasecmp(root->data,key)==0)
        return root;
    else if(strcasecmp(root->data,key)>0)
        return search(root->left,key);
    else if(strcasecmp(root->data,key)<0)
        return search(root->right,key);
}
node* minimum(node*root)
{
    if(root==NULL)
        return NULL;
    if(root->left!=NULL)
        minimum(root->left);
    else return root;
}
node* Delete(node* root,char* key)
{
    node* temp;
    if(root==NULL)
        return NULL;
    else if(strcasecmp(root->data,key)>0)
        root->left=Delete(root->left,key);
    else if(strcasecmp(root->right,key)<0)
        root->right=Delete(root->right,key);
    if(root->left!=NULL && root->right!=NULL)
        {
            temp=minimum(root->right);
            strcpy(root->data,temp->data);
            root->right=Delete(root->right,temp->data);
        }
        else
        {
            temp=root;
            if(root->left==NULL)
                root=root->right;
            else if(root->right==NULL)
                root=root->left;
            free(temp);
        }
        return root;
}
void preOrder(node* root)
{
    if(root==NULL)
        return NULL;
    else
    {
        printf("%s ",root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}
void inOrder(node* root)
{
    if(root==NULL)
        return NULL;
    else
    {
        inOrder(root->left);
        printf("%s ",root->data);
        inOrder(root->right);
    }
}
void postOrder(node* root)
{
    if(root==NULL)
        return NULL;
    else
    {
        postOrder(root->left);
        postOrder(root->right);
        printf("%s ",root->data);
    }
}
int countNodes(node* root)
{
    if(root==NULL)
        return 0;
    else return(1+countNodes(root->left)+countNodes(root->right));
}
int max(int x,int y)
{
    if(x>y)
        return x;
    else if(x<y)
        return y;
    else return x;
}
int height(node* root)
{
    if(root==NULL)
        return 0;
    else return 1+(max(height(root->left),height(root->right)));
}
node* successor(node* root,char* x)
{
    node* succ=NULL;
    node* temp=root;
    while(temp!=NULL)
    {
        if(strcasecmp(x,temp->data)<0)
        {
            succ=temp;
            temp=temp->left;
        }
        else if(strcasecmp(x,temp->data)>0)
        {
            temp=temp->right;
        }
        else if(temp->right!=NULL)
            return minimum(temp->right);
        else return succ;
    }
    //return succ;
}
node* maximum(node* root)
{
    if(root==NULL)
    return NULL;
    else if(root->right!=NULL)
        return maximum(root->right);
    else return root;
}
node* predeccessor(node* root,char* x)
{
    node* predecc=NULL;
    node* temp=root;
    while(temp!=NULL)
    {
      if(strcasecmp(x,temp->data)<0)
      {
         temp=temp->left;
      }
      else if(strcasecmp(x,temp->data)>0)
      {
          predecc=temp;
          temp=temp->right;
      }
      else if(temp->left!=NULL)
        return maximum(temp->left);
      else return predecc;
    }
    //return predecc;
}
node* lastNode(node* root,char* x)
{
    if(root==NULL)
        return NULL;
    if(strcasecmp(x,root->data)<0)
    {
        if(root->left==NULL)
            return root;
        else return lastNode(root->left,x);
    }
    if(strcasecmp(x,root->data)>0)
    {
        if(root->right==NULL)
           return root;
        else return lastNode(root->right,x);
    }

}
int main()
{
    node* root=NULL;
    
    FILE* f=fopen("EN-US-Dictionary.txt","r");
    if(!f)
    {
        printf("file cant be read");
    }
    else
    {
        printf("Dictionary loaded successfully\n");
    }
    char x[30];
    char key[100];
    while(!feof(f))
    {
        fscanf(f,"%s",x);
        root=insert(root,x);
    }
    fclose(f);



    //preOrder(root);
    int c=countNodes(root);
    printf("size=%d\n",c);
    int y=height(root);
    printf("height=%d\n",y);
    printf("please enter the key\n");
    gets(key);
    char *taken=strtok(key," ");
    node* last=lastNode(root,taken);
    node* succ=successor(root,last->data);
    node* predecc=predeccessor(root,last->data);
    while(taken!=NULL)
    {
       node*keyRoot=search(root,taken);

       if (keyRoot!=NULL)
            printf("%s is found\n",taken);
       else
        {printf("%s is not found\n",taken);
        printf("the suggestions are: ");
        if (succ->data!=NULL)
            printf("%s ",succ->data);
        if(predecc->data!=NULL)
            printf("%s ",predecc->data);
        printf("%s",last->data);
        }
       taken=strtok(NULL," ");
    }

    return 0;
}
