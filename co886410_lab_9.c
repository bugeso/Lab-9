#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	struct RecordType records;
	struct HashType* next;
};

// Compute the hash function
int hash(int x)
{
	return x % 15;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;
	for (i=0;i<hashSz;++i)
	{
		// if index is occupied with any records, print all
		if(pHashArray[i].next != NULL)
			printf("Index %d -> ", i);

			struct HashType* current = pHashArray[i].next;

			while(current != NULL){
				printf("%d %c %d ->", current->records.id, current->records.name, current->records.order);
				current = current->next;
			}
			printf(" NULL \n");
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation

	struct HashType pHashArray[15]; 
	for(int i = 0; i < 15; i++){
		pHashArray[i].next = NULL;
	}

	for(int i = 0; i < recordSz; i++){
		struct RecordType *pRecord = pRecords + i;
		int index = hash(pRecord->order);
		struct HashType *new = (struct HashType*)malloc(sizeof(struct HashType));
		
		new->records = *pRecord;
		new->next = NULL;

		if(pHashArray[index].next == NULL){
			pHashArray[index].next = new;
		}
		else{
			struct HashType *current = pHashArray[index].next;
			while(current->next != NULL){
				current = current->next;
			}
			current->next = new;
		}
	}
	displayRecordsInHash(pHashArray, 15);
}