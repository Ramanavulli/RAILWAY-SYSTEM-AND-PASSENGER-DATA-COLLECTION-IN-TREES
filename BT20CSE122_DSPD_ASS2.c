#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
// An AVL tree node
struct Node
{
    
    char name[10];
	int passenger_id;
	char boarding_train[10];
	char boarding_station[10];
	char travelling_class[10];		//(sleeper,3AC,2AC,1AC)
	char destination_station[10];
	int train_id;
	int bogie_no; //NO.OF.BOGIES assumed to be 10
	int seat_no;	//seats assumed to be 50
	char date_of_travel[10];
    struct Node *left;
    struct Node *right;
    int height;
};


struct train_node
{
	int train_id;
	char dt[10];
	int passenger_count;
	struct train_node* left;
	struct train_node* right;
};
 
// A utility function to get maximum of two integers
int max(int a, int b);

void inOrder(struct Node *root);
void get_List_Destination(struct Node* root);
int search(struct Node *root,int train,int bogie,int seat);
 
// A utility function to get the height of the tree
int height(struct Node *N)
{
    if (N == NULL)
    {
    	return 0;
	}
	else
	{
		return 1+max(height(N->left), height(N->right));
	}
}
 
// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
/* Helper function that allocates a new node with the given passenger_id  and NULL left and right pointers. */
struct Node* newNode(int passenger_id)
{
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    struct train_node* t_temp=(struct train_node*)malloc(sizeof(struct train_node));
    temp->passenger_id   = passenger_id;
    printf("\nEnter the data values for the node:\t" );
	printf("\nname:");
	scanf("%s",&temp->name);
	printf("\ndes_station:");
	scanf("%s",&temp->destination_station);
	printf("\ntrain_id:");
	scanf("%d",&temp->train_id);
	t_temp->train_id=temp->train_id;		//stores data of trainid in train node also
	printf("\nenter the bogie no in between 1-10  :");
	scanf("%d",&temp->bogie_no);
	printf("\nenter the bogie no in between 1-50   :");
	scanf("%d",&temp->seat_no);
	int s;
	s=search(temp,temp->train_id,temp->bogie_no,temp->seat_no);
	/*if(s==1)
	{
	    printf("boige and seatno entered is booked alredy enter another value");
	    inOrder(temp);
	    scanf("%d",&temp->seat_no);
	}*/
	        
	printf("BOARDING_TRAIN	BOARD_STATION	\n");
	scanf("%s",&temp->boarding_train);
	scanf("%s",&temp->boarding_station);
	printf("\nselect class:(sleeper,3AC,2AC,1AC)");
	scanf("%s",&temp->travelling_class);
	printf("Enter the travel date:");
	scanf("%s",temp->date_of_travel);
	printf("\n\t***\tThe Reservation done successfully\t***\n\n ");
    temp->left   = NULL;
    temp->right  = NULL;
    temp->height = 0;  // new node is initially added at leaf
    return(temp);
}


int search(struct Node *root,int train,int bogie,int seat)
{
	struct Node* temp = root;
    while(temp!=NULL)
	{
		
        if((temp->bogie_no==bogie)&&(temp->seat_no==seat)&&(temp->train_id==train))
		{
            return 1;
        }
        temp = temp->left;
        temp=temp->right;
    }
    return 0;
} 
// A utility function to right rotate subtree rooted with y

struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = height(y);
    x->height = height(x);
 
    // Return new root
    return x;
}
 
// A utility function to left rotate subtree rooted with x
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = height(x);
    y->height = height(y);
 
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
// Recursive function to insert a passenger in the subtree rooted  with node and returns the new root of the subtree.
struct Node* insert(struct Node* node, int passenger_id)
{
	
    
    if (node == NULL)
    {
    	return(newNode(passenger_id));
	}
 
    if (passenger_id < node->passenger_id)
    {
    	node->left  = insert(node->left ,passenger_id);
	}
    else if (passenger_id > node->passenger_id)
    {
    	node->right = insert(node->right ,passenger_id);
	}
    else 
    {
    	return node;
	}
 
    /*  Update height of this ancestor node */
    node->height = height(node);
 
    /*  Get the balance factor of this ancestor node to check whether this node became unbalanced */
    int balance = getBalance(node);
 
 
    // Left Left Case
    if (balance > 1 && passenger_id < node->left->passenger_id)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && passenger_id > node->right->passenger_id)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && passenger_id > node->left->passenger_id)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && passenger_id < node->right->passenger_id)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    return node;
}
 



struct Node * minValueNode(struct Node* node)
{
    struct Node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
 
 
 
 
// Recursive function to delete a node with given passenger_id

struct Node* delete_fun(struct Node* root, int passenger_id)
{
	
 
    if (root == NULL)
    {
    	return root;
	}
	
    if ( passenger_id < root->passenger_id )
    {
    	root->left = delete_fun(root->left, passenger_id);
	}
 
    
    else if( passenger_id > root->passenger_id )
    {
    	root->right = delete_fun(root->right, passenger_id);
	}
 
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct Node *temp = root->left ? root->left :
                                             root->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
             *root = *temp; // Copy the contents of
                            // the non-empty child
            free(temp);
        }
        else
        {

            struct Node* temp = minValueNode(root->right);
 
            
            root->passenger_id = temp->passenger_id;
 
            
            root->right = delete_fun(root->right, temp->passenger_id);
        }
    }
 
    if (root == NULL)
      return root;
 
    root->height = 1 + max(height(root->left),
                           height(root->right));
 
    int balance = getBalance(root);
 
 
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}





void inOrder(struct Node *root)
{
	
    if(root != NULL)
    {
    	inOrder(root->left);
    	printf("\n------------------------------------------\n");
    	printf("passenger_id\tname\tdestination_station\ttrain_id");
        printf("\n%d \t\t", root->passenger_id);
        printf("%s     \t",root->name);
        printf("%s    \t",root->destination_station);
	    printf("%d   \t",root->train_id);
	    printf("\nbogie:%d\t",root->bogie_no);
	    printf("seatno:%d\t",root->seat_no);
		printf("date of travel:%s",root->date_of_travel);
	    printf("\n");
	    printf("boarding_train:%s\t",root->boarding_train);
	    printf("boarding_station:%s\t",root->boarding_station);
	    printf("travelling_class:%s\t\n\n",root->travelling_class);
        inOrder(root->right);
    }
}




void get_List_Destination(struct Node* root)
{
	printf("Enter the destination station and  train id to get the list:");
	char des_station[10];
	int t_id;
	scanf("%s",&des_station);
	scanf("%d",&t_id);
	int flag=0;
	
	struct Node* temp = root;
    if(temp!=NULL)
	{
		
	    	if((strcmp(temp->destination_station,des_station))==0&&(temp->train_id==t_id))
	    	{
	 	
	    		printf("\npassenger name: %s\t", temp->name);
	            printf("passenger id: %d\t", temp->passenger_id);
	            printf("destination_station:%s \t",temp->destination_station);
		       	printf("train_id:%d\n",temp->train_id);
	    		get_List_Destination(root->left);
        		get_List_Destination(root->right);
        		flag=1;
			}
	       
		  
    }
    if(flag==0)
    {
    	printf("train with destination station and  train id  %d is not found !!!\n", t_id);
	}

}
 
 
 
 
void SortByTravelDate(struct Node* root,int p_id)
{
	
	int flag=0;
	struct Node* temp = root;
	printf("THE LIST OF DESTINATION STATIONS ARE:\n");
	if(temp!=NULL)
	{
		if(temp->passenger_id==p_id)
		{
			printf("\n destination_station:%s \t",temp->destination_station);
			printf("travel date:%s\n",temp->date_of_travel);
			flag=1;
		}
		SortByTravelDate(root->left,p_id);
		SortByTravelDate(root->right,p_id);
	}
	if(flag==0)
	{
		printf("Passenger with passenger_id %d is not found!!\n",p_id);
	}
}




void passenger_count(struct Node* root,struct train_node* ptr)			//stores the passenger count of particular train
{
	struct Node* temp=root;
	struct train_node* t_temp=ptr;
	int count=0;
	while(temp!=NULL)
	{
		
		printf("%d",t_temp->train_id);
		while(t_temp->train_id==temp->train_id)
		{
			count++;
			temp=temp->left;
			temp=temp->right;
		}
		printf("%d",count);
		t_temp->passenger_count =count;
		t_temp=t_temp->left;
		t_temp=t_temp->right;
	}
}




void Sort_Trains(struct train_node* root)
{
	if(root != NULL)
    {
    	Sort_Trains(root->left);
    	printf("\n------------------------------------------\n");
    	printf("dt:",root->dt);
    	printf("passenger_count:",root->passenger_count);
    	printf("train_id:",root->train_id);
        Sort_Trains(root->right);
    }
}





void range_print(struct Node* ptr)
{
	printf("\n Passenger ID \t Name \t\t Train ID \t destination_station \t Class \t   Bogie No \t Seat No \t Travel Date \n");
	printf("%d\t",ptr->passenger_id);
	printf("%s\t",ptr->name);
	printf("%d\t",ptr->train_id);
	printf("%s\t",ptr->destination_station);
	printf("%s\t",ptr->travelling_class);
	printf("%d\t",ptr->bogie_no);
	printf("%d\t",ptr->seat_no);
	printf("%s",ptr->date_of_travel);
	printf("\n");
	printf("boarding_train:%s\t",ptr->boarding_train);
	printf("boarding_station:%s\t\n",ptr->boarding_station);
	
}




void RangeSearch(struct Node* root,int f,int l)		//"f"variable for first,and "l" variable for last.
{
	if(root!=NULL)
	{
		
		RangeSearch(root->left,f,l);
		
		if(root->train_id<=l && root->train_id>=f)
		{
			
			range_print(root);
		}
		RangeSearch(root->right,f,l);
	}
}




//main function.
int main()
{
  struct Node *root = NULL;
  struct train_node* train_root=NULL;
  int c,flag=0;
  
  while(flag==0)
  {
  	
  	
  		printf("\n                Choices                            \n");
        printf("\n 1.Insert     \n");
        printf("\n 2.Delete    \n");
        printf("\n 3. display   \n");
        printf("\n 4.get_List_Destination\n");
        printf("\n 5.SortByTravelDate\n");
        printf("\n 6.Sort_Trains\n");
        printf("\n 7.RangeSearch     \n");
        printf("\n 8.Exit       \n");
        printf("\n--------------------------------------\n");		
  		printf("enter your choice:");
  		scanf("%d",&c);
  		
  		
  	  if (c==1)
	  {
	  	int passenger_id;
	    printf("Enter the passenger id:");
	    scanf("%d",& passenger_id);
	
	  	root=insert(root,passenger_id);
	  	flag=1;
	  	printf("inorder traversal of the constructed AVL tree is \n");
  		inOrder(root);
	  }
	  
	  
	  else if (c==2)
	  {
	  	int passenger_id;
	    printf("Enter the passenger id:");
	    scanf("%d",& passenger_id);
	    
	  	root = delete_fun(root,passenger_id);
	  	printf("\ninorder traversal after deletion of given passenger_id \n");
    	inOrder(root);
    	flag=1;
	  }
	  
	  
	  else if (c==3)
	  {
	  	if(root!=NULL)
	  	{
	  		inOrder(root);
		}
		else
		{
			printf("The tree is Empty\n");
		}
	  }
	  
	  
	  else if(c==4)
	  {
	  	get_List_Destination(root);
	  }
	  
	  
	  else if (c==5)
	  {
	  	int p_id;
		printf("Enter the passenger_id to search the data: ");
		scanf("%d",&p_id);
	  	SortByTravelDate(root,p_id);
	  }
	  
	  
	  else if(c==6)
	  {
	  	Sort_Trains(train_root);
	  }
	  
	  
	  else if(c==7)
	  {
	  	int f,l;
	  	printf("Enter the first and last values in the range:");
	  	printf("\nfirst value:");
	  	scanf("%d",&f);
	  	printf("\nlast value:");
	  	scanf("%d",&l);
	  	RangeSearch(root,f,l);
	  }
	  
	  
	  printf("to continue adding passengers enter 0 :");
	  scanf("%d",&flag);
 
  }
  
 
  return 0;
}
