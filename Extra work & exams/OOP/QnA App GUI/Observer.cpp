//
// Created by bia on 05/07/2022.
//

#include "Observer.h"

void Subject::notify() {
    for(auto o : this->list)
        o->update();
}
