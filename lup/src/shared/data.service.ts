import { Injectable } from '@angular/core';
import { BehaviorSubject  } from 'rxjs';

@Injectable({
    providedIn: 'root'
})

export class DataService{

    private id_loggedin = new BehaviorSubject(0);
    sharedId = this.id_loggedin.asObservable();

    constructor(){}

    nextId(id_loggedin: number) {
        this.id_loggedin.next(id_loggedin);
        //alert(message);
    }

}