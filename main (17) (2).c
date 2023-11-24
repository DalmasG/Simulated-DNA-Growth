
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int
main ()
{
  struct sequence call = initialize ();
  printf ("DNA sequence:");
  printsequence (call);
  lifeloop (&call);
  return 0;
}

struct bases
{
  char basetype;		//A,C,G,T. 

};

struct bases
createbases (char type)
{
  struct bases newbase;
  newbase.basetype = type;
  return newbase;
};


struct doublelist
{
  struct bases info;
  struct doublelist *next;
  struct doublelist *prev;
};

struct sequence
{
  struct doublelist *head;
  int currentage;
  int maxlifespan;
  float growthprob;
  float deletionprob;
  float mutateprob;
};
void
printsequence (struct sequence sequence)
{
  struct doublelist *pointer = sequence.head;
  while (pointer != NULL)
    {
      printf ("%c", pointer->info.basetype);
      pointer = pointer->next;
    }
  printf ("end");
}

//add base 
void
addbase (struct sequence *pointer2, char basetype)
{

  struct doublelist *newbase =
    (struct doublelist *) malloc (sizeof (struct doublelist));
  newbase->info = createbases (basetype);
  newbase->next = NULL;
  if (!pointer2->head)

    {
      pointer2->head = newbase;
    }
  else
    {
      struct doublelist *present = pointer2->head;
      while (present->next)
	{
	  present = present->next;
	}
      present->next = newbase;
      newbase->prev = present;
    }
}

//insert base 
void
insertbase (struct sequence *pointer2, char basetype, int position)
{
  struct doublelist *newbase =
    (struct doublelist *) malloc (sizeof (struct doublelist));
  newbase->info = createbases (basetype);
  newbase->next = NULL;
  newbase->prev = NULL;

  if (position == 0)
    {
      newbase->next = pointer2->head;
      if (pointer2->head)
	{
	  pointer2->head->prev = newbase;
	}
      pointer2->head = newbase;
    }
  else
    {
      struct doublelist *pointer3 = pointer2->head;
      for (int i = 0; i < position - 1; i++)
	{
	  pointer3 = pointer3->next;
	}
      newbase->next = pointer3->next;
      newbase->prev = pointer3;
      pointer3->next = newbase;

      if (newbase->next)
	{
	  newbase->next->prev = newbase;
	}
    }
}

  //delete 
void
delete (struct sequence *pointer4, int position)
{
  struct doublelist *listpos = pointer4->head;

  if (position == 0)
    {
      pointer4->head = listpos->next;
      if (pointer4->head)
	{
	  pointer4->head->prev = NULL;
	}
      free (listpos);
      return;
    }
  for (int i = 0; i < position - 1; i++)
    {
      if (!listpos->next)
	{
	  return;
	}
      listpos = listpos->next;
    }
  struct doublelist *inputdelete = listpos->next;
  if (inputdelete->next)
    {
      inputdelete->next->prev = listpos;
    }
  listpos->next = inputdelete->next;
  free (inputdelete);
}
}

  //search
int
search (struct sequence *pointer5, char *set)
{
  int searchlength = strlen (set);	//string.h library func
  struct doublelist *move = pointer5->head;
  int position = 0;

  while (move)
    {
      struct doublelist *check = move;
      int i;
      for (i = 0; i < searchlength; i++)
	{
	  if (!check || check->info.basetype != set[i])
	    {
	      break;
	    }
	  check = check->next;
	}

      if (i == searchlength)
	{
	  return position;
	}
      move = move->next;
      position++;
    }
  return -1;
}
}

struct sequence
initialize ()
{
  struct sequence initseq;
  initseq.head = NULL;
  initseq.maxlifespan = 8 + rand () % 43;	//https://exceljet.net/functions/rand-function#:~:text=The%20RAND%20function%20returns%20a,worksheet%20is%20opened%20or%20changed.
  //rand() and adding 8 is understood from youtube
  initseq.currentage = 0;
  initseq.deletionprob = 0.25;
  initseq.growthprob = 0.25;
  initseq.mutateprob = 0;

  for (int i = 0; i < 20; i++)
    {
      switch (rand () % 4)
	{
	case 0:
	  addbase (&initseq, 'A');
	  break;
	case 1:
	  addbase (&initseq, 'C');
	  break;
	case 2:
	  addbase (&initseq, 'G');
	  break;
	case 3:
	  addbase (&initseq, 'T');
	  break;
	}
    }
}

return initseq;
}

void
lifeloop (struct sequence *pointer6)
{
  while (pointer6->currentage < pointer6->maxlifespan)
    {
      pointer6->currentage++;
      growth (pointer6);
      deletionprob (pointer6);

      if (!pointer6->head)
	{
	  printf ("Sequence dead at %d\n", pointer6->currentage);
	  break;
	}
    }
}

void
growth (struct sequence *pointer7)
{
  if ((float) rand () / RAND_MAX < pointer7->growthprob)
    {
      int place = rand () % (20 + 1);
      char random;
      switch (rand () % 4)
	{
	case 0:
	  random = 'A';
	  break;
	case 1:
	  random = 'C';
	  break;
	case 2:
	  random = 'G';
	  break;
	case 3:
	  random = 'T';
	  break;
	}
    }
  insertbase (pointer7, random, place);

}

void
deleteprob (struct sequence *pointer8)
{
  if ((float) rand () / RAND_MAX < pointer8->deletionprob)
    {
      int place = rand () % 20;
      delete (pointer8, place);

      if (!pointer8->head)
	{
	  printf ("sequence dead");
	  return;
	}
    }
}
}


}

}
