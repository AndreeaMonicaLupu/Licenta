import { Injectable } from "@angular/core";
import { Subject } from 'rxjs';

@Injectable({
    providedIn: 'root'
  })
  

export class Interconectare {
    nr_catSubject = new Subject();
    nr_cat$ = this.nr_catSubject.asObservable();

    metoda(nr_categorie: number){
        this.nr_catSubject.next(nr_categorie);
    }
}
  
  