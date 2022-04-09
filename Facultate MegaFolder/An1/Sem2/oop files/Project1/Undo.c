//
// Created by moldo on 3/10/2022.
//

#include "Undo.h"
#include <stdlib.h>
#include "Medicine.h"
#include <string.h>
#include <stdio.h>

Undo* create_undo(){
    Undo* undo = malloc(sizeof(Undo));
    if(undo == NULL)
        return NULL;
    undo->length = 0;
    return undo;
}

void destroy_undo(Undo* undo){
    if(undo == NULL)
        return;
    for(int i = 0; i < undo->length; i++)
        destroy_medicine(undo->drugs[i]);
    free(undo);
}

void add_drug(Undo* undo, Medicine* medicine){

    undo->drugs[undo->length] = copy_medicine(medicine);
    undo->drugs[undo->length]->id = 1;
    undo->length++;
}

void delete_drug(Undo* undo, Medicine* medicine){

    undo->drugs[undo->length] = copy_medicine(medicine);
    undo->drugs[undo->length]->id = 2;
    undo->length++;

}

void update_drug_by_quantity(Undo* undo, Medicine* medicine){

    undo->drugs[undo->length] = copy_medicine(medicine);
    undo->drugs[undo->length]->id = 3;
    undo->length++;
}

void update_drug_by_price(Undo* undo, Medicine* medicine){

    undo->drugs[undo->length] = copy_medicine(medicine);
    undo->drugs[undo->length]->id = 4;
    undo->length++;
}