import { Injectable } from '@angular/core';
import { BehaviorSubject  } from 'rxjs';

@Injectable({
    providedIn: 'root'
})

export class GalerieService{

    private id_categorie = new BehaviorSubject(0);
    sharedCategorieId = this.id_categorie.asObservable();

    constructor(){}

    nextId(id_categorie: number) {
        this.id_categorie.next(id_categorie);

    }

}