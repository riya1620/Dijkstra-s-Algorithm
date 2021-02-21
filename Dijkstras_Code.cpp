
#include<iostream>
using namespace std;

//Function to print the table
void printTable(int dijkstraMatrix[][3],int n,char vertices[])
{
	cout<<"Dijkstra's Table: "<<endl;
	cout<<"___________________________________________________________"<<endl;
	cout<<"Vertex"<<"\t\t"<<"Visited"<<"\t\t"<<"Distance"<<"\t"<<"Parent"<<endl;
	cout<<"___________________________________________________________"<<endl;
	int minimumDistance=0;
	for(int i=0;i<n;i++)
	{
		cout<<vertices[i]<<"\t\t"<<dijkstraMatrix[i][0]<<"\t\t";
		if(dijkstraMatrix[i][1]==2147483647)
		{
			cout<<"inf";
		}
		else
		{
			cout<<dijkstraMatrix[i][1];
		}
		cout<<"\t\t"<<vertices[dijkstraMatrix[i][2]]<<"\t"<<endl;
	}
}

int sourceNode(char vertices[],int n)
{
	//Inputing the source node 
	char vertexNode;
	cout<<"Enter the source node: ";
	cin>>vertexNode;
	
	//Finding the index value of the source node
	for(int i=0;i<n;i++)
	{
		if (vertices[i]==vertexNode)
		{
			return i;
		}
	}
	return -1;
}
int main()
{
	int n;  //n stores the number of vertices 
	cout<<"Enter the number of vertices in the graph: ";
	cin>>n;
	char vertices[n];   //to store the vertices names 
	int adjacency[n][n];  //adjacency matrix 
	int vertex=0;    //storing the source node 
	
	//Inputing the vertices
	cout<<"Enter the vertrices names: "<<endl;
	for(int i=0;i<n;i++)
	{
		cin>>vertices[i];
	}
	
	//Inputing adajency matrix
	cout<<"Enter the adjacency matrix(distance between vertices)(Enter -1 for no link-inf): "<<endl;
	for(int i=0;i<n;i++)
	{
        int input;
		for(int j=0;j<n;j++)
		{
			cout<<"Distance between "<<vertices[i]<<" and "<<vertices[j]<<" : ";			 
			cin>>input;
			
			//As in dijkstras , the graph can have only positive weight, we check if the input is correct
			if (input<-1)
			{
				cout<<"Distance can not be negative! Enter again"<<endl;
				j=j-1;
			}
			else if(i==j&&input!=0)
			{
				cout<<"Distance between the node and the node itself will always be 0! Changing the value to 0."<<endl;
				input=0;
			}			
			else
			{
				adjacency[i][j]=input;
				//Changing the value of -1 to infinity					
				if (adjacency[i][j]==-1)
				{
					adjacency[i][j]=2147483647;
				}
			}			
		}
		cout<<endl;
	}
	
	
	
	
	do 
	{
		vertex=sourceNode(vertices,n);
		if(vertex==-1)
		{
		cout<<"Source node not available!"<<endl;
	}
	}while(vertex==-1);
	
	
	/*
	    If you want to skip the user input and hardcode the value, you can use this code snippet(comment the earlier part). Here I have used the graph shown in the example.
		int adjacency[6][6]={{0,1,5,2147483647,2147483647,2147483647},
					{2147483647,0,2,2,1,2147483647},
					{2147483647,2147483647,0,2147483647,2,2147483647},
					{2147483647,2147483647,2147483647,0,3,1},
					{2147483647,2147483647,2147483647,2147483647,0,2},
					{2147483647,2147483647,2147483647,2147483647,2147483647,0}};
		char vertices[6]={'A','B','C','D','E','F'};
		int n=6;
		int vertex=0;
	*/
	
	
	/*
	  The dijkstra's array will have row=number of nodes and 3 columns. The columns will be similiar to the table we have used in the example
	  column 0 -> visited value
	  column 1 -> distance value
	  column 2 -> parent
	*/
	
	int dijkstraMatrix[n][3];
	
	//Initializing the dijkstras matrix: visited=0, distance=inifinty, parent=0
	for(int i=0;i<n;i++)
	{
		dijkstraMatrix[i][0]=0;
		dijkstraMatrix[i][1]=2147483647;
		dijkstraMatrix[i][2]=0;
	}
	cout<<endl;
	
	//Making the distacnce for the source node as 0	
	dijkstraMatrix[vertex][1]=0;
	
	//finding the minimum distance among the the non visited vertices
	for(int i=0;i<n;i++)
	{
		int min=2147483647;
		for(int j=0;j<n;j++)
		{
			if (dijkstraMatrix[j][0]==0)
			{
				if(dijkstraMatrix[j][1]<=min)
				{
					min=dijkstraMatrix[j][1];
					vertex=j;
				}
			}
		}
		
		//Changing the visited of the current vertex as 1
		dijkstraMatrix[vertex][0]=1;
		
		
		//checking for the adjacent unvisited nodes of the current vertex
		for (int k=0;k<n;k++)
		{
			if(dijkstraMatrix[k][0]==0) //checking for visited
			{
				
				
				/* checking if there is an edge between the node and the vertex 
		        and if the (distance value of vertex + edge (vertex, node))< distance value of node*/
				if(adjacency[vertex][k]!=2147483647&&adjacency[vertex][k]+dijkstraMatrix[vertex][1]<=dijkstraMatrix[k][1])
				{
					dijkstraMatrix[k][1]=adjacency[vertex][k]+dijkstraMatrix[vertex][1]; //allocating the distance 
					dijkstraMatrix[k][2]=vertex;  //allocating the parent  
				}
			}
		}
		
	    //The next two lines are for printing the table after every node, if you don't want that you can just comment the next 2 lines
		cout<<"For vertex: "<<vertices[vertex]<<endl;
		printTable(dijkstraMatrix,n,vertices);		
		cout<<endl;	
	}
	
	//Printing the final table
	cout<<"***SOLUTION**"<<endl;
	printTable(dijkstraMatrix,n,vertices);
	
}

