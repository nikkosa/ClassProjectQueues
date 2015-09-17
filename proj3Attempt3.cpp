//***********************************  PROGRAM IDENTIFICATION  ************************************
//*																								  *
//*   PROGRAM FILE NAME:  Assignment3CSC360.cpp	   ASSIGNMENT #:  3	 Grade: ________	          *
//*																								  *
//*	  PROGRAM AUTHOR:	  _________________________________________								  *
//*										Anikko Barton											  *
//*																								  *
//*   COURSE #:  CSC 36000 11							   DUE DATE:  March 11, 2015		      *
//*																								  *
//*************************************************************************************************
//*                                 COMMENTS FINISHED ON NOTEPAD                             
//*  PROCESS: This program employs queues to simulate customer
//*			  processing at a retail store. The program employs
//*			classes and linked lists. An unknown number of records
//*			including the information for each customer is read
//*			in and then processed. The program processes customers
//*			as they enter one of the 3 checkout lines(which are
//*			all represented by an indiviual queue). The following
//*			rules apply when processing the customer. 1. Each
//*			Customer arrives at the appointed arrival time. 2.
//*			If a queue is empty, place the customer in the queue
//*			and begin processing. 3. If all queues have customers,
//*			place customer in queue with shortest total processing
//*			time(if there is a tie between the total processing 
//*			times, place customer in queue with lowest numeric
//*			value ex. line1 before line2 if equal). 4. Processing
//*			isn't done until the customer is at the head of the
//*			queue. 5. Once customer processing reaches 0 they leave
//*			the store(removed from queue) and added to the departure 
//*         list.The program then finally
//*			prints out the original arrival list of the customers
//*			and a list of when they left the store(departure).
//*                                                              
//*USER DEFINED MODULES: NodeType,NodeType2,NodeType3 - structures that
//                       hold the information of the customers
//                       Original - structure that holds the names of the
//                       customers originally read from the file
//                       Departure - structure that holds the names of the
//                       customers departing from a queue(leaving the store)
//                       LinkedQueueClass - class used to create and process 
//                       data in queues
//                       LinkedQueueClass() - contructor to initialize private variables
//						 Enqueue - class function that adds customer to 1 of 3 queues
//                       Dequeue - class function that removes a customer from 
//                       1 of the 3 queues
//                       processData - class function that updates the processing time
//                       for each customer at the head of their respective queue
//                       processRest - class function that uses the processData function
//                       to process any remaining customers in queues 
//                       departure - class function that adds customer leaving a queue into
//                       the Departure linked queue list
//                       PrintQ - class function that prints the original and departure
//                       list to the output file
//                       Header - prints output preamble for project
//                       Footer - prints end program message at end of file
//****************************************************************
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;
struct NodeType //structure to hold the first line list information of the customers
{
	int  ArrivalTime;
    char Name[26];
	int ProcessingTime;
    NodeType *next;
};
//******************************************
struct NodeType2 //structure to hold the second line list information of the customers
{
	int  ArrivalTime;
    char Name[26];
	int ProcessingTime;
    NodeType2 *next;
};
//******************************************
struct NodeType3 //structure to hold the third line list information of the customers
{
	int  ArrivalTime;
    char Name[26];
	int ProcessingTime;
    NodeType3 *next;
};
//******************************************
//****************************************
struct Original //structure to hold the names of the customers orinially read in from file
{
	char Name[26];
	Original *next;
};
//*****************************************
struct Departure //structure to hold the names of customers leaving queues(leaving store)
{
	char Name[26];
	Departure *next;
};
//*****************************************
//********************** LINKED QUEUE CLASS ******************************************
class LinkedQueueClass 
{
   public:
		LinkedQueueClass();
		void Enqueue(NodeType,NodeType2,NodeType3);
		void Dequeue(char);  
		void processData();
		void processRest();
		void departure(char[]);
		void PrintQ(ofstream&);        
   private:						
		int totalProcessing1;			//total processing time for queue 1
		int totalProcessing2;			//total processing time for queue 2
		int totalProcessing3;			//total processing time for queue 3
       	NodeType *front;				//pointer to front of the line in queue 1
        NodeType *rear;					//pointer to rear of the line in queue 1
		NodeType2 *front2;				//pointer to front of the line in queue 2
		NodeType2 *rear2;				//pointer to rear of the line in queue 2
		NodeType3 *front3;				//pointer to front of the line in queue 3
		NodeType3 *rear3;				//pointer to rear of the line in queue 3
		Original *start;				//pointer to the beginning of linked list 		
		Departure *beg;
 		};
//********************* END LINKED QUEUE CLASS **************************************
//*********************** PROCESS REST FUNCTION *******************
void LinkedQueueClass::processRest()
{
		//Receives - nothing
		//Task - process any remaining data in the 3 queues
		//returns nothing
	while(front != NULL || front2 != NULL || front3 != NULL)
	{
		processData(); //will continue until all 3 queues are empty
	}
	return;
};
//*********************** END PROCESS REST FUNCTION*****************
//************************* PROCESS DATA FUNCTION ******************
void LinkedQueueClass::processData()
{
	//Receives - nothing
	//Task - decrement processing times by 1 and if a customer reaches
	//        0 for processing time, remove from queue and add to 
	//        the departure list
	//returns nothing
	NodeType *ptr1;
	NodeType2 *ptr2;
	NodeType3 *ptr3;
	char theName[26],theName2[26],theName3[26];
	char code;
	ptr1 = front;	//points to beginning of the first queue
	ptr2 = front2;	//points to the beginning of the second queue
	ptr3 = front3;	//points to the beginning of the third queue
	if(ptr1 != NULL && ptr2 == NULL && ptr3 == NULL)
	{
		ptr1->ProcessingTime-= 1;	//decrement the processing times by 1
		totalProcessing1 -= 1;
		if(ptr1->ProcessingTime == 0)
		{
			strcpy(theName,ptr1->Name);	//copy the customers name leaving the queue
			departure(theName);			// add to the departure list
			code = 'F';					//F symbolizes first line
			Dequeue(code);				//delete from the first queue
		}
	}
	else if(ptr1!=NULL && ptr2 !=NULL && ptr3 == NULL)
	{
		ptr1->ProcessingTime -= 1;	//decrement the processing times of lines 1 & 2 by 1
		ptr2->ProcessingTime -= 1;
		totalProcessing1 -= 1;
		totalProcessing2 -= 1;
		if(ptr1->ProcessingTime == 0 && ptr2->ProcessingTime != 0)
		{
			strcpy(theName,ptr1->Name); //copy the name in the first line
			departure(theName);			// add to the departure list
			code = 'F';
			Dequeue(code);				//delete customer from queue
		}
		else if(ptr2->ProcessingTime == 0 && ptr1->ProcessingTime != 0)
		{
			strcpy(theName2,ptr2->Name); //copy the name in the second line
			departure(theName2);		// add to the departure list
			code = 'S';					//S symbolizes second queue
			Dequeue(code);				//delete customer from second first queue
		}
		else if(ptr2->ProcessingTime == 0 && ptr1->ProcessingTime == 0)
		{
			strcpy(theName,ptr1->Name);		//copy the name in the first line
			departure(theName);				// add to the departure list
			code = 'F';
			Dequeue(code);					//delete customer from first queue
			strcpy(theName2,ptr2->Name);	//copy the name in the second line
			departure(theName2);			// add to the departure list
			code = 'S';
			Dequeue(code);					//delete customer from second queue
		}
	}
	else if(ptr1!=NULL && ptr2 !=NULL && ptr3 != NULL)
	{
		ptr1->ProcessingTime -= 1;	//decrement 1 from processing times from lines 1,2,3
		ptr2->ProcessingTime -= 1;	//decrementing 1 from the front of the lists only
		ptr3->ProcessingTime -= 1;
		totalProcessing1 -= 1;
		totalProcessing2 -= 1;
		totalProcessing3 -= 1;

		if(ptr1->ProcessingTime == 0 && ptr2->ProcessingTime != 0 
			&& ptr3->ProcessingTime != 0)
		{
			strcpy(theName,ptr1->Name); //copy the name in the first line
			departure(theName);			// add to the departure list
			code = 'F';
			Dequeue(code);				//delete customer from first queue
		}
		else if(ptr2->ProcessingTime == 0 && ptr1->ProcessingTime != 0
			&& ptr3->ProcessingTime != 0)
		{
			strcpy(theName2,ptr2->Name); //copy the name in the second line
			departure(theName2);		// add to the departure list
			code = 'S';
			Dequeue(code);				//delete customer from second queue
		}
		else if(ptr3->ProcessingTime == 0 && ptr2->ProcessingTime != 0
			&& ptr1->ProcessingTime != 0)
		{
			strcpy(theName3,ptr3->Name);
			departure(theName3);		// add to the departure list
			code = 'L';					//L symbolizes the third and last queue
			Dequeue(code);				//delete customer from third queue
			
		}
		else if(ptr3->ProcessingTime == 0 && ptr2->ProcessingTime == 0
			&& ptr1->ProcessingTime != 0)
		{
			strcpy(theName2,ptr2->Name); //copy the name in the second line
			departure(theName2);		// add to the departure list
			code = 'S';
			Dequeue(code);				//delete customer from second queue
			strcpy(theName3,ptr3->Name); //copy the name in the third line
			departure(theName3);		// add to the departure list
			code = 'L';
			Dequeue(code);				//delete customer from third queue
		}
		else if(ptr3->ProcessingTime == 0 && ptr2->ProcessingTime != 0
			&& ptr1->ProcessingTime == 0)
		{
			strcpy(theName,ptr1->Name); //copy the name in the first line
			departure(theName);			// add to the departure list
			code = 'F';
			Dequeue(code);				//delete customer from first queue
			strcpy(theName3,ptr3->Name); //copy the name in the third line
			departure(theName3);		// add to the departure list
			code = 'L';
			Dequeue(code);				//delete customer from third queue
		}
	}
	else if(ptr1 != NULL && ptr2 == NULL && ptr3 != NULL)
	{
		ptr1->ProcessingTime -= 1;	//decrement 1 from processing times from lines 1,3
		ptr3->ProcessingTime -= 1;
		totalProcessing1 -= 1;
		totalProcessing3 -= 1;
		if(ptr1->ProcessingTime == 0 && ptr3->ProcessingTime != 0)
		{
			strcpy(theName,ptr1->Name); //copy the name in the first line
			departure(theName);			// add to the departure list
			code = 'F';
			Dequeue(code);				//delete customer from first queue
		}
		else if(ptr3->ProcessingTime == 0 && ptr1->ProcessingTime != 0)
		{
			strcpy(theName3,ptr3->Name); //copy the name in the second line
			departure(theName3);		// add to the departure list
			code = 'L';
			Dequeue(code);				//delete customer from third queue
		}
		else if(ptr3->ProcessingTime == 0 && ptr1->ProcessingTime == 0)
		{
			strcpy(theName,ptr1->Name); //copy the name in the first line
			departure(theName);			// add to the departure list
			code = 'F';
			Dequeue(code);				//delete customer from first queue
			strcpy(theName3,ptr3->Name); //copy the name in the second line
			departure(theName3);		// add to the departure list
			code = 'L';
			Dequeue(code);				//delete customer from third queue
		}
	}
	else if(ptr1 == NULL && ptr2 != NULL && ptr3 != NULL)
	{
		ptr2->ProcessingTime -= 1;	//decrement 1 from processing times from lines 2,3
		ptr3->ProcessingTime -= 1;
		totalProcessing2 -= 1;
		totalProcessing3 -= 1;
		if(ptr2->ProcessingTime == 0 && ptr3->ProcessingTime != 0)
		{
			strcpy(theName2,ptr2->Name); //copy the name in the first line
			departure(theName2);		// add to the departure list
			code = 'S';
			Dequeue(code);				//delete customer from second queue
		}
		else if(ptr3->ProcessingTime == 0 && ptr2->ProcessingTime != 0)
		{
			strcpy(theName3,ptr3->Name); //copy the name in the second line
			departure(theName3);		// add to the departure list
			code = 'L';
			Dequeue(code);				//delete customer from third queue
		}
		else if(ptr2->ProcessingTime == 0 && ptr3->ProcessingTime == 0)
		{
			strcpy(theName2,ptr2->Name); //copy the name in the first line
			departure(theName2);		// add to the departure list
			code = 'S';
			Dequeue(code);				//delete customer from second queue
			strcpy(theName3,ptr3->Name); //copy the name in the second line
			departure(theName3);		// add to the departure list
			code = 'L';
			Dequeue(code);				//delete customer from third queue
		}
	}
	else if(ptr1 == NULL && ptr2 == NULL && ptr3 != NULL)
	{
		ptr3->ProcessingTime-= 1;	//decrement 1 from processing times from line 3
		totalProcessing3 -= 1;
		if(ptr3->ProcessingTime == 0)
		{
			strcpy(theName3,ptr3->Name);
			departure(theName3); // add to the departure list
			code = 'L';
			Dequeue(code);		//delete customer from third queue
		}
	}
	else if(ptr1 == NULL && ptr3 == NULL && ptr2 !=NULL)
	{
		ptr2->ProcessingTime-= 1;	//decrement 1 from processing times from lines 2
		totalProcessing2 -= 1;
		if(ptr2->ProcessingTime == 0)
		{
			strcpy(theName2,ptr2->Name);
			departure(theName2); // add to the departure list
			code = 'S';
			Dequeue(code);		//delete customer from second queue 
		}
	}
	return;
};
//************************** END PROCESS DATA FUNCTION *******************************
//*********************** DEQUEUE FUNCTION **************************************
void LinkedQueueClass::Dequeue(char code)
{
		//Receives - a character F,S, or L 
		//Task - depending on the character read in, delete customer from specific queue
		//returns nothing
	NodeType *temp = new NodeType;			//create temporary nodes of the queues
	NodeType2 *temp2 = new NodeType2;
	NodeType3 *temp3 = new NodeType3;
	switch (code)
	{
		case 'F':
			if(front == NULL)
			{
				cout<<"\nQueue is Emtpty\n"; //do nothing
			}
			else
			{
				temp = front;				
				front = front->next;
				delete temp;
			}
			break;
		case 'S':
			if(front2 == NULL)
			{
				cout<<"\nQueue is Emtpty\n"; //do nothing
			}
			else
			{
				temp2 = front2;
				front2 = front2->next;
				delete temp2;
			}
			break;
		case 'L':
			if(front3 == NULL)
			{
				cout<<"\nQueue is Emtpty\n"; //do nothing
			}
			else
			{
				temp3 = front3;
				front3 = front3->next;
				delete temp3;
			}
			break;
	}
	return;
}
//******************* END DEQUEUE FUNCTION ****************************************
//************************ENQUEUE FUNCTION ****************************************
void LinkedQueueClass::Enqueue(NodeType line,NodeType2 line2,NodeType3 line3)
{
		//Receives - 3 structures holding the same data
		//Task - add the data from one of the structures to one of three
		//       queues depending on the total processing time
		//returns nothing
    NodeType *temp = new NodeType;
	NodeType2 *temp2 = new NodeType2;
	NodeType3 *temp3 = new NodeType3;
		//add customer to linked list for original arrival
	Original *temp4, *prev,*curr;
	temp4 = new Original;
	strcpy(temp4->Name,line.Name);
	prev = NULL;
	curr = start;
		//add names to orinal list
	while(curr!=NULL)
	{
		prev = curr;
		curr = curr->next;
	}
	if(curr == NULL)
	{
		if(prev == NULL)
		{
			temp4->next = start;
			start = temp4;
		}
		else
		{
			prev->next = temp4;
			temp4->next = curr;
		}
	}

    temp->ArrivalTime = line.ArrivalTime;			//copy data from the structures
	strcpy_s(temp->Name,line.Name);					//into the new nodes
	temp->ProcessingTime = line.ProcessingTime;
    temp->next = NULL;

	temp2->ArrivalTime = line2.ArrivalTime;
	strcpy_s(temp2->Name,line2.Name);
	temp2->ProcessingTime = line2.ProcessingTime;
    temp2->next = NULL;

	temp3->ArrivalTime = line3.ArrivalTime;
	strcpy_s(temp3->Name,line3.Name);
	temp3->ProcessingTime = line3.ProcessingTime;
    temp3->next = NULL;
	totalProcessing1 += line.ProcessingTime;		//initially add to the totalprocessing
	totalProcessing2 += line2.ProcessingTime;		//for each of the lines
	totalProcessing3 += line3.ProcessingTime;

	if(front == NULL)
	{
		front = rear = temp;
		totalProcessing2 -= line2.ProcessingTime;
		totalProcessing3 -= line3.ProcessingTime;
		return;
	}
	else if(front != NULL && front2 == NULL)
	{
		front2 = rear2 = temp2;
		totalProcessing1 -= line.ProcessingTime;
		totalProcessing3 -= line3.ProcessingTime;
		return;
	}
	else if(front != NULL && front2 != NULL && front3 == NULL)
	{
		front3 = rear3 = temp3;
		totalProcessing1 -= line.ProcessingTime;
		totalProcessing2 -= line2.ProcessingTime;
		return;
	}
	else if(front != NULL && front2 != NULL && front3 != NULL)
	{
		if(totalProcessing1 < totalProcessing2 && totalProcessing1 < totalProcessing3)
		{
		       rear->next = temp;
			   rear = temp;
			   totalProcessing2 -= line2.ProcessingTime;
			   totalProcessing3 -= line3.ProcessingTime;
		}

		else if(totalProcessing2 < totalProcessing1 && totalProcessing2 < totalProcessing3)
		{
			rear2->next = temp2;
			rear2 = temp2;
			totalProcessing1 -= line.ProcessingTime;
			totalProcessing3 -= line3.ProcessingTime;

		}
		else if(totalProcessing3 < totalProcessing1 && totalProcessing3 < totalProcessing2)
		{
			rear3->next = temp3;
			rear3 = temp3;
			totalProcessing1 -= line.ProcessingTime;
			totalProcessing2 -= line2.ProcessingTime;

		}

			//if any of the total times are equal go through these loops
		else if(totalProcessing1 == totalProcessing3 && totalProcessing1 < totalProcessing2)
		{
			rear->next = temp;
			rear = temp;
			totalProcessing2 -= line2.ProcessingTime;
			totalProcessing3 -= line3.ProcessingTime;

		}
		else if(totalProcessing1 == totalProcessing2 && totalProcessing1 < totalProcessing3)
		{
			rear->next = temp;
			rear = temp;
			totalProcessing2 -= line2.ProcessingTime;
			totalProcessing3 -= line3.ProcessingTime;
		}
		else if(totalProcessing2 == totalProcessing1 && totalProcessing2 < totalProcessing3)
		{
			rear2->next = temp2;
			rear2 = temp2;
			totalProcessing1 -= line.ProcessingTime;
			totalProcessing3 -= line3.ProcessingTime;
		}
		else if(totalProcessing2 == totalProcessing3 && totalProcessing2 < totalProcessing1)
		{
			rear2->next = temp2;
			rear2 = temp2;
			totalProcessing1 -= line.ProcessingTime;
			totalProcessing3 -= line3.ProcessingTime;
		}
		else if(totalProcessing3 == totalProcessing1 && totalProcessing3 < totalProcessing2)
		{
			rear3->next = temp3;
			rear3 = temp3;
			totalProcessing1 -= line.ProcessingTime;
			totalProcessing2 -= line2.ProcessingTime;
		}
		else if(totalProcessing3 == totalProcessing2 && totalProcessing3 < totalProcessing1)
		{
			rear3->next = temp3;
			rear3 = temp3;
			totalProcessing1 -= line.ProcessingTime;
			totalProcessing2 -= line2.ProcessingTime;
		}
		else if(totalProcessing1 == totalProcessing2 && totalProcessing1 == totalProcessing3)
		{
			rear->next = temp;
			rear = temp;
			totalProcessing2 -= line2.ProcessingTime;
			totalProcessing3 -= line3.ProcessingTime;
		}
	}

	return;
}
//***********************************************
void LinkedQueueClass::PrintQ(ofstream & outfile)
{
 
	Original *t = new Original;
	Departure *d = new Departure;
	t = start;
	d = beg;
	outfile << "The order of customer arrival is:" 
			<< setw(60) << "The order of customer departure is:" << endl;
	while(t!=NULL)
	{
		outfile << t->Name << setw(37) << "|" << setw(28) << d->Name << endl;
		t = t->next;
		d = d->next;
	}
	outfile << endl;
	return;
}

//******************* CONSTRUCTOR FOR LIN****************************
LinkedQueueClass::LinkedQueueClass()
{
			//Receives nothing
			//Task - initialize variables from the class
			//returns nothing
	   start = NULL;
	   beg = NULL;
 	   front = NULL;
   	   rear = NULL;
	   front2 = NULL;
	   rear2 = NULL;
	   front3 = NULL;
	   rear3 = NULL;
	   totalProcessing1 = 0;
	   totalProcessing2 = 0;
	   totalProcessing3 = 0;
}
//**********************************************
void LinkedQueueClass::departure(char name[26])
{
	//
	//
	//
	Departure *temp4,*prev,*curr;
	temp4 = new Departure;
	strcpy(temp4->Name,name);
	//temp4->next = origin.next;
	prev = NULL;
	curr = beg;
	if(temp4 == NULL)
	{
		cout << " no memory available " << endl;
	}
	else
	{
		strcpy(temp4->Name,name);
	//	temp4->next = NULL;
		prev = NULL;
		curr = beg;
		while(curr !=NULL)
		{
			prev = curr;
			curr = curr->next;
		}
		if(curr == NULL)
		{
			if(prev == NULL)
			{
				temp4->next = beg;
				beg = temp4;
			}
			else
			{
				prev->next = temp4;
				temp4->next = curr;
		}

	}

	return;
	}
};
//*****************************************
	//prototype for the header
void Header(ofstream &);
	//prototype for the footer
void Footer(ofstream &);
int main()
{  
	NodeType line1;				//instantiate objects of the queue structures
	NodeType2 line2;
	NodeType3 line3;
	Original origin;
	Departure depart;
    LinkedQueueClass  Queue;	//instantiate object of the queue class
    int code;					//declare variable

		//open specific file
	ifstream infile ("C:\\Users\\anikk_000\\Documents\\queue_in.txt");
		//create new file for output
	ofstream outfile ("C:\\Users\\anikk_000\\Documents\\results3CSC360.txt");                    
    infile >> code;										//read in the initial arrival time
    while ( code != -99 )
    {
		line1.ArrivalTime = code;						//copy contents of file into line1 structure
		infile >> ws;
		infile.get(line1.Name,26);
		infile >> ws;
		infile >> line1.ProcessingTime;

		line2.ArrivalTime = line1.ArrivalTime;			//copy contents of file into line2 structure
		strcpy_s(line2.Name,line1.Name);
		line2.ProcessingTime  = line1.ProcessingTime;

		line3.ArrivalTime = line1.ArrivalTime;			//copy contents of file into line3 structure
		strcpy_s(line3.Name,line1.Name);
		line3.ProcessingTime  = line1.ProcessingTime;

		Queue.Enqueue(line1,line2,line3);	/*add a customer to one of the three queues
											  this function call adds a customer to one of the three queues
											  depending on which queue currently has the shortest 
											  total processing time.
											*/
		Queue.processData();				/*process customer and data immediately after its added to a queue.
											  this function call decrements each customers processing time by 1
											  in each of the 3 lines(queues) if they are currently
											  at the head of the queue. And once customers reach 0
											  processing time, they are removed from their respective queue
											  and the next customers in the queue begins their processing.
											  after that customer is removed, they are then added
											  to the departure list.
											*/
		infile >> code;					//read in the next arrival time

    }
	Queue.processRest();				//process any customers still left in queues
	Header(outfile);					//print out the header before data
	Queue.PrintQ(outfile);				//print the original and departure list to the file
	Footer(outfile);					//print the footer at the end of the file
	infile.close();						
	outfile.close();					//close the input and output files
    return 0; 
}                
//**********************************  FUNCTION HEADER  ******************************
void Header(ofstream &Outfile)
{

				//Receives- the output file
				//Task - Prints the output preamble
				//Returns - Nothing
	Outfile << setw(30) << left << "Anikko Barton";
	Outfile << setw(17) << "CSC 36000";
	Outfile << setw(15) << "Section 11" << endl;
	Outfile << setw(30) << "Spring 2015";
	Outfile << setw(20) << "Assignment #3" << endl;
	Outfile << setw(35) << "--------------------------------------";
	Outfile << setw(35) << "--------------------------------------\n\n";
	return;
}

//************************************  END OF FUNCTION HEADER  ***************************

//**************************************  FUNCTION FOOTER  ****************************
void Footer(ofstream &Outfile)
{
				//Receives - the output file
				//Task - Prints the output salutation
				//Returns - Nothing
	Outfile << endl;
	Outfile << setw(35) << "------------------------------" << endl;
	Outfile << setw(35) << "|   END OF PROGRAM OUTPUT     |" << endl;
	Outfile << setw(35) << "------------------------------" << endl;
	return;
}
//*************************************  END OF FUNTION HEADER  ***********************

