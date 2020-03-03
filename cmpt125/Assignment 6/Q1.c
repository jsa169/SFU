int LLMax(LL_t * intlist){
	//Set first note to be max
	int max = intlist->head->data;
	//Keep track of current
	node_t * current = intlist->head->next;
	//Go through LL
	while (current != NULL){
		//If current > max, replace
		if(current->data > max){
			max = current->data;
		}
		current = current->next;
	}
	return max;
}

void LLDelete(LL_t * intlist, int target){
	int n = 0;
	//Keep track of both current and previous nodes
	node_t * current = intlist->head;
	node_t * previous;

	while(current != NULL){
		//Deleting a node if its the first node of LL, Change Head to next node
		if(intlist->head == current){
			if(current->data == target){
				intlist->head = current->next;
				current = current->next;
				previous = current;
				n++;
				continue;
			}
		}
		//Deleting nodes inside the LL without touching head
		if(current->data == target){
			previous->next = current->next;
			free(current);
			n++;
		}
		
		previous = current;
		current = current->next;
	}
	//Signals target not found
	if(n == 0){
		printf("Value not Found\n");
	}

}